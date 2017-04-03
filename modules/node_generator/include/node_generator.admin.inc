<?php

/**
 * @file
 * Admin settings file for node_generator module. 
 */

/**
 * Form constructor for node_generator_input_form form.
 */
function _node_generator_input_form($form, &$form_state) {
  drupal_set_title(t('Node Generator'));
  $form['content_pattern'] = array(
    '#type' => 'textfield',
    '#title' => t('Content Pattern'),
    '#required' => TRUE,
    '#description' => t('element.classname ') . '<strong>(like h1.classname) or element#id(like div#foo)</strong>' . t(' For multiple patterns, seperate them by \',\''),
  );
  $form['title_pattern'] = array(
    '#type' => 'textfield',
    '#title' => t('Title Pattern'),
    '#required' => TRUE,
    '#description' => t('element.classname ') . '<strong>(like h1.classname) or element#id(like div#foo)</strong>' . (' For multiple patterns, seperate them by \',\''),
  );
  $content_types = node_type_get_names(); //Get all content types list
  foreach ($content_types as $key => $val) {
    if (!_node_generator_get_content_types($key, 'body')) { //Check if given content type contains body field or not.
      unset($content_types[$key]); //If not contain body field, remove that content type from list.
    }
  }
  $form['select_content_type'] = array(
    '#type' => 'select',
    '#options' => array('' => t('Select')) + $content_types,
    '#title' => t('Select Content Type'),
    '#required' => TRUE,
    '#description' => t('Select content type for which you want to create the node.'),
  );
  $form['category_pattern'] = array(
    '#type' => 'textfield',
    '#title' => t('Category Pattern'),
    '#required' => False,
    '#description' => t('element.classname ') . '<strong>(like h1.classname) or element#id(like div#foo)</strong>' . (' For multiple patterns, seperate them by \',\''),
  );
  $form['category_field'] = array(
    '#type' => 'select',
    '#options' => array('' => t('Select')),
    '#title' => t('Select Field For Category'),
    '#validated' => TRUE,
    '#required' => false,
    '#description' => t('Select Term Refrence Field for Selected Content Type For which you want to create the category.'),
  );
  $form['tag_pattern'] = array(
    '#type' => 'textfield',
    '#title' => t('Tag Pattern'),
    '#required' => False,
    '#description' => t('element.classname ') . '<strong>(like h1.classname) or element#id(like div#foo)</strong>' . (' For multiple patterns, seperate them by \',\''),
  );
  $form['tag_field'] = array(
    '#type' => 'select',
    '#options' => array('' => t('Select')),
    '#title' => t('Select Field For Tags'),
    '#validated' => TRUE,
    '#required' => false,
    '#description' => t('Select Term Refrence Field for Selected Content Type For which you want to create the Tags.'),
  );
  $form['date_pattern'] = array(
    '#type' => 'textfield',
    '#title' => t('Post Date Pattern'),
    '#required' => False,
    '#description' => t('element.classname ') . '<strong>(like h1.classname) or element#id(like div#foo)</strong>' . (' For multiple patterns, seperate them by \',\''),
  );
  $form['upload_file'] = array(
    '#type' => 'managed_file',
    '#title' => t('Upload File'),
    '#required' => False,
    '#description' => t('Allowed Extensions: xml'),
    '#upload_location' => 'public://node_generator/',
    '#upload_validators' => array(
      'file_validate_extensions' => array('xml'),
      'file_validate_size' => array(1 * 1024 * 1024),
    ),
  );
  $form['xml_file_url'] = array(
    '#type' => 'textfield',
    '#title' => t('External URL Path Of XML File.'),
    '#required' => False,
//'#description' => t('element.classname ') . '<strong>(like h1.classname) or element#id(like div#foo)</strong>' . (' For multiple patterns, seperate them by \',\''),
  );
  $form['replace_domain'] = array(
    '#type' => 'checkbox',
    '#prefix' => '<b>Do You Want to Replace Domain.</b>',
    '#default_value' => 0,
  );

  // Code start adding by ISHWAR


  $form['url_patternflag'] = array(
    '#title' => 'Select the url pattern type',
    '#type' => 'radios',
    '#options' => array('Take Complete URL part', 'Take Last URL part'),
    '#default_value' => 0,
  );


  $form['url_patternflag_patternholder'] = array(
    '#type' => 'textfield',
    '#title' => t('Url pattern'),
    '#description' => t('Enter url pattern'),
    '#states' => array(
      'visible' => array(
        ':input[name="url_patternflag"]' => array('value' => 1),
      ),
    ),
  );



  // End code by ISHWAR


  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit')
  );
  $form['information'] = array(
    '#markup' => '<div><strong>' . t('Note:- Please use pattern only for class or id') . '</strong></div>',
  );
  return $form;
}

