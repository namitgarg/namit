<?php
/**
 * @file
 * blog_category_fixer.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function blog_category_fix_default_rules_configuration() {
  $items = array();
  $items['rules_blog'] = entity_import('rules_config', '{ "rules_blog" : {
      "LABEL" : "Blog category fix",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "php" ],
      "ON" : {
        "node_view--blog" : { "bundle" : "blog" },
        "node_update--blog" : { "bundle" : "blog" }
      },
      "IF" : [
        { "user_has_role" : {
            "account" : [ "user" ],
            "roles" : { "value" : { "2" : "2", "3" : "3", "4" : "4" } },
            "operation" : "OR"
          }
        }
      ],
      "DO" : [
        { "php_eval" : { "code" : "$nid=$node-\\u003Enid;\\r\\n$num_deleted = db_delete(\\u0027taxonomy_index\\u0027)\\r\\n  -\\u003Econdition(\\u0027nid\\u0027,$nid)\\r\\n  -\\u003Eexecute(); \\r\\ntaxonomy_build_node_index($node);" } }
      ]
    }
  }');
  return $items;
}
