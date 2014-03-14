<?php
/**
 * @file
 * escapia_property_fields.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function escapia_property_fields_taxonomy_default_vocabularies() {
  return array(
    'rental_amenities' => array(
      'name' => 'Rental Amenities',
      'machine_name' => 'rental_amenities',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
