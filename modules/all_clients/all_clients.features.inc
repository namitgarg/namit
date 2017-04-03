<?php
/**
 * @file
 * all_clients.features.inc
 */

/**
 * Implements hook_views_api().
 */
function all_clients_views_api() {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function all_clients_node_info() {
  $items = array(
    'blog' => array(
      'name' => t('Blog'),
      'base' => 'node_content',
      'description' => t('Use the blog content type to publish blog posts. '),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'mast_cycle' => array(
      'name' => t('Mast Cycle'),
      'base' => 'node_content',
      'description' => t('Use this content type to create your mast slideshow images. '),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'page' => array(
      'name' => t('Basic page'),
      'base' => 'node_content',
      'description' => t('Use <em>basic pages</em> for your static content, such as an \'About us\' page.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
