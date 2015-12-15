<?php

/**
 * The availability booking form.
 * @param $form
 * @param $form_state
 * @param $node
 * @return mixed
 */
function escapia_api_check_availability_request_form($form, &$form_state, $node = NULL) {
  form_load_include($form_state, 'inc', 'escapia_api', '/includes/availability');
  drupal_add_library('system', 'ui.dialog');

  $form['#attached']['css'] = array(
    drupal_get_path('module', 'escapia_api') . '/js/pickadate/themes/classic.css',
    drupal_get_path('module', 'escapia_api') . '/js/pickadate/themes/classic.date.css',
  );

  $form['#attached']['js'][] = array('data' => drupal_get_path('module', 'escapia_api') . '/js/pickadate/picker.js', 'type' => 'file', 'weight' => 10);
  $form['#attached']['js'][] = array('data' => drupal_get_path('module', 'escapia_api') . '/js/pickadate/picker.date.js', 'type' => 'file', 'weight' => 20);
  $form['#attached']['js'][] = array('data' => drupal_get_path('module', 'escapia_api') . '/js/escapia_api.js', 'type' => 'file', 'weight' => 1000);

  if (!isset($node)) {
    $node = menu_get_object();
  }

  if($node && $node->type == 'escapia_unit') {
    $form_state['node_id'] = $node->nid;
    $form_state['unit_code'] = $node->field_escapia_unit_code[LANGUAGE_NONE][0]['value'];
//  $calendar_check = _escapia_api_listing_has_available_days($node->nid);

//  if (!$calendar_check) {
//    $form['message'] = array(
//      '#markup' => t('This property does not have any available dates at the moment. Please check back in the future for openings or call us with any questions about this rental.')
//    );
//    return $form;
//  }

    $wrapper = entity_metadata_wrapper('node', $node->nid);
    $check_in = '';
    $check_out = array();

    $form['check-in'] = array(
      '#attributes' => array('placeholder' => 'Arrival Date', 'id' => 'escapia-availability-checkin', 'class' => array('escapia-checkin-popup')),
      '#type' => 'textfield',
//      '#title' => t('Check-in Day'),
      '#settings' => array(
        'selectMonths' => TRUE,
        'selectYears' => TRUE,
        'firstDay' => variable_get('date_first_day', 1),
        'min' => 1,
        'formatSubmit' => 'yyyy/mm/dd',
        'hiddenName' => true,
        'format' => 'mmmm d, yyyy'
      )
    );
    drupal_add_js(array('escapia_api' => array('dateSettings' => array('escapia-checkin-popup' => json_encode( $form['check-in']['#settings'])))), array('type' => 'setting'));

    // populate a list of acceptable check in check out dates.
//    foreach ($wrapper->field_check_in_dates as $date) {
//      $form['check-in']['#settings']['disable'][] = array((int) date('Y', $date->value()), (int) date('m', $date->value()) - 1, (int) date('d', $date->value()));
//    }

    $form['check-out'] = array(
      '#attributes' => array('placeholder' => 'Departure Date', 'id' => 'escapia-availability-checkout', 'class' => array('escapia-checkout-popup')),
      '#type' => 'textfield',
//      '#title' => t('Check-out Day'),
      '#settings' => array(
        'selectMonths' => TRUE,
        'selectYears' => TRUE,
        'firstDay' => variable_get('date_first_day', 1),
        'min' => 2,
        'formatSubmit' => 'yyyy/mm/dd',
        'hiddenName' => true,
        'format' => 'mmmm d, yyyy'
      )
    );
    drupal_add_js(array('escapia_api' => array('dateSettings' => array('escapia-checkout-popup' => json_encode( $form['check-out']['#settings'])))), array('type' => 'setting'));

    // populate a list of acceptable check in check out dates.
//    foreach ($wrapper->field_check_in_dates as $date) {
//      $timestamp =  strtotime('+1 week', $date->value());
//      $form['check-out']['#settings']['disable'][] = array((int) date('Y', $timestamp), (int) date('m', $timestamp) - 1, (int) date('d', $timestamp));
//    }

    $form['errors'] = array(
      '#type' => 'container',
      '#attributes' => array('class' => array('escapia-errors')),
    );

    $form['response'] = array(
      '#type' => 'container',
      '#attributes' => array('class' => array('escapia-response')),
    );

    $form['rate_details'] = array(
      '#type' => 'markup',
      '#markup' => '<div id="escapia-avail-rate-details"><div id="escapia-avail-rate-details-inner"></div></div>',
      '#attributes' => array('class' => array('escapia-response-details')),
    );

    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => 'Check Availability',
      '#attributes' => array('class' => array('button', 'info', 'radius', 'check-rates')),
      '#ajax' => array(
        'callback' => 'escapia_api_check_availability_fetch',
        'wrapper' => 'escapia-response',
        'method' => 'replace',
        'effect' => 'fade',
        'prevent' => 'click',
        'progress' => array('type' => 'throbber', 'message' => t('Checking. Please wait...'), 'class' => array('rates-throbber')),
      )
    );
    return $form;
  }
  else {
    return $form;
  }
}

