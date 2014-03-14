<?php

/**
 * Main class that interacts with the EscapiaAPI.
 */
class EscapiaAPI implements EscapiaAPIInterface {
  const API_VERSION = '1.030';
  const MAX_RESPONSES = 10000;
  const SOAP_NAMESPACE = 'http://www.escapia.com/EVRN/2007/02';
  const ADULT_AGE_CODE = 10;
  const CHILD_AGE_CODE = 8;

  protected $connection, $client;

  public function __construct(EscapiaConnection $connection) {
    if (empty($connection->wsdl)) {
      throw new EscapiaAPIException(EscapiaAPIException::NO_WSDL_PROVIDED);
    }

    if (empty($connection->username)) {
      throw new EscapiaAPIException(EscapiaAPIException::NO_USERNAME);
    }

    if (empty($connection->password)) {
      throw new EscapiaAPIException(EscapiaAPIException::NO_PASSWORD);
    }

    $this->connection = $connection;
    $this->client = new SoapClient($connection->wsdl, array('trace' => TRUE));
  }

  /**
   * Return the required POS parameter for requests.
   * @return array
   */
  protected function getAuthenticationParameter() {
    return array('Source' => array('RequestorID' => array('ID' => $this->connection->username, 'MessagePassword' => $this->connection->password)));
  }

  /**
   * Query for unit details in Escapia.
   * @param $unit_code
   * @return mixed
   */
  public function getUnitInfo($unit_code) {
    $response = $this->client->UnitDescriptiveInfo(
      array(
        'Version' => self::API_VERSION,
        'POS' => $this->getAuthenticationParameter(),
        'UnitDescriptiveInfos' =>
          array(
            'UnitDescriptiveInfo' =>
              array(
                'UnitCode' => $unit_code,
              )
          )
      )
    );

    return $this->parseResponse($response);
  }

  /**
   * Check availability on the specified unit by start and end date.
   * @param $unit_code
   * @param $start_date
   * @param $end_date
   * @param $duration
   * @return mixed
   */
  public function getUnitRateRange($unit_code, $start_date, $end_date, $duration = 7) {
    $response = $this->client->UnitCalendarAvail(
      array(
        'Version' => self::API_VERSION,
        'POS' => $this->getAuthenticationParameter(),
        'UnitRef' =>
          array(
            'UnitCode' => $unit_code,
          ),
        'CalendarDateRange' =>
          array(
            'Start' => format_date($start_date, 'custom', 'm/d/Y'),
            'End' => format_date($end_date, 'custom', 'm/d/Y'),
            'Duration' => $duration,
          )
      )
    );

    return $this->parseResponse($response);
  }

  /**
   * Queries for rate and policy information in Escapia. If the requested range is available, a result is returned, FALSE otherwise.
   * @param $unit_code
   * @param $start_date
   * @param $end_date
   * @param int $adults
   * @param int $children
   * @return bool|mixed
   */
  public function getUnitQuoteRequest($unit_code, $start_date, $end_date, $adults = 2, $children = 0) {
    $response = $this->client->UnitStay(
      array(
        'Version' => self::API_VERSION,
        'POS' => $this->getAuthenticationParameter(),
        'UnitStay' => array(
          'UnitRef' =>
            array(
              'UnitCode' => $unit_code,
            ),
          'BasicUnitInfo' => array('SendData' => FALSE),
          'StayDateRange' =>
            array(
              'Start' => format_date($start_date, 'custom', 'm/d/Y'),
              'End' => format_date($end_date, 'custom', 'm/d/Y'),
            ),
          'GuestCounts' =>
            array(
              'GuestCount' =>
                array(
                  'AgeQualifyingCode' => self::ADULT_AGE_CODE,
                  'Count' => $adults,
                )
            ),
            array(
              'GuestCount' =>
                array(
                  'AgeQualifyingCode' => self::CHILD_AGE_CODE,
                  'Count' => $children,
                )
            )
        )
      )
    );

    return $this->parseResponse($response);
  }

  /**
   * Perform a search based on a number of criteria.
   * If you are not searching by UnitCode, note that properties will only show in results if they meet this initial criteria:
   *   - Has photos
   *   - Has rates for a full year
   *   - Is attached to a rate Season
   *   - Has a connected owner contract
   *   - Is Active
   *   - Is published to network partners
   * @param $criteria
   * @return mixed
   */
  public function unitSearch($criteria = array()) {
    $response = $this->client->UnitSearch(
      array(
        'MaxResponses' => self::MAX_RESPONSES,
        'Version' => self::API_VERSION,
        'POS' => $this->getAuthenticationParameter(),
        'Criteria' => array(),
          // @todo: we should accept an argument which is basically an array of arrays for Criteria for some flexibility.
      )
    );

    return $this->parseResponse($response);
  }

