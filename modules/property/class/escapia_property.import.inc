<?php

class EscapiaPropertyImportAPI {
  const AMENITY_VOCABULARY = 'rental_amenities';

  protected $property_queue, $rate_queue, $photo_queue;

  public function __construct() {}

  /**
   * Loops through each active connection and obtains Escapia properties.
   */
  public function fullDataImport() {
    $this->clearQueues();

    $connections = entity_load('escapia_connection', FALSE);

    foreach ($connections as $connection) {
      watchdog('escapia_property', 'ESCAPIA IMPORT: Requesting properties for @label connection...', array('@label' => $connection->label), WATCHDOG_NOTICE);

      $api = new EscapiaAPI($connection);
      $properties = $api->getAllUnits();

      foreach ($properties as $property) {
        watchdog('escapia_property', 'Queuing property @code for import/update.', array('@property' => $property->UnitDescriptiveContents->UnitDescriptiveContent->InternalUnitCode));
        $this->property_queue->createItem($property);
        $this->photo_queue->createItem($property);
        // @todo: rates?? how?? $this->rate_queue->createItem($property);
      }
    }

    watchdog('escapia_property', 'ESCAPIA IMPORT: Process complete.', array(), WATCHDOG_NOTICE);
  }

  /**
   * Process a set of data from an Escapia API response.
   * XPath is used for quick selection. @ is suppressing warnings by using end() without a reference.
   * @param $data
   */
  public function processProperty($data) {
    $entity = $this->prepareEntity($data);

    $xml = simplexml_load_string($data->xmlResponse);
    $xml->registerXPathNamespace("ns", EscapiaAPI::SOAP_NAMESPACE);

    // Set entity properties
    $wrapper = entity_metadata_wrapper('escapia_property', $entity);
    $wrapper->label = $this->cleanText((string) @end($xml->xpath('//@UnitShortName')));
    $wrapper->active = 1;
    $wrapper->connection_id = $data->connection->id;
    $wrapper->unit_code = (string) @end($xml->xpath('//@UnitCode'));
    $wrapper->unit_name= $this->cleanText($wrapper->label->value());
    $wrapper->internal_code = (string) @end($xml->xpath('//@InternalUnitCode'));
    $wrapper->address_line_1 = $this->cleanText((string) @end($xml->xpath('//ns:Address'))->AddressLine[0]);
    $wrapper->address_line_2 = $this->cleanText((string) @end($xml->xpath('//ns:Address'))->AddressLine[1]);
    $wrapper->address_city = (string) @end($xml->xpath('//ns:Address'))->CityName;
    $wrapper->address_state = (string) @end($xml->xpath('//ns:Address'))->StateProv['StateCode'];
    $wrapper->address_zipcode = (string) @end($xml->xpath('//ns:Address'))->PostalCode;
    $wrapper->data = $data;
    
    // Set Field data
    if (module_exists('escapia_property_fields')) {
      $wrapper->field_esp_description->value = $this->cleanText((string) @end($xml->xpath('//ns:TextItem[@Title="Long Description"]'))->Description);
      $wrapper->field_esp_bedrooms = (string) @end($xml->xpath('//ns:RoomInfo[@CodeDetail="Bedrooms"]/@Quantity'));
      $wrapper->field_esp_bathrooms = (string) @end($xml->xpath('//ns:RoomInfo[@CodeDetail="Bathrooms"]/@Quantity'));
      $wrapper->field_esp_headline = (string) @end($xml->xpath('//@UnitHeadline'));
      $wrapper->field_esp_max_occupancy = (string) @end($xml->xpath('//@MaxOccupancy'));
      $wrapper->field_esp_minlos = (string) @end($xml->xpath('//@MinLOS'));
      $wrapper->field_esp_address->thoroughfare = $this->cleanText($wrapper->address_line_1->value());
      $wrapper->field_esp_address->premise = $this->cleanText($wrapper->address_line_2->value());
      $wrapper->field_esp_address->locality = $wrapper->address_city->value();
      $wrapper->field_esp_address->administrative_area =  $wrapper->address_state->value();
      $wrapper->field_esp_address->postal_code =  $wrapper->address_zipcode->value();
      $wrapper->field_esp_address->country =  (string) @end($xml->xpath('//ns:Address'))->CountryName['Code'];
    }

    $this->processAmenityData($data, $wrapper);
    $wrapper->save();
  }

