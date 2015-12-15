<?php

module_load_include('inc', 'availability_calendar', 'availability_calendar');

class EscapiaAPIImport {
  const API_VERSION = '1.030';
  const MAX_RESPONSES = 10000;
  const SOAP_NAMESPACE = 'http://www.escapia.com/EVRN/2007/02';
  const ADULT_AGE_CODE = 10;
  const CHILD_AGE_CODE = 8;

  public function __construct() {
  }

  public function getUnitAvailableRequest($unit_code, $send_unit_info = FALSE, $start_date, $end_date, $adults = 2, $children = 0) {
    $escapia_service = wsclient_service_load('escapia_api');
    $args =  array('EVRN_UnitStayRQ' =>
      array(
        'Version' => variable_get('escapia_api_schema_version', '1.0'),
        'POS' => array(array('RequestorID' => array('ID' => variable_get('escapia_api_username', ''), 'MessagePassword' =>variable_get('escapia_api_userpass', '')))),
        'UnitStay' => array(
          'UnitRef' => array('UnitCode' => $unit_code),
          'BasicUnitInfo' => array('SendData' => $send_unit_info),
          'DepositPayments' => array('SendData' => true),
          'RentalAgreement' => array('SendData' => false),
          'CancelPenalties' => array('SendData' => true),
          'AdditionalCharges' => array('OptionalChargesIndicator' => 'IncludeDefault'),
          'StayDateRange' => array(
            'Start' => format_date($start_date, 'custom', 'm/d/Y'),
            'End' => format_date($end_date, 'custom', 'm/d/Y'),
          ),
          'GuestCounts' => array(
            'GuestCount' => array(
              array(
                'AgeQualifyingCode' => 10,
                'Count' => $adults,
              ),
              array(
                'AgeQualifyingCode' => 8,
                'Count' => $children,
              ),
            ),
          ),
        )
      )
    );

    $response = $escapia_service->invoke('UnitStay', $args);
    return $response;
  }

  /**
   * Processes amenity data from the Services node on a property. Creates the proper parent/child tree structure in the Rental Amenities vocabulary before saving.
   * @param $item
   * @param EntityMetadataWrapper $wrapper
   */
  public function updateAmenitiesTaxonomyHierarchy($item, EntityMetadataWrapper &$wrapper) {
    $wrapper->field_escapia_amenities = array();
    $vocab = taxonomy_vocabulary_machine_name_load('escapia_api_amenities');

    foreach ($item['amenities_hierarchy'] as $amenity => $category) {
      $category = ucwords(str_replace("_", " ", strtolower($category)));
      $amenity = ucwords(str_replace("_", " ", $amenity));
      $child = false;
      $parent = false;
      $tree = taxonomy_get_tree($vocab->vid, 0, NULL, FALSE);
      $new_tree = array();
      foreach($tree as $val) {
        $new_tree[$val->tid] = $val;
      }

      try{
        if ($parent_t = taxonomy_get_term_by_name($category, $vocab->machine_name)) {
          foreach($parent_t as $i_p => $p_t) {
            if(count($new_tree) && in_array(0, array_values($new_tree[$i_p]->parents))) {
              $parent = $p_t;
              break;
            }
          }
        }
        if(!$parent) {
          $parent = $this->_create_taxonomy_term($category, $vocab, 0);
        }

        if ($child_t = taxonomy_get_term_by_name($amenity, $vocab->machine_name)) {
          foreach($child_t as $i_ch => $ch_t) {
            if(count($new_tree) && !in_array(0, array_values($new_tree[$i_ch]->parents))) {
              $child = $new_tree[$ch_t->tid];
              break;
            }
          }
        }
        if(!$child) {
          $child = $this->_create_taxonomy_term($amenity, $vocab, $parent->tid);
        }
        else if($child && isset($child->parents) && !in_array($parent->tid, array_values($child->parents))) {
          $child->parents[] = $parent->tid;
          $child->parent = $child->parents;
          taxonomy_term_save($child);
        }

        $wrapper->field_escapia_amenities[] = $parent->tid;
        $wrapper->field_escapia_amenities[] = $child->tid;
      } catch(Exception $e) {
        watchdog('escapia_feeds', 'Error while processing Escapia Amenities: Line @line of EscapiaFeeds import.inc:  @error', array(
          '@line' => $e->getLine(),
          '@error' => $e->getMessage()
        ), WATCHDOG_CRITICAL);
      }
    }
  }

