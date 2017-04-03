<?php

/**
 * @file
 * Admin settings file for search_replace_blocks_menus module. 
 */

/**
 * Form constructor for search_replace_blocks_menus_input_form form.
 */
function search_replace_blocks_menus_input_form($form, &$form_state) {
  if (isset($_SESSION['scanner_search'])) {
    $search = $_SESSION['scanner_search'];
  }
  else {
    $search = NULL;
  }
  if (isset($_SESSION['scanner_replace'])) {
    $replace = $_SESSION['scanner_replace'];
  }
  else {
    $replace = NULL;
  }
  if (isset($_SESSION['scanner_block_checkbox'])) {
    $scanner_block_checkbox = $_SESSION['scanner_block_checkbox'];
  }
  else {
    $scanner_block_checkbox = 0;
  }
  if (isset($_SESSION['scanner_menu_checkbox'])) {
    $scanner_menu_checkbox = $_SESSION['scanner_menu_checkbox'];
  }
  else {
    $scanner_menu_checkbox = 0;
  }
  $form['checkbox'] = array(
    '#type' => 'checkboxes',
    '#options' => array(1 => t('Search Or Replace In Menus Title'), 2 => t('Search Or Replace In Blocks Body')),
    '#title' => t('Search and replace in following locations'),
    '#required' => TRUE,
    '#default_value' => array($scanner_block_checkbox,$scanner_menu_checkbox),
  );
  $form['search_string'] = array(
    '#type' => 'textfield',
    '#title' => t('Search'),
    '#required' => TRUE,
    '#default_value' => $search,
  );
  $form['search_submit'] = array(
    '#type' => 'submit',
    '#value' => t('Search'),
    '#submit' => array('search_replace_blocks_menus_form_submit_one'),
  );
  $form['replace_string'] = array(
    '#type' => 'textfield',
    '#title' => t('Replace'),
    '#required' => FALSE,
    '#default_value' => $replace,
  );
  $form['replace_submit'] = array(
    '#type' => 'submit',
    '#value' => t('Replace'),
    '#submit' => array('search_replace_blocks_menus_form_submit_two'),
  );
  return $form;
}

/**
 * Submission handler for node_generator_input_form on Serch button. 
 */
function search_replace_blocks_menus_form_submit_one($form, &$form_state) {
  $_SESSION['scanner_search']    = $form_state['values']['search_string'];
  $_SESSION['scanner_replace']   = $form_state['values']['replace_string'];
  if ($form['checkbox'][2]['#checked'] == 1) {
    $_SESSION['scanner_block_checkbox'] = 2;
  }
  else {
    $_SESSION['scanner_block_checkbox'] = 0;
  }
  if ($form['checkbox'][1]['#checked'] == 1) {
    $_SESSION['scanner_menu_checkbox'] = 1;
  }
  else {
    $_SESSION['scanner_menu_checkbox'] = 0;
  }
  global $base_url;
  $tmp = $form_state['values']['search_string'];
  $output = '';
  if ($form['checkbox'][2]['#checked'] == 1) {
    $result = db_select('block_custom', 'bc')
              ->fields('bc', array('info', 'bid'))
              ->condition('body', '%' . db_like($tmp) . '%', 'LIKE')
              ->execute()
              ->fetchAll();
    if (!empty($result)) {
      foreach ($result as $key => $value) {
        $output .= '<span class="msg' . $key . '"><a href="' . $base_url . '/admin/structure/block/manage/block/' . $value->bid . '/configure">Search String Found in Block "' . $value->info . '".</a></span><br />';
      }
    }
    else {
      $output .= '<span>No Match Found For Search String In Blocks.</span><br />';
    }
  }
  if ($form['checkbox'][1]['#checked'] == 1) {
    $query = db_select('menu_links', 'ml')->fields('ml', array('menu_name', 'mlid'));
    $db_or = db_or();
    $db_or->condition('link_title', '%' . db_like($tmp) . '%', 'LIKE');
    $query->condition($db_or);
    $result = $query->execute()->fetchAll();
    if (!empty($result)) {
      foreach ($result as $key => $value) {
        $output .= '<span><a href="' . $base_url . '/admin/structure/menu/item/' . $value->mlid . '/edit">Search String Found in Menu "' . $value->menu_name . '".</a></span><br />';
      }
    }
    else {
      $output .= '<span>No Match Found For Search String In Menus.</span><br />';
    }
  }
  drupal_set_message($output, 'status');
}

/**
 * Submission handler for node_generator_input_form on Replace button.
 */
function search_replace_blocks_menus_form_submit_two($form, &$form_state) {
  $_SESSION['scanner_search']    = $form_state['values']['search_string'];
  $_SESSION['scanner_replace']   = $form_state['values']['replace_string'];
  if ($form['checkbox'][2]['#checked'] == 1) {
    $_SESSION['scanner_block_checkbox'] = 2;
  }
  else {
    $_SESSION['scanner_block_checkbox'] = 0;
  }
  if ($form['checkbox'][1]['#checked'] == 1) {
    $_SESSION['scanner_menu_checkbox'] = 1;
  }
  else {
    $_SESSION['scanner_menu_checkbox'] = 0;
  }
  $output = '';
  $tmp = $form_state['values']['search_string'];
  if ($form['checkbox'][2]['#checked'] == 1) {
    $result = db_select('block_custom', 'bc')
              ->fields('bc', array('bid', 'body', 'info'))
              ->condition('body', '%' . db_like($tmp) . '%', 'LIKE')
              ->execute()
              ->fetchAll();
    if (!empty($result)) {
      foreach ($result as $key => $value) {
        $body = str_replace($tmp, $form_state['values']['replace_string'], $value->body);
        db_update('block_custom')
        ->fields(array('body' => $body))
        ->condition('bid', $value->bid, '=')
        ->execute();
        $output .= '<span class="msg' . $key . '">Entered String Replaced by ' . $form_state['values']['replace_string'] . ' in Block "' . $value->info . '".</span><br />';
      }
    }
    else {
      $output .= '<span>No Match Found For Entered String In Blocks.</span><br />';
    }
  }
  if ($form['checkbox'][1]['#checked'] == 1) {
    $query = db_select('menu_links', 'ml')
             ->fields('ml', array(
                 'mlid',
                 'link_path',
                 'link_title',
                 'menu_name',
                 )
                 );
    $db_or = db_or();
    $db_or->condition('link_title', '%' . db_like($tmp) . '%', 'LIKE');
    $query->condition($db_or);
    $result = $query->execute()->fetchAll();
    if (!empty($result)) {
      foreach ($result as $key => $value) {
        $title = str_replace($tmp, $form_state['values']['replace_string'], $value->link_title);
        db_update('menu_links')
        ->fields(array('link_title' => $title))
        ->condition('mlid', $value->mlid, '=')
        ->execute();
        $output .= '<span>Entered String Replaced by ' . $form_state['values']['replace_string'] . ' in "' . $value->menu_name . '".</span><br />';
      }
    }
    else {
      $output .= '<span>No Match Found For Entered String In Menus.</span><br />';
    }
  }
  drupal_set_message($output, 'status');
}

/**
 * Validate form.
 */
function search_replace_blocks_menus_input_form_validate($form, &$form_state) {
  if ($form_state['values']['replace_string'] == '' && $form_state['submit_handlers'][0] == 'search_replace_blocks_menus_form_submit_two') {
    form_set_error('replace_string', t('Please enter some keywords In Replace field.'));
    return;
  }
}