  protected function processAmenityData($data, EntityMetadataWrapper &$wrapper) {
    $xml = simplexml_load_string($data->xmlResponse);
    $xml->registerXPathNamespace("ns", EscapiaAPI::SOAP_NAMESPACE);

    $amenities = $xml->xpath('//ns:UnitAmenity');
    $tree = self::getRentalAmenityParentList();
    $list = array();

    $wrapper->field_esp_amenities = array();

    foreach ($amenities as $amenity) {
      $code = (string) $amenity->attributes()->Code;

      if (!taxonomy_get_term_by_name($this->convertAmenityValue($code), self::AMENITY_VOCABULARY)) {
        $this->createAmenityTerm($this->convertAmenityValue($code));
      }

      $term = taxonomy_get_term_by_name($this->convertAmenityValue($code), self::AMENITY_VOCABULARY);
      $list[] = end($term)->tid;
    }

    $wrapper->field_esp_amenities->set($list);
  }

  /**
   * Creates a term to hold an Amenity value on a property.
   * @param $name
   */
  private function createAmenityTerm($name) {
    $term = new stdClass();
    $term->name = $name;
    $term->vid = taxonomy_vocabulary_machine_name_load(self::AMENITY_VOCABULARY)->vid;
    $term->parent = 0;
    taxonomy_term_save($term);
  }

  // @todo: import rate data for a property
  public function rateImport($data) {
    $entity = $this->prepareEntity($data);

    $xml = simplexml_load_string($data->xmlResponse);
    $xml->registerXPathNamespace("ns", EscapiaAPI::SOAP_NAMESPACE);

    // entity metadata wrapper load
    // set common properties
    // loop and set field data
    // save wrapper
  }

  /**
   * Process photo data from a EscapiaAPI SOAP response.
   * @param $data
   *  The SOAP response object stored after the last request for an import or property update.
   */
  public function processPhotos($data) {
    $entity = $this->prepareEntity($data);

    $xml = simplexml_load_string($data->xmlResponse);
    $xml->registerXPathNamespace("ns", EscapiaAPI::SOAP_NAMESPACE);

    $photos = (array) $xml->xpath('//*[@DimensionCategory="Original"]');

    if (count($photos)) {
      $wrapper = entity_metadata_wrapper('escapia_property', $entity);

      // Existing photos must be deleted through the FileAPI so image derivatives can be regenerated
      // This circumvents systems like Varnish, nginx and CDNs by making the filename unique with a timestamp.
      $old_photos = $wrapper->field_esp_photos->value();

      if (count($old_photos)) {
        foreach ($old_photos as $key => $value) {
          $file = file_load($value['fid']);

          if ($file) {
            file_delete($file, TRUE);
          }
        }

        $wrapper->field_esp_photos = array();
        $wrapper->save();
      }

      $files = array();

      foreach ($photos as $key => $photo) {
        if ($filecopy = copy($photo->URL, file_directory_temp() . '/' . $wrapper->unit_code->value() . '-' . REQUEST_TIME . '-' . $key . '.jpg')) {
          $content = file_get_contents(file_directory_temp() . '/' . $wrapper->unit_code->value() . '-' . REQUEST_TIME . '-' . $key . '.jpg');
          $file = file_save_data($content, 'public://escapia_property/' . $wrapper->unit_code->value() . '-' . REQUEST_TIME . '-' . $key . '.jpg', FILE_EXISTS_REPLACE);

          if ($file) {
            $files[] = (array) $file;
          }
        } else {
          watchdog('escapia_property', 'Photo could not be copied for property @id', array('@id' => $wrapper->id->value()), WATCHDOG_CRITICAL);
        }
      }

      if (count($files)) {
        $wrapper->field_esp_photos->set($files);
      }

      $wrapper->save();
    }
  }

