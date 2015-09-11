<?php

module_load_include('inc', 'availability_calendar', 'availability_calendar');

class EscapiaFeedsImport {
//  const AMENITY_VOCABULARY = 'rental_amenities';

//  protected $property_queue, $rate_queue, $photo_queue;

  public function __construct() {}

  /**
   * Loops through each active connection and obtains Escapia properties.
   */
/*  public function importAll() {
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
  }*/
/*  public function reconcile() {
    $this->delete_queue = DrupalQueue::get('EscapiaPropertyDelete');
    $this->delete_queue->deleteQueue();
    $query = new EscapiaPropertyFieldQuery();
    $listings = $query->result();

    foreach ($listings as $listing) {
      $wrapper = entity_metadata_wrapper('escapia_property', $listing->id);
      $connection = escapia_connection_load($wrapper->connection_id->value());
      $api = new EscapiaAPI($connection);

      if (!$api->getUnitInfo($wrapper->unit_code->value())) {
        watchdog('escapia_property', 'ESCAPIA IMPORT RECONCILER: Property @code (@internal_code) was not found in the remote system or is not published/active. Queuing it to be deleted.', array('@code' => $wrapper->unit_code->value(), '@internal_code' => $wrapper->internal_code->value()), WATCHDOG_NOTICE);
        $this->delete_queue->createItem(array('entity_type' => 'escapia_property', 'id' => $wrapper->id->value()));
      }
    }

    watchdog('escapia_property', 'ESCAPIA IMPORT RECONCILER: Process complete.', array(), WATCHDOG_NOTICE);
  }*/

  /**
   * Process a set of data from an Escapia API response.
   * XPath is used for quick selection, and PHP warnings are suppressed.
   * @param $soap_response
   *  - The result of executing unitInfo() in EscapiaAPI.
   * @see unitInfo() in the EscapiaAPI class.
   */
/*  public function processProperty($soap_response) {
    $entity = $this->prepareEntity($soap_response);
    $xml = EscapiaAPI::getSimpleXMLElement($soap_response);

    // Fetch values
    $unit_name = $this->cleanText((string) @end($xml->xpath('//@UnitShortName')));
    $unit_code = (string) @end($xml->xpath('//@UnitCode'));
    $internal_unit_code = (string) @end($xml->xpath('//@InternalUnitCode'));
    $description = $this->cleanText((string) @end($xml->xpath('//ns:TextItem[@Title="Long Description"]'))->Description);
    $bedrooms = (string) @end($xml->xpath('//ns:RoomInfo[@CodeDetail="Bedrooms"]/@Quantity'));
    $bathrooms = (string) @end($xml->xpath('//ns:RoomInfo[@CodeDetail="Bathrooms"]/@Quantity'));
    $headline = (string) @end($xml->xpath('//@UnitHeadline'));
    $max_occupancy = (string) @end($xml->xpath('//@MaxOccupancy'));
    $minlos = (string) @end($xml->xpath('//@MinLOS'));
    $street = $this->cleanText((string) @end($xml->xpath('//ns:Address'))->AddressLine[0]);
    $street_additional = $this->cleanText((string) @end($xml->xpath('//ns:Address'))->AddressLine[1]);
    $city = (string) @end($xml->xpath('//ns:Address'))->CityName;
    $state = (string) @end($xml->xpath('//ns:Address'))->StateProv['StateCode'];
    $zipcode = (string) @end($xml->xpath('//ns:Address'))->PostalCode;
    $country = (string) @end($xml->xpath('//ns:Address'))->CountryName['Code'];
    $bed_info = $xml->xpath('//ns:BedInfo');

    // Get the street address without the leading numbers:
    $pos = strpos ( $unit_name, ' ');
    $number = substr ($unit_name , 0, $pos);
    if(is_numeric($number) || preg_match('/([0-9]+)/', $number) == 1) {
      $street_name = substr ( $unit_name , $pos +1);
    }
    else $street_name = $unit_name;

    // Set entity properties
    $wrapper = entity_metadata_wrapper('escapia_property', $entity->id);
    $wrapper->label = $unit_name.' - For Rent';
    $wrapper->active = 1;
    $wrapper->uid = 1;
    $wrapper->connection_id = $soap_response->connection->id;
    $wrapper->unit_code = $unit_code;
    $wrapper->unit_name = $unit_name.' - For Rent';
    $wrapper->internal_code = $internal_unit_code;
    $wrapper->address_line_1 = trim($street);
    $wrapper->address_line_2 = trim($street_additional);
    $wrapper->address_city = trim($city);
    $wrapper->address_state = trim($state);
    $wrapper->address_zipcode = trim($zipcode);
    
    // Set Field data
    if (module_exists('escapia_property_fields')) {
      $wrapper->field_esp_description->value = drupal_strlen($description) ? $description : NULL;
      $wrapper->field_esp_bedrooms = drupal_strlen($bedrooms) ? $bedrooms : 0;
      $wrapper->field_esp_bathrooms = drupal_strlen($bathrooms) ? $bathrooms : 0;
      $wrapper->field_esp_headline = drupal_strlen($headline) ? $headline : NULL;
      $wrapper->field_esp_max_occupancy = drupal_strlen($max_occupancy) ? $max_occupancy : 0;
      $wrapper->field_esp_minlos = drupal_strlen($minlos) ? $minlos : 0;
      $wrapper->field_esp_address->thoroughfare = drupal_strlen($street) ? trim($street) : NULL;
      $wrapper->field_esp_address->premise = drupal_strlen($street_additional) ? trim($street_additional) : NULL;
      $wrapper->field_esp_address->locality = drupal_strlen($city) ? $city : NULL;
      $wrapper->field_esp_address->administrative_area =  drupal_strlen($state) ? $state : NULL;
      $wrapper->field_esp_address->postal_code =  drupal_strlen($zipcode) ? $zipcode : NULL;
      $wrapper->field_esp_address->country =  drupal_strlen($country) ? $country : NULL;
      $wrapper->field_esp_combined_solr = trim($unit_name . ' ' . $street . ' ' . $city . ' ' . $zipcode);
      $wrapper->field_esp_street_name_solr = trim($street_name);

      $wrapper->field_esp_bed_data = array();

      foreach ($bed_info as $bed) {
        $wrapper->field_esp_bed_data[] = $bed->attributes()->Quantity . ' ' . $bed->attributes()->CodeDetail . '(s)';
      }

      // save the amenities to the wrapper
      $this->processAmenityData($soap_response, $wrapper);

      // if no Availability Calendar is attached to this entity, create one.
      if (empty($entity->field_esp_availability)) {
        $calendar_id = availability_calendar_create_calendar();
        $wrapper->field_esp_availability->set(array('cid' => $calendar_id, 'enabled' => TRUE, 'name' => 'Availability'));
      }
    }

    $wrapper->save();
  }*/