/**
 * Form validate for node_generator_input_form form.
 */
function _node_generator_input_form_validate($form, &$form_state) {
  if ($form_state['values']['xml_file_url'] == '' && $form_state['values']['upload_file'] == '') {
    form_set_error('upload_file', t('Please Select Atleast 1 Field.'));
    form_set_error('xml_file_url');
  }
  $check_url = valid_url($form_state['values']['xml_file_url'], $absolute = TRUE);
  if (!$check_url && $form_state['values']['xml_file_url'] != '') {
    form_set_error('xml_file_url', t('Please Enter Valid URL.'));
  }
  if ($form_state['values']['xml_file_url'] != '') {
    $xml = get_content_from_xml_loc($form_state['values']['xml_file_url']);
    $validate_xml = simplexml_load_string($xml);
    if (!$validate_xml) {
      form_set_error('xml_file_url', t('Not Valid XML.'));
    }
  }
  if ($form_state['values']['xml_file_url'] == '' && $form_state['values']['upload_file'] != '') {
    $f = file_load($form_state['values']['upload_file']);
    $urll = file_create_url($f->uri);
    $xml = get_content_from_xml_loc($urll);
    $validate_xml = simplexml_load_string($xml);
    if (!$validate_xml) {
      form_set_error('edit_upload_file', t('Uploded File Is Not Valid XML.'));
    }
  }

  // Code added by ISHWAR

  if ($form_state['values']['url_patternflag'] == 1) {
    if (empty($form_state['values']['url_patternflag_patternholder'])) {
      form_set_error('url_patternflag_patternholder', t('Enter Url pattern please! '));
    }
  }


  // Code end by ISWHAR
}

/**
 * Submission handler for node_generator_input_form form.
 * @param type $form
 * @param type $form_state 
 */
function _node_generator_input_form_submit($form, &$form_state) {
  $batch = array(
    'title' => t('Parsing XML File...'),
    'error_message' => t('An error occurred during processing'),
    'init_message' => t('Creating'),
    'operations' => array(),
    'file' => drupal_get_path('module', 'node_generator') . '/include/node_generator.admin.inc',
    'finished' => '_node_generator_batch_finished',
  );
  if ($form_state['values']['xml_file_url'] != '') {
    $response_xml_data = get_content_from_xml_loc($form_state['values']['xml_file_url']);
    if ($response_xml_data) {
      $xml = simplexml_load_string($response_xml_data);  //Read the xml file.  
    }
  }
  else {
    $xml = simplexml_load_file(drupal_realpath(file_load($form_state['values']['upload_file'])->uri));  //Read the xml file.
  }

  foreach ($xml as $url) {
    $param = array(
      'url' => (string) $url->loc,
      'type' => $form_state['values']['select_content_type'],
      'content_pattern' => $form_state['values']['content_pattern'],
      'title_pattern' => $form_state['values']['title_pattern'],
      'category_pattern' => $form_state['values']['category_pattern'],
      'tag_pattern' => $form_state['values']['tag_pattern'],
      'date_pattern' => $form_state['values']['date_pattern'],
      'category_field' => $form_state['values']['category_field'],
      'tag_field' => $form_state['values']['tag_field'],
      'replace_domain' => $form_state['values']['replace_domain'],
      'replace_domain' => $form_state['values']['replace_domain'],
      // Start code by ISHWAR
      'url_patternflag' => $form_state['values']['url_patternflag'],
      'url_patternflag_patternholder' => $form_state['values']['url_patternflag_patternholder'],
        // End code adding by ISHWAR
    );
//This is only for testing purpose without batch processing.
//_node_generator_processing($param, $context);
    $batch['operations'][] = array('_node_generator_processing', array($param));
  }

//Batch Processing starts here.
  batch_set($batch);
}

