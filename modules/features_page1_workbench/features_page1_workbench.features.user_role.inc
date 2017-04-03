<?php
/**
 * @file
 * features_page1_workbench.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function features_page1_workbench_user_default_roles() {
  $roles = array();

  // Exported role: Client.
  $roles['Client'] = array(
    'name' => 'Client',
    'weight' => 4,
  );

  return $roles;
}
