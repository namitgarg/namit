<?php
/**
 * @file
 * cosmetic_client.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function cosmetic_client_user_default_permissions() {
  $permissions = array();

  // Exported permission: create gallery content.
  $permissions['create gallery content'] = array(
    'name' => 'create gallery content',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any gallery content.
  $permissions['delete any gallery content'] = array(
    'name' => 'delete any gallery content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own gallery content.
  $permissions['delete own gallery content'] = array(
    'name' => 'delete own gallery content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: delete terms in 2.
  $permissions['delete terms in 2'] = array(
    'name' => 'delete terms in 2',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: edit any gallery content.
  $permissions['edit any gallery content'] = array(
    'name' => 'edit any gallery content',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own gallery content.
  $permissions['edit own gallery content'] = array(
    'name' => 'edit own gallery content',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  return $permissions;
}