/**
 * Process the node generation in for each url and pattern.
 * @param type $content
 * @param type $context
 */
function _node_generator_processing($content = array(), &$context) {
  module_load_include('php', 'node_generator', 'include/simple_html_dom');  //Add the simple_html_dom.php file.
  $trimed_url = trim($content['url']);
  $html = file_get_html($trimed_url);  //Read the html from url.
  $valid = TRUE;

  $img = get_image_from_uri($html, $content['url']);
  $get_anchor_files = get_files_from_href($html, $content['url']);
//For Taxonomy Term.
  $category = array();
  foreach (explode(',', $content['category_pattern']) as $pattern_category) {
    foreach ($html->find($pattern_category) as $var_category) {
      $category[] = $var_category->innertext;
    }
  }
  $tag = array();
  foreach (explode(',', $content['tag_pattern']) as $pattern_tag) {
    foreach ($html->find($pattern_tag) as $var_tag) {
      $tag[] = $var_tag->innertext;
    }
  }
  $date = '';
  foreach (explode(',', $content['date_pattern']) as $pattern_date) {
    foreach ($html->find($pattern_date) as $var_date) {
      $date = $var_date->innertext;
      if (!empty($date)) {  //If we finds the content, no need to iterate more.
        break;
      }
    }
    if (!empty($date)) {  //If we finds the content, no need to iterate more.
      break;
    }
  }
//For Metatags.
  $metatags = array();
  $page_title = '';
  foreach (get_metatags_url($content['url']) as $key => $val) {
    if (!empty($val) && in_array($key, _node_generator_get_metatags_list())) {
//Adjust metatag array. If robots, then we create sub array.
      $metatags['und'][$key]['value'] = $key == 'robots' ? _node_generator_adjust_robot_tags($val) : $metatags['und'][$key]['value'] = $val;
      if ($key == 'title') {
        $page_title = $val;
      }
    }
  }
//For Body.
  foreach (explode(',', $content['content_pattern']) as $pattern) {
    foreach ($html->find($pattern) as $var) {
      $body = $var->innertext;
      if ($content['replace_domain'] == 1) {
        $body = replace_domain_anchor($body, $content['url']);
      }
      if (!empty($body)) {  //If we finds the content, no need to iterate more.
        break;
      }
    }
    if (!empty($body)) {  //If we finds the content, no need to iterate more.
      break;
    }
  }
  if (empty($body)) { //If cant generate node body.
    $context['results']['message'][] = t('Unable to create the node for url @url as body is empty', array('@url' => $content['url']));
    $valid = FALSE;
  }
//For Node Title.
  if ($valid) {  //If no error (body has value).
    foreach (explode(',', $content['title_pattern']) as $pattern) {
      foreach ($html->find($pattern) as $var) {
        $node_title = $var->innertext;
        if (!empty($node_title)) {  //If we finds the content, no need to iterate more.
          break;
        }
      }
      if (!empty($node_title)) {  //If we finds the content, no need to iterate more.
        break;
      }
    }
    if (empty($node_title)) {  //If cant generate node title.
      $context['results']['message'][] = t('Unable to create the node for url @url as node title is empty', array('@url' => $content['url']));
      $valid = FALSE;
    }
  }
  if ($valid) {
//Generate the node.

    $url_patternflag = isset($content['url_patternflag']) ? $content['url_patternflag'] : null;
    $url_patternflag_patternholder = isset($content['url_patternflag_patternholder']) ? $content['url_patternflag_patternholder'] : null;

    $params = array(
      'url' => $content['url'],
      'uid' => 1,
      'page_title' => $node_title,
      'body' => $body,
      'metatags' => $metatags,
      'type' => $content['type'],
      'alias' => _node_generator_generate_alias($content['url'], $url_patternflag, $url_patternflag_patternholder),
      'summary' => substr($body, 0, 250),
      'category' => $category,
      'tag' => $tag,
      'date' => $date,
      'page-title' => $page_title,
      'category_field' => $content['category_field'],
      'tag_field' => $content['tag_field'],
    );
    _node_generator_node_creation($params, $context); //Create the node.
  }
}

