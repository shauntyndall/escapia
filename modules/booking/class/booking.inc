<?php

class EscapiaAPIBooking /*extends EscapiaAPI*/ extends EscapiaAPIImport implements EscapiaAPIBookingInterface, EscapiaAPIHomeAwayPaymentIslandInterface {
  public function __construct() {
//  public function __construct(EscapiaConnection $connection) {
//    if (empty($connection->hapi_endpoint)) {
//      throw new EscapiaAPIException(EscapiaAPIException::NO_HAPI_ENDPOINT_PROVIDED);
//    }
//
//    if (empty($connection->hapi_client_id)) {
//      throw new EscapiaAPIException(EscapiaAPIException::NO_HAPI_CLIENT_ID);
//    }
//
//    if (empty($connection->hapi_api_key)) {
//      throw new EscapiaAPIException(EscapiaAPIException::NO_HAPI_API_KEY);
//    }

    parent::__construct();
//    parent::__construct($connection);
  }

  /**
   * Sends a create booking request to Escapia.
   * @param $reservation
   * @return array
   */
  public function createUnitBooking($reservation) {
    if(!$card_token = self::generateCreditCardToken($reservation->payment['cc_number'])) {
      return false;
    }

    $comments = array();
    if (isset($reservation->optional_fees)) {
      foreach ($reservation->optional_fees as $key => $fee) {
        if ($key !== $fee) {
          $comments['Comment'][]['Text'] = 'Customer has requested NOT to accept ' . $reservation->optional_fees[$key];
        }
        else {
          $comments['Comment'][]['Text'] = 'Customer has accepted the ' . $reservation->optional_fees[$key] . ' fee.';
        }
      }
    }

    $escapia_service = wsclient_service_load('escapia_api');
    $args =  array('EVRN_UnitResRQ' =>
      array(
        'TransactionIdentifier' => bin2hex(mcrypt_create_iv(22, MCRYPT_DEV_URANDOM)),
        'Version' => variable_get('escapia_api_schema_version', '1.0'),
        'POS' => array(array('RequestorID' => array('ID' => variable_get('escapia_api_username', ''), 'MessagePassword' =>variable_get('escapia_api_userpass', '')))),
        'UnitReservations' => array(
          'UnitReservation' => array(
            'UnitStays' => array(
              'UnitStay' => array(
                'BasicUnitInfo' => $reservation->quote_as_array['BasicUnitInfo'],
                'DepositPayments' => $reservation->quote_as_array['DepositPayments'],
                'GuestCounts' => $reservation->quote_as_array['GuestCounts'],
                'TimeSpan' => $reservation->quote_as_array['TimeSpan'],
                'Total' => $reservation->quote_as_array['Total'],
                'Comments' => $comments,
              ),
            ),
            'ResGuests' => array(
              'ResGuest' => array(
                'ResGuestRPH' => 1,
                'Profiles' => array(
                  'ProfileInfo' => array(
                    'Profile' => array(
                      'ProfileType' => 1,
                      'Customer' => array(
                        'PersonName' => array(
                          'GivenName' => $reservation->contact['first_name'],
                          'Surname' => $reservation->contact['last_name'],
                        ),
                        'Telephone' => array(
                          'PhoneTechType' => 1,
                          'CountryAccessCode' => 1,
                          'FormattedInd' => true,
//                          'AreaCityCode' => '302',
                          'PhoneNumber' => $reservation->contact['phone']
                        ),
                        'Email' => $reservation->contact['email'],
                        'Address' => array(
                          'AddressLine' => array($reservation->contact_address['address_1'], $reservation->contact_address['address_2']),
                          'CityName' => $reservation->contact_address['city'],
                          'PostalCode' => $reservation->contact_address['zipcode'],
                          'StateProv' => array('StateCode' => $reservation->contact_address['state']),
                          'CountryName' => array('Code' => 'US'),
                        )
                      )
                    )
                  )
                )
              ),
            ),
            'ResGlobalInfo' => array(
              'ResGuestRPHs' => array(
                'ResGuestRPH' => array('RPH' => 1),
              ),
              'Comments' => $comments,
              'DepositPayments' => array(
                'GuaranteePayment' => array(
                  'AcceptedPayments' => array(
                    'AcceptedPayment' => array(
                      'PaymentCard' => array(
                        'ExpireDate' => DateTime::createFromFormat('n', $reservation->payment['cc_expiration']['cc_month'])->format('m') . DateTime::createFromFormat('Y', $reservation->payment['cc_expiration']['cc_year'])->format('y'),
                        'CardType' => 1,
                        'CardToken' => $card_token,
                        'CardCode' => self::getCreditCardType($reservation->payment['cc_number']),
                        'MaskedCardNumber' => self::maskCreditCardNumber($reservation->payment['cc_number']),
                        'CardHolderName' => $reservation->payment['cc_name'],
                        'Address' => array(
                          'AddressLine' => $reservation->contact_address['address_1'],
                          'CityName' => $reservation->contact_address['city'],
                          'PostalCode' => $reservation->contact_address['zipcode'],
                          'StateProv' => array('StateCode' => $reservation->contact_address['state']),
                          'CountryName' => array('Code' => 'US'),
                        )
                      )
                    )
                  ),
                  'AmountPercent' => array('Amount' => self::getRentalBookingRate($reservation->quote_as_array)),
                )
              ),
            )
          )
        )
      )
    );
    $response = $escapia_service->invoke('UnitRes', $args);
    return $response;
  }

