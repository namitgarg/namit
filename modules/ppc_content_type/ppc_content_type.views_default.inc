<?php
/**
 * @file
 * ppc_content_type.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function ppc_content_type_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'ppc_banner';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'field_collection_item';
  $view->human_name = 'PPC Banner';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'PPC Banner';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'flexslider';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Field collection item: Entity with the PPC Top Banner (field_ppc_top_banner) */
  $handler->display->display_options['relationships']['field_ppc_top_banner_node']['id'] = 'field_ppc_top_banner_node';
  $handler->display->display_options['relationships']['field_ppc_top_banner_node']['table'] = 'field_collection_item';
  $handler->display->display_options['relationships']['field_ppc_top_banner_node']['field'] = 'field_ppc_top_banner_node';
  $handler->display->display_options['relationships']['field_ppc_top_banner_node']['required'] = TRUE;
  /* Field: Field collection item: Banner Text Top Line Color */
  $handler->display->display_options['fields']['field_banner_text_color']['id'] = 'field_banner_text_color';
  $handler->display->display_options['fields']['field_banner_text_color']['table'] = 'field_data_field_banner_text_color';
  $handler->display->display_options['fields']['field_banner_text_color']['field'] = 'field_banner_text_color';
  $handler->display->display_options['fields']['field_banner_text_color']['label'] = '';
  $handler->display->display_options['fields']['field_banner_text_color']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_banner_text_color']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_banner_text_color']['type'] = 'jquery_colorpicker_raw_hex_display';
  /* Field: Field collection item: PPC Banner */
  $handler->display->display_options['fields']['field_ppc_banner']['id'] = 'field_ppc_banner';
  $handler->display->display_options['fields']['field_ppc_banner']['table'] = 'field_data_field_ppc_banner';
  $handler->display->display_options['fields']['field_ppc_banner']['field'] = 'field_ppc_banner';
  $handler->display->display_options['fields']['field_ppc_banner']['label'] = '';
  $handler->display->display_options['fields']['field_ppc_banner']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_ppc_banner']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ppc_banner']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_ppc_banner']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_ppc_banner']['settings'] = array(
    'image_style' => '',
    'image_link' => '',
  );
  /* Field: Field collection item: PPC Banner Text Top Line */
  $handler->display->display_options['fields']['field_ppc_banner_text']['id'] = 'field_ppc_banner_text';
  $handler->display->display_options['fields']['field_ppc_banner_text']['table'] = 'field_data_field_ppc_banner_text';
  $handler->display->display_options['fields']['field_ppc_banner_text']['field'] = 'field_ppc_banner_text';
  $handler->display->display_options['fields']['field_ppc_banner_text']['label'] = '';
  $handler->display->display_options['fields']['field_ppc_banner_text']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_ppc_banner_text']['element_label_colon'] = FALSE;
  /* Field: Field collection item: PPC Banner Text Second Line */
  $handler->display->display_options['fields']['field_ppc_banner_slogan']['id'] = 'field_ppc_banner_slogan';
  $handler->display->display_options['fields']['field_ppc_banner_slogan']['table'] = 'field_data_field_ppc_banner_slogan';
  $handler->display->display_options['fields']['field_ppc_banner_slogan']['field'] = 'field_ppc_banner_slogan';
  $handler->display->display_options['fields']['field_ppc_banner_slogan']['label'] = '';
  $handler->display->display_options['fields']['field_ppc_banner_slogan']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_ppc_banner_slogan']['element_label_colon'] = FALSE;
  /* Field: Field collection item: PPC Banner Text Second Line Color */
  $handler->display->display_options['fields']['field_ppc_banner_slogan_color']['id'] = 'field_ppc_banner_slogan_color';
  $handler->display->display_options['fields']['field_ppc_banner_slogan_color']['table'] = 'field_data_field_ppc_banner_slogan_color';
  $handler->display->display_options['fields']['field_ppc_banner_slogan_color']['field'] = 'field_ppc_banner_slogan_color';
  $handler->display->display_options['fields']['field_ppc_banner_slogan_color']['label'] = '';
  $handler->display->display_options['fields']['field_ppc_banner_slogan_color']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_ppc_banner_slogan_color']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ppc_banner_slogan_color']['type'] = 'jquery_colorpicker_raw_hex_display';
  /* Field: Field collection item: PPC 'Get Help Now' Button */
  $handler->display->display_options['fields']['field_ppc_get_help_now']['id'] = 'field_ppc_get_help_now';
  $handler->display->display_options['fields']['field_ppc_get_help_now']['table'] = 'field_data_field_ppc_get_help_now';
  $handler->display->display_options['fields']['field_ppc_get_help_now']['field'] = 'field_ppc_get_help_now';
  $handler->display->display_options['fields']['field_ppc_get_help_now']['label'] = '';
  $handler->display->display_options['fields']['field_ppc_get_help_now']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_ppc_get_help_now']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ppc_get_help_now']['click_sort_column'] = 'url';
  /* Field: Field collection item: PPC 'Get Help Now' Button Text Color */
  $handler->display->display_options['fields']['field_ppc_get_help_now_color']['id'] = 'field_ppc_get_help_now_color';
  $handler->display->display_options['fields']['field_ppc_get_help_now_color']['table'] = 'field_data_field_ppc_get_help_now_color';
  $handler->display->display_options['fields']['field_ppc_get_help_now_color']['field'] = 'field_ppc_get_help_now_color';
  $handler->display->display_options['fields']['field_ppc_get_help_now_color']['label'] = '';
  $handler->display->display_options['fields']['field_ppc_get_help_now_color']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_ppc_get_help_now_color']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ppc_get_help_now_color']['type'] = 'jquery_colorpicker_raw_hex_display';
  /* Field: Global: PHP */
  $handler->display->display_options['fields']['php']['id'] = 'php';
  $handler->display->display_options['fields']['php']['table'] = 'views';
  $handler->display->display_options['fields']['php']['field'] = 'php';
  $handler->display->display_options['fields']['php']['label'] = '';
  $handler->display->display_options['fields']['php']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php']['php_output'] = '<?php
