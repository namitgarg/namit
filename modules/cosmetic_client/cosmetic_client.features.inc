<?php
/**
 * @file
 * cosmetic_client.features.inc
 */

/**
 * Implements hook_views_api().
 */
function cosmetic_client_views_api() {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function cosmetic_client_node_info() {
  $items = array(
    'gallery' => array(
      'name' => t('Before and After Gallery Entry'),
      'base' => 'node_content',
      'description' => t('Enter gallery items using this content type. '),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
