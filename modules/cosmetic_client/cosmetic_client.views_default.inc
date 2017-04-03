<?php
/**
 * @file
 * cosmetic_client.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function cosmetic_client_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'before_and_after_gallery_pages_and_sort';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Before and After Gallery Pages and Sort';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Before and After Gallery Pages and Sort';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Content: Taxonomy terms on node */
  $handler->display->display_options['relationships']['term_node_tid']['id'] = 'term_node_tid';
  $handler->display->display_options['relationships']['term_node_tid']['table'] = 'node';
  $handler->display->display_options['relationships']['term_node_tid']['field'] = 'term_node_tid';
  $handler->display->display_options['relationships']['term_node_tid']['vocabularies'] = array(
    'gallery_taxonomy' => 'gallery_taxonomy',
    'tags' => 0,
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: After Image 1 */
  $handler->display->display_options['fields']['field_after_image_1']['id'] = 'field_after_image_1';
  $handler->display->display_options['fields']['field_after_image_1']['table'] = 'field_data_field_after_image_1';
  $handler->display->display_options['fields']['field_after_image_1']['field'] = 'field_after_image_1';
  $handler->display->display_options['fields']['field_after_image_1']['label'] = '';
  $handler->display->display_options['fields']['field_after_image_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_after_image_1']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_after_image_1']['settings'] = array(
    'image_style' => 'medium',
    'image_link' => '',
  );
  /* Field: Content: Before Image 1 */
  $handler->display->display_options['fields']['field_before_image_1']['id'] = 'field_before_image_1';
  $handler->display->display_options['fields']['field_before_image_1']['table'] = 'field_data_field_before_image_1';
  $handler->display->display_options['fields']['field_before_image_1']['field'] = 'field_before_image_1';
  $handler->display->display_options['fields']['field_before_image_1']['label'] = '';
  $handler->display->display_options['fields']['field_before_image_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_before_image_1']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_before_image_1']['settings'] = array(
    'image_style' => 'medium',
    'image_link' => '',
  );
  /* Sort criterion: Sortable Grid: Rank */
  $handler->display->display_options['sorts']['rank']['id'] = 'rank';
  $handler->display->display_options['sorts']['rank']['table'] = 'sgrid';
  $handler->display->display_options['sorts']['rank']['field'] = 'rank';
  $handler->display->display_options['sorts']['rank']['order'] = 'DESC';
  /* Contextual filter: Taxonomy term: Name */
  $handler->display->display_options['arguments']['name']['id'] = 'name';
  $handler->display->display_options['arguments']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['arguments']['name']['field'] = 'name';
  $handler->display->display_options['arguments']['name']['relationship'] = 'term_node_tid';
  $handler->display->display_options['arguments']['name']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['name']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['name']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['name']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['name']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['name']['limit'] = '0';
  $handler->display->display_options['arguments']['name']['case'] = 'ucwords';
  $handler->display->display_options['arguments']['name']['path_case'] = 'lower';
  $handler->display->display_options['arguments']['name']['transform_dash'] = TRUE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'ba_gallery_entry' => 'ba_gallery_entry',
  );

  /* Display: Before After Landing (terms list) */
  $handler = $view->new_display('page', 'Before After Landing (terms list)', 'page_3');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Before and After Galleries';
  $handler->display->display_options['display_description'] = 'the list of taxonomy terms that link to individual gallery pages';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Content: Taxonomy terms on node */
  $handler->display->display_options['relationships']['term_node_tid']['id'] = 'term_node_tid';
  $handler->display->display_options['relationships']['term_node_tid']['table'] = 'node';
  $handler->display->display_options['relationships']['term_node_tid']['field'] = 'term_node_tid';
  $handler->display->display_options['relationships']['term_node_tid']['vocabularies'] = array(
    'gallery_taxonomy' => 'gallery_taxonomy',
    'tags' => 0,
  );
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Taxonomy term: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'term_node_tid';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['name']['alter']['path'] = 'before-after-gallery/[name]';
  $handler->display->display_options['fields']['name']['alter']['replace_spaces'] = TRUE;
  $handler->display->display_options['fields']['name']['alter']['path_case'] = 'lower';
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Taxonomy term: Name */
  $handler->display->display_options['arguments']['name']['id'] = 'name';
  $handler->display->display_options['arguments']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['arguments']['name']['field'] = 'name';
  $handler->display->display_options['arguments']['name']['relationship'] = 'term_node_tid';
  $handler->display->display_options['arguments']['name']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['name']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['name']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['name']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['name']['limit'] = '0';
  $handler->display->display_options['arguments']['name']['case'] = 'ucwords';
  $handler->display->display_options['arguments']['name']['path_case'] = 'lower';
  $handler->display->display_options['arguments']['name']['transform_dash'] = TRUE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Taxonomy term: Vocabulary */
  $handler->display->display_options['filters']['vid']['id'] = 'vid';
  $handler->display->display_options['filters']['vid']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['filters']['vid']['field'] = 'vid';
  $handler->display->display_options['filters']['vid']['relationship'] = 'term_node_tid';
  $handler->display->display_options['filters']['vid']['value'] = array(
    2 => '2',
  );
  $handler->display->display_options['path'] = 'before-after-gallery';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Before and After Gallery';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'main-menu';
  $handler->display->display_options['menu']['context'] = 0;

  /* Display: Before and After Gallery Page (Individual Pages) */
  $handler = $view->new_display('page', 'Before and After Gallery Page (Individual Pages)', 'page');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = '%1 Gallery';
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['content'] = '<a href="/before-after-gallery/sort/%1">Sort Gallery Entries</a>';
  $handler->display->display_options['header']['area']['format'] = 'full_html';
  $handler->display->display_options['header']['area']['tokenize'] = TRUE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: After Image 1 */
  $handler->display->display_options['fields']['field_after_image_1']['id'] = 'field_after_image_1';
  $handler->display->display_options['fields']['field_after_image_1']['table'] = 'field_data_field_after_image_1';
  $handler->display->display_options['fields']['field_after_image_1']['field'] = 'field_after_image_1';
  $handler->display->display_options['fields']['field_after_image_1']['label'] = '';
  $handler->display->display_options['fields']['field_after_image_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_after_image_1']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_after_image_1']['settings'] = array(
    'image_style' => 'medium',
    'image_link' => '',
  );
  /* Field: Content: Before Image 1 */
  $handler->display->display_options['fields']['field_before_image_1']['id'] = 'field_before_image_1';
  $handler->display->display_options['fields']['field_before_image_1']['table'] = 'field_data_field_before_image_1';
  $handler->display->display_options['fields']['field_before_image_1']['field'] = 'field_before_image_1';
  $handler->display->display_options['fields']['field_before_image_1']['label'] = '';
  $handler->display->display_options['fields']['field_before_image_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_before_image_1']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_before_image_1']['settings'] = array(
    'image_style' => 'medium',
    'image_link' => '',
  );
  /* Field: Taxonomy term: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'term_node_tid';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Taxonomy term: Name */
  $handler->display->display_options['arguments']['name']['id'] = 'name';
  $handler->display->display_options['arguments']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['arguments']['name']['field'] = 'name';
  $handler->display->display_options['arguments']['name']['relationship'] = 'term_node_tid';
  $handler->display->display_options['arguments']['name']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['name']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['name']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['name']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['name']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['name']['limit'] = '0';
  $handler->display->display_options['arguments']['name']['case'] = 'lower';
  $handler->display->display_options['arguments']['name']['path_case'] = 'lower';
  $handler->display->display_options['arguments']['name']['transform_dash'] = TRUE;
  $handler->display->display_options['path'] = 'before-after-gallery/%';

  /* Display: Sort Page */
  $handler = $view->new_display('page', 'Sort Page', 'page_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Sort Page %1';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'sgrid';
  $handler->display->display_options['style_options']['row_length'] = '5';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'sgrid_style';
  $handler->display->display_options['row_options']['inline'] = array(
    'title' => 'title',
  );
  $handler->display->display_options['row_options']['hide_empty'] = 1;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Taxonomy term: Name */
  $handler->display->display_options['arguments']['name']['id'] = 'name';
  $handler->display->display_options['arguments']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['arguments']['name']['field'] = 'name';
  $handler->display->display_options['arguments']['name']['relationship'] = 'term_node_tid';
  $handler->display->display_options['arguments']['name']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['name']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['name']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['name']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['name']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['name']['limit'] = '0';
  $handler->display->display_options['path'] = 'before-after-gallery/sort/%';
  $translatables['before_and_after_gallery_pages_and_sort'] = array(
    t('Master'),
    t('Before and After Gallery Pages and Sort'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('term'),
    t('All'),
    t('Before After Landing (terms list)'),
    t('Before and After Galleries'),
    t('the list of taxonomy terms that link to individual gallery pages'),
    t('Before and After Gallery Page (Individual Pages)'),
    t('%1 Gallery'),
    t('<a href="/before-after-gallery/sort/%1">Sort Gallery Entries</a>'),
    t('Sort Page'),
    t('Sort Page %1'),
  );
  $export['before_and_after_gallery_pages_and_sort'] = $view;

  $view = new view();
  $view->name = 'before_and_after_terms_page';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'taxonomy_term_data';
  $view->human_name = 'Before and After Terms Page';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Before and After Galleries';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'oops';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  /* Field: Taxonomy term: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['name']['alter']['path'] = 'before-after/[name]';
  $handler->display->display_options['fields']['name']['alter']['path_case'] = 'lower';
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['empty'] = 'oops';
  /* Filter criterion: Taxonomy vocabulary: Machine name */
  $handler->display->display_options['filters']['machine_name']['id'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['table'] = 'taxonomy_vocabulary';
  $handler->display->display_options['filters']['machine_name']['field'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['value'] = array(
    'gallery_taxonomy' => 'gallery_taxonomy',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Taxonomy term: Parent term */
  $handler->display->display_options['relationships']['parent']['id'] = 'parent';
  $handler->display->display_options['relationships']['parent']['table'] = 'taxonomy_term_hierarchy';
  $handler->display->display_options['relationships']['parent']['field'] = 'parent';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Taxonomy term: Name */
  $handler->display->display_options['arguments']['name']['id'] = 'name';
  $handler->display->display_options['arguments']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['arguments']['name']['field'] = 'name';
  $handler->display->display_options['arguments']['name']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['name']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['name']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['name']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['name']['limit'] = '0';
  $handler->display->display_options['arguments']['name']['case'] = 'lower';
  $handler->display->display_options['arguments']['name']['path_case'] = 'lower';
  $handler->display->display_options['arguments']['name']['transform_dash'] = TRUE;
  $handler->display->display_options['path'] = 'before-after';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Before and After Gallery';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'main-menu';
  $handler->display->display_options['menu']['context'] = 0;
  $translatables['before_and_after_terms_page'] = array(
    t('Master'),
    t('Before and After Galleries'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('oops'),
    t('Page'),
    t('Parent'),
    t('All'),
  );
  $export['before_and_after_terms_page'] = $view;

  $view = new view();
  $view->name = 'draggable_test';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'sortable gallery views';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'gallery view';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Content: Taxonomy terms on node */
  $handler->display->display_options['relationships']['term_node_tid']['id'] = 'term_node_tid';
  $handler->display->display_options['relationships']['term_node_tid']['table'] = 'node';
  $handler->display->display_options['relationships']['term_node_tid']['field'] = 'term_node_tid';
  $handler->display->display_options['relationships']['term_node_tid']['vocabularies'] = array(
    'gallery' => 'gallery',
    'tags' => 0,
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Before Image 1 */
  $handler->display->display_options['fields']['field_before_image_1']['id'] = 'field_before_image_1';
  $handler->display->display_options['fields']['field_before_image_1']['table'] = 'field_data_field_before_image_1';
  $handler->display->display_options['fields']['field_before_image_1']['field'] = 'field_before_image_1';
  $handler->display->display_options['fields']['field_before_image_1']['label'] = '';
  $handler->display->display_options['fields']['field_before_image_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_before_image_1']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_before_image_1']['settings'] = array(
    'image_style' => '',
    'image_link' => '',
  );
  /* Field: Content: Before Image 1 */
  $handler->display->display_options['fields']['field_before_image_1_1']['id'] = 'field_before_image_1_1';
  $handler->display->display_options['fields']['field_before_image_1_1']['table'] = 'field_data_field_before_image_1';
  $handler->display->display_options['fields']['field_before_image_1_1']['field'] = 'field_before_image_1';
  $handler->display->display_options['fields']['field_before_image_1_1']['label'] = '';
  $handler->display->display_options['fields']['field_before_image_1_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_before_image_1_1']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_before_image_1_1']['settings'] = array(
    'image_style' => '',
    'image_link' => '',
  );
  /* Field: Sortable Grid: Rank */
  $handler->display->display_options['fields']['rank']['id'] = 'rank';
  $handler->display->display_options['fields']['rank']['table'] = 'sgrid';
  $handler->display->display_options['fields']['rank']['field'] = 'rank';
  $handler->display->display_options['fields']['rank']['label'] = '';
  $handler->display->display_options['fields']['rank']['exclude'] = TRUE;
  $handler->display->display_options['fields']['rank']['element_label_colon'] = FALSE;
  /* Sort criterion: Sortable Grid: Rank */
  $handler->display->display_options['sorts']['rank']['id'] = 'rank';
  $handler->display->display_options['sorts']['rank']['table'] = 'sgrid';
  $handler->display->display_options['sorts']['rank']['field'] = 'rank';
  /* Contextual filter: Taxonomy term: Name */
  $handler->display->display_options['arguments']['name']['id'] = 'name';
  $handler->display->display_options['arguments']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['arguments']['name']['field'] = 'name';
  $handler->display->display_options['arguments']['name']['relationship'] = 'term_node_tid';
  $handler->display->display_options['arguments']['name']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['name']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['name']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['name']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['name']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['name']['limit'] = '0';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'gallery' => 'gallery',
  );

  /* Display: Gallery Page */
  $handler = $view->new_display('page', 'Gallery Page', 'page');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = '%1 Gallery';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['content'] = '<?php
global $user;
if ($user->uid): ?>
   <div id="sort"><a href="/before-after/sort/%1">Sort Gallery Entries</a>
   </div>
<?php else:
    return;
	endif;
?>';
  $handler->display->display_options['header']['area']['format'] = 'php_code';
  $handler->display->display_options['header']['area']['tokenize'] = TRUE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Content: Taxonomy terms on node */
  $handler->display->display_options['relationships']['term_node_tid']['id'] = 'term_node_tid';
  $handler->display->display_options['relationships']['term_node_tid']['table'] = 'node';
  $handler->display->display_options['relationships']['term_node_tid']['field'] = 'term_node_tid';
  $handler->display->display_options['relationships']['term_node_tid']['vocabularies'] = array(
    'gallery_taxonomy' => 'gallery_taxonomy',
    'tags' => 0,
  );
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Before Image 1 */
  $handler->display->display_options['fields']['field_before_image_1']['id'] = 'field_before_image_1';
  $handler->display->display_options['fields']['field_before_image_1']['table'] = 'field_data_field_before_image_1';
  $handler->display->display_options['fields']['field_before_image_1']['field'] = 'field_before_image_1';
  $handler->display->display_options['fields']['field_before_image_1']['label'] = '';
  $handler->display->display_options['fields']['field_before_image_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_before_image_1']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_before_image_1']['settings'] = array(
    'image_style' => 'medium',
    'image_link' => '',
  );
  /* Field: Content: After Image 1 */
  $handler->display->display_options['fields']['field_after_image_1']['id'] = 'field_after_image_1';
  $handler->display->display_options['fields']['field_after_image_1']['table'] = 'field_data_field_after_image_1';
  $handler->display->display_options['fields']['field_after_image_1']['field'] = 'field_after_image_1';
  $handler->display->display_options['fields']['field_after_image_1']['label'] = '';
  $handler->display->display_options['fields']['field_after_image_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_after_image_1']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_after_image_1']['settings'] = array(
    'image_style' => 'medium',
    'image_link' => '',
  );
  /* Field: Sortable Grid: Rank */
  $handler->display->display_options['fields']['rank']['id'] = 'rank';
  $handler->display->display_options['fields']['rank']['table'] = 'sgrid';
  $handler->display->display_options['fields']['rank']['field'] = 'rank';
  $handler->display->display_options['fields']['rank']['label'] = '';
  $handler->display->display_options['fields']['rank']['exclude'] = TRUE;
  $handler->display->display_options['fields']['rank']['element_label_colon'] = FALSE;
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Taxonomy term: Name */
  $handler->display->display_options['arguments']['name']['id'] = 'name';
  $handler->display->display_options['arguments']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['arguments']['name']['field'] = 'name';
  $handler->display->display_options['arguments']['name']['relationship'] = 'term_node_tid';
  $handler->display->display_options['arguments']['name']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['name']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['name']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['name']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['name']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['name']['limit'] = '0';
  $handler->display->display_options['arguments']['name']['case'] = 'lower';
  $handler->display->display_options['arguments']['name']['path_case'] = 'lower';
  $handler->display->display_options['path'] = 'before-after/%';

  /* Display: Sort Page */
  $handler = $view->new_display('page', 'Sort Page', 'page_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Sort Page %1';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'sgrid';
  $handler->display->display_options['style_options']['row_length'] = '5';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'sgrid_style';
  $handler->display->display_options['row_options']['hide_empty'] = 0;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Content: Taxonomy terms on node */
  $handler->display->display_options['relationships']['term_node_tid']['id'] = 'term_node_tid';
  $handler->display->display_options['relationships']['term_node_tid']['table'] = 'node';
  $handler->display->display_options['relationships']['term_node_tid']['field'] = 'term_node_tid';
  $handler->display->display_options['relationships']['term_node_tid']['vocabularies'] = array(
    'gallery_taxonomy' => 'gallery_taxonomy',
    'tags' => 0,
  );
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Before Image 1 */
  $handler->display->display_options['fields']['field_before_image_1']['id'] = 'field_before_image_1';
  $handler->display->display_options['fields']['field_before_image_1']['table'] = 'field_data_field_before_image_1';
  $handler->display->display_options['fields']['field_before_image_1']['field'] = 'field_before_image_1';
  $handler->display->display_options['fields']['field_before_image_1']['label'] = '';
  $handler->display->display_options['fields']['field_before_image_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_before_image_1']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_before_image_1']['settings'] = array(
    'image_style' => 'thumbnail',
    'image_link' => '',
  );
  /* Field: Content: Before Image 1 */
  $handler->display->display_options['fields']['field_before_image_1_1']['id'] = 'field_before_image_1_1';
  $handler->display->display_options['fields']['field_before_image_1_1']['table'] = 'field_data_field_before_image_1';
  $handler->display->display_options['fields']['field_before_image_1_1']['field'] = 'field_before_image_1';
  $handler->display->display_options['fields']['field_before_image_1_1']['label'] = '';
  $handler->display->display_options['fields']['field_before_image_1_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_before_image_1_1']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_before_image_1_1']['settings'] = array(
    'image_style' => 'thumbnail',
    'image_link' => '',
  );
  /* Field: Sortable Grid: Rank */
  $handler->display->display_options['fields']['rank']['id'] = 'rank';
  $handler->display->display_options['fields']['rank']['table'] = 'sgrid';
  $handler->display->display_options['fields']['rank']['field'] = 'rank';
  $handler->display->display_options['fields']['rank']['label'] = '';
  $handler->display->display_options['fields']['rank']['exclude'] = TRUE;
  $handler->display->display_options['fields']['rank']['element_label_colon'] = FALSE;
  $handler->display->display_options['path'] = 'before-after/sort/%';
  $translatables['draggable_test'] = array(
    t('Master'),
    t('gallery view'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('term'),
    t('.'),
    t(','),
    t('All'),
    t('Gallery Page'),
    t('%1 Gallery'),
    t('<?php
global $user;
if ($user->uid): ?>
   <div id="sort"><a href="/before-after/sort/%1">Sort Gallery Entries</a>
   </div>
<?php else:
    return;
	endif;
?>'),
    t('Sort Page'),
    t('Sort Page %1'),
  );
  $export['draggable_test'] = $view;

  return $export;
}
