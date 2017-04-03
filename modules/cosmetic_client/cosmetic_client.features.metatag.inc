<?php
/**
 * @file
 * cosmetic_client.features.metatag.inc
 */

/**
 * Implements hook_metatag_export_default().
 */
function cosmetic_client_metatag_export_default() {
  $config = array();

  // Exported Metatag config instance: taxonomy_term.
  $config['taxonomy_term'] = array(
    'instance' => 'taxonomy_term',
    'config' => array(
      'title' => array(
        'value' => '[term:name] | [site:name]',
      ),
      'description' => array(
        'value' => '[term:description]',
      ),
      'og:title' => array(
        'value' => '[term:name]',
      ),
      'og:description' => array(
        'value' => '[term:description]',
      ),
    ),
  );

  return $config;
}