  /**
   * Process a set of rate data from an Escapia API response.
   * XPath is used for quick selection, and PHP warnings are suppressed.
   * @param $soap_response
   *  - The result of executing unitInfo() in EscapiaAPI. It should contain a rate_bands array of simplified rate information.
   * @see unitInfo() in the EscapiaAPI class.
   * @see _ei_process_property_rate_item()
   */
/*  public function processRates($soap_response) {
    $entity = $this->prepareEntity($soap_response);
    $xml = EscapiaAPI::getSimpleXMLElement($soap_response);
    $wrapper = entity_metadata_wrapper('escapia_property', $entity);
    $wrapper->field_esp_available_days = array();
    $wrapper->field_check_in_dates = array();
    $wrapper->field_esp_minimum_rate = '';

    foreach ($soap_response->rate_bands as $rate) {
      $this->processDailyRateCodesToCalendar($rate, $wrapper);
    }

    // Set Field data
    if (module_exists('escapia_property_fields') && isset($soap_response->minimum_rate)) {
      $wrapper->field_esp_minimum_rate = drupal_strlen($soap_response->minimum_rate) ? $soap_response->minimum_rate : '';
    }

    $wrapper->save();
  }*/


  /**
   * Processes amenity data from the Services node on a property. Creates the proper parent/child tree structure in the Rental Amenities vocabulary before saving.
   * @param $soap_response
   * @param EntityMetadataWrapper $wrapper
   */
/*  protected function processAmenityData($soap_response, EntityMetadataWrapper &$wrapper) {
    $xml = EscapiaAPI::getSimpleXMLElement($soap_response);
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

      // Prevent infinite loops when the category is the same term as the child:
      if (strcasecmp($value, $category) == 0) {
        continue;
      }

        // child term
      if (!taxonomy_get_term_by_name($value, self::AMENITY_VOCABULARY)) {
        $this->createAmenityTerm($value, end($parent)->tid);
      }

      $parent = taxonomy_get_term_by_name($category, self::AMENITY_VOCABULARY);
      $child = taxonomy_get_term_by_name($value, self::AMENITY_VOCABULARY);

      // update the child parent, in case our parent is new
      $term = end($child);
      $term->parent = end($parent)->tid;
      taxonomy_term_save($term);

      $list[end($parent)->tid] = end($parent)->tid;
      $list[end($child)->tid] = end($child)->tid;
    }

    $wrapper->field_esp_amenities->set($list);
  }*/

