<?php

/**
 * @file
 * Stores the code for export process.
 */

/**
 * Gets the list of  Content Type for Content type dropdown.
 */
function metatag_import_export_csv_type_list() {
  $typedata = node_type_get_types();
  foreach ($typedata as $values1) {
    $type_machine_name = $values1->type;
    $type_human_name = t("@typename", array('@typename' => $values1->name));
    $func_content_type[$type_machine_name] = $type_human_name;
  }
  $default_type = array('all' => 'All');
  $content_type = array_merge($default_type, $func_content_type);
  return $content_type;
}

/**
 * Form for exporting Meta tags.
 */
function metatag_import_export_csv_download_form($form, &$form_state) {
  $content_type = metatag_import_export_csv_type_list();
  $form['content_type'] = array(
    '#type' => 'select',
    '#options' => $content_type,
    '#title' => t("Content type"),
    '#validated' => TRUE,
    '#required' => TRUE,
    '#default_value' => $content_type['all'],
    '#description' => t("Select the Content type"),
  );
  $form['export'] = array(
    '#type' => 'submit',
    '#value' => t("Export"),
    '#submit' => array('metatag_import_export_csv_download_submit'),
  );
  return $form;
}

/**
 * Submit Handler for Export Operation.
 */
function metatag_import_export_csv_download_submit($form, &$form_state) {
  $type = $form_state['values']['content_type'];
  metatag_import_export_csv_download_nid($type);
}

/**
 * Gets the list of nid's according to content type.
 */
function metatag_import_export_csv_download_nid($type) {
  $type_name = $type;
  $query = db_select('node', 'n')
      ->fields('n', array('nid'));
  if ($type != 'all') {
    $query->condition('type', $type);
  }
  elseif ($type = 'all') {
    $type = metatag_import_export_csv_type_list();
    $type = array_keys($type);
    $query->condition('type', ($type), 'IN');
  }
  $results = $query->execute()->fetchAll();
  foreach ($results as $values) {
    $nid_list[] = $values->nid;
  }
  metatag_import_export_csv_process_csv($nid_list, $type_name);
}

/**
 * Creates CSV file and downloads it to the System.
 */
function metatag_import_export_csv_process_csv($nid_list, $type) {
  $file_path = "public://metatag_import_export_csv/";
  $timestamp=time();
  $filename = "metatag_import_export_csv_" . $type ."_". $timestamp.".csv";
  $file_url = $file_path . $filename;
  drupal_add_http_header('Content-Type', 'text/csv');
  drupal_add_http_header('Content-Disposition', 'attachment;filename=' . $filename);

  if (!file_prepare_directory($file_path, FILE_CREATE_DIRECTORY)) {
    drupal_set_message(t('Unable to create directory in file system. Check permissions and try again.'), 'error');
    return;
  }
  $file = file_save_data('', $file_url, FILE_EXISTS_REPLACE);
  if (!($file)) {
    drupal_set_message(t('Unable to write to file system. Check permissions and try again.'), 'error');
    return;
  }
  $fp = fopen($file->uri, 'w');
  if (!$fp) {
    drupal_set_message(t('Unable open file for writing. Check permissions and try again.'), 'error');
    return;
  }
  $header = array(
     'Type',   
    'Node Title',
    'Path',
    ' Meta Title',
    'Meta Description',
    'Meta Abstract',
    ' Meta Keywords',
    'Language',
  );
  fputcsv($fp, $header);

  foreach ($nid_list as $values) {
    $node = node_load($values);
    $node_title = $node->title;
    $path = "node/" . $values;
    $meta_title = (isset($node->metatags[$node->language]['title']['value']) ? $node->metatags[$node->language]['title']['value'] : "");
    $meta_description = (isset($node->metatags[$node->language]['description']['value']) ? $node->metatags[$node->language]['description']['value'] : "");
    $meta_abstract = (isset($node->metatags[$node->language]['abstract']['value']) ? $node->metatags[$node->language]['abstract']['value'] : "");
    $meta_keywords = (isset($node->metatags[$node->language]['keywords']['value']) ? $node->metatags[$node->language]['keywords']['value'] : "");
    if (!empty($node_title) || !empty($meta_title) || !empty($meta_description) || !empty($meta_abstract) || !empty($meta_keywords)) {
      $row = array(
        $node->type,
        $node_title,
        $path,
        $meta_title,
        $meta_description,
        $meta_abstract,
        $meta_keywords,
        $node->language,
      );
      file_put_contents($file_url, $row, FILE_APPEND);
      fputcsv($fp, $row);
    }
  }

  fclose($fp);
  $file->filesize = filesize($file->uri);
  file_save($file);
  if (drupal_is_cli()) {
    drupal_set_message(dt("A File is created at  %file_url ", array('%file_url' => $file_url)));
    return ($file);
  }

  drupal_set_message(l('Download',file_create_url(($file_url))));
    
}
