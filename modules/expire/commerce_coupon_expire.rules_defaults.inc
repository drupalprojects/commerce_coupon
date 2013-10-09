<?php

/**
 * Implements hook_default_rules_configuration().
 */
function commerce_coupon_expire_default_rules_configuration() {
  $rules['rules_disable_coupon'] = entity_import('rules_config',
    '{ "rules_disable_coupon" : {
        "LABEL" : "Disable coupon",
        "PLUGIN" : "action set",
        "REQUIRES" : [ "rules" ],
        "USES VARIABLES" : { "coupon" : { "label" : "Coupon", "type" : "commerce_coupon" } },
        "ACTION SET" : [ { "data_set" : { "data" : [ "coupon:status" ], "value" : 1 } } ]
      }
    }'
  );

  $rules['rules_schedule_coupon_expiration_insert'] = entity_import('rules_config',
    '{ "rules_schedule_coupon_expiration_insert" : {
        "LABEL" : "Schedule coupon expiration (insert)",
        "PLUGIN" : "reaction rule",
        "REQUIRES" : [ "rules", "rules_scheduler", "commerce_coupon" ],
        "ON" : [ "commerce_coupon_insert" ],
        "IF" : [
          { "entity_has_field" : {
              "entity" : [ "commerce-coupon" ],
              "field" : "commerce_coupon_expiration"
            }
          },
          { "NOT data_is_empty" : { "data" : [ "commerce-coupon:commerce-coupon-expiration" ] } }
        ],
        "DO" : [
          { "schedule" : {
              "component" : "rules_disable_coupon",
              "date" : [ "commerce-coupon:commerce-coupon-expiration" ],
              "identifier" : "disable-coupon-[commerce-coupon:code]",
              "param_coupon" : [ "commerce-coupon" ]
            }
          }
        ]
      }
    }'
  );

  $rules['rules_schedule_coupon_expiration_update'] = entity_import('rules_config',
    '{ "rules_schedule_coupon_expiration_update" : {
        "LABEL" : "Schedule coupon expiration (update)",
        "PLUGIN" : "reaction rule",
        "REQUIRES" : [ "rules", "rules_scheduler", "commerce_coupon" ],
        "ON" : [ "commerce_coupon_update" ],
        "IF" : [
          { "entity_has_field" : {
              "entity" : [ "commerce-coupon" ],
              "field" : "commerce_coupon_expiration"
            }
          },
          { "NOT data_is_empty" : { "data" : [ "commerce-coupon:commerce-coupon-expiration" ] } },
          { "NOT data_is" : {
              "data" : [ "commerce-coupon:commerce-coupon-expiration" ],
              "value" : [ "commerce-coupon-unchanged:commerce-coupon-expiration" ]
            }
          }
        ],
        "DO" : [
          { "schedule_delete" : {
              "component" : "rules_disable_coupon",
              "task" : "disable-coupon-[commerce-coupon:code]"
            }
          },
          { "schedule" : {
              "component" : "rules_disable_coupon",
              "date" : [ "commerce-coupon:commerce-coupon-expiration" ],
              "identifier" : "disable-coupon-[commerce-coupon:code]",
              "param_coupon" : [ "commerce-coupon" ]
            }
          }
        ]
      }
    }'
  );

  $rules['rules_deschedule_coupon_expiration_delete'] = entity_import('rules_config',
    '{ "rules_deschedule_coupon_expiration_delete" : {
        "LABEL" : "Deschedule coupon expiration (delete)",
        "PLUGIN" : "reaction rule",
        "REQUIRES" : [ "rules", "rules_scheduler", "commerce_coupon" ],
        "ON" : [ "commerce_coupon_delete" ],
        "IF" : [
          { "entity_has_field" : {
              "entity" : [ "commerce-coupon" ],
              "field" : "commerce_coupon_expiration"
            }
          },
          { "NOT data_is_empty" : { "data" : [ "commerce-coupon:commerce-coupon-expiration" ] } }
        ],
        "DO" : [
          { "schedule_delete" : {
              "component" : "rules_disable_coupon",
              "task" : "disable-coupon-[commerce-coupon:code]"
            }
          }
        ]
      }
    }'
  );

  $rules['rules_deschedule_coupon_expiration_update'] = entity_import('rules_config',
    '{ "rules_deschedule_coupon_expiration_update" : {
        "LABEL" : "Deschedule coupon expiration (update)",
        "PLUGIN" : "reaction rule",
        "WEIGHT" : "-1",
        "REQUIRES" : [ "rules", "rules_scheduler", "commerce_coupon" ],
        "ON" : [ "commerce_coupon_update" ],
        "IF" : [
          { "entity_has_field" : {
              "entity" : [ "commerce-coupon" ],
              "field" : "commerce_coupon_expiration"
            }
          },
          { "data_is_empty" : { "data" : [ "commerce-coupon:commerce-coupon-expiration" ] } }
        ],
        "DO" : [
          { "schedule_delete" : {
              "component" : "rules_disable_coupon",
              "task" : "disable-coupon-[commerce-coupon:code]"
            }
          }
        ]
      }
    }'
  );

  return $rules;
}