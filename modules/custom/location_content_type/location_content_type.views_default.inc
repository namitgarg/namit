<?php
/**
 * @file
 * location_content_type.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function location_content_type_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'location_footer';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Location footer ';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Location footer ';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
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
    'location' => 'location',
  );

  /* Display: Block : Location footer  */
  $handler = $view->new_display('block', 'Block : Location footer ', 'block');
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Address Line 1 */
  $handler->display->display_options['fields']['field_address_line_1']['id'] = 'field_address_line_1';
  $handler->display->display_options['fields']['field_address_line_1']['table'] = 'field_data_field_address_line_1';
  $handler->display->display_options['fields']['field_address_line_1']['field'] = 'field_address_line_1';
  $handler->display->display_options['fields']['field_address_line_1']['label'] = '';
  $handler->display->display_options['fields']['field_address_line_1']['element_label_colon'] = FALSE;
  /* Field: Content: Address Line 2 */
  $handler->display->display_options['fields']['field_address_line_2']['id'] = 'field_address_line_2';
  $handler->display->display_options['fields']['field_address_line_2']['table'] = 'field_data_field_address_line_2';
  $handler->display->display_options['fields']['field_address_line_2']['field'] = 'field_address_line_2';
  $handler->display->display_options['fields']['field_address_line_2']['label'] = '';
  $handler->display->display_options['fields']['field_address_line_2']['element_label_colon'] = FALSE;
  /* Field: Content: City */
  $handler->display->display_options['fields']['field_city']['id'] = 'field_city';
  $handler->display->display_options['fields']['field_city']['table'] = 'field_data_field_city';
  $handler->display->display_options['fields']['field_city']['field'] = 'field_city';
  $handler->display->display_options['fields']['field_city']['label'] = '';
  $handler->display->display_options['fields']['field_city']['element_label_colon'] = FALSE;
  /* Field: Content: State */
  $handler->display->display_options['fields']['field_state']['id'] = 'field_state';
  $handler->display->display_options['fields']['field_state']['table'] = 'field_data_field_state';
  $handler->display->display_options['fields']['field_state']['field'] = 'field_state';
  $handler->display->display_options['fields']['field_state']['label'] = '';
  $handler->display->display_options['fields']['field_state']['element_label_colon'] = FALSE;
  /* Field: Content: Zip Code */
  $handler->display->display_options['fields']['field_zip_code']['id'] = 'field_zip_code';
  $handler->display->display_options['fields']['field_zip_code']['table'] = 'field_data_field_zip_code';
  $handler->display->display_options['fields']['field_zip_code']['field'] = 'field_zip_code';
  $handler->display->display_options['fields']['field_zip_code']['label'] = '';
  $handler->display->display_options['fields']['field_zip_code']['element_label_colon'] = FALSE;
  /* Field: Content: Map link */
  $handler->display->display_options['fields']['field_map_link']['id'] = 'field_map_link';
  $handler->display->display_options['fields']['field_map_link']['table'] = 'field_data_field_map_link';
  $handler->display->display_options['fields']['field_map_link']['field'] = 'field_map_link';
  $handler->display->display_options['fields']['field_map_link']['label'] = '';
  $handler->display->display_options['fields']['field_map_link']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_map_link']['click_sort_column'] = 'url';
  $translatables['location_footer'] = array(
    t('Master'),
    t('Location footer '),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Block : Location footer '),
  );
  $export['location_footer'] = $view;

  return $export;
}