  /**
   * Generates a hashed digest message for the token request.
   * @param $api_key
   * @return string
   * @see EscapiaAPIBooking::generateCreditCardToken()
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
   * @param $credit_card_number
   * @return string|bool
   */
  public static function generateCreditCardToken($credit_card_number) {
    $hapi_url = variable_get('escapia_hapi_endpoint', null);
    $hapi_client = variable_get('escapia_hapi_client_id', null);
    $hapi_key = variable_get('escapia_hapi_api_key', null);

    $body = '<tokenForm><tokenType>CC</tokenType><value>' . $credit_card_number . '</value></tokenForm>';
//    $url =  $connection->hapi_endpoint . '?' . drupal_http_build_query(array('time' => round(microtime(TRUE) * 1000), 'digest' => self::generateDigest($connection->hapi_api_key), 'clientId' => $connection->hapi_client_id));
    $url = $hapi_url . '?' . drupal_http_build_query(array('time' => round(microtime(TRUE) * 1000), 'digest' => self::generateDigest($hapi_key), 'clientId' => $hapi_client));
    $response = drupal_http_request($url, array('method' => 'POST', 'data' => $body, 'headers' => array('Content-Type' => 'application/xml; charset=UTF-8')));

    if ($response->code == 201 || (isset($response->status_message) && $response->status_message == 'Created')) {
      $data = simplexml_load_string($response->data);
      $token = @current($data->attributes());
      return $token['id'];
    }

    return FALSE;
  }

  /**
   * Return the internal link that links to the booking form.
   * @param $entity_id
   * @return string
   */
  public static function getOnlineBookingLink($entity_id) {
    return l('Book Now &raquo;', 'rental/' . $entity_id . '/book-online/review-rates', array('html' => TRUE, 'attributes' => array('class' => array('button', 'radius', 'success', 'expand'))));
  }

  public static function getRentalBookingCharges(SimpleXMLElement $xml, $optional = 'false') {
    $fees = $xml->xpath('//ns:Fees/*[@MandatoryIndicator="'. $optional .'"]');
    $items = array();

    foreach ($fees as $fee) {
      $title = (string) $fee->Description[0]->Text;
      $amount = (string) $fee->attributes()->Amount;
      $subtotal = $amount;
      $tax = (string) $fee->Taxes->attributes()->Amount;

      if ((string) $fee->attributes()->Type == 'Inclusive') {
        $subtotal = bcadd($subtotal, $tax, 2);
      }

      $items[] = array('title' => $title, 'amount' => $amount, 'subtotal' => $subtotal);
    }

    return $items;
  }

