<?php
/**
 * @file
 * escapia_wsclient_feeds.feeds_importer_default.inc
 */

/**
 * Implements hook_feeds_importer_default().
 */
function escapia_wsclient_feeds_feeds_importer_default() {
  $export = array();

  $feeds_importer = new stdClass();
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'escapia_rentals_calendar_availability';
  $feeds_importer->config = array(
    'name' => 'Escapia Rentals (Calendar Availability)',
    'description' => 'Imports Single Rental Property Availability Dates/Statuses values from Escapia',
    'fetcher' => array(
      'plugin_key' => 'FeedsWSClientFetcher',
      'config' => array(
        'service_operation' => 'escapia_api:UnitCalendarAvail',
        'operation_arguments' => array(
          'EVRN_UnitCalendarAvailRQ' => array(
            'UnitRef' => array(
              'PropertyManagerCode' => '',
              'UnitCode' => '',
              'UnitName' => '',
              'InfoSource' => '',
              'InternalUnitCode' => '',
              'UnitHeadline' => '',
              'PropertyURL' => '',
            ),
            'CalendarDateRange' => array(
              'DateWindowRange' => array(
                '_' => '',
                'WindowBefore' => '',
                'WindowAfter' => '',
                'CrossDateAllowedIndicator' => 'false',
              ),
              'StartDateWindow' => array(
                'EarliestDate' => '',
                'LatestDate' => '',
                'DOW' => '',
              ),
              'EndDateWindow' => array(
                'EarliestDate' => '',
                'LatestDate' => '',
                'DOW' => '',
              ),
              'Start' => '',
              'Duration' => '',
              'End' => '',
              'Release' => '',
            ),
            'ShowHolds' => '',
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
        'use_tidy' => FALSE,
        'sources' => array(
          'unit_code' => array(
            'name' => 'unit_code',
            'value' => '@UnitCode',
            'raw' => 0,
            'inner' => 0,
            'debug' => 0,
            'weight' => '0',
          ),
          'cal_start_date' => array(
            'name' => 'cal_start_date',
            'value' => 'UnitCalendarAvailSegment/@StartDate',
            'raw' => 0,
            'inner' => 0,
            'debug' => 0,
            'weight' => '1',
          ),
          'cal_end_date' => array(
            'name' => 'cal_end_date',
            'value' => 'UnitCalendarAvailSegment/@EndDate',
            'raw' => 0,
            'inner' => 0,
            'debug' => 0,
            'weight' => '2',
          ),
          'cal_days_statuses' => array(
            'name' => 'cal_days_statuses',
            'value' => 'UnitCalendarAvailSegment/DailyAvailability',
            'raw' => 0,
            'inner' => 0,
            'debug' => 0,
            'weight' => '3',
          ),
          'min_stay' => array(
            'name' => 'min_stay',
            'value' => 'UnitCalendarAvailSegment/StayRequirements/StayRequirement/@MinLOS',
            'raw' => 0,
            'inner' => 0,
            'debug' => 0,
            'weight' => '4',
          ),
        ),
        'context' => array(
          'value' => '//UnitCalendarAvailSegments',
        ),
        'display_errors' => 0,
        'source_encoding' => array(
          0 => 'auto',
        ),
        'debug_mode' => 0,
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
            'source' => 'unit_code',
            'target' => 'guid',
            'unique' => 1,
          ),
          1 => array(
            'source' => 'cal_start_date',
            'target' => 'field_escapia_availability_start:start',
            'unique' => FALSE,
          ),
          2 => array(
            'source' => 'cal_end_date',
            'target' => 'field_escapia_availability_start:end',
            'unique' => FALSE,
          ),
          3 => array(
            'source' => 'cal_days_statuses',
            'target' => 'field_escapia_avail_status_str',
            'unique' => FALSE,
          ),
        ),
        'update_existing' => '2',
        'update_non_existent' => 'skip',
        'input_format' => 'full_html',
        'skip_hash_check' => 0,
        'bundle' => 'rental',
      ),
    ),
    'content_type' => '',
    'update' => 0,
    'import_period' => '-1',
    'expire_period' => 3600,
    'import_on_create' => 0,
    'process_in_background' => 1,
  );
  $export['escapia_rentals_calendar_availability'] = $feeds_importer;

  $feeds_importer = new stdClass();
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'escapia_rentals_descriptive_info';
  $feeds_importer->config = array(
    'name' => 'Escapia Rentals (Descriptive Info)',
    'description' => 'Imports Single Rental Property values from Escapia based on UnitCode (v.1.030)',
    'fetcher' => array(
      'plugin_key' => 'FeedsWSClientFetcher',
      'config' => array(
        'service_operation' => 'escapia_api:UnitDescriptiveInfo',
        'operation_arguments' => array(
          'EVRN_UnitDescriptiveInfoRQ' => array(
            'UnitDescriptiveInfos' => array(
              0 => array(
                'UnitInfo' => array(
                  'SendData' => 'true',
                ),
                'Policies' => array(
                  'SendPolicies' => 'true',
                ),
                'UnitReviews' => array(
                  'SendReviews' => 'true',
                ),
                'Promotions' => array(
                  'SendPromotions' => 'true',
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
        'use_tidy' => FALSE,
        'sources' => array(
          'unit_code' => array(
            'name' => 'unit_code',
            'value' => '@UnitCode',
            'raw' => 0,
            'inner' => 0,
            'debug' => 0,
            'weight' => '0',
          ),
          'unit_images' => array(
            'name' => 'unit_images',
            'value' => './/*[@DimensionCategory="Original"]',
            'raw' => 0,
            'inner' => 0,
            'debug' => 0,
            'weight' => '1',
          ),
          'unit_address_street' => array(
            'name' => 'unit_address_street',
            'value' => 'UnitInfo/Address/AddressLine',
            'raw' => 0,
            'inner' => 0,
            'debug' => 0,
            'weight' => '2',
          ),
          'unit_address_city' => array(
            'name' => 'unit_address_city',
            'value' => 'UnitInfo/Address/CityName',
            'raw' => 0,
            'inner' => 0,
            'debug' => 0,
            'weight' => '3',
          ),
          'unit_address_state' => array(
            'name' => 'unit_address_state',
            'value' => 'UnitInfo/Address/StateProv/@StateCode',
            'raw' => 0,
            'inner' => 0,
            'debug' => 0,
            'weight' => '4',
          ),
          'unit_address_zip' => array(
            'name' => 'unit_address_zip',
            'value' => 'UnitInfo/Address/PostalCode',
            'raw' => 0,
            'inner' => 0,
            'debug' => 0,
            'weight' => '5',
          ),
          'unit_address_country' => array(
            'name' => 'unit_address_country',
            'value' => 'UnitInfo/Address/CountryName/@Code',
            'raw' => 0,
            'inner' => 0,
            'debug' => 0,
            'weight' => '6',
          ),
          'unit_beds' => array(
            'name' => 'unit_beds',
            'value' => 'UnitInfo/CategoryCodes/RoomInfo[@CodeDetail="Bedrooms"]/@Quantity',
            'raw' => 0,
            'inner' => 0,
            'debug' => 0,
            'weight' => '7',
          ),
        ),
        'context' => array(
          'value' => '//UnitDescriptiveContents/UnitDescriptiveContent',
        ),
        'display_errors' => 0,
        'source_encoding' => array(
          0 => 'auto',
        ),
        'debug_mode' => 0,
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
            'source' => 'unit_code',
            'target' => 'guid',
            'unique' => 1,
          ),
          1 => array(
            'source' => 'unit_images',
            'target' => 'field_escapia_unit_images:uri',
            'unique' => FALSE,
          ),
          2 => array(
            'source' => 'unit_beds',
            'target' => 'field_escapia_unit_beds',
            'unique' => FALSE,
          ),
          3 => array(
            'source' => 'unit_address_street',
            'target' => 'field_esapia_unit_address:thoroughfare',
            'unique' => FALSE,
          ),
          4 => array(
            'source' => 'unit_address_city',
            'target' => 'field_esapia_unit_address:locality',
            'unique' => FALSE,
          ),
          5 => array(
            'source' => 'unit_address_state',
            'target' => 'field_esapia_unit_address:administrative_area',
            'unique' => FALSE,
          ),
          6 => array(
            'source' => 'unit_address_zip',
            'target' => 'field_esapia_unit_address:postal_code',
            'unique' => FALSE,
          ),
          7 => array(
            'source' => 'unit_address_country',
            'target' => 'field_esapia_unit_address:country',
            'unique' => FALSE,
          ),
        ),
        'update_existing' => '2',
        'update_non_existent' => 'skip',
        'input_format' => 'full_html',
        'skip_hash_check' => 0,
        'bundle' => 'rental',
      ),
    ),
    'content_type' => '',
    'update' => 0,
    'import_period' => '-1',
    'expire_period' => 3600,
    'import_on_create' => 0,
    'process_in_background' => 1,
  );
  $export['escapia_rentals_descriptive_info'] = $feeds_importer;

  $feeds_importer = new stdClass();
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'escapia_rentals_units_search';
  $feeds_importer->config = array(
    'name' => 'Escapia Rentals (Units Search)',
    'description' => 'Gets a list of all the units from Escapia API',
    'fetcher' => array(
      'plugin_key' => 'FeedsWSClientFetcher',
      'config' => array(
        'service_operation' => 'escapia_api:UnitSearch',
        'operation_arguments' => array(
          'EVRN_UnitSearchRQ' => array(
            'Criteria' => array(
              'Criterion' => array(
                0 => array(
                  'Region' => array(
                    'CountryCode' => '',
                    'PostalCode' => '',
                  ),
                  'LastMinuteDiscountRange' => array(
                    'MinAdvanceBookingOffset' => '',
                    'MaxAdvanceBookingOffset' => '',
                    'MinDiscountPercent' => '',
                    'MaxDiscountPercent' => '',
                  ),
                  'Address' => array(
                    'StreetNmbr' => array(
                      '_' => array(
                        '_' => '',
                        'PO_Box' => '',
                      ),
                      'StreetNmbrSuffix' => '',
                      'StreetDirection' => '',
                      'RuralRouteNmbr' => '',
                    ),
                    'BldgRoom' => array(
                      '_' => '',
                      'BldgNameIndicator' => 'false',
                    ),
                    'AddressLine' => '',
                    'CityName' => '',
                    'PostalCode' => '',
                    'County' => '',
                    'StateProv' => array(
                      '_' => '',
                      'StateCode' => '',
                    ),
                    'CountryName' => array(
                      '_' => 'US',
                      'Code' => 'US',
                    ),
                    'FormattedInd' => 'false',
                    'ShareSynchInd' => '',
                    'ShareMarketInd' => '',
                    'Type' => '',
                  ),
                  'UnitRef' => array(
                    'PropertyManagerCode' => '',
                    'UnitCode' => '',
                    'UnitName' => '',
                    'InfoSource' => '',
                    'InternalUnitCode' => '',
                    'UnitHeadline' => '',
                    'PropertyURL' => '',
                  ),
                  'UnitAmenity' => array(
                    'Code' => '',
                    'Quantity' => '',
                  ),
                ),
                1 => array(
                  'Region' => array(
                    'CountryCode' => '',
                    'PostalCode' => '',
                  ),
                  'LastMinuteDiscountRange' => array(
                    'MinAdvanceBookingOffset' => '',
                    'MaxAdvanceBookingOffset' => '',
                    'MinDiscountPercent' => '',
                    'MaxDiscountPercent' => '',
                  ),
                  'Address' => array(
                    'StreetNmbr' => array(
                      '_' => array(
                        '_' => '',
                        'PO_Box' => '',
                      ),
                      'StreetNmbrSuffix' => '',
                      'StreetDirection' => '',
                      'RuralRouteNmbr' => '',
                    ),
                    'BldgRoom' => array(
                      '_' => '',
                      'BldgNameIndicator' => 'false',
                    ),
                    'AddressLine' => '',
                    'CityName' => '',
                    'PostalCode' => '',
                    'County' => '',
                    'StateProv' => array(
                      '_' => '',
                      'StateCode' => '',
                    ),
                    'CountryName' => array(
                      '_' => '',
                      'Code' => '',
                    ),
                    'FormattedInd' => 'false',
                    'ShareSynchInd' => '',
                    'ShareMarketInd' => '',
                    'Type' => '',
                  ),
                  'UnitRef' => array(
                    'PropertyManagerCode' => '',
                    'UnitCode' => '',
                    'UnitName' => '',
                    'InfoSource' => '',
                    'InternalUnitCode' => '',
                    'UnitHeadline' => '',
                    'PropertyURL' => '',
                  ),
                  'UnitAmenity' => array(
                    'Code' => '',
                    'Quantity' => '',
                  ),
                ),
                2 => array(
                  'Region' => array(
                    'CountryCode' => '',
                    'PostalCode' => '',
                  ),
                  'LastMinuteDiscountRange' => array(
                    'MinAdvanceBookingOffset' => '',
                    'MaxAdvanceBookingOffset' => '',
                    'MinDiscountPercent' => '',
                    'MaxDiscountPercent' => '',
                  ),
                  'Address' => array(
                    'StreetNmbr' => array(
                      '_' => array(
                        '_' => '',
                        'PO_Box' => '',
                      ),
                      'StreetNmbrSuffix' => '',
                      'StreetDirection' => '',
                      'RuralRouteNmbr' => '',
                    ),
                    'BldgRoom' => array(
                      '_' => '',
                      'BldgNameIndicator' => 'false',
                    ),
                    'AddressLine' => '',
                    'CityName' => '',
                    'PostalCode' => '',
                    'County' => '',
                    'StateProv' => array(
                      '_' => '',
                      'StateCode' => '',
                    ),
                    'CountryName' => array(
                      '_' => '',
                      'Code' => '',
                    ),
                    'FormattedInd' => 'false',
                    'ShareSynchInd' => '',
                    'ShareMarketInd' => '',
                    'Type' => '',
                  ),
                  'UnitRef' => array(
                    'PropertyManagerCode' => '',
                    'UnitCode' => '',
                    'UnitName' => '',
                    'InfoSource' => '',
                    'InternalUnitCode' => '',
                    'UnitHeadline' => '',
                    'PropertyURL' => '',
                  ),
                  'UnitAmenity' => array(
                    'Code' => '',
                    'Quantity' => '',
                  ),
                ),
              ),
              'AvailableOnlyIndicator' => 'false',
            ),
            'MaxResponses' => '',
            'SortOrder' => '',
            'SendRateDetails' => 'true',
            'SendUnitSummary' => 'true',
            'PictureSize' => 'Thumbnail',
            'ResponseType' => 'PropertyList',
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
      'plugin_key' => 'FeedsWSClientParser',
      'config' => array(
        'context' => '|Units|Unit',
        'sources' => array(),
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
            'source' => 'UnitCode',
            'target' => 'guid',
            'unique' => 1,
          ),
          1 => array(
            'source' => 'UnitName',
            'target' => 'title',
            'unique' => FALSE,
          ),
          2 => array(
            'source' => 'UnitCode',
            'target' => 'field_escapia_unit_code',
            'unique' => FALSE,
          ),
        ),
        'update_existing' => '2',
        'update_non_existent' => 'unpublish',
        'input_format' => 'full_html',
        'skip_hash_check' => 1,
        'bundle' => 'rental',
      ),
    ),
    'content_type' => '',
    'update' => 0,
    'import_period' => '0',
    'expire_period' => 3600,
    'import_on_create' => 1,
    'process_in_background' => 1,
  );
  $export['escapia_rentals_units_search'] = $feeds_importer;

  return $export;
}
