<?php

/**
 * Implements hook_entity_property_info().
 */
function escapia_connection_entity_property_info() {
  $info = array();
  $properties = &$info['escapia_connection']['properties'];

  $properties['id'] = array(
    'label' => t('Connection Id'),
    'type' => 'integer',
    'description' => t('The unique ID of the connection entity.'),
    'schema field' => 'id',
  );

  $properties['label'] = array(
    'label' => t('Connection label'),
    'type' => 'text',
    'description' => t('The connection entity label.'),
    'schema field' => 'label',
    'setter callback' => 'entity_property_verbatim_set',
  );

  $properties['wsdl'] = array(
    'label' => t('Escapia Connection Id'),
    'type' => 'text',
    'description' => t('The EscapiaNET WSDL URL this connection entity uses.'),
    'schema field' => 'wsdl',
    'setter callback' => 'entity_property_verbatim_set',
  );

  $properties['account_id'] = array(
    'label' => t('Account ID'),
    'type' => 'text',
    'description' => t('Your Escapia account ID.'),
    'schema field' => 'account_id',
    'setter callback' => 'entity_property_verbatim_set',
  );

  $properties['username'] = array(
    'label' => t('Username'),
    'type' => 'text',
    'description' => t('The username used in the authentication to the WSDL service.'),
    'schema field' => 'username',
    'setter callback' => 'entity_property_verbatim_set',
  );

  $properties['password'] = array(
    'label' => t('Password'),
    'type' => 'text',
    'description' => t('The password used in the authentication to the WSDL service.'),
    'schema field' => 'password',
    'setter callback' => 'entity_property_verbatim_set',
  );

  $properties['active'] = array(
    'label' => t('Active'),
    'type' => 'integer',
    'description' => t('Whether or not this connection is active.'),
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

  return $info;
}