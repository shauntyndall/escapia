<?php

interface EscapiaHomeAwayPaymentIslandInterface {
  public static function generateDigest($api_key);
  public static function getTimeInMilliseconds();
  public static function generateCreditCardToken(EscapiaConnection $connection, $credit_card_number);
}