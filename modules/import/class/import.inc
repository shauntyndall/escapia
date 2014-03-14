<?php

module_load_include('inc', 'availability_calendar', 'availability_calendar');

class EscapiaImport implements EscapiaImportInterface {
  const AMENITY_VOCABULARY = 'rental_amenities';

  protected $property_queue, $rate_queue, $photo_queue;

  public function __construct() {}

  /**
   * Loops through each active connection and obtains Escapia properties.
   */
  public function importAll() {
    $this->clearQueues();

    $connections = entity_load('escapia_connection', FALSE, array('active' => TRUE));

    foreach ($connections as $connection) {
      watchdog('escapia_property', 'ESCAPIA IMPORT: Requesting properties for @label connection...', array('@label' => $connection->label), WATCHDOG_NOTICE);

      $api = new EscapiaAPI($connection);
      $properties = $api->getAllUnits();

      foreach ($properties->Units->Unit as $property) {
        watchdog('escapia_property', 'Queuing property @code for import/update.', array('@code' => $property->UnitCode));
        $queue = array('UnitCode' => $property->UnitCode, 'connection_id' => $connection->id);
        $this->property_queue->createItem($queue);
        $this->photo_queue->createItem($queue);
        $this->rate_queue->createItem($queue);
      }
    }

    watchdog('escapia_property', 'ESCAPIA IMPORT: Process complete.', array(), WATCHDOG_NOTICE);
  }

  /**
   * Process a set of data from an Escapia API response.
   * XPath is used for quick selection, and PHP warnings are suppressed.
   * @param $soap_response
   *  - The result of executing unitInfo() in EscapiaAPI.
   * @see unitInfo() in the EscapiaAPI class.
   */
  public function processProperty($soap_response) {
    $entity = $this->prepareEntity($soap_response);
    $xml = $this->getSimpleXMLElement($soap_response);

    // Set entity properties
    $wrapper = entity_metadata_wrapper('escapia_property', $entity->id);
    $wrapper->label = $this->cleanText((string) @end($xml->xpath('//@UnitShortName')));
    $wrapper->active = 1;
    $wrapper->connection_id = $soap_response->connection->id;
    $wrapper->unit_code = (string) @end($xml->xpath('//@UnitCode'));
    $wrapper->unit_name= $this->cleanText($wrapper->label->value());
    $wrapper->internal_code = (string) @end($xml->xpath('//@InternalUnitCode'));
    $wrapper->address_line_1 = $this->cleanText((string) @end($xml->xpath('//ns:Address'))->AddressLine[0]);
    $wrapper->address_line_2 = $this->cleanText((string) @end($xml->xpath('//ns:Address'))->AddressLine[1]);
    $wrapper->address_city = (string) @end($xml->xpath('//ns:Address'))->CityName;
    $wrapper->address_state = (string) @end($xml->xpath('//ns:Address'))->StateProv['StateCode'];
    $wrapper->address_zipcode = (string) @end($xml->xpath('//ns:Address'))->PostalCode;
    
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

      // save the amenities to the wrapper
      $this->processAmenityData($soap_response, $wrapper);

      // if no Availability Calendar is attached to this entity, create one.
      if (empty($entity->field_esp_availability)) {
        $calendar_id = availability_calendar_create_calendar();
        $wrapper->field_esp_availability->set(array('cid' => $calendar_id, 'enabled' => TRUE, 'name' => 'Availability'));
      }
    }

