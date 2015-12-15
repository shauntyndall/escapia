<?php
/**
 * @file
 * escapia_wsclient_feeds.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function escapia_wsclient_feeds_taxonomy_default_vocabularies() {
  return array(
    'escapia_api_amenities' => array(
      'name' => 'Escapia API Amenities',
      'machine_name' => 'escapia_api_amenities',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
