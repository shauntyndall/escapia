<?php
/**
 * @file
 * escapia_property_fields.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function escapia_property_fields_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_availability|escapia_property|escapia_property|form';
  $field_group->group_name = 'group_availability';
  $field_group->entity_type = 'escapia_property';
  $field_group->bundle = 'escapia_property';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Availability',
    'weight' => '3',
    'children' => array(
      0 => 'field_esp_availability',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-availability field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_availability|escapia_property|escapia_property|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_photos|escapia_property|escapia_property|form';
  $field_group->group_name = 'group_photos';
  $field_group->entity_type = 'escapia_property';
  $field_group->bundle = 'escapia_property';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Photos',
    'weight' => '1',
    'children' => array(
      0 => 'field_esp_photos',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-photos field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_photos|escapia_property|escapia_property|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_property|escapia_property|escapia_property|form';
  $field_group->group_name = 'group_property';
  $field_group->entity_type = 'escapia_property';
  $field_group->bundle = 'escapia_property';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Property Information',
    'weight' => '0',
    'children' => array(
      0 => 'field_esp_description',
      1 => 'field_esp_bedrooms',
      2 => 'field_esp_bathrooms',
      3 => 'field_esp_max_occupancy',
      4 => 'field_esp_headline',
      5 => 'field_esp_minlos',
      6 => 'field_esp_address',
      7 => 'field_esp_amenities',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-property field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_property|escapia_property|escapia_property|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_rates|escapia_property|escapia_property|form';
  $field_group->group_name = 'group_rates';
  $field_group->entity_type = 'escapia_property';
  $field_group->bundle = 'escapia_property';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Rate Information',
    'weight' => '2',
    'children' => array(
      0 => 'field_esp_minimum_rate',
      1 => 'field_esp_maximum_rate',
      2 => 'field_esp_minimum_fees',
      3 => 'field_esp_maximum_fees',
      4 => 'field_esp_minimum_tax',
      5 => 'field_esp_maximum_tax',
      6 => 'field_esp_minimum_rent',
      7 => 'field_esp_maximum_rent',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-rates field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_rates|escapia_property|escapia_property|form'] = $field_group;

  return $export;
}
