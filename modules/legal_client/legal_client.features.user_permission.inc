<?php
/**
 * @file
 * legal_client.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function legal_client_user_default_permissions() {
  $permissions = array();

  // Exported permission: create verdicts_settlements content.
  $permissions['create verdicts_settlements content'] = array(
    'name' => 'create verdicts_settlements content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: delete any verdicts_settlements content.
  $permissions['delete any verdicts_settlements content'] = array(
    'name' => 'delete any verdicts_settlements content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: delete own verdicts_settlements content.
  $permissions['delete own verdicts_settlements content'] = array(
    'name' => 'delete own verdicts_settlements content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: edit any verdicts_settlements content.
  $permissions['edit any verdicts_settlements content'] = array(
    'name' => 'edit any verdicts_settlements content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: edit own verdicts_settlements content.
  $permissions['edit own verdicts_settlements content'] = array(
    'name' => 'edit own verdicts_settlements content',
    'roles' => array(),
    'module' => 'node',
  );

  return $permissions;
}
