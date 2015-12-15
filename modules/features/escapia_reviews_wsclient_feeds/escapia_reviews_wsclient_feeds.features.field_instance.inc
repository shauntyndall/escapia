<?php
/**
 * @file
 * escapia_reviews_wsclient_feeds.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function escapia_reviews_wsclient_feeds_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-escapia_unit-field_escapia_unit_reviews_ref'
  $field_instances['node-escapia_unit-field_escapia_unit_reviews_ref'] = array(
    'bundle' => 'escapia_unit',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => array(
          'field_delimiter' => '',
          'field_formatter_class' => '',
          'field_multiple_limit' => -1,
          'field_multiple_limit_offset' => 0,
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 35,
      ),
      'full' => array(
        'label' => 'hidden',
        'module' => 'entityreference',
        'settings' => array(
          'field_delimiter' => '',
          'field_formatter_class' => '',
          'field_multiple_limit' => -1,
          'field_multiple_limit_offset' => 0,
          'links' => 0,
          'view_mode' => 'teaser',
        ),
        'type' => 'entityreference_entity_view',
        'weight' => 0,
      ),
      'grid' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'ical' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'list' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'node',
    'field_name' => 'field_escapia_unit_reviews_ref',
    'label' => 'Unit Reviews',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 37,
    ),
  );

  // Exported field_instance: 'node-escapia_unit_review-body'
  $field_instances['node-escapia_unit_review-body'] = array(
    'bundle' => 'escapia_unit_review',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(
          'field_delimiter' => '',
          'field_formatter_class' => '',
          'field_multiple_limit' => -1,
          'field_multiple_limit_offset' => 0,
        ),
        'type' => 'text_default',
        'weight' => 8,
      ),
      'ical' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(
          'field_delimiter' => '',
          'field_formatter_class' => '',
          'field_multiple_limit' => -1,
          'field_multiple_limit_offset' => 0,
        ),
        'type' => 'text_default',
        'weight' => 9,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'body',
    'label' => 'Body',
    'required' => FALSE,
    'settings' => array(
      'display_summary' => TRUE,
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'module' => 'text',
      'settings' => array(
        'rows' => 20,
        'summary_rows' => 5,
      ),
      'type' => 'text_textarea_with_summary',
      'weight' => 2,
    ),
  );

  // Exported field_instance: 'node-escapia_unit_review-field_esc_review_clean_rate'
  $field_instances['node-escapia_unit_review-field_esc_review_clean_rate'] = array(
    'bundle' => 'escapia_unit_review',
    'default_value' => array(
      0 => array(
        'value' => 'null',
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'starrating',
        'settings' => array(
          'field_delimiter' => '',
          'field_formatter_class' => '',
          'field_multiple_limit' => -1,
          'field_multiple_limit_offset' => 0,
          'fill_blank' => 1,
          'icon_color' => 1,
          'icon_type' => 'star',
        ),
        'type' => 'starrating_rating_formatter',
        'weight' => 2,
      ),
      'ical' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'inline',
        'module' => 'starrating',
        'settings' => array(
          'field_delimiter' => '',
          'field_formatter_class' => '',
          'field_multiple_limit' => -1,
          'field_multiple_limit_offset' => 0,
          'fill_blank' => 1,
          'icon_color' => 1,
          'icon_type' => 'star',
        ),
        'type' => 'starrating_rating_formatter',
        'weight' => 2,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'node',
    'field_name' => 'field_esc_review_clean_rate',
    'label' => 'Cleanliness',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'starrating',
      'settings' => array(),
      'type' => 'starrating_rating_widget',
      'weight' => 15,
    ),
  );

  // Exported field_instance: 'node-escapia_unit_review-field_esc_review_condition_rate'
  $field_instances['node-escapia_unit_review-field_esc_review_condition_rate'] = array(
    'bundle' => 'escapia_unit_review',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'starrating',
        'settings' => array(
          'field_delimiter' => '',
          'field_formatter_class' => '',
          'field_multiple_limit' => -1,
          'field_multiple_limit_offset' => 0,
          'fill_blank' => 1,
          'icon_color' => 1,
          'icon_type' => 'star',
        ),
        'type' => 'starrating_rating_formatter',
        'weight' => 3,
      ),
      'ical' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'inline',
        'module' => 'starrating',
        'settings' => array(
          'field_delimiter' => '',
          'field_formatter_class' => '',
          'field_multiple_limit' => -1,
          'field_multiple_limit_offset' => 0,
          'fill_blank' => 1,
          'icon_color' => 1,
          'icon_type' => 'star',
        ),
        'type' => 'starrating_rating_formatter',
        'weight' => 3,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'node',
    'field_name' => 'field_esc_review_condition_rate',
    'label' => 'Property Condition',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'starrating',
      'settings' => array(),
      'type' => 'starrating_rating_widget',
      'weight' => 17,
    ),
  );

  // Exported field_instance: 'node-escapia_unit_review-field_esc_review_location_rate'
  $field_instances['node-escapia_unit_review-field_esc_review_location_rate'] = array(
    'bundle' => 'escapia_unit_review',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'starrating',
        'settings' => array(
          'field_delimiter' => '',
          'field_formatter_class' => '',
          'field_multiple_limit' => -1,
          'field_multiple_limit_offset' => 0,
          'fill_blank' => 1,
          'icon_color' => 1,
          'icon_type' => 'star',
        ),
        'type' => 'starrating_rating_formatter',
        'weight' => 4,
      ),
      'ical' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'inline',
        'module' => 'starrating',
        'settings' => array(
          'field_delimiter' => '',
          'field_formatter_class' => '',
          'field_multiple_limit' => -1,
          'field_multiple_limit_offset' => 0,
          'fill_blank' => 1,
          'icon_color' => 1,
          'icon_type' => 'star',
        ),
        'type' => 'starrating_rating_formatter',
        'weight' => 4,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'node',
    'field_name' => 'field_esc_review_location_rate',
    'label' => 'Location',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'starrating',
      'settings' => array(),
      'type' => 'starrating_rating_widget',
      'weight' => 19,
    ),
  );

  // Exported field_instance: 'node-escapia_unit_review-field_esc_review_overall_rate'
  $field_instances['node-escapia_unit_review-field_esc_review_overall_rate'] = array(
    'bundle' => 'escapia_unit_review',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'starrating',
        'settings' => array(
          'field_delimiter' => '',
          'field_formatter_class' => '',
          'field_multiple_limit' => -1,
          'field_multiple_limit_offset' => 0,
          'fill_blank' => 1,
          'icon_color' => 1,
          'icon_type' => 'star',
        ),
        'type' => 'starrating_rating_formatter',
        'weight' => 5,
      ),
      'ical' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'inline',
        'module' => 'starrating',
        'settings' => array(
          'field_delimiter' => '',
          'field_formatter_class' => '',
          'field_multiple_limit' => -1,
          'field_multiple_limit_offset' => 0,
          'fill_blank' => 1,
          'icon_color' => 1,
          'icon_type' => 'star',
        ),
        'type' => 'starrating_rating_formatter',
        'weight' => 1,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'node',
    'field_name' => 'field_esc_review_overall_rate',
    'label' => 'Overall Satisfaction',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'starrating',
      'settings' => array(),
      'type' => 'starrating_rating_widget',
      'weight' => 21,
    ),
  );

  // Exported field_instance: 'node-escapia_unit_review-field_esc_review_recommend_rate'
  $field_instances['node-escapia_unit_review-field_esc_review_recommend_rate'] = array(
    'bundle' => 'escapia_unit_review',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'starrating',
        'settings' => array(
          'field_delimiter' => '',
          'field_formatter_class' => '',
          'field_multiple_limit' => -1,
          'field_multiple_limit_offset' => 0,
          'fill_blank' => 1,
          'icon_color' => 1,
          'icon_type' => 'star',
        ),
        'type' => 'starrating_rating_formatter',
        'weight' => 6,
      ),
      'ical' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'inline',
        'module' => 'starrating',
        'settings' => array(
          'field_delimiter' => '',
          'field_formatter_class' => '',
          'field_multiple_limit' => -1,
          'field_multiple_limit_offset' => 0,
          'fill_blank' => 1,
          'icon_color' => 1,
          'icon_type' => 'star',
        ),
        'type' => 'starrating_rating_formatter',
        'weight' => 6,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'node',
    'field_name' => 'field_esc_review_recommend_rate',
    'label' => 'Recommend to Others',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'starrating',
      'settings' => array(),
      'type' => 'starrating_rating_widget',
      'weight' => 23,
    ),
  );

  // Exported field_instance: 'node-escapia_unit_review-field_esc_review_services_rate'
  $field_instances['node-escapia_unit_review-field_esc_review_services_rate'] = array(
    'bundle' => 'escapia_unit_review',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'starrating',
        'settings' => array(
          'field_delimiter' => '',
          'field_formatter_class' => '',
          'field_multiple_limit' => -1,
          'field_multiple_limit_offset' => 0,
          'fill_blank' => 1,
          'icon_color' => 1,
          'icon_type' => 'star',
        ),
        'type' => 'starrating_rating_formatter',
        'weight' => 7,
      ),
      'ical' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'inline',
        'module' => 'starrating',
        'settings' => array(
          'field_delimiter' => '',
          'field_formatter_class' => '',
          'field_multiple_limit' => -1,
          'field_multiple_limit_offset' => 0,
          'fill_blank' => 1,
          'icon_color' => 1,
          'icon_type' => 'star',
        ),
        'type' => 'starrating_rating_formatter',
        'weight' => 5,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'node',
    'field_name' => 'field_esc_review_services_rate',
    'label' => 'Services from Rental Manager',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'starrating',
      'settings' => array(),
      'type' => 'starrating_rating_widget',
      'weight' => 25,
    ),
  );

  // Exported field_instance: 'node-escapia_unit_review-field_escapia_review_date'
  $field_instances['node-escapia_unit_review-field_escapia_review_date'] = array(
    'bundle' => 'escapia_unit_review',
    'deleted' => 0,
    'description' => 'Start date - for review original date. End date - for review changed date.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 29,
      ),
      'ical' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 28,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'node',
    'field_name' => 'field_escapia_review_date',
    'label' => 'Review Date',
    'required' => 0,
    'settings' => array(
      'default_value' => 'now',
      'default_value2' => 'same',
      'default_value_code' => '',
      'default_value_code2' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'date',
      'settings' => array(
        'display_all_day' => 0,
        'increment' => 15,
        'input_format' => 'Y-m-d H:i:s',
        'input_format_custom' => '',
        'label_position' => 'above',
        'repeat_collapsed' => 0,
        'text_parts' => array(),
        'year_range' => '-3:+3',
      ),
      'type' => 'date_text',
      'weight' => 9,
    ),
  );

  // Exported field_instance: 'node-escapia_unit_review-field_escapia_review_rejected'
  $field_instances['node-escapia_unit_review-field_escapia_review_rejected'] = array(
    'bundle' => 'escapia_unit_review',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 26,
      ),
      'ical' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 25,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'node',
    'field_name' => 'field_escapia_review_rejected',
    'label' => 'Property Manager Rejected',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'display_label' => 0,
      ),
      'type' => 'options_onoff',
      'weight' => 6,
    ),
  );

  // Exported field_instance: 'node-escapia_unit_review-field_escapia_reviewer_email'
  $field_instances['node-escapia_unit_review-field_escapia_reviewer_email'] = array(
    'bundle' => 'escapia_unit_review',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 24,
      ),
      'ical' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 23,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'node',
    'field_name' => 'field_escapia_reviewer_email',
    'label' => 'Reviewer Email',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 4,
    ),
  );

  // Exported field_instance: 'node-escapia_unit_review-field_escapia_reviewer_id'
  $field_instances['node-escapia_unit_review-field_escapia_reviewer_id'] = array(
    'bundle' => 'escapia_unit_review',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 28,
      ),
      'ical' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 27,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'node',
    'field_name' => 'field_escapia_reviewer_id',
    'label' => 'Reviewer ID',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 8,
    ),
  );

  // Exported field_instance: 'node-escapia_unit_review-field_escapia_reviewer_info'
  $field_instances['node-escapia_unit_review-field_escapia_reviewer_info'] = array(
    'bundle' => 'escapia_unit_review',
    'default_value' => array(
      0 => array(
        'element_key' => 'node|escapia_unit_review|field_escapia_reviewer_info|und|0',
        'thoroughfare' => '',
        'premise' => '',
        'locality' => '',
        'administrative_area' => '',
        'postal_code' => '',
        'country' => 'US',
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'addressfield',
        'settings' => array(
          'field_delimiter' => '',
          'field_formatter_class' => '',
          'field_multiple_limit' => -1,
          'field_multiple_limit_offset' => 0,
          'format_handlers' => array(
            'name-oneline' => 'name-oneline',
          ),
          'use_widget_handlers' => 0,
        ),
        'type' => 'addressfield_default',
        'weight' => 1,
      ),
      'ical' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'hidden',
        'module' => 'addressfield',
        'settings' => array(
          'field_delimiter' => '',
          'field_formatter_class' => '',
          'field_multiple_limit' => -1,
          'field_multiple_limit_offset' => 0,
          'format_handlers' => array(
            'name-oneline' => 'name-oneline',
          ),
          'use_widget_handlers' => 0,
        ),
        'type' => 'addressfield_default',
        'weight' => 2,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'node',
    'field_name' => 'field_escapia_reviewer_info',
    'label' => 'Unit Reviewer Information',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'addressfield',
      'settings' => array(
        'available_countries' => array(),
        'format_handlers' => array(
          'address' => 'address',
          'name-oneline' => 'name-oneline',
          'address-hide-country' => 0,
          'thoroughfare-textarea' => 0,
          'organisation' => 0,
          'name-full' => 0,
        ),
      ),
      'type' => 'addressfield_standard',
      'weight' => 3,
    ),
  );

  // Exported field_instance: 'node-escapia_unit_review-field_escapia_reviewer_res_id'
  $field_instances['node-escapia_unit_review-field_escapia_reviewer_res_id'] = array(
    'bundle' => 'escapia_unit_review',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 27,
      ),
      'ical' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 26,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'node',
    'field_name' => 'field_escapia_reviewer_res_id',
    'label' => 'Reservation Number',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 7,
    ),
  );

  // Exported field_instance: 'node-escapia_unit_review-field_escapia_reviewer_stay_date'
  $field_instances['node-escapia_unit_review-field_escapia_reviewer_stay_date'] = array(
    'bundle' => 'escapia_unit_review',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 25,
      ),
      'ical' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 24,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'node',
    'field_name' => 'field_escapia_reviewer_stay_date',
    'label' => 'Reviewer Stay Dates',
    'required' => 0,
    'settings' => array(
      'default_value' => 'now',
      'default_value2' => 'same',
      'default_value_code' => '',
      'default_value_code2' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'date',
      'settings' => array(
        'display_all_day' => 0,
        'increment' => 15,
        'input_format' => 'Y-m-d H:i:s',
        'input_format_custom' => '',
        'label_position' => 'above',
        'repeat_collapsed' => 0,
        'text_parts' => array(),
        'year_range' => '-3:+3',
      ),
      'type' => 'date_text',
      'weight' => 5,
    ),
  );

  // Exported field_instance: 'node-escapia_unit_review-field_escapia_unit_code'
  $field_instances['node-escapia_unit_review-field_escapia_unit_code'] = array(
    'bundle' => 'escapia_unit_review',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 30,
      ),
      'ical' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 29,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'node',
    'field_name' => 'field_escapia_unit_code',
    'label' => 'Escapia Unit Code',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 1,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Body');
  t('Cleanliness');
  t('Escapia Unit Code');
  t('Location');
  t('Overall Satisfaction');
  t('Property Condition');
  t('Property Manager Rejected');
  t('Recommend to Others');
  t('Reservation Number');
  t('Review Date');
  t('Reviewer Email');
  t('Reviewer ID');
  t('Reviewer Stay Dates');
  t('Services from Rental Manager');
  t('Start date - for review original date. End date - for review changed date.');
  t('Unit Reviewer Information');
  t('Unit Reviews');

  return $field_instances;
}
