<?php
/**
 * @file
 * escapia_wsclient_feeds.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function escapia_wsclient_feeds_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'date_format_escapia_rate_range';
  $strongarm->value = 'l M d, Y';
  $export['date_format_escapia_rate_range'] = $strongarm;

  return $export;
}
