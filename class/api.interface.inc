<?php

interface EscapiaAPIInterface {
  public function __construct(EscapiaConnection $connection);

  /**
   * Query for unit details in Escapia.
   * @param $unit_code
   * @return mixed
   */
  public function getUnitInfo($unit_code);

  /**
   * Check availability on the specified unit by start and end date.
   * @param $unit_code
   * @param $start_date
   * @param $end_date
   * @param $duration
   * @return mixed
   */
  public function getUnitRateRange($unit_code, $start_date, $end_date, $duration = 7);

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
  public function unitSearch($criteria = array());

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
  public function getAllUnits();

  /**
   * Obtains only recently updated units from Escapia.
   * Note that properties will only show in results if they meet this initial criteria:
   *   - Has photos
   *   - Has rates for a full year
   *   - Is attached to a rate Season
   *   - Has a connected owner contract
   *   - Is Active
   *   - Is published to network partners
   * @param $last_updated
   * @return mixed
   */
  public function getUpdatedUnits($last_updated = REQUEST_TIME);

  /**
   * Obtain booking information if the unit is available in Escapia.
   * @param $unit_code
   * @param $start_date
   * @param $end_date
   * @param $adults
   * @param $children
   * @return mixed
   */
  public function getUnitQuoteRequest($unit_code, $start_date, $end_date, $adults, $children);
}