/**
 * Batch process finsh function for node creations.
 * @param type $success
 * @param type $results
 * @param type $operations 
 */
function _node_generator_batch_finished($success, $results, $operations) {
  if ($success) {
    drupal_set_message(t('File parsed successfully') . '<br>', 'status');
    if (isset($results['message'])) {
      foreach ($results['message'] as $msg) {
        drupal_set_message($msg, 'status');
      }
    }
    if (isset($results['error'])) {
      foreach ($results['error'] as $msg) {
        drupal_set_message($msg, 'error');
      }
    }
  }
  else {
    drupal_set_message(t('File parsed with error.'), 'error');
  }
}

/**
 * Get html data from url using curl.
 * @param $url.
 * @return $data.
 */
function get_content_from_xml_loc($url) {
  $ch = curl_init();
  curl_setopt($ch, CURLOPT_AUTOREFERER, TRUE);
  curl_setopt($ch, CURLOPT_HEADER, 0);
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
  curl_setopt($ch, CURLOPT_URL, $url);
  curl_setopt($ch, CURLOPT_FOLLOWLOCATION, TRUE);
  $data = curl_exec($ch);
  curl_close($ch);
  return $data;
}

/**
 * Method to generate metatag list supported by metatag module.
 * @return type array
 */
function _node_generator_get_metatags_list() {
  $tags = metatag_get_info();
  $taglist = array();
  foreach ($tags['tags'] as $key => $val) {
    $taglist[] = $tags['tags'][$key]['name'];
  }
  return $taglist;
}

/**
 * Method to adjust the robot metatags to make them in array from string(comma separated).
 * @param type $robot_list.
 * @return type array.
 */
function _node_generator_adjust_robot_tags($robot_list) {
  $tags = array();
  foreach (explode(',', $robot_list) as $key => $val) {
    $tags[trim($val)] = trim($val);
  }
  return $tags;
}

/**
 * Method to create the new node of specified content type.
 * @param type $content
 * @param type $context
 */