  public static function getRentalBookingAdditionalCharges(SimpleXMLElement $xml) {
    $fees = $xml->xpath('//ns:AdditionalCharges');
    $items = array();

    foreach ($fees as $fee) {
      $title = (string) $fee->AdditionalCharge->Description[0]->Text;
      $amount = (string) $fee->AdditionalCharge->Amount->attributes()->AmountBeforeTax;
      $subtotal = $amount;
      $tax = (string) $fee->Taxes->attributes()->Amount;

      $items[] = array('title' => $title, 'amount' => $amount, 'subtotal' => $subtotal);
    }

    return $items;
  }

  /**
   * Return all the applicable taxes for the booking request.
   * @param $quote
   * @return array
   * @todo: $taxes returns empty array, should be populated
   */
  public static function getRentalBookingTaxes($quote) {
    $rates = $quote['UnitRates']['UnitRate']['Rates'];
    $taxes = $rates['Rate']['Base']['Taxes'];
    $items = array();

    foreach ($taxes as $tax) {
      if(is_array($tax)) {
        $title = (string) $tax['Tax']['TaxDescription']['Text'];
        $amount = (string) $tax['Amount'];

        if (drupal_strlen($title) && drupal_strlen($amount)) {
          $items[] = array('title' => $title, 'amount' => $amount);
        }
      }
    }
    return $items;
  }

  /**
   * Return a specific fee amount for the booking request.
   * @param SimpleXMLElement $xml
   * @param $charge_name
   * @return string
   */
  public static function getRentalBookingFee(SimpleXMLElement $xml, $charge_name) {
    $fees = @end($xml->xpath('//ns:Fees'));
    $amount = FALSE;

    foreach ($fees as $fee) {
      $charge = (string) $fee->Description[0]->Text;

      if ($charge == $charge_name) {
        $amount = (string) $fee->attributes()->Amount;
        break;
      }
    }

    return $amount;
  }

  public static function getRentalBookingAdditionalCharge(SimpleXMLElement $xml, $charge_name) {
    $fees = $xml->xpath('//ns:AdditionalCharges');
    $amount = FALSE;

    foreach ($fees as $fee) {
      $charge = (string) $fee->AdditionalCharge->Description[0]->Text;

      if ($charge == $charge_name) {
        $amount = (string) $fee->AdditionalCharge->Amount->attributes()->AmountBeforeTax;
        break;
      }
    }

    return $amount;
  }

  /**
   * Return the sub-total for the booking request.
   * @param SimpleXMLElement $xml
   * @return string
   */
  public static function getRentalBookingRate($quote) {
    $taxes = self::getRentalBookingTaxes($quote);
    $base = (float)$quote['Total']['AmountBeforeTax'];

    foreach ($taxes as $key => $tax) {
      $base += $tax['amount'];
    }

    return $base;
  }

  /**
   * Return a masked credit card number, up to the last 4 digits.
   * @param $number
   * @return string
   */
  public static function maskCreditCardNumber($number) {
    return str_pad(substr($number, -4), strlen($number), '*', STR_PAD_LEFT);
  }

  /**
   * Return the credit card type based on the credit card number.
   * @param $number
   * @return bool|string
   */
  public static function getCreditCardType($number) {
    if (preg_match("/^5[1-5][0-9]{14}$/", $number)) {
      return "MC";
    }

    if (preg_match("/^4[0-9]{12}([0-9]{3})?$/", $number)) {
      return "VI";
    }

    if (preg_match("/^3[47][0-9]{13}$/", $number)) {
      return "AX";
    }

    if (preg_match("/^6011[0-9]{12}$/", $number)) {
      return "DS";
    }

    return FALSE;
  }

  /**
   * Converts a multilevel object to an array.
   * @param $object
   * @param $array
   * @return mixed
   */
  public static function objectToArray($object, &$array){
    if (!is_object($object) && !is_array($object)) {
      $array = $object;
      return $array;
    }

    foreach ($object as $key => $value) {
      if (!empty($value)) {
        $array[$key] = array();
        self::objectToArray($value, $array[$key]);
      } else {
        $array[$key] = $value;
      }
    }

    return $array;
  }
}