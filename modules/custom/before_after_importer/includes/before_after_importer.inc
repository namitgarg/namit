<?php

/**
 * Function  :: before_after_importer_form
 * Building form Array
 * @param type $form 
 * @param type $form_state 
 */
function before_after_importer_form($form, &$form_state) {
  global $base_url;
  $form['afterbeforeholder'] = array(
    '#type' => 'fieldset',
    '#description' => t("Upload a CSV file."),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $file_size = t('Maximum file size: !size MB.', array('!size' => file_upload_max_size()));

  $form['afterbeforeholder']['file_upload'] = array(
    '#type' => 'file',
    '#title' => t('CSV File'),
    '#size' => 40,
    '#description' => t('Select the CSV file to be Import <i>Before After Node</i>\'s. ') . $file_size);

  $form['afterbeforeholder']['submit_button'] = array(
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
function before_after_importer_form_validate($form, &$form_state) {
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
function before_after_importer_form_submit($form, &$form_state) {
  // get the submitted value

  global $base_url;
  global $user;

  $line_max = variable_get('before_after_import_line_max', BEFORE_AFTER_IMPORT_LINE_MAX);
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


  $number_of_nodes = $send_counter - 1;
  // Create operations array.
  $operations = array();

  foreach ($data as $key => $nodedata) {
    $node_data_string = trim($nodedata[0]);
    // This function will contain code for node creation.
    if (!empty($node_data_string) && isset($node_data_string)) {
      $operations[] = array('before_after_create_nodes', array($nodedata));
    }
  }

  // Start Batch of node creation.
  $batch = array(
    'title' => t('Creating Before After Type Nodes Finally.'),
    'operations' => $operations,
    'finished' => 'before_after_batch_finished',
    'init_message' => t('Before After Type Node Creation Is Starting.'),
    'progress_message' => t('Processed @current out of @total.'),
    'error_message' => t('Before After Type Node creation has encountered an error.'),
    'file' => drupal_get_path('module', 'before_after_importer') . '/includes/before_after_importer.inc',
  );

  // Set the batch operation.
  batch_set($batch);
  batch_process('before-after-importer'); // The path to redirect to when done.
}

/**
 * Helper function to create nodes in batch process.
 * Function :: before_after_create_nodes
 * @param type $nodedata
 */
function before_after_create_nodes($nodedata, &$context) {
  /*
   *  Programatically Node Creation TYPE :: Gallery .... (Before and After Gallery Entry)
   */

  global $user;
  $node = new stdClass();
  $node->type = 'gallery';  // Content type gallery  for Before After Node
  $node->language = 'en';
  node_object_prepare($node);  //Setting some default values
  /*
   * Setting data for title field
   */

  if (isset($nodedata[0]) && !empty($nodedata[0]))
    $node->title = trim($nodedata[0]);
  else
    $node->title = 'NULL';


  /*
   * Setting data for body field
   */

  if (isset($nodedata[2]) && !empty($nodedata[2])) {
    $body = check_plain(trim($nodedata[2]));
    $node->body[LANGUAGE_NONE][0]['value'] = html_entity_decode($body);
    $node->body[LANGUAGE_NONE][0]['summary'] = text_summary(html_entity_decode($body));
    $node->body[LANGUAGE_NONE][0]['format'] = 'full_html';
  }


  /*
   * Setting data for Gallery type
   */

  if (isset($nodedata[1]) && !empty($nodedata[1])) {
    $hold_term_data = trim($nodedata[1]);
    $hold_term_data_strstr = strstr($hold_term_data, ',');


    if (strlen($hold_term_data_strstr) > 0) {
      $termRaw = trim($nodedata[1]);
      $termArray = explode(',', $termRaw);
      $termArrayCount = count($termArray);
      foreach ($termArray as $key => $data) {
        $passedData = trim($data);
        $term_id = __load_taxonomy_by_name($passedData);

        if (isset($term_id) && !empty($term_id)) {
          $node->field_gallery_type[LANGUAGE_NONE][$key]['tid'] = $term_id;
        }
      }
    }
    else {
      $elsepassedData = trim(trim($nodedata[1]));
      $term_id = __load_taxonomy_by_name($elsepassedData);
      if (isset($term_id) && !empty($term_id)) {
        $node->field_gallery_type[LANGUAGE_NONE][0]['tid'] = $term_id;
      }
    }
  }

// Code for Image Uploading section 
  if (isset($nodedata[3]) && !empty($nodedata[3])) {

    $images = explode(',', $nodedata[3]);
    $k = 1;
    foreach ($images as $imgkey => $imagechunk) {

      $before_after_img_combined = trim($imagechunk);


      //   preg_match_all("/\[([^\]]*)\]/", $before_after_img_combined, $matches);

      $___input = $before_after_img_combined;
      $___output = substr($___input, 1, -1);

      if (isset($___output) && !empty($___output)) {
        $CorretImage = $___output;
        $CorrectImageInArray = explode('|', $CorretImage);

        $before_img = $CorrectImageInArray[0];
        $after_img = $CorrectImageInArray[1];

        // Action for before image 
        if (isset($before_img) && !empty($before_img)) {
          $beforeFileObject = saving_before_after_image_programatically($before_img);
          $before_image_dynamic_variable = BEFORE_IMAGE_PREFIX . $k;
          $node->{$before_image_dynamic_variable}[LANGUAGE_NONE][0] = (array) $beforeFileObject;
        }

        // Action for after image 
        if (isset($after_img) && !empty($after_img)) {
          $afterFileObject = saving_before_after_image_programatically($after_img);
          $after_image_dynamic_variable = AFTER_IMAGE_PREFIX . $k;
          $node->{$after_image_dynamic_variable}[LANGUAGE_NONE][0] = (array) $afterFileObject;
        }
      }

      $k++;
    }
  }

// End code for image upload section 

  $node->status = 1;
  $node->promote = 0;
  $node->sticky = 0;
  $node->comment = 1;
  $node->uid = $user->uid;
  $node->date = time();
  $node->created = time();


  try {
    $success = node_save($node);
  }
  catch (Exception $e) {
    $context['results'][] = $node->nid . ' : ' . $nodedata[0];
    drupal_set_message('Failed to import record for - ' . $nodedata[0] . '::' . $e->getMessage(), 'warning');
    watchdog('before after gallery import error', 'There is a before after gallery import error:' . $e->getMessage());
  }
}

/**
 * Callback : Called when batch process is finished.
 */

/**
 * Function  :: before_after_batch_finished
 * @param type $success 
 * @param type $results 
 * @param type $operations 
 */
function before_after_batch_finished($success, $results, $operations) {

  if ($success) {
    drupal_set_message(t('Before and After Gallery Entry imported Successfully.'));
  }
  else {
    // An error occurred.
    // $operations contains the operations that remained unprocessed.
    $error_operation = reset($operations);
    drupal_set_message(t('An error occurred while processing @operation with arguments : @args', array('@operation' => $error_operation[0], '@args' => print_r($error_operation[0], TRUE))));
  }
}

/**
 * Aim of this function is returning the taxonomy term tid if term exist otherwise creates new one and return newly created
 * Function  :: __load_taxonomy_by_name
 * @param type $term termname
 */
function __load_taxonomy_by_name($term) {
    $term = trim($term);
   $vocab = taxonomy_vocabulary_machine_name_load(BEFORE_AFTER_TAXONOMY_MACHINENAME);
  $result = db_select('taxonomy_term_data', 't')
      ->fields('t', array('tid'))
      ->condition('name', $term, '=')
      ->condition('vid', $vocab->vid, '=')
      ->execute()
      ->fetchObject();
  // Checking whether taxonomy is available of not
  if (isset($result->tid) && !empty($result->tid)) {
    return $result->tid;
  }
  else {
    return create_taxonomy_term_by_vocabulary_machine_name($term);
  }
}

/**
 * Function ::  saving_before_after_image_programatically
 * @param type $filename Object
 */
function saving_before_after_image_programatically($filename) {

  global $base_url;
  $pathfile = $base_url . '/' . DIRECTORY_PATH_WHERE_FILES_PICKED;
  $fileRealName = $filename;
  $path = $pathfile . $fileRealName;
  $path = str_replace(' ', '%20', $path);
  $image = file_get_contents($path);
  $destination = 'public://' . $fileRealName;
  $file = file_save_data($image, $destination, FILE_EXISTS_REPLACE);
  if (is_object($file)) {
    $file->status = 1;
    $file = file_save($file);
  }
  return $file;
}

/**
 * This function creates the new term by loading the vocabulary machine name
 * Function ::  create_taxonomy_term_by_vocabulary_machine_name
 * @param type $newtermname 
 */
function create_taxonomy_term_by_vocabulary_machine_name($newtermname) {
  $vocab = taxonomy_vocabulary_machine_name_load(BEFORE_AFTER_TAXONOMY_MACHINENAME);

  $term1 = (object) array(
        'name' => $newtermname,
        'description' => $newtermname,
        'vid' => $vocab->vid,
  );

  taxonomy_term_save($term1);
  if (isset($term1->tid) && !empty($term1->tid))
    return $term1->tid;
  else
    return NULL;
}
