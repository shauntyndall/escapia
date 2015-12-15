<?php

/**
 * Implements hook_feeds_node_processor_targets_alter().
 */
function escapia_api_feeds_processor_targets_alter(&$targets, $entity_type, $bundle_name) {
  foreach (field_info_instances($entity_type, $bundle_name) as $name => $instance) {
    $info = field_info_field($name);
    if ($info['type'] == 'starrating_rating') {
      $targets[$info['field_name'] . ':value'] = array(
        'name' => t($instance['label'] . ' Value'),
        'callback' => 'escapia_api_set_target_simple',
        'real_target' => $info['field_name'],
      );
    }
  }
}

function escapia_api_set_target_simple($source, $entity, $target, $values) {
  list($field_name, $sub_field) = explode(':', $target, 2);
  $field = isset($entity->$field_name) ? $entity->$field_name : array('und' => array());
  $delta = 0;

  foreach ($values as $value) {
    if ($value == 'null') {
      $field['und'][$delta][$sub_field] = NULL;
    }
    else if (is_scalar($value)) {
      $field['und'][$delta][$sub_field] = (int)$value;
    }
    $delta++;
  }

  $entity->$field_name = $field;
}