<?php

/**
 * Implements hook_entity_property_info().
 */
function escapia_property_entity_property_info() {
  $info = array();
  $properties = &$info['escapia_property']['properties'];

  $properties['id'] = array(
    'label' => t('Property Id'),
    'type' => 'integer',
    'description' => t('The unique ID of the property entity.'),
    'schema field' => 'id',
  );

  $properties['label'] = array(
    'label' => t('Property label'),
    'type' => 'text',
    'description' => t('The property label.'),
    'schema field' => 'label',
    'setter callback' => 'entity_property_verbatim_set',
  );

  $properties['connection_id'] = array(
    'label' => t('Escapia Connection Id'),
    'type' => 'integer',
    'description' => t('The Escapia connection entity ID.'),
    'schema field' => 'connection_id',
    'setter callback' => 'entity_property_verbatim_set',
  );

  $properties['unit_code'] = array(
    'label' => t('Unit Code'),
    'type' => 'text',
    'description' => t('The unit code of the property as set in Escapia.'),
    'schema field' => 'unit_code',
    'setter callback' => 'entity_property_verbatim_set',
  );

  $properties['unit_name'] = array(
    'label' => t('Unit Name'),
    'type' => 'text',
    'description' => t('The unit name as set in Escapia.'),
    'schema field' => 'unit_name',
    'setter callback' => 'entity_property_verbatim_set',
  );

  $properties['internal_code'] = array(
    'label' => t('Internal Code'),
    'type' => 'text',
    'description' => t('The internal unit code of the property as set in Escapia, by the property manager.'),
    'schema field' => 'internal_code',
    'setter callback' => 'entity_property_verbatim_set',
  );

  $properties['address_line_1'] = array(
    'label' => t('Address Line 1'),
    'type' => 'text',
    'description' => t('The street address as set in Escapia.'),
    'schema field' => 'address_line_1',
    'setter callback' => 'entity_property_verbatim_set',
  );

  $properties['address_line_2'] = array(
    'label' => t('Address Line 2'),
    'type' => 'text',
    'description' => t('The additional street address (Apt, Unit number) name as set in Escapia.'),
    'schema field' => 'address_line_2',
    'setter callback' => 'entity_property_verbatim_set',
  );

  $properties['address_city'] = array(
    'label' => t('Address City'),
    'type' => 'text',
    'description' => t('The address city as set in Escapia.'),
    'schema field' => 'address_city',
    'setter callback' => 'entity_property_verbatim_set',
  );

  $properties['address_state'] = array(
    'label' => t('Address State'),
    'type' => 'text',
    'description' => t('The address state as set in Escapia.'),
    'schema field' => 'address_state',
    'setter callback' => 'entity_property_verbatim_set',
  );

  $properties['address_zipcode'] = array(
    'label' => t('Address Zipcode'),
    'type' => 'integer',
    'description' => t('The address zipcode as set in Escapia.'),
    'schema field' => 'address_zipcode',
    'setter callback' => 'entity_property_verbatim_set',
  );

  $properties['address_verified'] = array(
    'label' => t('Address Verified'),
    'type' => 'integer',
    'description' => t('Whether or not the address was verified in Escapia.'),
    'schema field' => 'address_verified',
    'setter callback' => 'entity_property_verbatim_set',
  );

  $properties['active'] = array(
    'label' => t('Active'),
    'type' => 'integer',
    'description' => t('Whether or not this property is active.'),
    'schema field' => 'active',
    'setter callback' => 'entity_property_verbatim_set',
  );

  $properties['uid'] = array(
    'label' => t('User id'),
    'type' => 'integer',
    'description' => t('The user id who created the property entity.'),
    'schema field' => 'uid',
    'setter callback' => 'entity_property_verbatim_set',
  );

  $properties['created'] = array(
    'label' => t('Created'),
    'type' => 'integer',
    'description' => t('The created date of the property entity.'),
    'schema field' => 'created',
    'setter callback' => 'entity_property_verbatim_set',
  );

  $properties['changed'] = array(
    'label' => t('Changed'),
    'type' => 'integer',
    'description' => t('The date the property entity was last updated.'),
    'schema field' => 'changed',
    'setter callback' => 'entity_property_verbatim_set',
  );

  $properties['data'] = array(
    'label' => t('Data'),
    'type' => 'blob',
    'description' => t('Arbitrary data about the entity.'),
    'schema field' => 'data',
    'setter callback' => 'entity_property_verbatim_set',
  );

  return $info;
}