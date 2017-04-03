<?php

/**
 * @file
 * Used to create file upload field and provide download link after processing.
 */

/**
 * Implements hook_form().
 */
function _get_metatags_form($form, &$form_state) {
  $form['file_upload'] = array(
    '#type' => 'managed_file',
    '#title' => t('Upload file here'),
    '#description' => t('Upload your file here for metatags'),
    '#required' => TRUE,
    '#upload_location' => 'public://getmeta/',
    '#upload_validators' => array(
      'file_validate_extensions' => array('csv'),
    ),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );
  return $form;
}

/**
 * Form Submit of _get_metatags_form.
 */
function _get_metatags_form_submit($form, &$form_state) {
  $file_path = drupal_get_path('module', 'get_metatags') . '/include/simple_html_dom.php';
  if (file_exists($file_path)) {
    $file_id = $form_state['values']['file_upload'];
    $sql = db_select('file_managed', 'fm');
    $sql->fields('fm', array('uri'));
    $sql->condition('fm.fid', $file_id);
    $uri = $sql->execute()->fetchField();
    if (!empty($uri)) {
      if (file_exists(drupal_realpath($uri))) {
        $handle = fopen(drupal_realpath($uri), "r");
        $batch = array(
          'title' => t('Importing CSV...'),
          'error_message' => t('The installation has encountered an error.'),
          'init_message' => t('Creating'),
          'operations' => array(),
          'file' => drupal_get_path('module', 'get_metatags') . '/include/get_metatags.inc',
          'finished' => '_get_metatags_import_finished',
        );
        $counter = 0;
        while (($data = fgetcsv($handle, 0, ',', '"')) !== FALSE) {
          if ($counter >= 1) {
            $data['fileid'] = $file_id;
            $batch['operations'][] = array('get_metatags_batch_processing', array($data));
          }
          $counter++;
        }

        batch_set($batch);
        fclose($handle);
      }
    }
  }
  else {
    drupal_set_message(t('Please download the latest version of PHP Simple HTML DOM Parser library from http://sourceforge.net/projects/simplehtmldom/ to your include folder '.drupal_get_path('module', 'get_metatags').'/include/simple_html_dom.php'), 'error');
  }
}


/**
 * Batch processing to upload csv file and get meta details in processing.
 */
function get_metatags_batch_processing($content, &$context) {
  $insert_url = $content[0];
  if ($insert_url != '') {
    $url_extension = pathinfo($insert_url);
    $url_ext = strtolower(trim($url_extension['extension']));
    if ($url_ext != 'doc' && $url_ext != 'pdf' && $url_ext != 'jpg' && $url_ext != 'gif') {

      module_load_include('php', 'get_metatags', '/include/simple_html_dom');
      $html = file_get_html($insert_url);
      $h1tag_text = get_metatags_getTextBetweenTags('h1', $html);
      $title_text = get_metatags_getTextBetweenTags('title', $html);
      foreach ($h1tag_text as $item) {
        $content['h1_name'] = $item;
      }
      foreach ($title_text as $items) {
        $content['title_text'] = $items;
      }

      $tags = get_meta_tags($insert_url);

      $tags_desc = $tags['description'];
      $tags_keywords = $tags['keywords'];
    }
    else {

      $content['h1_name'] = '';
      $content['title_text'] = '';
      $tags_desc = '';
      $tags_keywords = '';
    }
    db_insert('get_metatags')->fields(array(
                                'site_url' => $insert_url,
                                'h1' => $content['h1_name'],
                                'page_title' => $content['title_text'],
                                'description' => $tags_desc,
                                'keywords' => $tags_keywords,
                                'fid' => $content['fileid']))->execute();
    $context['results']['fid'] = $content['fileid'];
  }
}

/**
 * Function used for get Text between tags.
 */
function get_metatags_getTextBetweenTags($tag, $html, $strict = 0) {
  /*   * * a new dom object ** */
  $dom = new domDocument();

  /*   * * load the html into the object ** */
  $dom->loadHTML($html);

  /*   * * discard white space ** */
  $dom->preserveWhiteSpace = FALSE;

  /*   * * the tag by its tag name ** */
  $content = $dom->getElementsByTagname($tag);

  /*   * * the array to return ** */
  $out = array();
  foreach ($content as $item) {
    /*     * * add node value to the out array ** */
    $out[] = $item->nodeValue;
  }
  /*   * * return the results ** */
  return $out;
}

/**
 * After completing batch processing _get_metatags_import_finished work.
 */
function _get_metatags_import_finished($success, $results, $operations) {
  if ($success) {
    if(isset($results['fid'])) {
      $csv_file_id = trim($results['fid']);
      drupal_set_message(l(t("Download File"), 'admin/config/system/get-metatags/download', array('query' => array("fid" => $csv_file_id))));
    }
  }
}
