<?php

class EscapiaPropertyUIController extends EntityDefaultUIController {

  public function __construct($entity_type, $entity_info) {
    parent::__construct($entity_type, $entity_info);
  }

  /**
   * Overrides hook_menu() defaults.
   */
  public function hook_menu() {
    $id_count = count(explode('/', $this->path));
    $wildcard = isset($this->entityInfo['admin ui']['menu wildcard']) ? $this->entityInfo['admin ui']['menu wildcard'] : '%entity_object';
    $plural_label = isset($this->entityInfo['plural label']) ? $this->entityInfo['plural label'] : $this->entityInfo['label'];

    $items = parent::hook_menu();

    $items[$this->path . '/add'] = array(
      'title callback' => 'entity_ui_get_action_title',
      'title arguments' => array('add', $this->entityType),
      'page callback' => 'entity_ui_get_form',
      'page arguments' => array($this->entityType, NULL, 'add'),
      'access callback' => 'escapia_property_access',
      'access arguments' => array('create', $this->entityType),
      'type' => MENU_NORMAL_ITEM | MENU_LOCAL_ACTION,
    );

    $items[$this->path . '/' . $wildcard] = array(
      'title callback' => 'escapia_property_page_title',
      'title arguments' => array(4),
      'page callback' => 'escapia_property_view',
      'page arguments' => array(4),
      'access callback' => 'escapia_property_access',
      'access arguments' => array('view escapia_property entity'),
      'type' => MENU_CALLBACK,
    );

    $items[$this->path . '/' . $wildcard . '/view'] = array(
      'title' => 'View',
      'type' => MENU_DEFAULT_LOCAL_TASK,
      'weight' => -10,
    );

    $items[$this->path . '/' . $wildcard . '/delete'] = array(
      'title callback' => 'escapia_property_page_title',
      'title arguments' => array(3),
      'page callback' => 'escapia_property_view',
      'page arguments' => array(3),
      'access callback' => 'escapia_property_access',
      'access arguments' => array('delete escapia_property entity'),
      'type' => MENU_CALLBACK,
    );

    $items[$this->path . '/' . $wildcard . '/edit'] = array(
      'title' => 'Edit',
      'page callback' => 'entity_ui_get_form',
      'page arguments' => array($this->entityType, 4, 'edit'),
      'access callback' => 'escapia_property_access',
      'access arguments' => array('edit escapia_property entity'),
      'type' => MENU_LOCAL_TASK,
    );

    $items[$this->path . '/' . $wildcard . '/update'] = array(
      'title' => 'Update',
      'page callback' => 'ADD_CALLBACK_HERE',
      'page arguments' => array($this->entityType, 4, 'update'),
      'access callback' => 'escapia_property_access',
      'access arguments' => array('update escapia_property entity'),
      'type' => MENU_LOCAL_TASK,
    );

    return $items;
  }
}