  /**
   * Obtains ALL the available units from Escapia.
   * Note that properties will only show in results if they meet this initial criteria:
   *   - Has photos
   *   - Has rates for a full year
   *   - Is attached to a rate Season
   *   - Has a connected owner contract
   *   - Is Active
   *   - Is published to network partners
   * @return mixed
   */
  public function getAllUnits() {
    $response = $this->client->UnitSearch(
      array(
        'MaxResponses' => self::MAX_RESPONSES,
        'Version' => self::API_VERSION,
        'POS' => $this->getAuthenticationParameter(),
        'Criteria' =>
          array(
            'Criterion' => array('LastUpdated' => date('Y-m-d\TH:i:s\Z', REQUEST_TIME + 86400)),
            'Criterion' => array(
              'Region' => array(
                'CountryCode' => 'US',
              ),
            ),
          )
      )
    );

    return $this->parseResponse($response);
  }

  public function getUpdatedUnits($last_updated = REQUEST_TIME) {
    $response = $this->client->UnitDescriptiveInfo(
      array(
        'Version' => self::API_VERSION,
        'POS' => $this->getAuthenticationParameter(),
        'UnitDescriptiveInfos' =>
          array(
            'UnitDescriptiveInfo' =>
              array(
                'LastUpdated' => DateTime::createFromFormat('Y-m-d\TH:i:sZ', $last_updated),
              )
          )
      )
    );

    return $this->parseResponse($response);
  }

  /**
   * If the SOAP request was successful, Escapia returns a 'Success' item in the response.
   * @param $response
   * @return bool
   */
  public function hasError($response) {
    return isset($response->Success) ? FALSE : TRUE;
  }

  /**
   * Log errors returned in the SOAP response.
   * @param $errors
   */
  protected function logErrors($errors) {
    foreach ($errors as $error) {
      watchdog('escapia_api', 'Error: @error -- Error Type: @type -- Error Code: @code', array('@error' => $error->_, '@type' => $error->Type, '@code' => $error->Code), WATCHDOG_ERROR);
    }
  }

  /**
   * Check the response for errors before returning it to the caller.
   * Also assign the connection information and raw XML response.
   * @param $response
   * @return bool
   */
  protected function parseResponse($response) {
    if ($this->hasError($response)) {
      $this->logErrors($response->Errors);
      return FALSE;
    }

    // meh.. not a fan of this but I need to pass it on for now.
    // @todo: find a better way to set this information
    $response->connection = $this->connection;
    $response->xmlResponse = $this->client->__getLastResponse();

    return $response;
  }
}

class EscapiaAPIException extends Exception {
  const BAD_AUTHENTICATION = 100;
  const NO_USERNAME = 101;
  const NO_PASSWORD = 102;
  const NO_WSDL_PROVIDED = 200;
  const NO_HAPI_ENDPOINT_PROVIDED = 300;
  const NO_HAPI_CLIENT_ID = 301;
  const NO_HAPI_API_KEY = 302;

  public function __construct($error_code = 0) {
    parent::__construct(self::getErrorMessage($error_code), $error_code);
  }

  public static function getErrorMessage($error_code) {
    switch($error_code) {
      case self::BAD_AUTHENTICATION:
        return 'The authentication username/password is invalid.';
        break;
      case self::NO_USERNAME:
        return 'The username for the connection was not provided.';
        break;
      case self::NO_PASSWORD:
        return 'The password for the connection was not provided.';
        break;
      case self::NO_WSDL_PROVIDED:
        return 'A WSDL URL was not provided by the Escapia Connection entity.';
        break;
      case self::NO_HAPI_ENDPOINT_PROVIDED:
        return 'No HAPI endpoint URL was provided in the connection object.';
        break;
      case self::NO_HAPI_CLIENT_ID:
        return 'No HAPI client ID was provided in the connection object.';
        break;
      case self::NO_HAPI_API_KEY:
        return 'No HAPI API key was provided in the connection object.';
        break;
      default:
        return 'An unexpected/undefined error has occurred.';
        break;
    }
  }
}