<?php

/**
 * Main class that interacts with the EscapiaAPI.
 */
class EscapiaAPI {
  const API_VERSION = '1.030';
  const MAX_RESPONSES = 10000;
  const SOAP_NAMESPACE = 'http://www.escapia.com/EVRN/2007/02';

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

    $this->client = new SoapClient($connection->wsdl, array('trace' => TRUE));
    $this->connection = $connection;
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
  public function unitInfo($unit_code) {
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
   * @return mixed
   */
  public function unitRateRange($unit_code, $start_date, $end_date) {
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
          )
      )
    );

    return $this->parseResponse($response);
  }

  /**
   * Perform a search based on a number of criteria.
   * @param $criteria
   * @return mixed
   */
  public function unitSearch($criteria = array()) {
    $response = $this->client->UnitSearch(
      array(
        'MaxResponses' => self::MAX_RESPONSES, // @todo: this should be a variable maybe?
        'Version' => self::API_VERSION,
        'POS' => $this->getAuthenticationParameter(),
        'Criteria' =>
          // @todo: we should accept an argument which is basically an array of arrays for Criteria for some flexibility
          array(
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

  /**
   * Obtain all the available units from Escapia. Useful for importing data.
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
   * @param $response
   * @return bool
   */
  protected function parseResponse($response) {
    if ($this->hasError($response)) {
      $this->logErrors($response->Errors);
      return FALSE;
    }

    // meh.. not a fan of this but I need to pass it on for now.
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
      default:
        return 'An unexpected/undefined error has occurred.';
        break;
    }
  }
}