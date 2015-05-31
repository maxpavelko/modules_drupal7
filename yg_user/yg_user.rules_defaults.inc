<?php
/**
 * @file
 * yg_user.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function yg_user_default_rules_configuration() {
  $items = array();
  $items['rules_yg_assign_an_anonymous_order_to_a_pre_existing_user'] = entity_import('rules_config', '{ "rules_yg_assign_an_anonymous_order_to_a_pre_existing_user" : {
      "LABEL" : "yg - Assign an anonymous order to a pre-existing user",
      "PLUGIN" : "reaction rule",
      "WEIGHT" : "1",
      "REQUIRES" : [ "rules", "commerce", "yg_order_post_xml" ],
      "ON" : [ "yg_order_post_xml" ],
      "IF" : [
        { "data_is" : { "data" : [ "commerce-order:uid" ], "value" : "0" } },
        { "entity_exists" : {
            "type" : "user",
            "property" : "mail",
            "value" : [ "commerce-order:mail" ]
          }
        },
        { "data_is" : { "data" : [ "commerce-order:type" ], "value" : "commerce_order" } }
      ],
      "DO" : [
        { "entity_query" : {
            "USING" : {
              "type" : "user",
              "property" : "mail",
              "value" : [ "commerce-order:mail" ],
              "limit" : 1
            },
            "PROVIDE" : { "entity_fetched" : { "account_fetched" : "Fetched account" } }
          }
        },
        { "LOOP" : {
            "USING" : { "list" : [ "account-fetched" ] },
            "ITEM" : { "list_item" : "Current list item" },
            "DO" : [
              { "data_set" : { "data" : [ "commerce-order:uid" ], "value" : [ "list-item:uid" ] } },
              { "data_set" : {
                  "data" : [ "commerce-order:commerce-customer-billing:uid" ],
                  "value" : [ "list-item:uid" ]
                }
              },
              { "data_set" : {
                  "data" : [ "commerce-order:commerce-customer-shipping:uid" ],
                  "value" : [ "list-item:uid" ]
                }
              }
            ]
          }
        }
      ]
    }
  }');
  $items['rules_yg_create_a_new_account_for_an_anonymous_order'] = entity_import('rules_config', '{ "rules_yg_create_a_new_account_for_an_anonymous_order" : {
      "LABEL" : "yg - Create a new account for an anonymous order",
      "PLUGIN" : "reaction rule",
      "WEIGHT" : "2",
      "REQUIRES" : [ "rules", "commerce", "yg_order_post_xml" ],
      "ON" : [ "yg_order_post_xml" ],
      "IF" : [
        { "data_is" : { "data" : [ "commerce-order:uid" ], "value" : "0" } },
        { "NOT entity_exists" : {
            "type" : "user",
            "property" : "mail",
            "value" : [ "commerce-order:mail" ]
          }
        },
        { "data_is" : { "data" : [ "commerce-order:type" ], "value" : "commerce_order" } }
      ],
      "DO" : [
        { "entity_create" : {
            "USING" : {
              "type" : "user",
              "param_name" : [ "commerce-order:mail-username" ],
              "param_mail" : [ "commerce-order:mail" ]
            },
            "PROVIDE" : { "entity_created" : { "account_created" : "Created account" } }
          }
        },
        { "data_set" : { "data" : [ "account-created:status" ], "value" : 1 } },
        { "entity_save" : { "data" : [ "account-created" ], "immediate" : 1 } },
        { "entity_query" : {
            "USING" : {
              "type" : "user",
              "property" : "mail",
              "value" : [ "commerce-order:mail" ],
              "limit" : 1
            },
            "PROVIDE" : { "entity_fetched" : { "account_fetched" : "Fetched account" } }
          }
        },
        { "LOOP" : {
            "USING" : { "list" : [ "account-fetched" ] },
            "ITEM" : { "list_item" : "Current list item" },
            "DO" : [
              { "data_set" : { "data" : [ "commerce-order:uid" ], "value" : [ "list-item:uid" ] } },
              { "data_set" : {
                  "data" : [ "commerce-order:commerce-customer-billing:uid" ],
                  "value" : [ "list-item:uid" ]
                }
              },
              { "data_set" : {
                  "data" : [ "commerce-order:commerce-customer-shipping:uid" ],
                  "value" : [ "list-item:uid" ]
                }
              }
            ]
          }
        }
      ]
    }
  }');
  return $items;
}