    $wrapper->save();
  }

  /**
   * Process a set of rate data from an Escapia API response.
   * XPath is used for quick selection, and PHP warnings are suppressed.
   * @param $soap_response
   *  - The result of executing unitInfo() in EscapiaAPI.
   * @see unitInfo() in the EscapiaAPI class.
   */
  public function processRates($soap_response) {
    $entity = $this->prepareEntity($soap_response);
    $xml = $this->getSimpleXMLElement($soap_response);

    $wrapper = entity_metadata_wrapper('escapia_property', $entity);

    // Set Field data
    if (module_exists('escapia_property_fields')) {
      $wrapper->field_esp_minimum_rate = (string) @end($xml->xpath('//@MinRate'));
      $wrapper->field_esp_maximum_rate = (string) @end($xml->xpath('//@MaxRate'));
      $wrapper->field_esp_minimum_fees = (string) @end($xml->xpath('//@MinFees'));
      $wrapper->field_esp_maximum_fees = (string) @end($xml->xpath('//@MaxFees'));
      $wrapper->field_esp_minimum_tax = (string) @end($xml->xpath('//@MinTax'));
      $wrapper->field_esp_maximum_tax = (string) @end($xml->xpath('//@MaxTax'));
      $wrapper->field_esp_minimum_rent = (string) @end($xml->xpath('//@MinRent'));
      $wrapper->field_esp_maximum_rent = (string) @end($xml->xpath('//@MaxRent'));

      // process daily rates
      $this->processDailyRateCodesToCalendar($soap_response, $wrapper);
    }

    $wrapper->save();
  }

  /**
   * Process photo data from a EscapiaAPI SOAP response.
   * @param $soap_response
   *  - The SOAP response object stored after the last request for an import or property update.
   */
  public function processPhotos($soap_response) {
    $entity = $this->prepareEntity($soap_response);
    $xml = $this->getSimpleXMLElement($soap_response);

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
   * Clears all specified tasks in the DrupalQueue.
   */
  protected function clearQueues() {
    $this->property_queue = DrupalQueue::get('EscapiaProperty');
    $this->property_queue->deleteQueue();

    $this->rate_queue = DrupalQueue::get('EscapiaPropertyRate');
    $this->rate_queue->deleteQueue();

    $this->photo_queue = DrupalQueue::get('EscapiaPropertyPhoto');
    $this->photo_queue->deleteQueue();
  }

  /**
   * If an entity is found by Unit Code it is loaded and returned, otherwise we prime it by saving the entity so EntityMetadataWrapper can be utilized.
   * @param $soap_response
   * @return bool|mixed
   */
  protected function prepareEntity($soap_response) {
    if (!($entity = $this->doesPropertyExistAsEntity($soap_response->UnitDescriptiveContents->UnitDescriptiveContent->UnitCode))) {
      $entity = entity_get_controller('escapia_property')->create();
      $entity->label = $soap_response->UnitDescriptiveContents->UnitDescriptiveContent->UnitInfo->UnitName->UnitShortName;
      entity_save('escapia_property', $entity);
    } else {
      $id = @end(array_keys($entity));
      $entity = escapia_property_load($id);
    }

    return $entity;
  }

  /**
   * Processes amenity data from the Services node on a property. Creates the proper parent/child tree structure in the Rental Amenities vocabulary before saving.
   * @param $soap_response
   * @param EntityMetadataWrapper $wrapper
   */
  protected function processAmenityData($soap_response, EntityMetadataWrapper &$wrapper) {
    $xml = $this->getSimpleXMLElement($soap_response);
    $amenities = $xml->xpath('//ns:Services/*');
    $list = array();

    $wrapper->field_esp_amenities = array();

    foreach ($amenities as $amenity) {
      $category = (string) $amenity->attributes()->CodeDetail;
      $value = (string) $amenity->DescriptiveText;

      // parent term
      if (!taxonomy_get_term_by_name($category, self::AMENITY_VOCABULARY)) {
        $this->createAmenityTerm($category);
      }

      $parent = taxonomy_get_term_by_name($category, self::AMENITY_VOCABULARY);

      // child term
      if (!taxonomy_get_term_by_name($value, self::AMENITY_VOCABULARY)) {
        $this->createAmenityTerm($value, end($parent)->tid);
      }

      $parent = taxonomy_get_term_by_name($category, self::AMENITY_VOCABULARY);
      $child = taxonomy_get_term_by_name($value, self::AMENITY_VOCABULARY);

      $list[end($parent)->tid] = end($parent)->tid;
      $list[end($child)->tid] = end($child)->tid;
    }

    $wrapper->field_esp_amenities->set($list);
  }

  protected function processDailyRateCodesToCalendar($soap_response, EntityMetadataWrapper &$wrapper) {
    $entity = $this->prepareEntity($soap_response);
    $codes = str_split($soap_response->availability);

    foreach ($codes as $key => $code) {
      // map the array key as the day of the year
      $datetime = DateTime::createFromFormat('z Y' , $key . ' ' . date('Y'));

      // if code is A, or U, map to the date
      switch ($code) {
        case 'A':
          availability_calendar_update_availability($wrapper->field_esp_availability->cid->value(), 2, $datetime, $datetime);
          break;
        case 'U':
          availability_calendar_update_availability($wrapper->field_esp_availability->cid->value(), 3, $datetime, $datetime);
          break;
        default;
          availability_calendar_update_availability($wrapper->field_esp_availability->cid->value(), 1, $datetime, $datetime);
          break;
      }
    }
  }

  /**
   * Creates a term to hold an Amenity value on a property.
   * @param $name
   * @param $parent
   */
  private function createAmenityTerm($name, $parent = 0) {
    $term = new stdClass();
    $term->name = $name;
    $term->vid = taxonomy_vocabulary_machine_name_load(self::AMENITY_VOCABULARY)->vid;
    $term->parent = $parent;
    taxonomy_term_save($term);
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
   * Returns a SimpleXMLElement ready for xpath use from the raw SOAP response from Escapia.
   * @param $soap_response
   * @return SimpleXMLElement
   */
  private function getSimpleXMLElement($soap_response) {
    $xml = simplexml_load_string($soap_response->xmlResponse);
    $xml->registerXPathNamespace("ns", EscapiaAPI::SOAP_NAMESPACE);
    return $xml;
  }
}