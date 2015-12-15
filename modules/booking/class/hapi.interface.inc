<?php

interface EscapiaAPIHomeAwayPaymentIslandInterface {
  public static function generateDigest($api_key);
  public static function getTimeInMilliseconds();
  public static function generateCreditCardToken($credit_card_number);
}