  /**
   * If an entity is found by Unit Code it is loaded and returned, otherwise we prime it by saving the entity so EntityMetadataWrapper can be utilized.
   * @param $data
   * @return bool|mixed
   */
  protected function prepareEntity($data) {
    if (!($entity = $this->doesPropertyExistAsEntity($data->UnitDescriptiveContents->UnitDescriptiveContent->UnitCode))) {
      $entity = entity_get_controller('escapia_property')->create();
      $entity->label = $data->UnitDescriptiveContents->UnitDescriptiveContent->UnitInfo->UnitName->UnitShortName;
      entity_save('escapia_property', $entity);
    } else {
      $id = @end(array_keys($entity));
      $entity = escapia_property_load($id);
    }

    return $entity;
  }

  /**
   * Query for an existing Drupal entity.
   * @param null $unit_code
   * @param null $unit_name
   * @param null $internal_code
   * @return bool
   */
  public function doesPropertyExistAsEntity($unit_code = NULL, $unit_name = NULL, $internal_code = NULL) {
    $query = new EscapiaPropertyFieldQuery();

    if (isset($unit_code)) {
      $query->unitCode($unit_code);
    }

    if (isset($unit_name)) {
      $query->unitName($unit_name);
    }

    if (isset($internal_code)) {
      $query->internalCode($internal_code);
    }

    return $query->result();
  }

  /**
   * Process queued properties in the DrupalQueue.
   */
  public function processQueuedProperties() {
    $this->property_queue = DrupalQueue::get('EscapiaPropertyData');
    $total = $this->property_queue->numberOfItems();
    $count = 0;

    while ($queue_item = $this->property_queue->claimItem()) {
      watchdog('escapia_property', 'Processing property @property', array('@property' => $queue_item->data->UnitDescriptiveContents->UnitDescriptiveContent->UnitCode));
      try {
        $this->processProperty($queue_item->data);
        $this->property_queue->deleteItem($queue_item);
        $count++;
      } catch (Exception $error) {
        watchdog('escapia_property', 'Error processing property @property. @error', array('@property' => $queue_item->data->UnitDescriptiveContents->UnitDescriptiveContent->UnitCode, '@error' => $error->getMessage()));
        $this->property_queue->releaseItem($queue_item);
      }
    }

    watchdog('escapia_property', '@count properties processed out of @total. Those not processed had an unknown issue. Check the queue to see which properties were not processed.', array('@count' => $count, '@total' => $total));
  }

  /**
   * Process queued photos in the DrupalQueue.
   */
  public function processQueuedPhotos() {
    $this->photo_queue = DrupalQueue::get('EscapiaPropertyPhoto');
    $total = $this->photo_queue->numberOfItems();
    $count = 0;

    while ($queue_item = $this->photo_queue->claimItem()) {
      watchdog('escapia_property', 'Processing internal property id @property photos', array('@property' => $queue_item->data['unit_code']));
      try {
        $this->processQueuedPhotoset($queue_item->data['id'], $queue_item->data['photos']);
        $this->photo_queue->deleteItem($queue_item);
        $count++;
      } catch (Exception $error) {
        watchdog('escapia_property', 'Error processing property @property photo. @error', array('@property' => $queue_item->data['unit_code'], '@error' => $error->getMessage()));
        $this->photo_queue->releaseItem($queue_item);
      }
    }

    watchdog('escapia_property', '@count properties photos processed out of @total. Those not processed had an unknown issue. Check the queue to see which properties were not processed.', array('@count' => $count, '@total' => $total));
  }

  /**
   * Process queued rates in the DrupalQueue.
   */
  public function processQueuedRates() {
    $this->rate_queue = DrupalQueue::get('isilink_rates');
    $total = $this->rate_queue->numberOfItems();
    $count = 0;

    while ($queue_item = $this->property_rate_queue->claimItem()) {
      watchdog('escapia_property', 'Processing internal property id @property rates.', array('@property' => $queue_item->data['unit_code']));
      try {
        $this->processQueuedRateData($queue_item->data['id'], $queue_item->data['available_dates'], $queue_item->data['unavailable_dates'], $queue_item->data['turnday']);
        $this->rate_queue->deleteItem($queue_item);
        $count++;
      } catch (Exception $error) {
        watchdog('escapia_property', 'Error processing property @property rates. @error', array('@property' => $queue_item->data['unit_code'], '@error' => $error->getMessage()));
        $this->rate_queue->releaseItem($queue_item);
      }
    }

    watchdog('escapia_property', '@count property rates processed out of @total. Those not processed had an unknown issue. Check the queue to see which properties were not processed.', array('@count' => $count, '@total' => $total));
  }

