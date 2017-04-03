<?php

/**
 * @file
 * Stores the code for import Process.
 */

define("BLANK", "_blank");

/**
 * Checks CSV for Html and Php.
 */
function metatag_import_export_csv_xss_check($path, $meta_title, $meta_description, $meta_abstract, $meta_keywords) {
  $checked_path = strip_tags($path);
  $checked_meta_title = strip_tags($meta_title);
  $checked_meta_description = strip_tags($meta_description);
  $checked_meta_abstract = strip_tags($meta_abstract);
  $checked_meta_keywords = strip_tags($meta_keywords);
  if (($checked_path == $path) && ($checked_meta_title == $meta_title) && ($checked_meta_description == $meta_description) && ($checked_meta_abstract == $meta_abstract) && ($checked_meta_keywords == $meta_keywords)) {
    return TRUE;
  }
  else {
    return FALSE;
  }
}

/**
 * Form for Import operation.
 */
function metatag_import_export_csv_upload_form($form, &$form_state) {
  metatag_import_export_csv_getpath();
  $form['upload_file'] = array(
    '#type' => 'managed_file',
    '#title' => t('Upload File'),
    '#required' => TRUE,
    '#description' => t('Allowed Extensions: csv'),
    '#upload_location' => 'public://metatag_import_export_csv/',
    '#upload_validators' => array(
      'file_validate_extensions' => array('csv'),
      'file_validate_size' => array(1 * 1024 * 1024),
    ),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t("Import"),
    '#submit' => array('metatag_import_export_csv_upload_submit'),
  );
  return $form;
}

/**
 * Submit Handler for Import Operation.
 */
function metatag_import_export_csv_upload_submit($form, &$form_state) {
  $file = file_load($form_state['values']['upload_file']);
  $file->status = 0;
  file_save($file);
  $fileurl = file_create_url($file->uri);
  metatag_import_export_csv_read_file($fileurl);
}

/**
 * Reads the CSV file and passes the data to batch operation.
 */
function metatag_import_export_csv_read_file($fileurl) {

  $count = 0;
  $handle = fopen($fileurl, "r");
  fgetcsv($handle);
  $batch = array(
    'operations' => array(),
    'finished' => 'metatag_import_export_csv_finish_batch_upload',
    'title' => t("Processing Nodes for importing Metatags"),
    'init_message' => t("Starting Metatag Import Process"),
    'progress_message' => t("Processed @current out of @total Nodes"),
    'file' => drupal_get_path('module', 'metatag_import_export_csv') . '/metatag_import_export_csv_upload_admin.inc',
    'error_message' => t("Metatag import process has encountered an error."),
  );
  while (!feof($handle)) {
    $count++;
    $data = fgetcsv($handle);
    $batch['operations'][] = array('metatag_import_export_csv_start_batch_upload', array(
      $data[1],
      $data[2],
      $data[3],
      $data[4],
      $data[5],
      $count,
    ),
    );
  }
  batch_set($batch);
  if (drupal_is_cli()) {
    $batch = & batch_get();
    $batch['progressive'] = FALSE;
    drush_backend_batch_process();
  }
  else {
    batch_process('admin/config/search/metatags/import');
  }
}

/**
 * Gets nid of all nodes.
 */
function metatag_import_export_csv_getnid() {
  $query = db_select('node', 'n')
      ->fields('n', array('nid'));
  $results = $query->execute()->fetchAll();
  foreach ($results as $values) {
    $nid_list[] = "node/" . $values->nid;
  }
  return ($nid_list);
}

/**
 * Get URl Alias from database.
 */
function metatag_import_export_csv_getpath() {
  $query2 = db_select('url_alias', 'ua')
      ->fields('ua', array('source', 'alias'));
  $results2 = $query2->execute()->fetchAll();
  foreach ($results2 as $values) {
    $path['source'][] = explode("/", $values->source)[1];
    $path['alias_path'][] = $values->alias;
  }
  return ($path);
}