  /**
   * Given a string of availability codes, interpret them and transpose them to the availability calendar.
   * @param $item
   * @param $status_field
   * @param EntityMetadataWrapper $wrapper
   */
  public function processAvailabilityDatesToCalendar($item, EntityMetadataWrapper &$wrapper, $status_field) {
    module_load_include('inc', 'availability_calendar');

    try {
      $start = DateTime::createFromFormat('Y-m-d', $item['cal_start_date']);
      $start->setTime(0, 0, 0);
      $end = DateTime::createFromFormat('Y-m-d', $item['cal_end_date']);
      $end->setTime(0, 0, 0);
//    $availability = array();

//    $start = strtotime($item['cal_start_date']);
//    $end = strtotime($item['cal_end_date']);

      if (empty($entity['field_escapia_availability_cal'])) {
        $calendar_id = availability_calendar_create_calendar();
        $wrapper->field_escapia_availability_cal->set(array(  // assign calendar for the Rental node
          'cid' => $calendar_id,
          'enabled' => TRUE,
          'name' => 'Availability'
        ));
      }
      else {
        $calendar_id = $wrapper->field_escapia_availability_cal->cid->value();
      }

      if (preg_match('/^(A+)$/', $item['cal_days_statuses'])) {
        $cid = availability_calendar_update_multiple_availability($calendar_id, array(
          'state' => $this->_escapia_feeds_map_escapia_cal_status_to_drupal('A'),
          'from' => $start,
          'to' => $end
        ));

        // now add our days - Solr indexes on a per day basis to facilitate searching by timestamp range
//      $time_start = $start->format('U');
//      $time_end = $end->format('U');
//
//      while ($time_start < $time_end) {
//        $availability[] = $time_start;
//        $time_start = strtotime('+1 day', $time_start);
//      }
//
//      $availability[] = $time_start;
      }
      else {
        if (preg_match('/^(U+)$/', $item['cal_days_statuses'])) {
          $cid = availability_calendar_update_multiple_availability($calendar_id, array(
            'state' => $this->_escapia_feeds_map_escapia_cal_status_to_drupal('U'),
            'from' => $start,
            'to' => $end
          ));
        }
        else {
          $codes = str_split($item['cal_days_statuses']);

          foreach ($codes as $code) {
            $cid = availability_calendar_update_multiple_availability($calendar_id, array(array(
              'state' => $this->_escapia_feeds_map_escapia_cal_status_to_drupal($code),
              'from' => $start,
              'to' => $start
            )
            ));
            $start = $start->add(new DateInterval('P1D'));
          }
        }
      }

//    $wrapper->field_check_in_dates[] = $start->format('U');
//
//    if (count($availability)) {
//      // set wrapper field
//      foreach ($availability as $id => $time) {
//        $wrapper->field_esp_available_days[] = $time;
//      }
//    }
    } catch(Exception $e) {
      watchdog('escapia_feeds', 'Error while processing Availability Dates to Calendar: Line @line of EscapiaFeeds import.inc:  @error', array('@line' => $e->getLine(), '@error' => $e->getMessage()), WATCHDOG_CRITICAL);
    }
  }


  private function _escapia_feeds_map_escapia_cal_status_to_drupal($esc_status_code) {
    switch(strtolower($esc_status_code)) {
      case 'u':
        $code = 3;
        break;
      case 'a':
      case 'i':
        $code = 2;
        break;
      case 'o':
        $code = 4;
        break;
      default:
        $code = 1;
        break;
    }
    return $code;
  }

  /**
   * Creates a term to hold an Amenity value on a property.
   * @param $name
   * @param $parent
   */
/*  private function createAmenityTerm($name, $parent = 0) {
    $term = new stdClass();
    $term->name = $name;
    $term->vid = taxonomy_vocabulary_machine_name_load(self::AMENITY_VOCABULARY)->vid;
    $term->parent = $parent;
    taxonomy_term_save($term);
  }*/

  /**
   * From the code listed on the Unit from UnitDescriptiveInfo, return the proper Amenity.
   * These values are from the Escapia API documentation.
   * @param $code
   * @return mixed
   */
/*  private function convertAmenityValue($code) {
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
  }*/
}