<?php

interface EscapiaImportInterface {
  public function __construct();
  public function importAll();
  public function processProperty($soap_response);
  public function processPhotos($soap_response);
  public function processRates($soap_response);
}