function _node_generator_node_creation($content = array(), &$context) {
 // watchdog('$content', '<pre>'.print_r($content, TRUE) . '</pre>');
  $remove_html_title = preg_replace("/&#?[a-z0-9]{2,8};/i", "", $content['page-title']);
  $node = new stdClass();
  $node->uid = $content['uid'];
  $node->type = $content['type'];
  $node->created = strtotime(trim($content['date']));
  $node->title = preg_replace("/&#?[a-z0-9]{2,8};/i", "", $content['page_title']);
  $node->status = 1;
  $node->promote = 0;
  $node->sticky = 0;
  $node->language = language_default()->language;
  $node->body = array('und' => array(array('value' => $content['body'])));
  //$node->body['und'][0]['summary'] = $content['summary'];
  $node->body['und'][0]['format'] = 'full_html';
  $node->metatags = $content['metatags']['und'];
  $node->page_title = $remove_html_title;
  if ($content['category_field'] != '') {
    $tmp_array_cat = array();
    $get_voc_cat = field_info_field($content['category_field']);
    $cat_voc = $get_voc_cat['settings']['allowed_values'][0]['vocabulary'];
    $attachcategory = $content['category_field'];
    $attachtag = $content['tag_field'];
    foreach ($content['category'] as $key => $value) {
      $tmp_array_cat[] = get_tid_from_term_name($value, $cat_voc);
    }
    $result = array_unique($tmp_array_cat);
    $cat_attach = array();
    foreach ($result as $key_cat => $value_cat) {
      $cat_attach['und'][] = array('tid' => $value_cat);
    }
    $node->$attachcategory = $cat_attach;
  }
  if ($content['tag_field'] != '') {
    $attachtag = $content['tag_field'];
    $tmp_array = array();
    $get_voc_tag = field_info_field($content['tag_field']);
    $tag_voc = $get_voc_tag['settings']['allowed_values'][0]['vocabulary'];
    foreach ($content['tag'] as $key => $value) {
      $tmp_array[] = get_tid_from_term_name($value, $tag_voc);
    }
    $result = array_unique($tmp_array);
    $tag_attach = array();
    foreach ($result as $key_tag => $value_tag) {
      $tag_attach['und'][] = array('tid' => $value_tag);
    }
    $node->$attachtag = $tag_attach;
  }
  $node->created = strtotime($content['date']);
  try {
    node_save($node);
    $context['results']['message'][] = t('Node for @url created having nid @nid', array('@url' => $content['url'], '@nid' => $node->nid));
    if (!drupal_lookup_path('alias', "node/" . $node->nid)) { //If path alias not exists for given path, then create it.
      if (!_node_generator_check_alias_exist($content['alias'])) { //If alias not exist for a path.
        $path = array(
          'source' => 'node/' . $node->nid,
          'alias' => $content['alias'],
          'language' => language_default()->language, //Default language of the site.
        );
        path_save($path); //Save the path alias.
      }
      else {  //Alias already exist for a path.
        $context['results']['message'][] = t('Alias already in use. So we haven\'t created/updated alias for node \'@nid\'.', array('@nid' => $node->nid));
      }
    }
  }
  catch (Exception $e) { //If error occurs.
    $context['results']['error'][] = t('Unable to create the node for url @url due to some problem. Please check the logs.', array('@url' => $content['url']));
  }
}

/**
 * Method to get check whether given content type contains specified field or not.
 * @param type $bundle
 * @param type $field
 * @return string. 
 */
function _node_generator_get_content_types($bundle, $field) {
  $sql = db_select('field_config_instance', 'fci');
  $sql->fields('fci', array('field_id'));
  $sql->condition('fci.bundle', $bundle);
  $sql->condition('fci.field_name', $field);
  return $sql->execute()->fetchField();
}

/**
 * Method to generate the alias for the given url node.
 * @param type $url
 * @return string
 */
function _node_generator_generate_alias($url, $url_patternflag, $url_patternflag_patternholder) {
  $substr = substr($url, strpos($url, '//') + 2);  //Remove the http://  Example:- http://kelltontech.com/contact  => kelltontech.com/contact
  if (strpos($substr, '/') === FALSE) {  // Example:- http://kelltontech.com  (not contain / in last.)
    return '';
  }

  $alias = str_replace(' ', '-', substr($substr, strpos($substr, '/') + 1)); //Get the url after first / and replace space with -.


  if ($url_patternflag == 1) {
    $node_def_pattern = $url_patternflag_patternholder;

    if (substr($node_def_pattern, -1) == '/') {
      $node_def_pattern_split_final_patern = $url_patternflag_patternholder;
    }
    else {
      $node_def_pattern_split_final_patern = $url_patternflag_patternholder . '/';
    }

    if (strpos($alias, '/') === FALSE) {
      $final_alias = $alias;
    }
    else {
      $final_alias_pre = explode('/', $alias);
      $final_alias = trim(end($final_alias_pre));
      if (isset($final_alias) && !empty($final_alias)) {
        
      }
      else {
        //$final_alias = $alias;
        $final_alias = substr_replace($alias, "", -1);
      }
    }


    if (isset($node_def_pattern_split_final_patern) && !empty($node_def_pattern_split_final_patern)) {
      $return_final_alias = $node_def_pattern_split_final_patern . $final_alias;
    }
    else {  // If NULL
      $return_final_alias = $final_alias;
    }

    return $return_final_alias;
  }
  else {
    if (substr($alias, -1) == '/') { 
      return substr($alias, 0, -1);
    } 
    else 
    return $alias; //Get the url after first / and replace space with -.
  }


//$tmp = explode('/', $alias);
  //$last = array_pop($tmp);
  //$tmp1 = explode('.', $last);
  //$alias = 'practice-area/' . $tmp1[0];
  //$alias = 'practice-area/' . $alias ;
  //return $alias;
}

