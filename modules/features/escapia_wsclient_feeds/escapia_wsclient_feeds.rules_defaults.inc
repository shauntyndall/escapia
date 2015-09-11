<?php
/**
 * @file
 * escapia_wsclient_feeds.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function escapia_wsclient_feeds_default_rules_configuration() {
  $items = array();
  $items['rules_escapia_unit_info_update_after_unitsearch_feed'] = entity_import('rules_config', '{ "rules_escapia_unit_info_update_after_unitsearch_feed" : {
      "LABEL" : "Trigger Escapia Unit Info update after UnitSearch Feed import",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "Escapia" ],
      "REQUIRES" : [ "escapia_feeds", "rules" ],
      "ON" : {
        "node_insert--rental" : { "bundle" : "rental" },
        "node_update--rental" : { "bundle" : "rental" }
      },
      "DO" : [
        { "escapia_feeds_escapia_feed_description_update_by_unit" : {
            "lookup_source_name" : "escapia_rentals_descriptive_info",
            "unit_code" : [ "node:field-escapia-unit-code" ]
          }
        },
        { "escapia_feeds_escapia_feed_description_update_by_unit" : {
            "lookup_source_name" : "escapia_rentals_calendar_availability",
            "unit_code" : [ "node:field-escapia-unit-code" ],
            "date_start" : "today",
            "date_end" : "today +18 months"
          }
        }
      ]
    }
  }');
  return $items;
}