$banner_image = $data->_field_data[item_id][entity]->field_ppc_banner[und][0][uri];
$banner_text = $data->_field_data[item_id][entity]->field_ppc_banner_text[und][0][value];
$banner_text_color = $data->_field_data[item_id][entity]->field_banner_text_color[und][0][jquery_colorpicker];

$banner_slogan = $data->_field_data[item_id][entity]->field_ppc_banner_slogan[und][0][value];
$banner_slogan_color = $data->_field_data[item_id][entity]->field_ppc_banner_slogan_color[und][0][jquery_colorpicker];

$get_help = $data->_field_data[item_id][entity]->field_ppc_get_help_now[und][0][title];
$get_help_url = $data->_field_data[item_id][entity]->field_ppc_get_help_now[und][0][url];
$get_help_color = $data->_field_data[item_id][entity]->field_ppc_get_help_now_color[und][0][jquery_colorpicker];

$get_help_border_color = $data->_field_data[item_id][entity]->field_ppc_get_help_now_border_co[und][0][jquery_colorpicker];
$get_help_bg_color = $data->_field_data[item_id][entity]->field_ppc_get_help_now_backgroun[und][0][jquery_colorpicker];
$get_text_bg_color = $data->_field_data[item_id][entity]->field_banner_text_slogan_bg_colo[und][0][jquery_colorpicker];

$banner_text_size = $data->_field_data[item_id][entity]->field_ppc_banner_text_size[und][0][value];
$banner_slog_size = $data->_field_data[item_id][entity]->field_ppc_banner_slogan_size[und][0][value];
?>
<?php
//print theme(\'image_style\', array(\'style_name\' => \'large\', \'path\' => $banner_image, \'attributes\' => array(\'class\' => //array(\'banner-image\'))));

print \'<img src=" \'. file_create_url($banner_image) .\' "  class="banner-image" />\';
?>
<div class="banner-text-area">