/**
 * Validation handler.
 * @param $form
 * @param $form_state
 */
function escapia_api_check_availability_request_form_validate($form, &$form_state) {
  if (!drupal_strlen($form_state['values']['check-in'])) {
    form_set_error('check-in', t('Please enter a check-in date.'));
  }

  if (!drupal_strlen($form_state['values']['check-out'])) {
    form_set_error('check-in', t('Please enter a check-out date.'));
  }

  if (strtotime($form_state['values']['check-in']) > strtotime($form_state['values']['check-out'])) {
    form_set_error('check-in', t('You cannot pick a check-in date that happens after a check-out date.'));
  }
}

/**
 * Submit handler.
 * @param $form
 * @param $form_state
 */
function escapia_api_check_availability_request_form_submit($form, &$form_state) {
  // save simple data in the user session
  $_SESSION['escapia_api_booking'] = array(
    'timestamp' => REQUEST_TIME,
    'unit_code' => $form_state['unit_code'],
    'check-in' => $form_state['values']['check-in'],
    'check-out' => $form_state['values']['check-out'],
    'id' => $form_state['node_id'],
    'adults' => isset($form_state['values']['adults']) ? $form_state['values']['adults'] : '1',
    'children' => isset($form_state['values']['children']) ? $form_state['values']['children'] : '0',
    'reviewed_rates' => FALSE,
  );
}

/**
 * Callback for the AJAX submit in the Check Availability form utilizing WebServices Operation invocation.
 * @param $form
 * @param $form_state
 * @return array
 */
