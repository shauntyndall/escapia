<?php

/**
 * Entity controller for the EscapiaProperty entity.
 */
class EscapiaPropertyController extends EntityAPIControllerExportable {

  public function __construct($entityType)
  {
    parent::__construct($entityType);
  }

  public function create(array $values = array())
  {
    $values += array(
      'id' => '',
      'label' => NULL,
      'connection_id' => NULL,
      'unit_code' => NULL,
      'unit_name' => NULL,
      'address_line_1' => NULL,
      'address_line_2' => NULL,
      'address_city' => NULL,
      'address_state' => NULL,
      'address_zipcode' => NULL,
      'address_verified' => NULL,
      'active' => FALSE,
      'uid' => NULL,
      'created' => REQUEST_TIME,
      'changed' => NULL,
    );

    return parent::create($values);
  }

  /**
   * Save a Escapia Property entity.
   * @param $entity
   * @param DatabaseTransaction $transaction
   * @return bool|int
   */
  public function save($entity, DatabaseTransaction $transaction = NULL)
  {
    global $user;

    $entity->uid = $user->uid;
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