<?php
print "<div class=\'text-slogan\' style=\'background-color:#".$get_text_bg_color.";\'>";
print "<div class=\'text-slogan-before\' style=\'border-bottom-color:#".$get_text_bg_color.";\'></div>";
print "<div class=\'banner-text ".$banner_text_size."\' style=\'color:#".$banner_text_color.";\'>".$banner_text."</div>";
print "<div class=\'banner-slogan ".$banner_slog_size."\' style=\'color:#".$banner_slogan_color.";\'>".$banner_slogan."</div>";
print "</div>";
?>

<?php
print "<div class=\'get-help\'><a href=\'".$get_help_url."\' style=\'color:#".$get_help_color."; background-color:#".$get_help_bg_color."; border:#".$get_help_border_color." 1px solid; \'> ".$get_help."</a></div>";
?>
</div>';
  $handler->display->display_options['fields']['php']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php']['php_click_sortable'] = '';
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['relationship'] = 'field_ppc_top_banner_node';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'ppc-banner';
  $translatables['ppc_banner'] = array(
    t('Master'),
    t('PPC Banner'),
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
    t('field_ppc_top_banner'),
    t('All'),
    t('Page'),
  );
  $export['ppc_banner'] = $view;

  $view = new view();
  $view->name = 'ppc_choosing';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'field_collection_item';
  $view->human_name = 'PPC Choosing';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'PPC Choosing';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Field collection item: Entity with the PPC S&amp;S Section Bullet Choices (field_ppc_choosing) */
  $handler->display->display_options['relationships']['field_ppc_choosing_node']['id'] = 'field_ppc_choosing_node';
  $handler->display->display_options['relationships']['field_ppc_choosing_node']['table'] = 'field_collection_item';
  $handler->display->display_options['relationships']['field_ppc_choosing_node']['field'] = 'field_ppc_choosing_node';
  $handler->display->display_options['relationships']['field_ppc_choosing_node']['required'] = TRUE;
  /* Field: Field collection item: PPC S&S Section Bullet Icon ( from fontawesome.com) */
  $handler->display->display_options['fields']['field_choose_us_icon']['id'] = 'field_choose_us_icon';
  $handler->display->display_options['fields']['field_choose_us_icon']['table'] = 'field_data_field_choose_us_icon';
  $handler->display->display_options['fields']['field_choose_us_icon']['field'] = 'field_choose_us_icon';
  $handler->display->display_options['fields']['field_choose_us_icon']['label'] = '';
  $handler->display->display_options['fields']['field_choose_us_icon']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_choose_us_icon']['element_label_colon'] = FALSE;
  /* Field: Field collection item: PPC S&S Section Bullet Title */
  $handler->display->display_options['fields']['field_choose_us_title']['id'] = 'field_choose_us_title';
  $handler->display->display_options['fields']['field_choose_us_title']['table'] = 'field_data_field_choose_us_title';
  $handler->display->display_options['fields']['field_choose_us_title']['field'] = 'field_choose_us_title';
  $handler->display->display_options['fields']['field_choose_us_title']['label'] = '';
  $handler->display->display_options['fields']['field_choose_us_title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_choose_us_title']['element_label_colon'] = FALSE;
  /* Field: Field collection item: PPC S&S Section Bullet Content */
  $handler->display->display_options['fields']['field_choose_us_description']['id'] = 'field_choose_us_description';
  $handler->display->display_options['fields']['field_choose_us_description']['table'] = 'field_data_field_choose_us_description';
  $handler->display->display_options['fields']['field_choose_us_description']['field'] = 'field_choose_us_description';
  $handler->display->display_options['fields']['field_choose_us_description']['label'] = '';
  $handler->display->display_options['fields']['field_choose_us_description']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_choose_us_description']['element_label_colon'] = FALSE;
  /* Field: Global: PHP */
  $handler->display->display_options['fields']['php']['id'] = 'php';
  $handler->display->display_options['fields']['php']['table'] = 'views';
  $handler->display->display_options['fields']['php']['field'] = 'php';
  $handler->display->display_options['fields']['php']['label'] = '';
  $handler->display->display_options['fields']['php']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php']['php_output'] = '<?php
