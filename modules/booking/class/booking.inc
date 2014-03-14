<?php

class EscapiaBooking extends EscapiaAPI implements EscapiaBookingAPIInterface, EscapiaHomeAwayPaymentIslandInterface {
  public function __construct(EscapiaConnection $connection) {
    if (empty($connection->hapi_endpoint)) {
      throw new EscapiaAPIException(EscapiaAPIException::NO_HAPI_ENDPOINT_PROVIDED);
    }

    if (empty($connection->hapi_client_id)) {
      throw new EscapiaAPIException(EscapiaAPIException::NO_HAPI_CLIENT_ID);
    }

    if (empty($connection->hapi_api_key)) {
      throw new EscapiaAPIException(EscapiaAPIException::NO_HAPI_API_KEY);
    }

    $this->connection = $connection;
  }

  /**
   * Create a booking entry in Escapia.
   * @param $unit_code
   */
  public function createUnitBooking($unit_code) {

  }

  // @todo: finish this jazz
  public static function processRatesFromResponse($soap_response) {
    return $foo;
  }

  /**
   * Generates a hashed digest message for the token request.
   * @param $api_key
   * @return string
   * @see EscapiaBooking::generateCreditCardToken()
   */
  public static function generateDigest($api_key) {
    return hash('sha256', mb_convert_encoding(self::getTimeInMilliseconds() . $api_key, 'UTF-8'));
  }

  /**
   * Returns the current UTC time in milliseconds.
   * @return float
   */
  public static function getTimeInMilliseconds() {
    return round(microtime(TRUE) * 1000);
  }

  /**
   * Requests and returns credit card token from HAPI.
   * @param EscapiaConnection $connection
   * @param $credit_card_number
   * @return string|bool
   */
  public static function generateCreditCardToken(EscapiaConnection $connection, $credit_card_number) {
    $body = '<tokenForm><tokenType>CC</tokenType><value>' . $credit_card_number . '</value></tokenForm>';
    $url =  $connection->hapi_endpoint . '?' . drupal_http_build_query(array('time' => round(microtime(TRUE) * 1000), 'digest' => self::generateDigest($connection->hapi_api_key), 'clientId' => $connection->hapi_client_id));
    $response = drupal_http_request($url, array('method' => 'POST', 'data' => $body, 'headers' => array('Content-Type' => 'application/xml; charset=UTF-8')));

    if ($response->code == 201 || $response->status_message == 'Created') {
      $data = simplexml_load_string($response->data);
      $token = current($data->attributes());
      return $token['id'];
    }

    return FALSE;
  }
}