/**
 * Method to check whether given alias already exists or not.
 * @param type $alias.
 * @return string.
 */
function _node_generator_check_alias_exist($alias) {
  $sql = db_select('url_alias', 'ua');
  $sql->fields('ua', array('pid'));
  $sql->condition('ua.alias', $alias);
  return $sql->execute()->fetchField();
}

/**
 * Download images from remote server to local server.
 * @param type $html.
 * @param type $content.
 */
function get_image_from_uri($html, $content) {
  global $base_url;
  foreach ($html->find('img') as $element) {
    $result = parse_url($content);
    $base = $result['scheme'] . "://" . $result['host'];
    $starts_with = substr($element->src, 0, 1);

    if (stripos($element->src, 'http') !== 0) {
      if ($starts_with != '/') {
        $source = $base . '/' . $element->src;
      }
      else {
        $source = $base . $element->src;
      }
    }
    else {
      $source = $element->src;
    }

    $path_parts = pathinfo($element->src);
    $image_name = $path_parts['filename'] . '.' . $path_parts['extension'];
    $destination = 'public://' . $image_name;
    $copy = grab_files($source, $destination);
    if ($copy) {
      $uri = 'public://';
      $path_file = file_create_url($uri);
      $p = str_replace($base_url, "", $path_file);
      $element->src = $path_file . $image_name;
    }
  }
}

/**
 * Get tid from existing term name if not exist then create new term.
 * @param type $term_name.
 * @param type $vocabulary.
 * @return $tid.
 */
function get_tid_from_term_name($term_name, $vocabulary) {
  $arr_terms = taxonomy_get_term_by_name($term_name, $vocabulary);
  if (!empty($arr_terms)) {
    $arr_terms = array_values($arr_terms);
    $tid = $arr_terms[0]->tid;
  }
  else {
    $vobj = taxonomy_vocabulary_machine_name_load($vocabulary);
    $term = new stdClass();
    $term->name = $term_name;
    $term->vid = $vobj->vid;
    taxonomy_term_save($term);
    $tid = $term->tid;
  }
  return $tid;
}

/**
 * Get metatags from url.
 * @param type $url.
 * @return metatags.
 */
function get_metatags_url($url) {
  $metatagss = array();
  $htmll = get_content_from_xml_loc($url);
//parsing begins here:
  $doc = new DOMDocument();
  @$doc->loadHTML($htmll);
  $nodes = $doc->getElementsByTagName('title');
//get and display what you need:
  $title = $nodes->item(0)->nodeValue;
  $metas = $doc->getElementsByTagName('meta');
  $description = '';
  $keywords = '';
  for ($i = 0; $i < $metas->length; $i++) {
    $meta = $metas->item($i);
    if ($meta->getAttribute('name') == 'description' || $meta->getAttribute('name') == 'Description')
      $description = $meta->getAttribute('content');

    if ($meta->getAttribute('name') == 'keywords')
      $keywords = $meta->getAttribute('content');
    if ($meta->getAttribute('language') == 'language')
      ;
    $language = $meta->getAttribute('language');
  }
  $metatagss['description'] = preg_replace("/&#?[a-z0-9]{2,8};/i", "", $description);
  //$metatagss['keywords'] = html_entity_decode($keywords);
  $metatagss['title'] = html_entity_decode($title);
  return $metatagss;
}

