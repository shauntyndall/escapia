<?php

class EscapiaConnectionUIController extends EntityDefaultUIController {

  protected $entityType;
  protected $entityInfo, $path;
  protected $id_count;

  /**
   * Defines the number of entries to show per page in overview table.
   */
  public $overviewPagerLimit = 25;

  public function __construct($entity_type, $entity_info) {
    $this->entityType = $entity_type;
    $this->entityInfo = $entity_info;
    $this->path = $this->entityInfo['admin ui']['path'];
    $this->statusKey = empty($this->entityInfo['entity keys']['status']) ? 'status' : $this->entityInfo['entity keys']['status'];
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
      'access callback' => 'escapia_connection_access',
      'access arguments' => array('create', $this->entityType),
      'type' => MENU_NORMAL_ITEM | MENU_LOCAL_ACTION,
    );

    $items[$this->path . '/' . $wildcard] = array(
      'title callback' => 'escapia_connection_page_title',
      'title arguments' => array(4),
      'page callback' => 'escapia_connection_view',
      'page arguments' => array(4),
      'access callback' => 'escapia_connection_access',
      'access arguments' => array('view escapia_connection entity'),
      'type' => MENU_CALLBACK,
    );

    $items[$this->path . '/' . $wildcard . '/view'] = array(
      'title' => 'View',
      'type' => MENU_DEFAULT_LOCAL_TASK,
      'weight' => -10,
    );

    $items[$this->path . '/' . $wildcard . '/delete'] = array(
      'title callback' => 'escapia_connection_page_title',
      'title arguments' => array(3),
      'page callback' => 'escapia_connection_view',
      'page arguments' => array(3),
      'access callback' => 'escapia_connection_access',
      'access arguments' => array('delete escapia_connection entity'),
      'type' => MENU_CALLBACK,
    );

    $items[$this->path . '/' . $wildcard . '/edit'] = array(
      'title' => 'Edit',
      'page callback' => 'entity_ui_get_form',
      'page arguments' => array($this->entityType, 4, 'edit'),
      'access callback' => 'escapia_connection_access',
      'access arguments' => array('edit escapia_connection entity'),
      'type' => MENU_LOCAL_TASK,
    );

