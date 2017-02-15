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
          The argument fot the command is filename and delimter enclosed in quotes'
      );
        break;
    case 'drush:metatag-export':
      return dt('This commans helps you to import metatag to node pages from a csv file
          The argument fot the command is the machine name for content type and the delimter enclosed in  quotes'
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



function metatag_import_export_csv_delimiter_list_drush() {

  $delimiter_type = array(
    ',' => 'comma (,)',
    ';' => 'semicolon (;)',
    '\t' => 'tab (\t)',
    '|' => 'pipe (|)',
    ':' => 'colon (:)',
  );

  return $delimiter_type;
}

/**
 * Implements hook_drush_command().
 */
function metatag_import_export_csv_drush_command() {
  $items['metatag-import'] = array(
    'description' => dt("Import metatags form a csv"),
    'arguments' => array(
      'filepath' => dt("The filepath to your file"),
        'delimeter' => dt("The delimeter you want CSV to be exported in")
    ),
    'examples' => array(
      'Windows_example' => 'drush metatag-import C:\\drupal\\multi.csv "|"',
      'Linux_example' => 'drush metatag-import /home/user/Desktkop/metatag_import_export_csv_all.csv ";',
    ),
  );
  $items['metatag-export'] = array(
    'description' => dt("Export  metatags to a csv file"),
    'arguments' => array(
      'type' => dt("The type of Content types"),
      'delimeter' =>dt("The delemter for the CSV File to be used"),
    ),
    'examples' => array(
      'Basic page' => 'drush metatag-export page ";" ',
      'All' => 'drush metatag-export all ","',
    ),
    'options' => metatag_import_export_csv_type_drush(),
  );
  return $items;
}

/**
 * Drush callback for export operation.
 */
function drush_metatag_import_export_csv_metatag_export($type,$delimeter) {
  if (empty($type)) {
    $type = drush_choice(metatag_import_export_csv_type_drush(), 'Select the content type you want to export metatags');
  }
  if (empty($delimeter)) {
    $delimeter = drush_choice(metatag_import_export_csv_delimiter_list_drush(), 'Select the delemeter for CSV');
  }
  
  if (!(in_array($type, metatag_import_export_csv_type_drush()))) {
    drush_set_error(dt('@type is not a machine name of any Content type', array('@type' => $type)));
  }
  else {
    include_once 'metatag_import_export_csv_download_admin.inc';
    metatag_import_export_csv_download_nid($type,$delimeter);
  }
}

/**
 * Drush callback for import operatioon.
 */
function drush_metatag_import_export_csv_metatag_import($filepath,$delimeter) {
    if (empty($filepath)) {
        $filepath=drush_prompt(dt('Enter the path you want the CSV to be imported form'));
     }
     if(empty($delimeter))
     {
     $delimeter = drush_choice(metatag_import_export_csv_delimiter_list_drush(), 'Select the delemeter for CSV');

     }
  if (file_exists($filepath)) {

    $file_info = pathinfo($filepath);
    $file_extension = $file_info['extension'];
    if ($file_extension == 'csv') {
      if (drush_confirm('Are you sure you want to import metatags this will replace your old metatags ?')) {
        module_load_include('inc', 'metatag_import_export_csv', 'metatag_import_export_csv_upload_admin');
        metatag_import_export_csv_read_file($filepath,$delimeter);
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