$choose_title = $data->_field_data[item_id][entity]->field_choose_us_title[und][0][value];
$choose_desc = $data->_field_data[item_id][entity]->field_choose_us_description[und][0][value];
$choose_icon_class = $data->_field_data[item_id][entity]->field_choose_us_icon[und][0][value];
$choose_title_color = $data->_field_data[item_id][entity]->field_choose_us_title_color[und][0][jquery_colorpicker];
$choose_desc_color = $data->_field_data[item_id][entity]->field_choose_us_description_colo[und][0][jquery_colorpicker];
$choose_icon_bgcolor = $data->_field_data[item_id][entity]->field_choose_us_icon_background[und][0][jquery_colorpicker];
$icon_design_class = $data->_field_data[item_id][entity]->field_choose_us_icon_design[und][0][value];

$choose_title_text_size = $data->_field_data[item_id][entity]->field_choose_us_title_text_size[und][0][value];
$choose_desctxt_size = $data->_field_data[item_id][entity]->field_choose_us_description_text[und][0][value];
?>

<?php
print "<div class=\'choose-icon\'>";
print "<div class=\'icon-wrap ".$icon_design_class."\' style=\'background-color:#".$choose_icon_bgcolor.";\'>";
print "<div class=\'icon-wrap-before\' style=\'border-bottom-color:#".$choose_icon_bgcolor.";\'></div>";
print "<div class=\'icon-wrap-after\' style=\'border-top-color:#".$choose_icon_bgcolor.";\'></div>";
print "<div class=\'fa ".$choose_icon_class." 4x\'></div>";
print "</div>";

print "<div class=\'choose-icon-title ".$choose_title_text_size."\' style=\'color:#".$choose_title_color.";\'>".$choose_title."</div>";
print "<div class=\'choose-icon-desc ".$choose_desctxt_size."\' style=\'color:#".$choose_desc_color.";\'>".$choose_desc."</div>";