    return $items;
  }

  /**
   * Generates the render array for a overview table for arbitrary entities
   * matching the given conditions.
   * @param array $conditions
   * @return array
   */
  public function overviewTable($conditions = array()) {
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', $this->entityType);

    // Add all conditions to query.
    foreach ($conditions as $key => $value) {
      $query->propertyCondition($key, $value);
    }

    if ($this->overviewPagerLimit) {
      $query->pager($this->overviewPagerLimit);
    }

    $results = $query->execute();

    $ids = isset($results[$this->entityType]) ? array_keys($results[$this->entityType]) : array();
    $entities = $ids ? entity_load($this->entityType, $ids) : array();
    ksort($entities);

    $rows = array();
    foreach ($entities as $entity) {
      $rows[] = $this->overviewTableRow($conditions, entity_id($this->entityType, $entity), $entity);
    }

    $render = array(
      '#theme' => 'table',
      '#header' => $this->overviewTableHeaders($conditions, $rows),
      '#rows' => $rows,
      '#empty' => t('No connections exist.'),
    );

    return $render;
  }

  /**
   * Generates the table headers for the overview table.
   * @param $conditions
   * @param $rows
   * @param array $additional_header
   * @return array
   */
  protected function overviewTableHeaders($conditions, $rows, $additional_header = array()) {
    $header = $additional_header;
    array_unshift($header, t('Connection'), t('WSDL Url'), t('Username'), t('Password'), t('Active'));
    $header[] = array('data' => t('Operations'), 'colspan' => $this->operationCount());
    return $header;
  }

  /**
   * Generates the row for the passed entity and may be overridden in order to
   * customize the rows.
   * @param $conditions
   * @param $id
   * @param $entity
   * @param array $additional_cols
   * @return array
   */
  protected function overviewTableRow($conditions, $id, $entity, $additional_cols = array()) {
    $entity_uri = entity_uri($this->entityType, $entity);

    $row[] = array(
      'data' => array(
        '#theme' => 'entity_ui_overview_item',
        '#label' => entity_label($this->entityType, $entity),
        '#name' => !empty($this->entityInfo['exportable']) ? entity_id($this->entityType, $entity) : FALSE,
        '#url' => $entity_uri ? $entity_uri : FALSE,
        '#entity_type' => $this->entityType
      ),
    );

    $row[] = array(
      'data' => array(
        '#theme' => 'entity_ui_overview_item',
        '#label' => $entity->wsdl,
        '#name' => !empty($this->entityInfo['exportable']) ? entity_id($this->entityType, $entity) : FALSE,
        '#entity_type' => $this->entityType
      ),
    );

    $row[] = array(
      'data' => array(
        '#theme' => 'entity_ui_overview_item',
        '#label' => $entity->username,
        '#name' => !empty($this->entityInfo['exportable']) ? entity_id($this->entityType, $entity) : FALSE,
        '#entity_type' => $this->entityType
      ),
    );

    $row[] = array(
      'data' => array(
        '#theme' => 'entity_ui_overview_item',
        '#label' => $entity->password,
        '#name' => !empty($this->entityInfo['exportable']) ? entity_id($this->entityType, $entity) : FALSE,
        '#entity_type' => $this->entityType
      ),
    );

    $row[] = array(
      'data' => array(
        '#theme' => 'entity_ui_overview_item',
        '#label' => isset($entity->active) && $entity->active === '1' ? 'Yes' : 'No',
        '#name' => !empty($this->entityInfo['exportable']) ? entity_id($this->entityType, $entity) : FALSE,
        '#entity_type' => $this->entityType
      ),
    );

    // Add in any passed additional cols.
    foreach ($additional_cols as $col) {
      $row[] = $col;
    }

    // Add a row for the exportable status.
    if (!empty($this->entityInfo['exportable'])) {
      $row[] = array('data' => array(
        '#theme' => 'entity_status',
        '#status' => $entity->{$this->statusKey},
      ));
    }
    // In case this is a bundle, we add links to the field ui tabs.
    $field_ui = !empty($this->entityInfo['bundle of']) && entity_type_is_fieldable($this->entityInfo['bundle of']) && module_exists('field_ui');
    // For exportable entities we add an export link.
    $exportable = !empty($this->entityInfo['exportable']);
    // If i18n integration is enabled, add a link to the translate tab.
    $i18n = !empty($this->entityInfo['i18n controller class']);

    // Add operations depending on the status.
    if (entity_has_status($this->entityType, $entity, ENTITY_FIXED)) {
      $row[] = array('data' => l(t('clone'), $this->path . '/manage/' . $id . '/clone'), 'colspan' => $this->operationCount());
    }
    else {
      $row[] = l(t('edit'), $this->path . '/manage/' . $id . '/edit');

      if ($field_ui) {
        $row[] = l(t('manage fields'), $this->path . '/manage/' . $id . '/fields');
        $row[] = l(t('manage display'), $this->path . '/manage/' . $id . '/display');
      }
      if ($i18n) {
        $row[] = l(t('translate'), $this->path . '/manage/' . $id . '/translate');
      }
      if ($exportable) {
        $row[] = l(t('clone'), $this->path . '/manage/' . $id . '/clone');
      }

      if (empty($this->entityInfo['exportable']) || !entity_has_status($this->entityType, $entity, ENTITY_IN_CODE)) {
        $row[] = l(t('delete'), $this->path . '/manage/' . $id . '/delete', array('query' => drupal_get_destination()));
      }
      elseif (entity_has_status($this->entityType, $entity, ENTITY_OVERRIDDEN)) {
        $row[] = l(t('revert'), $this->path . '/manage/' . $id . '/revert', array('query' => drupal_get_destination()));
      }
      else {
        $row[] = '';
      }
    }
    if ($exportable) {
      $row[] = l(t('export'), $this->path . '/manage/' . $id . '/export');
    }
    return $row;
  }
}