function escapia_api_check_availability_fetch($form, &$form_state) {
  if (!form_get_errors()) {
    $api = new EscapiaAPIImport();
    $response = $api->getUnitAvailableRequest($_SESSION['escapia_api_booking']['unit_code'], false, strtotime($_SESSION['escapia_api_booking']['check-in']), strtotime($_SESSION['escapia_api_booking']['check-out']), $_SESSION['escapia_api_booking']['adults'], $_SESSION['escapia_api_booking']['children']);

    $form_state['response'] = $response;

    if ($response && isset($response->Success)) {
      $total = escapia_api_availability_process_quote_response($response);

      $output = '<hr><h5>Available!</h5>';
//      $output .= '<p>This property is available for the period: <br>' . $response->UnitStay->TimeSpan->Start . '  --  ' . $response->UnitStay->TimeSpan->End . '<hr></p>';
      $output .= '<div><strong>Estimated total:</strong> $' . $total . '</div><br>';
//      $output .= '<p><span class="book-link">' . l('Book Now &raquo;', 'rental/' . $_SESSION['escapia_api_booking']['unit_code'] . '/book-online/review-rates',
//          array('html' => TRUE, 'attributes' => array('class' => array('escapia-book-now', 'button', 'success')))
//        ) . '</span>';
//      $output .= '<button id="escapia-avail-rate-details-link" class="book-details-open">View Rate Details</button>';
//      $output .= '</p>';
//      $output .= '<hr>';

      $detailed_total = escapia_api_availability_process_quote_response_detailed($response);

      $_SESSION['escapia_api_booking']['initial_total'] = $total;

    } else {
      $output = '<div class="unavailable-response error-text"><p>' . $response->Errors->Error->_ . ' ' . variable_get('escapia_error_contact_msg', '') . '</p><hr></div>';
      $_SESSION['escapia_api_booking'] = array();
    }
  } else {
    $_SESSION['escapia_api_booking'] = array();
    $errors = TRUE;
  }

  global $theme;

  $theme_function = $theme . '_status_messages';

  if (!function_exists($theme_function)) {
    $theme_function = 'theme_status_messages';
  }

  $commands = array();
  $commands[] = ajax_command_html('div.escapia-response', $output);
  $commands[] = ajax_command_html('div#escapia-avail-rate-details-inner', $detailed_total);


  if ($errors) {
    $commands[] = ajax_command_html('div.escapia-errors', $theme_function(array()));
  }

  $commands[] = ajax_command_invoke('.alert-box', 'foundation', array('alert'));
  return array('#type' => 'ajax', '#commands' => $commands);
}

/**
 * Grab an estimated total from the availability quote response.
 * @param $response
 * @return string
 */
function escapia_api_availability_process_quote_response($response) {
  $subtotal = $response->UnitStay->Total->AmountBeforeTax;
  $taxes = $response->UnitStay->Total->Taxes->Amount;
  return bcadd($subtotal, $taxes, 2);
}

/**
 * Grab an estimated total from the availability quote response - detailed output.
 * @param $response
 * @return string
 */
function escapia_api_availability_process_quote_response_detailed($response) {
  $ratesClass = new EscapiaAPIBookingRates($response->UnitStay, null, null, $response->Success);

  $optional_charges_details = $ratesClass->getOptionalChargesDetails();
  $optional_total = $ratesClass->get_SUMM_OptionalCharges();
  $optional_total_tax = $ratesClass->get_SUMM_OptionalCharges('taxAmount');
  $total_charges = $ratesClass->getTotalPrice();

  $subtotal = bcadd($optional_total, $total_charges['beforeTax'], 2);
  $taxes = bcadd($optional_total_tax, $total_charges['taxAmount'], 2);

  $items['items'][] = '<span class="confirmation-label required-label">Rent Fee:</span> ' . money_format('$%i', $total_charges['beforeTax']);
  foreach($optional_charges_details as $charge) {
    $items['items'][] = '<span class="confirmation-label optional-label">' . $charge['label']. ' (Optional):</span> ' . money_format('$%i', $charge['beforeTax']);
  }
  $items['items'][] = '<span class="confirmation-label subtotal-label">Sub-Total:</span> ' . money_format('$%i', $subtotal);
  $items['items'][] = '<span class="confirmation-label tax-label">Tax:</span> ' . money_format('$%i', $taxes);
  $items['items'][] = '<span class="confirmation-label total-label">Total:</span> ' . money_format('$%i', bcadd($subtotal, $taxes, 2));

  $output = theme('item_list', $items, 'ul');
  $output = theme('item_list', $items, 'ul');

  return $output;
}

/**
 * Check to see if we have any tracked days. If not, there is no point in showing a check availability form - and the Javascript that renders the datepicker crashes in a loop (pickadate.js bug).
 * @param $entity_id
 * @return bool
 */
function _escapia_api_listing_has_available_days($entity_id) {
  $availability = db_query('SELECT * FROM field_data_field_esp_available_days WHERE entity_id = :id AND field_esp_available_days_value >= :date', array(':id' => $entity_id, ':date' => REQUEST_TIME))->fetchAllAssoc('entity_id');
  return count($availability) ? TRUE : FALSE;
}