/**
 * Batch Operation Callback.
 */
function metatag_import_export_csv_start_batch_upload($path, $meta_title, $meta_description, $meta_abstract, $meta_keywords, $keys, &$context) {
  $row_num = $keys + 1;
  $xsscheck = metatag_import_export_csv_xss_check($path, $meta_title, $meta_description, $meta_abstract, $meta_keywords);
  if (empty($xsscheck)) {
    drupal_set_message(t("Row %row_num was skipped as it contains PHP or HTML tags", array('%row_num' => $row_num)), 'error');
  }
  else {
    $nid_db = metatag_import_export_csv_getnid();
    preg_match("/node/", $path, $path_match);
    $cur_nid = explode("/", $path)[1];
    if (!empty($path_match)) {
      if (in_array($path, $nid_db)) {
        metatag_import_export_csv_node_processing($cur_nid, $meta_title, $meta_description, $meta_abstract, $meta_keywords, $keys);
        drupal_set_message(t("%path  Metatag on row %row_num updated Successfully", array('%path ' => $path, '%row_num' => $row_num)));
      }
      else {
        drupal_set_message(t("%path  Metatag on row %row_num does not exists", array('%path' => $path, '%row_num' => $row_num)), 'error');
      }
    }
    else {
      $pathdb = metatag_import_export_csv_getpath();
      foreach ($pathdb['alias_path'] as $keys => $values) {
        $path_url[] = $values;
        $path_nid[] = $pathdb['source'][$keys];
      }
      $path_search = array_keys($path_url, $path)[0];
      if (!empty($path_nid[$path_search])) {
        metatag_import_export_csv_node_processing($path_nid[$path_search], $meta_title, $meta_description, $meta_abstract, $meta_keywords, $keys);
        drupal_set_message(t("%path  Metatag on row %row_num updated Successfully", array('%path ' => $path, '%row_num' => $row_num)));
      }
      else {
        drupal_set_message(t("%path  Metatag on row %row_num does not exists", array('%path' => $path, '%row_num' => $row_num)), 'error');
      }
    }
  }
}

/**
 * Batch 'finished' callback for Import Operation.
 */
function metatag_import_export_csv_finish_batch_upload($success, $results, $operations) {
  if ($success) {
    drupal_set_message(t("Finished Importing Metatags"));
  }
  else {
    $error_operation = reset($operations);
    drupal_set_message(t("An error occurred while processing @operation with arguments : @args", array(
      '@operation' => $error_operation[0],
      '@args' => print_r($error_operation[0], TRUE),
    )));
  }
}

/**
 * Changes the Metatag for the Nodes.
 */
function metatag_import_export_csv_node_processing($cur_nid, $meta_title, $meta_description, $meta_abstract, $meta_keywords, $keys) {
  $node = node_load($cur_nid);
  if (!empty($meta_title)) {
    if ($meta_title == BLANK) {
      $node->metatags[$node->language]['title']['value'] = "";
    }
    else {
      $node->metatags[$node->language]['title']['value'] = $meta_title;
    }
  }
  if (!empty($meta_description)) {
    if ($meta_description == BLANK) {
      $node->metatags[$node->language]['description']['value'] = "";
    }
    else {
      $node->metatags[$node->language]['description']['value'] = $meta_description;
    }
  }
  if (!empty($meta_abstract)) {
    if ($meta_abstract == BLANK) {
      $node->metatags[$node->language]['abstract']['value'] = "";
    }
    else {
      $node->metatags[$node->language]['abstract']['value'] = $meta_abstract;
    }
  }
  if (!empty($meta_keywords)) {
    if ($meta_keywords == BLANK) {
      $node->metatags[$node->language]['keywords']['value'] = "";
    }
    else {
      $node->metatags[$node->language]['keywords']['value'] = $meta_keywords;
    }
  }
  $node->revision = 1;
  $node->log = "Modified by Metatag Import Export Module.";
  node_save($node);
}
