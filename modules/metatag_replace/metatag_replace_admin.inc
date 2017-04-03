<?php

/**
 * @file
 * All the search and replace operatons are performed here.
 */

/**
 * Checks field for Html and Php.
 *
 * @return bool
 *   True if fields contains No Html or Php.
 */
function metatag_replace_xss_check($data) {
  $new_data = strip_tags($data);
  if ($data == $new_data) {
    return TRUE;
  }
  else {
    return FALSE;
  }
}

/**
 * Gets the list of  Content Type for Content type dropdown.
 */
function metatag_replace_type_list() {
  $typedata = node_type_get_types();
  foreach ($typedata as $values1) {
    $type_machine_name = $values1->type;
    $type_human_name = t("@typename", array('@typename' => $values1->name));
    $func_content_type[$type_machine_name] = $type_human_name;
  }

  return $func_content_type;
}

/**
 * Defines Main form for the module to Search and Replace.
 */
function metatag_replace_form($form, &$form_state) {
  $intial_search = '';
  $default_replace = '';
  $default_case = '';
  $default_field = '';
  $content_type = metatag_replace_type_list();
  // All Content type will be selected by default.
  $default_type = array('all' => 'All');
  // To Merge list of individual content type with all option.
  $content_type = array_merge($default_type, $content_type);
  // List of Metatag fields.
  $field_list = array(
    "title" => t("Title"),
    "description" => t("Description"),
    "abstract" => t("Abstract"),
    "keywords" => t("Keywords"),
    "all" => t("All Tags"),
  );
  // To select Case sensitivity.
  $case_list = array(
    "sensitive" => t("Sensitive"),
    "insensitive" => t("Insensitive"),
  );
  $session_match = FALSE;
  if (!empty($_SESSION['metatag_replace_show_result']) && $_SESSION['metatag_replace_show_result'] == 'TRUE') {
    $default_type = $_SESSION['metatag_replace_type'];
    $intial_search = $_SESSION['metatag_replace_word_search'];
    $default_case = $_SESSION['metatag_replace_case'];
    $session_match = $_SESSION['metatag_replace_match'];
    $default_field = $_SESSION['metatag_replace_field_result'];
    if ($session_match == 1) {
      $session_match = TRUE;
    }
    if (isset($_SESSION['metatag_replace_word_replace'])) {
      $default_replace = $_SESSION['metatag_replace_word_replace'];
    }
  }
  $form['search_box'] = array(
    '#type' => 'textfield',
    '#required' => TRUE,
    '#title' => t("Search"),
    '#default_value' => $intial_search,
    '#description' => t("Enter the text to be searched for"),
  );
  $form['replace_box'] = array(
    '#type' => 'textfield',
    '#title' => t("Replace"),
    '#default_value' => $default_replace,
    '#description' => t("Enter the text to be replaced with"),
  );
  $form['content_type'] = array(
    '#type' => 'select',
    '#options' => $content_type,
    '#title' => t("Content type"),
    '#validated' => TRUE,
    '#required' => TRUE,
    '#default_value' => $default_type,
    '#description' => t("Select the Content type"),
  );
  $form['case'] = array(
    '#type' => 'select',
    '#options' => $case_list,
    '#title' => t("Case Sensitive"),
    '#validated' => TRUE,
    '#required' => TRUE,
    '#default_value' => $default_case,
    '#description' => t("Select whether to Search  Search with case Sensitive or not"),
  );
  $form['exact_match'] = array(
    '#type' => 'checkbox',
    '#options' => $session_match,
    '#title' => t("Exact Match"),
    '#validated' => TRUE,
    '#description' => t("Select to search exact words."),
    '#default_value' => $session_match,
  );
  $form['field_select'] = array(
    '#type' => 'select',
    '#options' => $field_list,
    '#title' => t("Field"),
    '#validated' => TRUE,
    '#required' => TRUE,
    '#default_value' => $default_field,
    '#description' => t("Choose meta fields to be Searched"),
  );
  $form['search'] = array(
    '#type' => 'submit',
    '#value' => t("Search"),
    '#validate' => array('metatag_replace_form_search_validate'),
    '#submit' => array('metatag_replace_form_search_submit'),
  );
  $form['replace'] = array(
    '#type' => 'submit',
    '#value' => t("Replace"),
    '#validate' => array('metatag_replace_form_replace_validate'),
    '#submit' => array('metatag_replace_form_replace_submit'),
  );
  // To Display the Result of The operation in the Field.
  if (!empty($_SESSION['metatag_replace_show_result']) && $_SESSION['metatag_replace_show_result'] == 'TRUE') {
    if ($_SESSION['metatag_replace_opn'] == 'complete') {
      $dispaly_result = $_SESSION['metatag_replace_result_of_replace'];
      $theme_name = 'metatag_replace_operation_replace';
    }
    elseif ($_SESSION['metatag_replace_opn'] == 'replace' || $_SESSION['metatag_replace_opn'] == 'search') {
      $dispaly_result = $_SESSION['metatag_replace_result_of_search'];
      $theme_name = 'metatag_replace_operation_search';
    }
    $form['results'] = array(
      '#type' => 'markup',
      '#theme' => $theme_name,
      '#list' => $dispaly_result,
    );
    $_SESSION['metatag_replace_show_result'] = FALSE;
  }
  return $form;
}
/**
 * Form Validation for Search Operation.
 */
