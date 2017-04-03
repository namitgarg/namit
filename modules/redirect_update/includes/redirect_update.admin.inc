<?php

/**
 * @file
 * Admin settings file for Redirect Update module. 
 */

/**
 * Form generator for redirect update module.
 * @return array
 */
function _redirect_update_form() {
  $form = array();
  $form['node_body_update'] = array(
    '#type' => 'checkbox',
    '#title' => '<strong>' . t('Node Content') . '</strong>',
    '#description' => t('Select to update the node body content.'),
  );
  $form['redirect_update_fieldset'] = array(
      '#type' => 'fieldset',
      '#title' => t('Select Content Types'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#states' => array(
        'invisible' => array(
          ':input[name="node_body_update"]' => array('checked' => FALSE),
        ),  
      ),
  );
  
  $form['redirect_update_fieldset']['redirect_updatecheck_uncheck_all'] = array(
    '#type' => 'checkbox',
    '#title' => '<strong>' . t('Select All') . '</strong>',
  );
  $content_types = node_type_get_names(); //Get all content types.
  $form['redirect_update_fieldset']['content_types_check'] = array(
    '#type' => 'checkboxes',
    '#options' => $content_types,
    '#description' => t('Select the content types for which you want to update the redirections.'),
    '#prefix' => '<div class=\'redirect-update-all-ccontent-types\'>',
    '#suffix' => '</div>',  
  );
  
  $form['block_update'] = array(
    '#type' => 'checkbox',
    '#title' => '<strong>' . t('Block Content') . '</strong>',
    '#description' => t('Select to update the block content.'),
  );
  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Update'),
  );
  
  $form['#attached']['css'] = array(
      drupal_get_path('module', 'redirect_update') . '/js_css/redirect_update.css',
  );
  $form['#attached']['js'] = array(
      drupal_get_path('module', 'redirect_update') . '/js_css/redirect_update.js',
  );
  
  return $form;
}

/**
 * Validation handler for _redirect_update_form form.
 * @param array $form
 * @param array $form_state 
 */
function _redirect_update_form_validate(&$form, &$form_state) { 
  $node_body_update = $form_state['values']['node_body_update'];
  $block_update = $form_state['values']['block_update'];
  $content_types = array_filter($form_state['values']['content_types_check']); //Get all selected content types.
  if ($node_body_update == 0 && $block_update == 0) { //If nothing is selected.
    form_set_error('node_body_update', t('Please choose node / block.'));
  }
  elseif ($node_body_update == 1 && count($content_types) < 1) { //If content type is not selected.
    form_set_error('content_types_check', t('Please choose atleast one content type.'));
  }
}

/**
 * Submit handler for _redirect_update_form form.
 * @param array $form
 * @param array $form_state 
 */
function _redirect_update_form_submit(&$form, &$form_state) {
  $node_update = $form_state['values']['node_body_update'];
  $block_update = $form_state['values']['block_update'];
  $content_types = array_filter($form_state['values']['content_types_check']); //Get all selected content types.
  
  //Bacth array.
  $batch = array(
    'title' => t('Updating Redirects...'),
    'error_message' => t('An error occurred during processing'),
    'init_message' => t('Updating'),
    'operations' => array(),
    'file' => drupal_get_path('module', 'redirect_update') . '/includes/redirect_update.admin.inc',  
    'finished' => '_redirect_update_batch_finished',
  );
  
  //Get all redirects from db.
  $redirects = _redirect_update_get_all_redirects();
  foreach ($redirects as $redirect) {
    //Uncomment below method for without batch testing. Just comment the batch_set() method to stop batch processing.
    //_redirect_update_batch_process($redirect, $node_update, $block_update, $content_types, $context);
    $batch['operations'][] = array('_redirect_update_batch_process', array($redirect, $node_update, $block_update, $content_types));
  }
  //Batch Processing starts here.
  batch_set($batch);
}

/**
 * Batch processing callback for _redirect_update_form form.
 * @param array $redirect
 * @param int $node_update
 * @param int $block_update
 * @param array $content_types
 * @param array $context 
 */
function _redirect_update_batch_process($redirect, $node_update, $block_update, $content_types, &$context) {
  $redirect->redirect = _redirect_update_check_alias($redirect->redirect);
  if ($node_update == 1) {  //If node content checkbox is checked.
    _redirect_update_node_processing($redirect, $content_types, $context);
  }
  
  if ($block_update == 1) {//If block content checkbox is checked.
    _redirect_update_block_processing($redirect, $context);
  }
}

/**
 * Callback called after successfully completion of batch processing.
 * @param boolean $success
 * @param array $results
 * @param array $operations 
 */
