<?php
/**
 * @file
 * legal_client.features.inc
 */

/**
 * Implements hook_views_api().
 */
function legal_client_views_api() {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function legal_client_node_info() {
  $items = array(
    'verdicts_settlements' => array(
      'name' => t('Verdicts & Settlements'),
      'base' => 'node_content',
      'description' => t('Create a new Verdict or Settlement Page.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