function metatag_replace_form_search_validate($form, &$form_state) {
  $search_check = metatag_replace_xss_check($form_state['values']['search_box']);
  if (!$search_check) {
    form_set_error('search_box', t("Do not enter any HTML or PHP code."));
  }
}
/**
 * Form Validation for Replace operation.
 */
function metatag_replace_form_replace_validate($form, &$form_state) {
  if (empty($form_state['values']['replace_box'])) {
    form_set_error('replace_box', t("Replace Field is empty."));
  }
  if ($form_state['values']['replace_box'] == $form_state['values']['search_box']) {
    form_set_error('replace_box', t("Search and Replace Texts are Same."));
  }
  $search_check = metatag_replace_xss_check($form_state['values']['search_box']);
  if ($search_check == FALSE) {
    form_set_error('search_box', t("Do not enter any HTML or PHP code."));
  }
  $replace_check = metatag_replace_xss_check($form_state['values']['replace_box']);
  if ($replace_check == FALSE) {
    form_set_error('replace_box', t("Do not enter any HTML or PHP code."));
  }
}

/**
 * Submmit Handler for Search Operation.
 */
function metatag_replace_form_search_submit($form, &$form_state) {
  $opn = 'search';
  metatag_replace_search_operation($form, $form_state, $opn);
}

/**
 * Submit Handler for Replace Operation.
 */
function metatag_replace_form_replace_submit($form, &$form_state) {
  $opn = 'replace';
  metatag_replace_search_operation($form, $form_state, $opn);
}

/**
 * Gets nid of nodes and passes to batch.
 *
 * Information about variables used.
 * $_SESSION['metatag_replace_word_search']=>Stores the Search word.
 * $_SESSION['metatag_replace_word_replace']=> Stores The Replaced word.
 * $_SESSION['metatag_replace_field_result'] => Stores field to be searched.
 * $_SESSION['metatag_replace_case']=> Stores the Case Sensitivity.
 * $_SESSION['metatag_replace_match']=>Checks to search the exact word or not.
 * $_SESSION['metatag_replace_opn']=> Stores state of Operation.
 * $opn => Stores which operation is performed.
 */
function metatag_replace_search_operation($form, &$form_state, $opn) {
  $_SESSION['metatag_replace_word_search'] = $form_state['values']['search_box'];
  $_SESSION['metatag_replace_word_replace'] = $form_state['values']['replace_box'];
  $_SESSION['metatag_replace_field_result'] = $form_state['values']['field_select'];
  $_SESSION['metatag_replace_case'] = ($form_state['values']['case'] == "insensitive" ? "i" : "");
  $_SESSION['metatag_replace_match'] = ($form_state['values']['exact_match'] == "insensitive" ? "i" : "");
  $_SESSION['metatag_replace_show_result'] = "TRUE";
  $_SESSION['metatag_replace_opn'] = $opn;
  $type = $form_state['values']['content_type'];
  $_SESSION['metatag_replace_type'] = $type;
  // Define The batch For Search Operation.
  $batch = array(
    'operations' => array(),
    'finished' => 'metatag_replace_finish_batch_search',
    'title' => t("Processing  All Node For Searching"),
    'init_message' => t("Starting Metatag Search Operation"),
    'progress_message' => t("Processed @current out of @total Nodes"),
    'file' => drupal_get_path('module', 'metatag_replace') . '/metatag_replace_admin.inc',
    'error_message' => t("MetaTag Module has encountered an error."),
  );
  // Query to get nid from node table.
  $query = db_select('node', 'vd')
      ->fields('vd', array('nid', 'title'));
  if ($type != 'all') {
    $query->condition('type', $type);
  }
  elseif ($type = 'all') {
    $type = metatag_replace_type_list();
    $type = array_keys($type);
    $query->condition('type', ($type), 'IN');
  }
  $results = $query->execute()->fetchAll();
  if (empty($results)) {
    $_SESSION['metatag_replace_show_result'] = FALSE;
    drupal_set_message(t("No nodes exists for the Content type."), "status");
  }
  else {
    foreach ($results as $values) {
      $batch['operations'][] = array('metatag_replace_start_batch_search', array($values->nid));
    }
    batch_set($batch);
    // The path to redirect when batch process is completed.
    batch_process('admin/config/search/metatags/replace');
  }
}

