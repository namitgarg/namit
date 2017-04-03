<?php
/**
 * @file
 * location_content_type.features.inc
 */

/**
 * Implements hook_views_api().
 */
function location_content_type_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function location_content_type_node_info() {
  $items = array(
    'location' => array(
      'name' => t('Location'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
