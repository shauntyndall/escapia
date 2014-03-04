<?php

class EscapiaPropertyFieldQuery extends EntityFieldQuery {
  public function __construct(array $values = array()) {
    $this->entityCondition('entity_type', 'escapia_property');
  }

  public function unitCode($code) {
    $this->propertyCondition('unit_code', $code);
  }

  public function internalCode($code) {
    $this->propertyCondition('internal_code', $code);
  }

  public function unitName($name) {
    $this->propertyCondition('unit_name', $name);
  }

  public function lastUpdated($timestamp) {
    $this->propertyCondition('changed', $timestamp, '>=');
  }

  public function isActive() {
    $this->propertyCondition('active', 1);
  }

  public function result() {
    $result = $this->execute();
    return isset($result['escapia_property']) ? $result['escapia_property'] : FALSE;
  }
}