/**
 * Batch Operation Callback.
 *
 * Information about variables used.
 * $context['results']['matches'] => Stores the result of Search operation.
 * $context['results']['detail] => Stores the link and nid of The found nodes.
 * $context['results']['matches1'] => Stores the Second field result.
 * $context => Stores context information about the execution.
 */
function metatag_replace_start_batch_search($values, &$context) {
  $nid_list = $values;
  $searchword = $_SESSION['metatag_replace_word_search'];
  $replaceword = $_SESSION['metatag_replace_word_replace'];
  $context['results']['search-word'] = $searchword;
  $context['results']['replace-word'] = $replaceword;
  $context['results']['opn'] = $_SESSION['metatag_replace_opn'];
  $node = node_load($nid_list);
  $meta_field = $_SESSION['metatag_replace_field_result'];
  $search_string = "/" . $_SESSION['metatag_replace_case'] . $searchword . $_SESSION['metatag_replace_case'] . "/" . $_SESSION['metatag_replace_case'];
  $node_title = $node->title;
  $meta_nid = $values;
  // To check all nodes that have Meta tags and store them.
  if (!empty($node->metatags[$node->language]['title']) || !empty($node->metatags[$node->language]['description']) || !empty($node->metatags[$node->language]['abstract']) || !empty($node->metatags[$node->language]['keywords'])) {
    if ($_SESSION['metatag_replace_field_result'] != 'all') {
      $match_field = $node->metatags[$node->language][$meta_field]['value'];
      $context['message'] = t("Meta %meta_field is working...", array('%meta_field' => $meta_field));
      $context['results']['field_result'] = $meta_field;
      preg_match($search_string, $match_field, $matches);
      if (!empty($matches)) {
        $context['results']['matches'][] = $match_field;
        $context['results']['detail']['nid'][] = $meta_nid;
        $context['results']['detail']['node_link'][] = l($node_title, 'node/' . $meta_nid);
      }
    }
    elseif ($_SESSION['metatag_replace_field_result'] == 'all') {
      $meta_title = $node->metatags[$node->language]['title']['value'];
      $meta_description = $node->metatags[$node->language]['description']['value'];
      $meta_abstract = $node->metatags[$node->language]['abstract']['value'];
      $meta_keywords = $node->metatags[$node->language]['keywords']['value'];
      $context['message'] = t("Meta All Tags  is working...");
      $context['results']['field_result'] = "all";
      preg_match($search_string, $meta_title, $matches);
      preg_match($search_string, $meta_description, $matches1);
      preg_match($search_string, $meta_abstract, $matches2);
      preg_match($search_string, $meta_keywords, $matches3);
      if (!empty($matches) || !empty($matches1) || !empty($matches2) || !empty($matches3)) {
        $context['results']['matches'][$meta_nid] = array();
        if (!empty($matches)) {
          $context['results']['matches'][$meta_nid]['title'][] = "Meta Title : " . $meta_title;
        }
        if (!empty($matches1)) {
          $context['results']['matches'][$meta_nid]['description'][] = "Meta Description : " . $meta_description;
        }
        if (!empty($matches2)) {
          $context['results']['matches'][$meta_nid]['abstract'][] = "Meta Abstract : " . $meta_abstract;
        }
        if (!empty($matches3)) {
          $context['results']['matches'][$meta_nid]['keywords'][] = "Meta Keywords : " . $meta_keywords;
        }
        $context['results']['detail'][$meta_nid]['nid'][] = $meta_nid;
        $context['results']['detail'][$meta_nid]['node_link'][] = l($node_title, 'node/' . $meta_nid);
      }
    }
  }
  $context['message'] = t("Matching the Meta Tags");
}

/**
 * Batch 'finished' callback for Search Operation.
 *
 * Information about variables used.
 * $success => The success parameter means no fatal PHP errors were detected.
 * $results =>  Stores the result of Batch process.
 * $operations => Stores Whether it is Search or Replace operation.
 */
