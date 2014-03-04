<?php

function escapia_management_page() {
  $output = '';

  if (module_exists('escapia_connection')) {
    $output .= '<h4>' . l('Manage Connections', 'admin/structure/escapia/connection') . '</h4>';
    $output .= '<p>Create or update connection(s) to the Escapia API.</p>';
  }

  if (module_exists('escapia_property')) {
    $output .= '<h4>' . l('Manage Properties', 'admin/structure/escapia/property') . '</h4>';
    $output .= '<p>Add or remove fields from the Escapia property entity.</p>';
  }

  return drupal_strlen($output) ? $output : t('Please enable one or more of the Escapia modules to see more options here.');
}