  private function _create_taxonomy_term($term_name, $vocab, $parent = 0) {
    $new_term = new stdClass(); // create new PARENT term
    $new_term->name = $term_name;
    $new_term->vid = $vocab->vid;
    $new_term->parent = array($parent);
    taxonomy_term_save($new_term);
    return $new_term;
  }

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
      $changes = array();

      $cal_exist = $wrapper->field_escapia_availability_cal->value();

      if (empty($cal_exist)) {
        $calendar_id = availability_calendar_create_calendar();
        $wrapper->field_escapia_availability_cal->set(array(  // assign calendar for the Rental node
          'cid' => $calendar_id,
          'enabled' => TRUE,
          'name' => 'Availability'
        ));
      }
      else {
        if(is_array($cal_exist) && isset($cal_exist['cid']))
          $calendar_id = $cal_exist['cid'];
      }

      if (preg_match('/^(A+)$/', $item['cal_days_statuses'])) {
        availability_calendar_update_availability($calendar_id, $this->_escapia_api_map_escapia_cal_status_to_drupal('A'), $start, $end);
      }
      else  if (preg_match('/^(U+)$/', $item['cal_days_statuses'])) {
        availability_calendar_update_availability($calendar_id, $this->_escapia_api_map_escapia_cal_status_to_drupal('U'), $start, $end);
      }
      else {
        $codes = str_split($item['cal_days_statuses']);
        foreach ($codes as $code) {
          availability_calendar_update_availability($calendar_id, $this->_escapia_api_map_escapia_cal_status_to_drupal($code), $start, $start);
          $start = $start->add(new DateInterval('P1D'));
        }
      }
    } catch (Exception $e) {
      watchdog('escapia_feeds', 'Error while processing Availability Dates to Calendar: Line @line of EscapiaFeeds import.inc:  @error', array(
        '@line' => $e->getLine(),
        '@error' => $e->getMessage()
      ), WATCHDOG_CRITICAL);
    }
  }

  /**
   * Helper function for mapping Availability Calendar values.
   * @param $esc_status_code
   * @return integer
   */
  private function _escapia_api_map_escapia_cal_status_to_drupal($esc_status_code) {
    switch (strtolower($esc_status_code)) {
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
   * Given a string of RAW data from the Escapia API response, retrieve StayRequirement Days values.
   * @param $raw
   * @param $item
   * @return array
   */
  public function processStayRequirementsDays($raw, $item) {
    $xml = simplexml_load_string($raw);
    $xml->registerXPathNamespace("ns", EscapiaAPIImport::SOAP_NAMESPACE);

    $days = array('Sun', 'Mon', 'Tue', 'Weds', 'Thur', 'Fri', 'Sat');
    $item['unit_raterange_checkin_day'] = NULL;
    $item['unit_raterange_checkout_day'] = NULL;

    $rates = $xml->xpath('//ns:RateRange');
    foreach ($rates as $ind => $rate) {
      $attributes_stay = @end($rate->StayRequirement->attributes());
      $item['unit_raterange_checkin_day'][$ind] = NULL;
      $item['unit_raterange_checkout_day'][$ind] = NULL;

      if (in_array('true', array_values($attributes_stay))) {
        foreach ($attributes_stay as $key => $attribute) {
          if (in_array($key, $days) && $attribute === 'true') {
            if ($attributes_stay['StayContext'] == 'Checkin') {
              $item['unit_raterange_checkin_day'][$ind][] = $key;
            }
            else {
              if ($attributes_stay['StayContext'] == 'Checkout') {
                $item['unit_raterange_checkout_day'][$ind][] = $key;
              }
            }
          }
        }
      }
      if(count($item['unit_raterange_checkin_day'][$ind]) == 1)
        $item['unit_raterange_checkin_day'][$ind] = $item['unit_raterange_checkin_day'][$ind][0];
      if(count($item['unit_raterange_checkout_day'][$ind]) == 1)
        $item['unit_raterange_checkout_day'][$ind] = $item['unit_raterange_checkout_day'][$ind][0];
    }

    $policies = $xml->xpath('//ns:Policy');
    foreach ($policies as $policy) {
      $attributes_stay = @end($policy->StayRequirements->StayRequirement->attributes());
      foreach ($attributes_stay as $key => $attribute) {
        if (in_array($key, $days) && $attribute === 'true') {
          if ($attributes_stay['StayContext'] == 'Checkin') {
            $item['unit_allowed_checkin_day'][] = $key;
          }
          else {
            if ($attributes_stay['StayContext'] == 'Checkout') {
              $item['unit_allowed_checkout_day'][] = $key;
            }
          }
        }
      }
    }

    return $item;
  }

  /**
   * Trigger import of additional Feeds Importers to obtain additional information for Escapia Unit fields.
   * @param $lookup_source_name
   * @param $unit_code
   * @param $start_date
   * @param $end_date
   */
  public function triggerFeedsImport($lookup_source_name, $unit_code, $start_date = NULL, $end_date = NULL) {
    $lookup_source_name = trim(preg_replace('!\s+!', ' ', $lookup_source_name));
    $feed_source = feeds_source($lookup_source_name);
    $feed_fetcher = $feed_source->importer->fetcher;
    $array_index = '';

    if (!is_a($feed_fetcher, 'FeedsWSClientFetcher')) {
      drupal_set_message('Invalid Feed Source name provided. Source has to be based on FeedsWSClientFetcher Fetcher. No descriptive information will be updated for Rental units.', 'warning');
      watchdog('escapia_feeds', 'Invalid Feed Source name provided. Source has to be based on FeedsWSClientFetcher Fetcher.', array(), WATCHDOG_NOTICE);
      return;
    }
    $source_config = $feed_fetcher->config;

    if ($unit_code) {
      try {
        $array_index = '';
        if (isset($source_config['service_operation'])) {
          if (strpos($source_config['service_operation'], 'UnitDescriptiveInfo') !== FALSE) {
            $array_index = 'EVRN_UnitDescriptiveInfoRQ';
            $source_config['operation_arguments'][$array_index]['UnitDescriptiveInfos'][0]['UnitCode'] = $unit_code;
          }
          else if (strpos($source_config['service_operation'], 'UnitCalendarAvail') !== FALSE) {
            $start_date = empty($start_date) ? date('m/d/Y', strtotime('today')) : date('m/d/Y', strtotime($start_date));
            $end_date = empty($end_date) ? date('m/d/Y', strtotime('today +18 months')) : date('m/d/Y', strtotime($end_date));
            $array_index = 'EVRN_UnitCalendarAvailRQ';

            $source_config['operation_arguments'][$array_index]['UnitRef']['UnitCode'] = $unit_code;
            $source_config['operation_arguments'][$array_index]['CalendarDateRange']['Start'] = $start_date;
            $source_config['operation_arguments'][$array_index]['CalendarDateRange']['End'] = $end_date;
          }
          $source_config['operation_arguments'][$array_index]['POS'][0]['RequestorID']['ID'] = variable_get('escapia_api_username', '');
          $source_config['operation_arguments'][$array_index]['POS'][0]['RequestorID']['MessagePassword'] = variable_get('escapia_api_userpass', '');
          $source_config['operation_arguments'][$array_index]['Version'] = variable_get('escapia_api_schema_version', '1.0');

          $feed_source->setConfigFor($feed_source->importer->fetcher, $source_config);
          $feed_source->save();
          $feed_source->startImport();

          $feed_source->state(FEEDS_FETCH);
          $feed_source->state(FEEDS_PROCESS);
          $feed_source->state(FEEDS_PROCESS_CLEAR);
        }
      } catch (Exception $e) {
        drupal_set_message('Exception during invocation of Escapia API request: ' . $e, 'error', TRUE);
      }
    }
    else {
      drupal_set_message('There was no valid UNIT CODE provided for Escapia API request.', 'error', TRUE);
    }
  }

  public function mapLocationCoordinatesToGeofield(EntityMetadataWrapper &$wrapper) {
    $coordinates = $wrapper->field_escapia_location_map->value();
    if (!empty($coordinates['lat']) && !empty($coordinates['lon'])) {
      $wrapper->field_escapia_location_map = array(
        'wkt' => 'POINT (' . $coordinates['lon'][0] . ' ' . $coordinates['lat'][0] . ')',
        'geo_type' => 'point',
        'lat' => $coordinates['lat'][0],
        'lon' => $coordinates['lon'][0],
      );
    }
  }

  public function updateReviewsReference(EntityMetadataWrapper &$wrapper) {
    if($field = field_info_instance('node', 'field_escapia_unit_reviews_ref', $wrapper->type->value())) {
      $field_values = $wrapper->field_escapia_unit_reviews_ref->value();

      $query = new EntityFieldQuery();
      $query->entityCondition('entity_type', 'node')
        ->entityCondition('bundle', 'escapia_unit_review')
        ->fieldCondition('field_escapia_unit_code', 'value', $wrapper->field_escapia_unit_code->value(), '=');
      $result = $query->execute();

      if (isset($result['node'])) {
        $reviews_nids = array_keys($result['node']);
        $wrapper->field_escapia_unit_reviews_ref->set($reviews_nids);
      }
      else
        $wrapper->field_escapia_unit_reviews_ref->set(array());
    }
  }
}