function metatag_replace_finish_batch_search($success, $results, $operations) {
  if ($success) {
    $_SESSION['metatag_replace_result_of_search'] = $results;
    $opn = $results['opn'];
    $searchword = $results['search-word'];
    $replaceword = $results['replace-word'];
    $count = 0;
    $flag = TRUE;
    if (!empty($results['matches'])) {
      $count = count($results['matches']);
    }
    if ($count == 0) {
      drupal_set_message(t("No Matches Found"));
      $flag = FALSE;
    }
    if ($opn == 'search' && $flag) {
      $_SESSION['metatag_replace_show_result'] = 'TRUE';
      drupal_set_message(t("We found occurrences in %count Pages", array('%count' => $count)), 'status');
    }
    elseif ($opn == 'replace' && $flag) {
      $_SESSION['metatag_replace_show_result'] = 'TRUE';
      drupal_set_message(t("Do You want to replace [%searchword] with [%replaceword] at %count pages", array(
        '%searchword' => $searchword,
        '%replaceword' => $replaceword,
        '%count' => $count,
      )));
      drupal_goto('admin/config/search/metatags/replace/confirm');
    }
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
 * Confirm Form Function.
 *
 * @return form
 *   Return the array for form.
 */
function metatag_replace_confirm_form($form, &$form_state) {
  $form['confirm'] = array(
    '#type' => 'submit',
    '#value' => t("Confirm"),
    '#submit' => array('metatag_replace_confirm_form_submit'),
  );
  $form['cancel'] = array(
    '#type' => 'submit',
    '#value' => t("Cancel"),
    '#submit' => array('metatag_replace_cancel_form_submit'),
  );
  if ($_SESSION['metatag_replace_show_result'] == 'TRUE') {

    $form['results'] = array(
      '#type' => 'markup',
      '#theme' => 'metatag_replace_operation_search',
      '#list' => $_SESSION['metatag_replace_result_of_search'],
    );
  }
  return $form;
}

/**
 * Implements Submit Handler to Confirm Replace.
 */
function metatag_replace_confirm_form_submit($form, &$form_state) {
  $_SESSION['metatag_replace_opn'] = 'complete';
  $batch1 = array(
    'operations' => array(),
    'finished' => 'metatag_replace_batch_fix_finished',
    'title' => t("Replacing Meta tags Fields"),
    'init_message' => t("Metatag Replace Operation"),
    'progress_message' => t("Processed @current out of @total Nodes"),
    'file' => drupal_get_path('module', 'metatag_replace') . '/metatag_replace_admin.inc',
    'error_message' => t("Meta tag Module has encountered an error."),
  );
  if ($_SESSION['metatag_replace_result_of_search']['field_result'] != 'all') {
    $replace_list = $_SESSION['metatag_replace_result_of_search']['matches'];
    $nid_replace = $_SESSION['metatag_replace_result_of_search']['detail']['nid'];
    $node_replace_link = $_SESSION['metatag_replace_result_of_search']['detail']['node_link'];
    foreach ($node_replace_link as $keys => $values) {
      $batch1['operations'][] = array('metatag_replace_start_batch_replace_single', array(
        $values,
        $nid_replace[$keys],
        $replace_list[$keys],
      ),
      );
    }
  }
  else {
    $replace_list = $_SESSION['metatag_replace_result_of_search']['matches'];
    $replace_detail = $_SESSION['metatag_replace_result_of_search']['detail'];
    foreach ($replace_list as $keys => $values) {
      $batch1['operations'][] = array('metatag_replace_start_batch_replace_all', array(
        $values,
        $replace_detail[$keys],
      ),
      );
    }
  }
  batch_set($batch1);
  batch_process('admin/config/search/metatags/replace/');
}

/**
 * Batch Process for Single Field.
 *
 * Information about variables used.
 * $node_title=> Stores the title of node.
 * $nid => Stores the nid of the Node.
 * $meta_list => Stores the meta Field for the node.
 * $context => Stores context information about the execution.
 */
function metatag_replace_start_batch_replace_single($node_link, $nid, $meta_list, &$context) {
  $searchword = $_SESSION['metatag_replace_word_search'];
  $replaceword = $_SESSION['metatag_replace_word_replace'];
  $search_string = "/" . $_SESSION['metatag_replace_case'] . $searchword . $_SESSION['metatag_replace_case'] . "/" . $_SESSION['metatag_replace_case'];
  $replace_result = preg_replace($search_string, $replaceword, $meta_list);
  $context['results']['replace'][] = $replace_result;
  $context['results']['detail']['nid'][] = $nid;
  $context['results']['detail']['node_link'][] = $node_link;
  $context['results']['opn'] = "complete";
  $context['results']['field_result'] = $_SESSION['metatag_replace_field_result'];
  $node = node_load($nid);
  $node->metatags[$node->language][$_SESSION['metatag_replace_field_result']]['value'] = $replace_result;
  $node->revision = 1;
  $node->log = "Modified by Meta tag replace module Replaced $searchword with $replaceword";
  node_save($node);
}

/**
 * This is the batch process for Replace operation.
 *
 * Information about variables used.
 * $node_title => Stores the title of node.
 * $nid => Stores the nid of node.
 * $meta_list => Stores the meta title for operation.
 * $meta_description => Stores the meta description for operation.
 * $meta_abstract => Stores the meta abstract for operation.
 * $meta_keywords => Stores the meta keywords for operayions.
 * $context => Stores context information about the execution.
 */
function metatag_replace_start_batch_replace_all($meta_list, $meta_detail, &$context) {
  $nid = $meta_detail['nid'][0];
  $node_link = $meta_detail['node_link'][0];
  $searchword = $_SESSION['metatag_replace_word_search'];
  $replaceword = $_SESSION['metatag_replace_word_replace'];
  $replace_result_title = metatag_replace_perform_replace($meta_list['title'][0]);
  $replace_result_description = metatag_replace_perform_replace($meta_list['description'][0]);
  $replace_result_abstract = metatag_replace_perform_replace($meta_list['abstract'][0]);
  $replace_result_keywords = metatag_replace_perform_replace($meta_list['keywords'][0]);
  $context['results']['opn'] = "complete";
  $context['results']['field_result'] = $_SESSION['metatag_replace_field_result'];
  $context['results']['replace'][$nid] = array();
  $context['results']['detail'][$nid]['node_link'] = $node_link;
  $node = node_load($nid);
  if ($replace_result_title != "") {
    $node->metatags[$node->language]['title']['value'] = $replace_result_title;
    $context['results']['replace'][$nid]['title'] = "Meta title : " . $replace_result_title;
  }
  if ($replace_result_description != "") {
    $node->metatags[$node->language]['description']['value'] = $replace_result_description;
    $context['results']['replace'][$nid]['description'] = "Meta description : " . $replace_result_description;
  }
  if ($replace_result_abstract != "") {
    $node->metatags[$node->language]['abstract']['value'] = $replace_result_abstract;
    $context['results']['replace'][$nid]['abstract'] = "Meta abstract : " . $replace_result_abstract;
  }
  if ($replace_result_keywords != "") {
    $node->metatags[$node->language]['keywords']['value'] = $replace_result_keywords;
    $context['results']['replace'][$nid]['keywords'] = "Meta Keywords : " . $replace_result_keywords;
  }
  $node->revision = 1;
  $node->log = "Modified by Meta tag replace module Replaced $searchword with $replaceword";
  node_save($node);
}
/**
 * Helper function to perform replace on Meta tags.
 *
 * $search_result => stores the result of Meta fields.
 */
function metatag_replace_perform_replace($search_result) {
  $searchword = $_SESSION['metatag_replace_word_search'];
  $replaceword = $_SESSION['metatag_replace_word_replace'];
  $search_string = "/" . $_SESSION['metatag_replace_case'] . $searchword . $_SESSION['metatag_replace_case'] . "/" . $_SESSION['metatag_replace_case'];
  $search_tag = explode(": ", $search_result, "2");
  $match_tag = $search_tag[1];
  return preg_replace($search_string, $replaceword, $match_tag);
}

/**
 * Batch 'finished' callback for Replace Operation.
 *
 * Information about variables used.
 * $success => The success parameter means no fatal PHP errors were detected.
 * $results => Stores the result of Batch process.
 * $operations => Stores Whether it is Search or Replace operation.
 */
function metatag_replace_batch_fix_finished($success, $results, $operations) {
  if ($success) {
    $searchword = $_SESSION['metatag_replace_word_search'];
    $replaceword = $_SESSION['metatag_replace_word_replace'];
    $count = count($results['replace']);
    $_SESSION['metatag_replace_result_of_replace'] = $results;
    drupal_set_message(t("Replaced %count occurrences of %searchword in pages with %replaceword", array(
      '%count' => $count,
      '%searchword' => $searchword,
      '%replaceword' => $replaceword,
    )
        ),
      'status'
        );
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
 * Submit Handler for Cancel Operation for Replace Operation.
 */
function metatag_replace_cancel_form_submit($form, &$form_state) {
  drupal_set_message(t("You pressed cancel button"));
  $form_state['redirect'] = 'admin/config/search/metatags/replace';
}