function _redirect_update_batch_finished($success, $results, $operations) {
  $message = "";
  if ($success) {
    $message = t('Redirects updated successfully !');
    if (isset($results['body'])) {  //Status message for node body.
      $res = array_unique($results['body']);  //Remove duplicate messages.
      $message .= "<br>";
      foreach ($res as $val) {
        $message .= t($val) . "<br>";
      }
    }
    
    if (isset($results['block'])) { //Status message for block content.
      $res = array_unique($results['block']);  //Remove duplicate messages.
      $message .= "<br>";
      foreach ($res as $val) {
        $message .= t($val) . "<br>";
      }
    }
    
    if (isset($results['total']['body'])) {  //Total node update count message.
      $message .= t('Total @count updates in node body content.', array('@count' => $results['total']['body'])) . "<br>";
    }
    if (isset($results['total']['block'])) {  //Total block update count message.
      $message .= t('Total @count updates in block body content.', array('@count' => $results['total']['block'])) . "<br>";
    }
    
    if (!isset($results['total']['block']) && !isset($results['total']['body'])) {  //If there is nothing to update.
      $message .= "<br>";
      $message .= t('There was nothing to update !');
    }
  }
  else {
    $message = t("There was a problem in updating redirects.");
  }
  cache_clear_all(); //Clear all the cache.
  drupal_set_message($message); //Status message to display.
}

/**
 * Processing the node body content.
 * @param array $redirect
 * @param array $content_types
 * @param array $context 
 */
function _redirect_update_node_processing($redirect, $content_types, &$context) {
  $nids = _redirect_update_get_node_by_types($content_types);
  //Create the instance of RedirectUpdate. At this point we are setting id=0 as we dont know the id yet.
  $callback = new RedirectUpdate('body', 0, $redirect->source, $redirect->redirect, $context);
  foreach ($nids as $nid) {
    $node = node_load($nid->nid);
    if (isset($node->body)) {  //If node contains body.
      $callback->_set_id($nid->nid);
      $content_old = $node->body['und'][0]['value'];
      $content_new = preg_replace_callback('!<a.*?href=[\'"]([^\'"]+)[\'"].*?>!', array($callback, '_callback_replace'), $content_old);
      if ($content_new != $content_old) {  //If there is any change in content only then we will save and create the revision.
        $node->body['und'][0]['value'] = $content_new;
        node_save($node);  //Saving updated node.
      }
    }
  }
}

/**
 * Processing the block body content.
 * @param array $redirect
 * @param array $context 
 */
function _redirect_update_block_processing($redirect, &$context) {
  $blocks = _redirect_update_get_blocks();
  //Create the instance of RedirectUpdate. At this point we are setting id=0 as we dont know the id yet.
  $callback = new RedirectUpdate('block', 0, $redirect->source, $redirect->redirect, $context);
  foreach ($blocks as $block) {
    $callback->_set_id($block->bid);
    $content_old = $block->body;
    $content_new = preg_replace_callback('!<a.*?href=[\'"]([^\'"]+)[\'"].*?>!', array($callback, '_callback_replace'), $content_old);
    //if ($content_new != $content_old) { //If there is any change in content only then we will save.
      db_update('block_custom')->fields(array('body' => $content_new))->condition('bid', $block->bid, '=')->execute(); //Update the block content.
    //}
  }
}

/**
 * Get all available blocks which having content.
 * @return array Returns all the blocks which having body part.
 */
function _redirect_update_get_blocks() {
  $query = db_select('block_custom', 'bc');
  $query->fields('bc', array('bid', 'body', 'format'));
  $blocks = $query->execute()->fetchAll();
  return $blocks;
}
/**
 * Get all nids from db of specified content types.
 * @param array $content_types
 * @return array 
 */
function _redirect_update_get_node_by_types($content_types) {
  $nodes = &drupal_static(__FUNCTION__);
  if (!isset($nodes)) {
    $query = db_select('node', 'nd');
    $query->fields('nd', array('nid'));
    $query->condition('nd.type', $content_types, 'IN');
    $nodes = $query->execute()->fetchAll();
  }
  return $nodes;
}

/**
 * Method to get the all available redirects from db (table {redirect}).
 * @return Array Array of all the redirects and their sources.
 */
function _redirect_update_get_all_redirects() {
  $redirects = &drupal_static(__FUNCTION__);
  if (!isset($redirects)) {
    $query = db_select('redirect', 'rd');
    $query->fields('rd', array('rid', 'source', 'redirect'));
    $redirects = $query->execute()->fetchAll();
  }
  return $redirects;
}

/**
 * Method to check whether the alias exist of a url or not.
 * If exists, then return the alias else return original url
 * as provided to the method as argument.
 * @param string $redirect
 * @return string
 *   If alias exists, then return the alias else the supplied path as it is (without change).
 */
function _redirect_update_check_alias($redirect) {
  $alias = drupal_lookup_path('alias', $redirect);
  if (!$alias) {  //If no alias exists.
    $alias = $redirect;
  }
  return $alias;
}