  /**
   * Clears all specified tasks in the DrupalQueue.
   */
  protected function clearQueues() {
    $this->property_queue = DrupalQueue::get('EscapiaPropertyData');
    $this->property_queue->deleteQueue();

    $this->rate_queue = DrupalQueue::get('EscapiaPropertyRate');
    $this->rate_queue->deleteQueue();

    $this->photo_queue = DrupalQueue::get('EscapiaPropertyPhoto');
    $this->photo_queue->deleteQueue();
  }

  /**
   * Deletes all Escapia Property entities.
   */
  public static function propertyFlush() {
    $entities = entity_load('escapia_property', FALSE);

    foreach ($entities as $entity) {
      entity_delete('escapia_property', $entity->id);
    }
  }

  /**
   * Utility function - clean incoming text and strip it of HTML and bad characters.
   * @param $text
   * @return string
   */
  public function cleanText($text) {
    if (!drupal_strlen($text)) {
      return '';
    }

    libxml_use_internal_errors(TRUE);
    $document = new DOMDocument();
    $document->loadHTML($text);
    $document->preserveWhiteSpace = FALSE;
    $output = '';
    $xpath = new DOMXPath($document);

    // save the document HTML string
    $document->saveHTML();

    $nodes = $document->getElementsByTagName('body')->item(0);

    foreach ($nodes->childNodes as $node) {
      $node->normalize();

      if (trim($node->textContent, "\xc2 \n \t ") != '' && trim($node->textContent, "\xc2 \n \t ") != ' ') {
        $output .= trim($node->C14N());
      }
    }

    $output = str_replace('<p>&nbsp;</p>', '', $output);
    $output = str_replace('<span>&nbsp;</span>', '', $output);
    $output = str_replace('<span>_</span>', '', $output);
    $output = str_replace('<span> </span>', '', $output);
    $output = str_replace('</img>', '', $output);
    $output = str_replace('<p> </p>', '', $output);
    $output = str_replace(chr(130), "'", $output);    // baseline single quote
    $output = str_replace('”', '"', $output);    // baseline double quote
    $output = str_replace(chr(133), '...', $output);  // ellipsis
    $output = str_replace('‘', "'", $output);    // left single quote
    $output = str_replace('’', "'", $output);    // right single quote
    $output = str_replace('“', '"', $output);    // left double quote
    $output = str_replace('”', '"', $output);    // right double quote
    $output = strip_tags($output);
    $output = preg_replace('/(?!\n)[\p{Cc}]/', ' ', $output);
    $output = preg_replace('/[\x00-\x1F\x7f-\xFF]/', ' ', $output);
    $output = preg_replace('/[^\da-z -.,]/i', '', $output);
    $output = preg_replace(array('/\s{2,}/', '/[\t\n]/'), ' ', $output);
    $output = mb_convert_encoding($output, 'UTF-8', 'UTF-8');

    return $output;
  }

  /**
   * From the code listed on the Unit from UnitDescriptiveInfo, return the proper Amenity.
   * These values are from the Escapia API documentation.
   * @param $code
   * @return mixed
   */
  private function convertAmenityValue($code) {
    $amenities = array(
      1 => 'Air Conditioning',
      2 => 'Wheelchair Accessible',
      3 => 'Internet Access',
      4 => 'Hot Tub',
      5 => 'Kitchen',
      6 => 'Pool',
      7 => 'Washer & Dryer',
      8 => 'Beach',
      9 => 'Biking',
      10 => 'Boating',
      11 => 'Fishing',
      12 => 'Golf',
      13 => 'Skiing',
    );

    return $amenities[$code];
  }

  /**
   * Throwaway testing function.
   * @return mixed
   */
  public function testPropertyImport() {
    $connection = escapia_connection_load(2);
    $api = new EscapiaAPI($connection);
    $units = array();
    $this->clearQueues();
    $units[] = $api->unitInfo('1880-85274');
    $units[] = $api->unitInfo('1880-85285');
    foreach ($units as $unit) {
      $this->property_queue->createItem($unit);
      $this->photo_queue->createItem($unit);
    }
  }
}