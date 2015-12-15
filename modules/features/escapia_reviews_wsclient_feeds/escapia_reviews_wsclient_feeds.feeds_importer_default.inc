<?php
/**
 * @file
 * escapia_reviews_wsclient_feeds.feeds_importer_default.inc
 */

/**
 * Implements hook_feeds_importer_default().
 */
function escapia_reviews_wsclient_feeds_feeds_importer_default() {
  $export = array();

  $feeds_importer = new stdClass();
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'escapia_api_rentals_reviews';
  $feeds_importer->config = array(
    'name' => 'Escapia Rentals (Reviews)',
    'description' => 'Import of Escapia Unit Reviews',
    'fetcher' => array(
      'plugin_key' => 'FeedsWSClientFetcher',
      'config' => array(
        'service_operation' => 'escapia_api:UnitDescriptiveInfo',
        'operation_arguments' => array(
          'EVRN_UnitDescriptiveInfoRQ' => array(
            'UnitDescriptiveInfos' => array(
              0 => array(
                'UnitInfo' => array(
                  'SendData' => 'false',
                ),
                'Policies' => array(
                  'SendPolicies' => 'false',
                ),
                'UnitReviews' => array(
                  'SendReviews' => 'false',
                ),
                'Promotions' => array(
                  'SendPromotions' => 'false',
                ),
                'PropertyManagerCode' => '',
                'UnitCode' => '',
                'UnitName' => '',
                'InfoSource' => '',
                'InternalUnitCode' => '',
                'UnitHeadline' => '',
                'PropertyURL' => '',
                'StateCodeList' => '',
                'CountryCodeList' => '',
                'BrandCodeList' => '',
                'MoreDataEchoToken' => '',
                'UpdatedAfter' => '',
              ),
              1 => array(
                'UnitInfo' => array(
                  'SendData' => 'false',
                ),
                'Policies' => array(
                  'SendPolicies' => 'false',
                ),
                'UnitReviews' => array(
                  'SendReviews' => 'false',
                ),
                'Promotions' => array(
                  'SendPromotions' => 'false',
                ),
                'PropertyManagerCode' => '',
                'UnitCode' => '',
                'UnitName' => '',
                'InfoSource' => '',
                'InternalUnitCode' => '',
                'UnitHeadline' => '',
                'PropertyURL' => '',
                'StateCodeList' => '',
                'CountryCodeList' => '',
                'BrandCodeList' => '',
                'MoreDataEchoToken' => '',
                'UpdatedAfter' => '',
              ),
              2 => array(
                'UnitInfo' => array(
                  'SendData' => 'false',
                ),
                'Policies' => array(
                  'SendPolicies' => 'false',
                ),
                'UnitReviews' => array(
                  'SendReviews' => 'false',
                ),
                'Promotions' => array(
                  'SendPromotions' => 'false',
                ),
                'PropertyManagerCode' => '',
                'UnitCode' => '',
                'UnitName' => '',
                'InfoSource' => '',
                'InternalUnitCode' => '',
                'UnitHeadline' => '',
                'PropertyURL' => '',
                'StateCodeList' => '',
                'CountryCodeList' => '',
                'BrandCodeList' => '',
                'MoreDataEchoToken' => '',
                'UpdatedAfter' => '',
              ),
            ),
            'SummaryOnly' => 'false',
            'POS' => array(
              0 => array(
                'RequestorID' => array(
                  'ID' => '',
                  'MessagePassword' => '',
                ),
                'BookingChannel' => array(
                  'CompanyName' => array(
                    '_' => '',
                    'CompanyShortName' => '',
                    'TravelSector' => '',
                    'Code' => '',
                    'CodeContext' => '',
                    'Division' => '',
                    'Department' => '',
                  ),
                  'Type' => '',
                  'Primary' => 'false',
                ),
              ),
              1 => array(
                'RequestorID' => array(
                  'ID' => '',
                  'MessagePassword' => '',
                ),
                'BookingChannel' => array(
                  'CompanyName' => array(
                    '_' => '',
                    'CompanyShortName' => '',
                    'TravelSector' => '',
                    'Code' => '',
                    'CodeContext' => '',
                    'Division' => '',
                    'Department' => '',
                  ),
                  'Type' => '',
                  'Primary' => 'false',
                ),
              ),
              2 => array(
                'RequestorID' => array(
                  'ID' => '',
                  'MessagePassword' => '',
                ),
                'BookingChannel' => array(
                  'CompanyName' => array(
                    '_' => '',
                    'CompanyShortName' => '',
                    'TravelSector' => '',
                    'Code' => '',
                    'CodeContext' => '',
                    'Division' => '',
                    'Department' => '',
                  ),
                  'Type' => '',
                  'Primary' => 'false',
                ),
              ),
            ),
            'Version' => '1.0',
          ),
        ),
        'raw' => 1,
      ),
    ),
    'parser' => array(
      'plugin_key' => 'FeedsExXml',
      'config' => array(
        'context' => array(
          'value' => '//UnitDescriptiveContents/UnitDescriptiveContent/UnitReviews//UnitReview',
        ),
        'sources' => array(
          'unit_code' => array(
            'name' => 'unit_code',
            'value' => './/@UnitCode',
            'raw' => 0,
            'inner' => 0,
            'debug' => 0,
            'weight' => '0',
          ),
          'unit_review_title' => array(
            'name' => 'unit_review_title',
            'value' => '@Title',
            'raw' => 0,
            'inner' => 0,
            'debug' => 0,
            'weight' => '1',
          ),
          'unit_review_date' => array(
            'name' => 'unit_review_date',
            'value' => '@ReviewedDate',
            'raw' => 0,
            'inner' => 0,
            'debug' => 0,
            'weight' => '2',
          ),
          'unit_review_last_updated' => array(
            'name' => 'unit_review_last_updated',
            'value' => '@LastUpdated',
            'raw' => 0,
            'inner' => 0,
            'debug' => 0,
            'weight' => '3',
          ),
          'unit_review_reviewer_id' => array(
            'name' => 'unit_review_reviewer_id',
            'value' => '@ReviewerID',
            'raw' => 0,
            'inner' => 0,
            'debug' => 0,
            'weight' => '4',
          ),
          'unit_review_reviewer_name' => array(
            'name' => 'unit_review_reviewer_name',
            'value' => '@ReviewerName',
            'raw' => 0,
            'inner' => 0,
            'debug' => 0,
            'weight' => '5',
          ),
          'unit_review_reviewer_city' => array(
            'name' => 'unit_review_reviewer_city',
            'value' => '@ReviewerCity',
            'raw' => 0,
            'inner' => 0,
            'debug' => 0,
            'weight' => '6',
          ),
          'unit_review_reviewer_state' => array(
            'name' => 'unit_review_reviewer_state',
            'value' => '@ReviewerState',
            'raw' => 0,
            'inner' => 0,
            'debug' => 0,
            'weight' => '7',
          ),
          'unit_review_reviewer_country' => array(
            'name' => 'unit_review_reviewer_country',
            'value' => '@ReviewerCountry',
            'raw' => 0,
            'inner' => 0,
            'debug' => 0,
            'weight' => '8',
          ),
          'unit_review_reviewer_email' => array(
            'name' => 'unit_review_reviewer_email',
            'value' => '@ReviewerEmail',
            'raw' => 0,
            'inner' => 0,
            'debug' => 0,
            'weight' => '9',
          ),
          'unit_review_reviewer_checkin' => array(
            'name' => 'unit_review_reviewer_checkin',
            'value' => '@CheckIn',
            'raw' => 0,
            'inner' => 0,
            'debug' => 0,
            'weight' => '10',
          ),
          'unit_review_reviewer_checkout' => array(
            'name' => 'unit_review_reviewer_checkout',
            'value' => '@CheckOut',
            'raw' => 0,
            'inner' => 0,
            'debug' => 0,
            'weight' => '11',
          ),
          'unit_review_rejected' => array(
            'name' => 'unit_review_rejected',
            'value' => '@PropertyManagerRejected',
            'raw' => 0,
            'inner' => 0,
            'debug' => 0,
            'weight' => '12',
          ),
          'unit_review_reviewer_reserv_num' => array(
            'name' => 'unit_review_reviewer_reserv_num',
            'value' => '@ReservationNumber',
            'raw' => 0,
            'inner' => 0,
            'debug' => 0,
            'weight' => '13',
          ),
          'unit_review_category' => array(
            'name' => 'unit_review_category',
            'value' => 'ReviewScore/@CategoryID',
            'raw' => 0,
            'inner' => 0,
            'debug' => 0,
            'weight' => '15',
          ),
          'unit_review_comment' => array(
            'name' => 'unit_review_comment',
            'value' => 'ReviewComment/@Comment',
            'raw' => 0,
            'inner' => 0,
            'debug' => 0,
            'weight' => '16',
          ),
          'unit_review_overall_score' => array(
            'name' => 'unit_review_overall_score',
            'value' => 'ReviewScore[@CategoryID="1000"]/@Score',
            'raw' => 0,
            'inner' => 0,
            'debug' => 0,
            'weight' => '17',
          ),
          'unit_review_services_score' => array(
            'name' => 'unit_review_services_score',
            'value' => 'ReviewScore[@CategoryID="1001"]/@Score',
            'raw' => 0,
            'inner' => 0,
            'debug' => 0,
            'weight' => '18',
          ),
          'unit_review_cleanliness_score' => array(
            'name' => 'unit_review_cleanliness_score',
            'value' => 'ReviewScore[@CategoryID="1002"]/@Score',
            'raw' => 0,
            'inner' => 0,
            'debug' => 0,
            'weight' => '19',
          ),
          'unit_review_location_score' => array(
            'name' => 'unit_review_location_score',
            'value' => 'ReviewScore[@CategoryID="1003"]/@Score',
            'raw' => 0,
            'inner' => 0,
            'debug' => 0,
            'weight' => '20',
          ),
          'unit_review_condition_score' => array(
            'name' => 'unit_review_condition_score',
            'value' => 'ReviewScore[@CategoryID="1005"]/@Score',
            'raw' => 0,
            'inner' => 0,
            'debug' => 0,
            'weight' => '21',
          ),
          'unit_review_recommend_score' => array(
            'name' => 'unit_review_recommend_score',
            'value' => 'ReviewScore[@CategoryID="1006"]/@Score',
            'raw' => 0,
            'inner' => 0,
            'debug' => 0,
            'weight' => '22',
          ),
        ),
        'display_errors' => 0,
        'debug_mode' => 0,
        'source_encoding' => array(
          0 => 'auto',
        ),
        'use_tidy' => FALSE,
      ),
    ),
    'processor' => array(
      'plugin_key' => 'FeedsUniqueNodeProcessor',
      'config' => array(
        'expire' => '-1',
        'author' => '1',
        'authorize' => 1,
        'mappings' => array(
          0 => array(
            'source' => 'unit_review_reviewer_reserv_num',
            'target' => 'guid',
            'unique' => 1,
          ),
          1 => array(
            'source' => 'unit_code',
            'target' => 'field_escapia_unit_code',
            'unique' => FALSE,
          ),
          2 => array(
            'source' => 'unit_review_title',
            'target' => 'title',
            'unique' => FALSE,
          ),
          3 => array(
            'source' => 'unit_review_comment',
            'target' => 'body',
            'unique' => FALSE,
          ),
          4 => array(
            'source' => 'unit_review_reviewer_reserv_num',
            'target' => 'field_escapia_reviewer_res_id',
            'unique' => FALSE,
          ),
          5 => array(
            'source' => 'unit_review_date',
            'target' => 'field_escapia_review_date:start',
            'unique' => FALSE,
          ),
          6 => array(
            'source' => 'unit_review_last_updated',
            'target' => 'field_escapia_review_date:end',
            'unique' => FALSE,
          ),
          7 => array(
            'source' => 'unit_review_rejected',
            'target' => 'field_escapia_review_rejected',
            'unique' => FALSE,
          ),
          8 => array(
            'source' => 'unit_review_reviewer_checkin',
            'target' => 'field_escapia_reviewer_stay_date:start',
            'unique' => FALSE,
          ),
          9 => array(
            'source' => 'unit_review_reviewer_checkout',
            'target' => 'field_escapia_reviewer_stay_date:end',
            'unique' => FALSE,
          ),
          10 => array(
            'source' => 'unit_review_reviewer_name',
            'target' => 'field_escapia_reviewer_info:name_line',
            'unique' => FALSE,
          ),
          11 => array(
            'source' => 'unit_review_reviewer_city',
            'target' => 'field_escapia_reviewer_info:locality',
            'unique' => FALSE,
          ),
          12 => array(
            'source' => 'unit_review_reviewer_state',
            'target' => 'field_escapia_reviewer_info:administrative_area',
            'unique' => FALSE,
          ),
          13 => array(
            'source' => 'unit_review_reviewer_country',
            'target' => 'field_escapia_reviewer_info:country',
            'unique' => FALSE,
          ),
          14 => array(
            'source' => 'unit_review_reviewer_email',
            'target' => 'field_escapia_reviewer_email',
            'unique' => FALSE,
          ),
          15 => array(
            'source' => 'unit_review_reviewer_id',
            'target' => 'field_escapia_reviewer_id',
            'unique' => FALSE,
          ),
          16 => array(
            'source' => 'unit_review_location_score',
            'target' => 'field_esc_review_location_rate:value',
            'unique' => FALSE,
          ),
          17 => array(
            'source' => 'unit_review_cleanliness_score',
            'target' => 'field_esc_review_clean_rate:value',
            'unique' => FALSE,
          ),
          18 => array(
            'source' => 'unit_review_condition_score',
            'target' => 'field_esc_review_condition_rate:value',
            'unique' => FALSE,
          ),
          19 => array(
            'source' => 'unit_review_overall_score',
            'target' => 'field_esc_review_overall_rate:value',
            'unique' => FALSE,
          ),
          20 => array(
            'source' => 'unit_review_recommend_score',
            'target' => 'field_esc_review_recommend_rate:value',
            'unique' => FALSE,
          ),
          21 => array(
            'source' => 'unit_review_services_score',
            'target' => 'field_esc_review_services_rate:value',
            'unique' => FALSE,
          ),
        ),
        'update_existing' => '2',
        'update_non_existent' => 'skip',
        'input_format' => 'plain_text',
        'skip_hash_check' => 0,
        'bundle' => 'escapia_unit_review',
      ),
    ),
    'content_type' => '',
    'update' => 0,
    'import_period' => '-1',
    'expire_period' => 3600,
    'import_on_create' => 1,
    'process_in_background' => 1,
  );
  $export['escapia_api_rentals_reviews'] = $feeds_importer;

  return $export;
}
