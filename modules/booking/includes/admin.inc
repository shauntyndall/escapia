<?php

/**
 * Configure settings for booking a property online.
 * @param $form
 * @param $form_state
 * @return mixed
 */

function escapia_api_booking_admin_settings($form, &$form_state) {
  $page_nodes = new EntityFieldQuery();
  $page_nodes->entityCondition('entity_type', 'node');
  $page_nodes->propertyCondition('type', 'page')
    ->propertyCondition('status', 1);
  $page_nodes->propertyOrderBy('title');
  $pages = array(0 => 'None');
  $result = $page_nodes->execute();

  foreach (reset($result) as $nid => $item) {
    $wrapper = entity_metadata_wrapper('node', $nid);
    $pages[$nid] = $wrapper->title->value();
  }

  $confirmation_email = variable_get('escapia_api_booking_confirmation_email', array('format' => 'full_html', 'value' => ''));
  $confirmation_email = isset($confirmation_email['value']) ? $confirmation_email['value'] : '';

  $form['escapia_api_booking_confirmation_email'] = array(
    '#type' => 'text_format',
    '#title' => 'Confirmation Email Content',
    '#description' => 'Please enter the content of the confirmation email in the textbox. Information like booking dates and estimated charges will be included in the email automatically for you.',
    '#default_value' => $confirmation_email,
    '#base_type' => 'textarea',
    '#format' => 'full_html',
  );

  $form['escapia_api_booking_extra_insurance'] = array(
    '#type' => 'select',
    '#options' => $pages,
    '#title' => 'Additional Insurance Content',
    '#default_value' => variable_get('escapia_api_booking_extra_insurance', 0),
    '#description' => 'Please select which node will act as the content for travelers insurance. This will be linked to from the booking form, and the page content will be included in booking emails.',
  );

  return system_settings_form($form);
}