<?php
/**
 * @file
 * features_page1_workbench.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function features_page1_workbench_default_rules_configuration() {
  $items = array();
  $items['rules_onpublish'] = entity_import('rules_config', '{ "rules_onpublish" : {
      "LABEL" : "onpublish",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "workbench_moderation", "php", "rules" ],
      "ON" : [ "workbench_moderation_after_moderation_transition" ],
      "IF" : [
        { "content_is_using_workbench_moderation" : { "node" : [ "node" ] } },
        { "contents_current_state" : { "node" : [ "node" ], "moderation_state" : "published" } },
        { "php_eval" : { "code" : "if( isset($_SESSION[\\u0027sendmail\\u0027]) \\u0026\\u0026 $_SESSION[\\u0027sendmail\\u0027] == 1){\\u000D\\u000A\\u000D\\u000Aunset($_SESSION[\\u0027sendmail\\u0027]);\\u000D\\u000Areturn FALSE;\\u000D\\u000A} else {\\u000D\\u000A\\u000D\\u000Areturn TRUE;\\u000D\\u000A}" } }
      ],
      "DO" : [
        { "mail" : {
            "to" : "\\u003C?php \\u000D\\u000Aecho variable_get(\\u0027pub\\u0027, $default = NULL);\\u000D\\u000A?\\u003E",
            "subject" : "[node:content-type] \\u0022[node:title]\\u0022 is Published on [site:url].",
            "message" : "Do not reply to this email; this is an auto-generated email.\\u000D\\u000APlease follow the link below to your new content.\\u000D\\u000A[node:url]",
            "language" : [ "" ]
          }
        }
      ]
    }
  }');
  $items['rules_send_mail_on_author_on_clients_to_approve'] = entity_import('rules_config', '{ "rules_send_mail_on_author_on_clients_to_approve" : {
      "LABEL" : "Send mail on author on clients to approve",
      "PLUGIN" : "reaction rule",
      "ACTIVE" : false,
      "REQUIRES" : [ "workbench_moderation", "php", "rules" ],
      "ON" : [ "workbench_moderation_after_moderation_transition" ],
      "IF" : [
        { "content_is_using_workbench_moderation" : { "node" : [ "node" ] } },
        { "contents_current_state" : { "node" : [ "node" ], "moderation_state" : "reviewed" } },
        { "contents_previous_state" : { "node" : [ "node" ], "moderation_state" : "needs_review" } },
        { "php_eval" : { "code" : "if( isset($_SESSION[\\u0027sendmail\\u0027]) \\u0026\\u0026 $_SESSION[\\u0027sendmail\\u0027] == 1){\\u000D\\u000A\\u000D\\u000Aunset($_SESSION[\\u0027sendmail\\u0027]);\\u000D\\u000Areturn FALSE;\\u000D\\u000A} else {\\u000D\\u000A\\u000D\\u000Areturn TRUE;\\u000D\\u000A}" } }
      ],
      "DO" : [
        { "mail" : {
            "to" : "\\u003C?php \\u000D\\u000Aecho variable_get(\\u0027needtoapprove\\u0027, $default = NULL);\\u000D\\u000A?\\u003E",
            "subject" : "[node:content-type] \\u0022[node:title]\\u0022 is updated from Needs Client Review to Approved or Awaiting SEO.",
            "message" : "Do not reply to this email, it is an auto-generated email. Please contact your IMC at Page 1 Solutions with any questions regarding this email.\\u000D\\u000A[node:content-type] \\u0022[node:title]\\u0022 is updated from Needs Client Review to Approved or Awaiting SEO.\\u000D\\u000A[node:edit-url]",
            "language" : [ "" ]
          }
        }
      ]
    }
  }');
  $items['rules_send_mail_on_author_on_clients_to_draft'] = entity_import('rules_config', '{ "rules_send_mail_on_author_on_clients_to_draft" : {
      "LABEL" : "Send mail on author on clients to draft",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "workbench_moderation", "php", "rules" ],
      "ON" : [ "workbench_moderation_after_moderation_transition" ],
      "IF" : [
        { "content_is_using_workbench_moderation" : { "node" : [ "node" ] } },
        { "contents_current_state" : { "node" : [ "node" ], "moderation_state" : "draft" } },
        { "contents_previous_state" : { "node" : [ "node" ], "moderation_state" : "needs_review" } },
        { "php_eval" : { "code" : "if( isset($_SESSION[\\u0027sendmail\\u0027]) \\u0026\\u0026 $_SESSION[\\u0027sendmail\\u0027] == 1){\\u000D\\u000A\\u000D\\u000Aunset($_SESSION[\\u0027sendmail\\u0027]);\\u000D\\u000Areturn FALSE;\\u000D\\u000A} else {\\u000D\\u000A\\u000D\\u000Areturn TRUE;\\u000D\\u000A}" } }
      ],
      "DO" : [
        { "mail" : {
            "to" : "\\u003C?php \\u000D\\u000Aecho variable_get(\\u0027needtodraft\\u0027, $default = NULL);\\u000D\\u000A?\\u003E",
            "subject" : "[node:content-type] \\u0022[node:title]\\u0022 is updated on [site:url] from Needs Client Review to Draft.",
            "message" : "Do not reply to this email, it is an auto-generated email. Please contact your IMC at Page 1 Solutions with any questions regarding this email.\\u000D\\u000A[node:content-type] \\u0022[node:title]\\u0022 is updated from Needs Client Review to Draft.\\u000D\\u000A[node:edit-url]",
            "language" : [ "" ]
          }
        }
      ]
    }
  }');
  $items['rules_send_mail_to_admin_on_new_content'] = entity_import('rules_config', '{ "rules_send_mail_to_admin_on_new_content" : {
      "LABEL" : "send mail to admin on new content",
      "PLUGIN" : "reaction rule",
      "ACTIVE" : false,
      "REQUIRES" : [ "workbench_moderation", "php", "rules" ],
      "ON" : [ "workbench_moderation_after_moderation_transition" ],
      "IF" : [
        { "content_is_using_workbench_moderation" : { "node" : [ "node" ] } },
        { "contents_current_state" : { "node" : [ "node" ], "moderation_state" : "needs_editorial_review" } },
        { "contents_previous_state" : { "node" : [ "node" ], "moderation_state" : "draft" } },
        { "php_eval" : { "code" : "if( isset($_SESSION[\\u0027sendmail\\u0027]) \\u0026\\u0026 $_SESSION[\\u0027sendmail\\u0027] == 1){\\u000D\\u000A\\u000D\\u000Aunset($_SESSION[\\u0027sendmail\\u0027]);\\u000D\\u000Areturn FALSE;\\u000D\\u000A} else {\\u000D\\u000A\\u000D\\u000Areturn TRUE;\\u000D\\u000A}" } }
      ],
      "DO" : [
        { "mail" : {
            "to" : "\\u003C?php echo variable_get(\\u0027admin_mail\\u0027, $default = NULL); ?\\u003E",
            "subject" : "[node:content-type] \\u0022[node:title]\\u0022 is updated on [site:url] from Draft to Needs Editorial Review.",
            "message" : "Do not reply to this email, it is an auto-generated email. Please contact your IMC at Page 1 Solutions with any questions regarding this email.\\u000D\\u000A[node:content-type] \\u0022[node:title]\\u0022 is updated from Draft to Needs Editorial Review.\\u000D\\u000A[node:edit-url]",
            "language" : [ "" ]
          }
        }
      ]
    }
  }');
  $items['rules_send_mail_to_client_on_needs_client_review'] = entity_import('rules_config', '{ "rules_send_mail_to_client_on_needs_client_review" : {
      "LABEL" : "send mail to client on Needs Client Review",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "workbench_moderation", "php", "rules" ],
      "ON" : [ "workbench_moderation_after_moderation_transition" ],
      "IF" : [
        { "content_is_using_workbench_moderation" : { "node" : [ "node" ] } },
        { "contents_current_state" : { "node" : [ "node" ], "moderation_state" : "needs_review" } },
        { "php_eval" : { "code" : "if( isset($_SESSION[\\u0027sendmail\\u0027]) \\u0026\\u0026 $_SESSION[\\u0027sendmail\\u0027] == 1){\\u000D\\u000A\\u000D\\u000Aunset($_SESSION[\\u0027sendmail\\u0027]);\\u000D\\u000Areturn FALSE;\\u000D\\u000A} else {\\u000D\\u000A\\u000D\\u000Areturn TRUE;\\u000D\\u000A}" } }
      ],
      "DO" : [
        { "mail" : {
            "to" : "\\u003C?php echo variable_get(\\u0027client_mail\\u0027, $default = NULL); ?\\u003E",
            "subject" : "[node:content-type] \\u0022[node:title]\\u0022 is updated on [site:url] to Needs Client Review.",
            "message" : "Do not reply to this email; this is an auto-generated email.\\u000D\\u000A\\u000D\\u000AThis content will be scheduled to post automatically in 2 business days if you take no action.\\u000D\\u000A\\u000D\\u000APlease follow the link below to review the content.\\u000D\\u000A\\u000D\\u000AIf you have extensive changes that need to be reviewed by your  Internet Marketing Consultant or writer mark as \\u0022Draft\\u0022 and we will review it.\\u000D\\u000A\\u000D\\u000A[node:edit-url]",
            "language" : [ "" ]
          }
        }
      ]
    }
  }');
  return $items;
}