print "</div>";
?>';
  $handler->display->display_options['fields']['php']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php']['php_click_sortable'] = '';
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['relationship'] = 'field_ppc_choosing_node';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'ppc-choosing';
  $translatables['ppc_choosing'] = array(
    t('Master'),
    t('PPC Choosing'),
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
    t('field_ppc_choosing'),
    t('All'),
    t('Page'),
  );
  $export['ppc_choosing'] = $view;

  $view = new view();
  $view->name = 'ppc_reviews';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'field_collection_item';
  $view->human_name = 'PPC Reviews';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'PPC Reviews';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '0';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['style_plugin'] = 'flexslider';
  $handler->display->display_options['style_options']['optionset'] = 'ppc_reviewer_image_style';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Field collection item: Entity with the PPC Single Review/Logo/Trust Symbol (field_ppc_review) */
  $handler->display->display_options['relationships']['field_ppc_review_node']['id'] = 'field_ppc_review_node';
  $handler->display->display_options['relationships']['field_ppc_review_node']['table'] = 'field_collection_item';
  $handler->display->display_options['relationships']['field_ppc_review_node']['field'] = 'field_ppc_review_node';
  $handler->display->display_options['relationships']['field_ppc_review_node']['required'] = TRUE;
  /* Field: Field collection item: PPC Single Review/Logo/Trust Symbol Content */
  $handler->display->display_options['fields']['field_reviews_description']['id'] = 'field_reviews_description';
  $handler->display->display_options['fields']['field_reviews_description']['table'] = 'field_data_field_reviews_description';
  $handler->display->display_options['fields']['field_reviews_description']['field'] = 'field_reviews_description';
  $handler->display->display_options['fields']['field_reviews_description']['label'] = '';
  $handler->display->display_options['fields']['field_reviews_description']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_reviews_description']['element_label_colon'] = FALSE;
  /* Field: Field collection item: PPC Single Review/Logo/Trust Symbol Upload Area */
  $handler->display->display_options['fields']['field_reviewer_image']['id'] = 'field_reviewer_image';
  $handler->display->display_options['fields']['field_reviewer_image']['table'] = 'field_data_field_reviewer_image';
  $handler->display->display_options['fields']['field_reviewer_image']['field'] = 'field_reviewer_image';
  $handler->display->display_options['fields']['field_reviewer_image']['label'] = '';
  $handler->display->display_options['fields']['field_reviewer_image']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_reviewer_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_reviewer_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_reviewer_image']['settings'] = array(
    'image_style' => 'ppc_reviewer_image',
    'image_link' => '',
  );
  /* Field: Field collection item: PPC Single Review/Logo/Trust Symbol Text Description */
  $handler->display->display_options['fields']['field_reviewer_name']['id'] = 'field_reviewer_name';
  $handler->display->display_options['fields']['field_reviewer_name']['table'] = 'field_data_field_reviewer_name';
  $handler->display->display_options['fields']['field_reviewer_name']['field'] = 'field_reviewer_name';
  $handler->display->display_options['fields']['field_reviewer_name']['label'] = '';
  $handler->display->display_options['fields']['field_reviewer_name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_reviewer_name']['element_label_colon'] = FALSE;
  /* Field: Field collection item: PPC Single Review/Logo/Trust Symbol Text Description Color */
  $handler->display->display_options['fields']['field_reviewer_name_color']['id'] = 'field_reviewer_name_color';
  $handler->display->display_options['fields']['field_reviewer_name_color']['table'] = 'field_data_field_reviewer_name_color';
  $handler->display->display_options['fields']['field_reviewer_name_color']['field'] = 'field_reviewer_name_color';
  $handler->display->display_options['fields']['field_reviewer_name_color']['label'] = '';
  $handler->display->display_options['fields']['field_reviewer_name_color']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_reviewer_name_color']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_reviewer_name_color']['type'] = 'jquery_colorpicker_raw_hex_display';
  /* Field: Global: PHP */
  $handler->display->display_options['fields']['php']['id'] = 'php';
  $handler->display->display_options['fields']['php']['table'] = 'views';
  $handler->display->display_options['fields']['php']['field'] = 'php';
  $handler->display->display_options['fields']['php']['label'] = '';
  $handler->display->display_options['fields']['php']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php']['php_output'] = '<?php 
$rev_desc = $data->_field_data[item_id][entity]->field_reviews_description[und][0][value];
$rev_image = $data->_field_data[item_id][entity]->field_reviewer_image[und][0][uri];
$rev_name = $data->_field_data[item_id][entity]->field_reviewer_name[und][0][value];
$rev_name_color = $data->_field_data[item_id][entity]->field_reviewer_name_color[und][0][jquery_colorpicker];
$rev_desc_color = $data->_field_data[item_id][entity]->field_reviews_description_color[und][0][jquery_colorpicker];
$rev_desc_size = $data->_field_data[item_id][entity]->field_reviews_description_text_s[und][0][value];
?>
<div class="ppc-reviews-area">
<?php
print "<div class=\'reviews-desc ".$rev_desc_size."\' style=\'color:# ".$rev_desc_color.";\'>".$rev_desc."</div>";
print \'<img src=" \'. file_create_url($rev_image) .\' " class="reviewer-image" />\';
print "<div class=\'reviewer-name\' style=\'color:#".$rev_name_color.";\'>".$rev_name."</div>";
?>
</div>';
  $handler->display->display_options['fields']['php']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php']['php_click_sortable'] = '';
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['relationship'] = 'field_ppc_review_node';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'ppc-reviews';
  $translatables['ppc_reviews'] = array(
    t('Master'),
    t('PPC Reviews'),
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
    t('field_ppc_review'),
    t('All'),
    t('Page'),
  );
  $export['ppc_reviews'] = $view;

  return $export;
}
