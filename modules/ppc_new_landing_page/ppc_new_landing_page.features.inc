<?php
/**
 * @file
 * ppc_new_landing_page.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ppc_new_landing_page_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function ppc_new_landing_page_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function ppc_new_landing_page_node_info() {
  $items = array(
    'ppc_new_landing_page' => array(
      'name' => t('PPC New Landing Page'),
      'base' => 'node_content',
      'description' => t('This is the new ppc landing page that will holds the contents for ppc new pages'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
