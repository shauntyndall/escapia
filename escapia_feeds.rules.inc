<?php


/**
 * Implements hook_rules_action_info().
 */
function escapia_feeds_rules_action_info(){
  $actions = array();

  $actions['escapia_feeds_escapia_feed_description_update_by_unit'] = array(
    'label' => t('Call Escapia Feed Importer by UnitCode (and/or Dates).'),
    'parameter' => array(
      'lookup_source_name' => array(
        'type' => 'text',
        'label' => t('Lookup Feed Source Name'),
        'description' => t('Enter Feed Source machine name.'),
      ),
      'unit_code' => array(
        'type' => 'text',
        'label' => t('Lookup Escapia Unit Code'),
        'description' => t('Enter Escapia unique unit code.'),
      ),
      'date_start' => array(
        'type' => 'date',
        'label' => t('Date Start'),
        'description' => t('Can be left empty. This can be used for the call that require Date Start value.'),
        'optional' => 'true',
      ),
      'date_end' => array(
        'type' => 'date',
        'label' => t('Date End'),
        'description' => t('Can be left empty. This can be used for the call that require Date End value.'),
        'optional' => 'true',
      ),
    ),
    'group' => t('Escapia Feeds'),
    'callbacks' => array(
      'execute' => 'escapia_feeds_escapia_feed_description_update_by_unit',
    ),
  );

  return $actions;
}

// Load Feed Source to obtain Escapia Unit DescriptiveInfo() and update config UnitCode
function escapia_feeds_escapia_feed_description_update_by_unit($lookup_source_name, $unit_code, $start_date = null, $end_date = null) {
  $lookup_source_name = trim(preg_replace('!\s+!', ' ', $lookup_source_name));
  if($unit_code) {
    $feed_source = feeds_source($lookup_source_name);
    $feed_fetcher = $feed_source->importer->fetcher;

    if (!is_a($feed_fetcher, 'FeedsWSClientFetcher')) {
      drupal_set_message('Invalid Feed Source name provided. Source has to be based on FeedsWSClientFetcher Fetcher. No descriptive information will be updated for Rental units.', 'warning');
      watchdog('escapia_feeds', 'Invalid Feed Source name provided. Source has to be based on FeedsWSClientFetcher Fetcher.', array(), WATCHDOG_NOTICE);
      return;
    }

    $source_config = $feed_fetcher->config;
    if(isset($source_config['service_operation'])) {
      if(strpos($source_config['service_operation'], 'UnitDescriptiveInfo') !== false) {
        $source_config['operation_arguments']['EVRN_UnitDescriptiveInfoRQ']['UnitDescriptiveInfos'][0]['UnitCode'] = $unit_code;
        $feed_source->setConfigFor($feed_source->importer->fetcher, $source_config);
        $feed_source->save();
        $feed_source->startImport();

        $feed_source->state(FEEDS_FETCH);
        $feed_source->state(FEEDS_PROCESS);
        $feed_source->state(FEEDS_PROCESS_CLEAR);
//      drupal_set_message('Escapia Units information have been updated.', 'status', true);
      }
      else if(strpos($source_config['service_operation'], 'UnitCalendarAvail') !== false) {
        $start_date = empty($start_date) ? date ('m/d/Y', strtotime('today')) : date ('m/d/Y', $start_date);
        $end_date = empty($end_date) ? date ('m/d/Y', strtotime('today +18 months')) : date ('m/d/Y', $end_date);

        $source_config['operation_arguments']['EVRN_UnitCalendarAvailRQ']['UnitRef']['UnitCode'] = $unit_code;
        $source_config['operation_arguments']['EVRN_UnitCalendarAvailRQ']['CalendarDateRange']['Start'] = $start_date;
        $source_config['operation_arguments']['EVRN_UnitCalendarAvailRQ']['CalendarDateRange']['End'] = $end_date;
        $feed_source->setConfigFor($feed_source->importer->fetcher, $source_config);
        $feed_source->save();
        $feed_source->startImport();

        $feed_source->state(FEEDS_FETCH);
        $feed_source->state(FEEDS_PROCESS);
        $feed_source->state(FEEDS_PROCESS_CLEAR);
//      drupal_set_message('Escapia Units information have been updated.', 'status', true);
      } else {
        drupal_set_message('Escapia Units have been imported. Units complete information will be updated on the next Cron run.', 'status', true);
      }

    }
  }
  else {
    drupal_set_message('There was no valid UNIT CODE provided for Escapia DescriptiveInfo() request.', 'error', true);
  }
}