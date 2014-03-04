<?php

define('DRUPAL_ROOT', getcwd());
require_once DRUPAL_ROOT . '/includes/bootstrap.inc';
drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);

include_once DRUPAL_ROOT . '/sites/default/modules/custom/escapia/modules/property/class/escapia_property.import.inc';

class EscapiaPropertyImportTest extends PHPUnit_Framework_TestCase {
  protected $importer;

  protected function setUp()
  {
    $this->importer = new EscapiaPropertyImportAPI();
  }

  /**
   * Test that addresses provided are not modified by the cleanText method.
   * @dataProvider goodAddressProvider
   */
  public function testTextShouldEqualItselfAfterStripping($address) {
    $this->assertTrue(($this->importer->cleanText($address) == $address), "cleanText() did not return the same string. Expected '{$address}' got '{$this->importer->cleanText($address)}'");
  }

  /**
   * Test that addresses provided are modified by the cleanText method.
   * @dataProvider badAddressProvider
   */
  public function testTextShouldNotEqualItselfAfterStripping($address) {
    $this->assertFalse(($this->importer->cleanText($address) == $address), 'cleanText() returned the same string.');
  }

  /**
   * Provider of good or 'acceptable' addresses.
   */
  public function goodAddressProvider() {
    return array(
      array('123 Fake Street, Unit 90-1C'),
      array('123 Fake St., Unit 90-1C'),
      array('123 Fake Street, Unit #90-1C'),
    );
  }

  /**
   * Provider of bad addresses, with symbols/characters it should not have.
   */
  public function badAddressProvider() {
    return array(
      array('123 Fake Street,   Unit 90-1C/'),
      array('123 Fake Street,$ Unit 90-1C/'),
      array('* 2453 (Fake Street), ~ Unit %3492'),
    );
  }
}