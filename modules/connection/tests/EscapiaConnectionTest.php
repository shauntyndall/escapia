<?php

define('DRUPAL_ROOT', getcwd());
require_once DRUPAL_ROOT . '/includes/bootstrap.inc';
drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);

include_once DRUPAL_ROOT . '/sites/default/modules/custom/escapia/modules/connection/class/escapia.entity.inc';

class EscapiaConnectionTest extends PHPUnit_Framework_TestCase {

  protected function setUp()
  {
    $this->entity = entity_create('escapia_connection', array());
  }

  /**
   * Test that our custom entity has all the properties we expect it to have.
   * @dataProvider entityPropertyProvider
   */
  public function testEscapiaConnectionEntityHasCorrectProperties($attribute) {
    return $this->assertObjectHasAttribute($attribute, $this->entity, "EscapiaConnection entity does not have a '{$attribute}' attribute.");
  }

  /**
   * Provider: return an array of entity properties as a data provider.
   * @return array
   */
  public function entityPropertyProvider()
  {
    return array(
      array('id'),
      array('label'),
      array('wsdl'),
      array('username'),
      array('password'),
      array('active'),
      array('uid'),
      array('created'),
      array('changed'),
    );
  }
}