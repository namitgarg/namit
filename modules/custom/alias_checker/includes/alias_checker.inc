<?php

/**
 * Function  :: alias_checker_form
 * Building form Array
 * @param type $form 
 * @param type $form_state 
 */
function alias_checker_form($form, &$form_state) {
  global $base_url;
  $form['alias_checkerholder'] = array(
    '#type' => 'fieldset',
    '#description' => t("Upload a CSV file."),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $file_size = t('Maximum file size: !size MB.', array('!size' => file_upload_max_size() / 1024));

  $form['alias_checkerholder']['file_upload'] = array(
    '#type' => 'file',
    '#title' => t('CSV File'),
    '#size' => 40,
    '#description' => t('Select the CSV file to check whether <i>Alias</i> are exist or not. ') . $file_size);

  $form['alias_checkerholder']['submit_button'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );

  return $form;
}

/**
 * Implements hook_form_validate
 * @param type $form
 * @param type $form_state
 */
function alias_checker_form_validate($form, &$form_state) {
  // attempt to save the uploaded file
  $validators = array('file_validate_extensions' => array('csv'));

  $file = file_save_upload('file_upload', $validators);

  if (!$file) {
    form_set_error('file_upload', t('A file must be uploaded or selected.'));
  }
  else if ($file->filemime != 'text/csv') {
    form_set_error('file_upload', t('The file must be of CSV type only.'));
  }
  else {
    // set files to form_state, to process when form is submitted
    $form_state['values']['file_upload'] = $file;
  }
}

/**
 * Implements hook_form_submit
 * @param type $form
 * @param type $form_state
 */
function alias_checker_form_submit($form, &$form_state) {
  // get the submitted value

  global $base_url;
  global $user;

  $line_max = variable_get('alias_checker_import_line_max', ALIAS_CHECKER_LINE_MAX);
  $filepath = $form_state['values']['file_upload']->uri;
  $handle = fopen($filepath, "r");
  $send_counter = 0;

  $data = array();
  $label = array();

  while ($row = fgetcsv($handle, $line_max, ',')) {

    if ($send_counter == 0) {
      $label = $row;
    }
    else {
      $data[] = $row;
    }
    $send_counter++;
  }

  $number_of_chunk = $send_counter - 1;
  // Create operations array.
  $operations = array();

  foreach ($data as $key => $csvdata) {
    $first_string = trim($csvdata[0]);
    // This function will contain code for node creation.
    if (!empty($first_string) && isset($first_string)) {
      $operations[] = array('op_alias_checker', array($csvdata));
    }
  }

  // Start Batch of node creation.
  $batch = array(
    'title' => t('Checking the node alias finally....please wait....!'),
    'operations' => $operations,
    'finished' => 'op_alias_checker_batch_finished',
    'init_message' => t('Node alias checking started...please wait....!'),
    'progress_message' => t('Processed @current out of @total.'),
    'error_message' => t('Node alias checking process has encountered an error.'),
    'file' => drupal_get_path('module', 'alias_checker') . '/includes/alias_checker.inc',
  );

  // Set the batch operation.
  batch_set($batch);
  batch_process('alias-checker'); // The path to redirect to when done.
}

/**
 * Helper function to create nodes in batch process.
 * Function :: op_alias_checker
 * @param type $nodedata
 */
function op_alias_checker($csvdata, &$context) {
  /*
   *  Programatically checking the url alieas is exist or not
   */

  if (isset($csvdata[0]) && !empty($csvdata)) {
    $check = check_whether_alias_exist_not($csvdata[0]);

    if ($check == true) {
      drupal_set_message('URL Found:   ' . $csvdata[0]);
    }
    else {
      drupal_set_message('URL not Found:   ' . $csvdata[0], 'warning');
    }
  }
}

/**
 * Callback : Called when batch process is finished.
 */

/**
 * Function  :: op_alias_checker_batch_finished
 * @param type $success 
 * @param type $results 
 * @param type $operations 
 */
function op_alias_checker_batch_finished($success, $results, $operations) {

  if ($success) {
    drupal_set_message(t('Url processed successfully.'));
  }
  else {   
    // An error occurred.
    // $operations contains the operations that remained unprocessed.
    $error_operation = reset($operations);
    drupal_set_message(t('An error occurred while processing @operation with arguments : @args', array('@operation' => $error_operation[0], '@args' => print_r($error_operation[0], TRUE))));
  }
}

/**
 * Function  :: op_alias_checker_batch_finished
 * @param type $success 
 * @param type $results 
 * @param type $operations 
 */
function check_whether_alias_exist_not($url) {

  $substr = substr($url, strpos($url, '//') + 2);
  if (strpos($substr, '/') === FALSE) {
    return '';
  }

  $alias = str_replace(' ', '-', substr($substr, strpos($substr, '/') + 1));
  // Code that remove the '/' char from the string for handling the 1 level exception 
  // Removing the last character 
  $new_url_alieas = null;
  if (substr($alias, -1) == '/') {
    $trimmed = rtrim($alias, "/");
    $new_url_alieas = $trimmed;
  }
  else
    $new_url_alieas = $alias;

  if (check_alias_exist_or_not($new_url_alieas)) {
    // This code is never run
    return true;
  }
  else {
    return false;
  }
}

/**
 * Method to check whether given alias already exists or not.
 * @param type $alias.
 * @return string.
 */
function check_alias_exist_or_not($alias) {
  $sql = db_select('url_alias', 'ua');
  $sql->fields('ua', array('pid'));
  $sql->condition('ua.alias', $alias);
  return $sql->execute()->fetchField();
}