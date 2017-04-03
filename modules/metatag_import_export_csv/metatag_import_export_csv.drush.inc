<?php

/**
 * @file
 * Drush command for the module.
 */

/**
 * Implements hook_drush_help().
 */
function metatag_import_export_csv_drush_help($command) {
  switch ($command) {
    case 'drush:metatag-import':
      return dt('This commans helps you to import metatag to node pages from a csv file
          The argument fot the command is filename
          follow the exampees'
      );
  }
}

/**
 * Gets content type for drush export operation.
 */
function metatag_import_export_csv_type_drush() {
  define('DRUPAL_ROOT', getcwd());
  require_once DRUPAL_ROOT . '/includes/bootstrap.inc';
  drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);

  $typedata = node_type_get_types();
  foreach ($typedata as $values1) {
    $type_machine_name[$values1->type] = $values1->type;
  }
  $default_type = array('all' => 'all');
  $content_type = array_merge($default_type, $type_machine_name);
  return $content_type;
}

/**
 * Implements hook_drush_command().
 */
function metatag_import_export_csv_drush_command() {
  $items['metatag-import'] = array(
    'description' => dt("Import metatags form a csv"),
    'arguments' => array(
      'filepath' => dt("The filepath to your file"),
    ),
    'examples' => array(
      'Windows_example' => 'drush metatag-import C:\\drupal\\multi.csv',
      'Linux_example' => 'drush metatag-import /home/user/Desktkop/metatag_import_export_csv_all.csv',
    ),
  );
  $items['metatag-export'] = array(
    'description' => dt("Export  metatags to a csv file"),
    'arguments' => array(
      'type' => dt("The type of option"),
    ),
    'examples' => array(
      'Basic page' => 'drush metatag-export page',
      'All' => 'drush metatag-export all',
    ),
    'options' => metatag_import_export_csv_type_drush(),
  );
  return $items;
}

/**
 * Drush callback for export operation.
 */
function drush_metatag_import_export_csv_metatag_export($type) {
  if (empty($type)) {
    $type = drush_choice(metatag_import_export_csv_type_drush(), 'Select the content type you want to export metatags');
  }
  if (!(in_array($type, metatag_import_export_csv_type_drush()))) {
    drush_set_error(dt('@type is not a machine name of any Content type', array('@type' => $type)));
  }
  else {
    include_once 'metatag_import_export_csv_download_admin.inc';
    metatag_import_export_csv_download_nid($type);
  }
}

/**
 * Drush callback for import operatioon.
 */
function drush_metatag_import_export_csv_metatag_import($filepath) {
  if (file_exists($filepath)) {

    $file_info = pathinfo($filepath);
    $file_extension = $file_info['extension'];
    if ($file_extension == 'csv') {
      if (drush_confirm('Are you sure you want to import metatags this will replace your old metatags ?')) {
        module_load_include('inc', 'metatag_import_export_csv', 'metatag_import_export_csv_upload_admin');
        metatag_import_export_csv_read_file($filepath);
      }
    }
    else {
      drush_set_error(dt('File type is not CSV .'));
    }
  }
  else {
    drush_set_error(dt('File with the given path does not exists.'));
  }
}
