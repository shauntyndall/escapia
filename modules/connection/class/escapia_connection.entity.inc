<?php

/**
 * Entity class definition for the EscapiaConnection entity.
 */
class EscapiaConnection extends Entity {

  public function __construct($values = array()) {
    parent::__construct($values, 'escapia_connection');
  }

  protected function defaultLabel() {
    return $this->label;
  }

  protected function defaultUri() {
    return array('path' => 'admin/structure/escapia/connection' . $this->id);
  }

  public function path() {
    $uri = $this->entity();
    return $uri['path'];
  }

  public function url() {
    $uri = $this->uri();
    return url($uri['path'], $uri);
  }

  public function label() {
    return $this->label;
  }
}