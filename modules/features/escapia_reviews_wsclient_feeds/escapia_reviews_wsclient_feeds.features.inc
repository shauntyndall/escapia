<?php
/**
 * @file
 * escapia_reviews_wsclient_feeds.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function escapia_reviews_wsclient_feeds_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "feeds" && $api == "feeds_importer_default") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function escapia_reviews_wsclient_feeds_node_info() {
  $items = array(
    'escapia_unit_review' => array(
      'name' => t('Escapia Unit Review'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
