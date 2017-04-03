<?php
/**
 * @file
 * all_clients.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function all_clients_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: user-menu:admin/config/system/backup_migrate
  $menu_links['user-menu:admin/config/system/backup_migrate'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'admin/config/system/backup_migrate',
    'router_path' => 'admin/config/system/backup_migrate',
    'link_title' => 'Backup',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
  );
  // Exported menu link: user-menu:admin/content
  $menu_links['user-menu:admin/content'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'admin/content',
    'router_path' => 'admin/content',
    'link_title' => 'Manage Content',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -46,
  );
  // Exported menu link: user-menu:admin/dashboard
  $menu_links['user-menu:admin/dashboard'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'admin/dashboard',
    'router_path' => 'admin/dashboard',
    'link_title' => 'Dashboard',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
  );
  // Exported menu link: user-menu:node/add
  $menu_links['user-menu:node/add'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'node/add',
    'router_path' => 'node/add',
    'link_title' => 'Create Content',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -47,
  );
  // Exported menu link: user-menu:user
  $menu_links['user-menu:user'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'user',
    'router_path' => 'user',
    'link_title' => 'User account',
    'options' => array(
      'alter' => TRUE,
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
  );
  // Exported menu link: user-menu:user/logout
  $menu_links['user-menu:user/logout'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'user/logout',
    'router_path' => 'user/logout',
    'link_title' => 'Log out',
    'options' => array(),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -45,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Backup');
  t('Create Content');
  t('Dashboard');
  t('Log out');
  t('Manage Content');
  t('User account');


  return $menu_links;
}
