<?php

/**
 * Entity controller for the EscapiaConnection entity.
 */
class EscapiaConnectionController extends EntityAPIControllerExportable {

  public function __construct($entityType)
  {
    parent::__construct($entityType);
  }

  public function create(array $values = array())
  {
    $values += array(
      'id' => '',
      'label' => NULL,
      'wsdl' => NULL,
      'wsdl_content' => NULL,
      'username' => NULL,
      'password' => NULL,
      'active' => FALSE,
      'hapi_endpoint' => NULL,
      'hapi_api_key' => NULL,
      'hapi_client_id' => NULL,
      'uid' => NULL,
      'created' => REQUEST_TIME,
      'changed' => NULL,
    );

    return parent::create($values);
  }

  /**
   * Save a Escapia Connection entity.
   * @param $entity
   * @param DatabaseTransaction $transaction
   * @return bool|int
   */
  public function save($entity, DatabaseTransaction $transaction = NULL)
  {
    $entity->changed = REQUEST_TIME;

    if (empty($entity->{$this->idKey}) || !empty($entity->is_new)) {
      // Set the creation timestamp if not set, for new entities.
      if (empty($entity->created)) {
        $entity->created = REQUEST_TIME;
      }
    }

    return parent::save($entity, $transaction);
  }
}