/**
 * Get images from url and save them on our server. 
 * @param type $url.
 * @param type $saveto.
 * @return boolean.
 */
function grab_files($url, $saveto) {
  $ch = curl_init($url);
  curl_setopt($ch, CURLOPT_HEADER, 0);
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
  curl_setopt($ch, CURLOPT_BINARYTRANSFER, 1);
  $raw = curl_exec($ch);
  curl_close($ch);
  if (file_exists($saveto)) {
    unlink($saveto);
  }
  $fp = fopen($saveto, 'x');
  fwrite($fp, $raw);
  fclose($fp);
  return true;
}

/**
 * Replace absoult anchor paths in body to our server paths. 
 * @param type $body_html.
 * @param type $url.
 * @return $body.
 */
function replace_domain_anchor($body_html, $url) {
  $result = parse_url($url);
  $base = $result['scheme'] . "://" . $result['host'];
  $base_url = 'href="' . $base . '/';
  $body = str_replace($base_url, 'href="/', $body_html);
  return $body;
}

/**
 * Download images from remote server to local server.
 * @param type $html.
 * @param type $content.
 */
//function get_files_from_href($html, $content) {
//    watchdog('actions', 'Action.', array());
//    global $base_url;
//    foreach ($html->find('a') as $element) {
//        $path_parts = pathinfo($element->href);
//        if ($path_parts['extension']) {
//            $file_name = $path_parts['filename'] . '.' . $path_parts['extension'];
//            if ($path_parts['extension'] == 'pdf' || $path_parts['extension'] == 'doc') {
//                $result = parse_url($content);
//                $base = $result['scheme'] . "://" . $result['host'];
//                $starts_with = substr($element->href, 0, 1);
//                if (stripos($element->href, 'http') !== 0) {
//                    if ($starts_with != '/') {
//                        $source = $base . '/' . $element->href;
//                    } else {
//                        $source = $base . $element->href;
//                    }
//                } else {
//                    $source = $element->href;
//                }
//                $destination = 'public://' . $file_name;
//                $copy = grab_files($source, $destination);
//                if ($copy) {
//                    $uri = 'public://';
//                    $path_file = file_create_url($uri);
//                    $p = str_replace($base_url, "", $path_file);
//                    $element->href = $path_file . $file_name;
//                }
//            }
//        }
//    }
//}

function get_files_from_href($html, $content) {
  watchdog('actions', 'Action.', array());
  global $base_url;
  foreach ($html->find('a') as $element) {
    $path_parts = pathinfo($element->href);
    if (isset($path_parts['extension'])) {
      $filenametemp = preg_replace("/[^a-zA-Z0-9]+/", "", $path_parts['filename']);
      $file_name = $filenametemp . '.' . $path_parts['extension'];
      if ($path_parts['extension'] == 'pdf' || $path_parts['extension'] == 'doc' || $path_parts['extension'] == 'jpg' || $path_parts['extension'] == 'JPG' || $path_parts['extension'] == 'jpeg' || $path_parts['extension'] == 'JPEG' || $path_parts['extension'] == 'png' || $path_parts['extension'] == 'gif') {
        $result = parse_url($content);
        $base = $result['scheme'] . "://" . $result['host'];
        $starts_with = substr($element->href, 0, 1);
        if (stripos($element->href, 'http') !== 0) {
          if ($starts_with != '/') {
            $source = $base . '/' . $element->href;
          }
          else {
            $source = $base . $element->href;
          }
        }
        else {
          $source = $element->href;
        }
        $destination = 'public://' . $file_name;
        $copy = grab_files($source, $destination);
        if ($copy) {
          $uri = 'public://';
          $path_file = file_create_url($uri);
          $p = str_replace($base_url, "", $path_file);
          $element->href = $path_file . $file_name;
        }
      }
    }
  }
}
