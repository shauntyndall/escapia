<?php

interface EscapiaBookingAPIInterface {
  public function createUnitBooking($unit_code);
  public static function processRatesFromResponse($soap_response);
}