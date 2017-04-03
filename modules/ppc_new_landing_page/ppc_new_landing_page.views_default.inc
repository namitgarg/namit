<?php
/**
 * @file
 * ppc_new_landing_page.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function ppc_new_landing_page_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'ppc_new_banner';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'field_collection_item';
  $view->human_name = 'PPC New Banner';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'PPC New Banner';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Field collection item: Entity with the PPC Top Banner (field_ppc_new_top_banner) */
  $handler->display->display_options['relationships']['field_ppc_new_top_banner_node']['id'] = 'field_ppc_new_top_banner_node';
  $handler->display->display_options['relationships']['field_ppc_new_top_banner_node']['table'] = 'field_collection_item';
  $handler->display->display_options['relationships']['field_ppc_new_top_banner_node']['field'] = 'field_ppc_new_top_banner_node';
  $handler->display->display_options['relationships']['field_ppc_new_top_banner_node']['required'] = TRUE;
  /* Field: Field collection item: PPC  Banner */
  $handler->display->display_options['fields']['field_ppc_new_banner']['id'] = 'field_ppc_new_banner';
  $handler->display->display_options['fields']['field_ppc_new_banner']['table'] = 'field_data_field_ppc_new_banner';
  $handler->display->display_options['fields']['field_ppc_new_banner']['field'] = 'field_ppc_new_banner';
  $handler->display->display_options['fields']['field_ppc_new_banner']['label'] = '';
  $handler->display->display_options['fields']['field_ppc_new_banner']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_ppc_new_banner']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ppc_new_banner']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_ppc_new_banner']['settings'] = array(
    'image_style' => '',
    'image_link' => '',
  );
  /* Field: Field collection item: PPC Banner Text Top Line */
  $handler->display->display_options['fields']['field_ppc_new_banner_text_top_li']['id'] = 'field_ppc_new_banner_text_top_li';
  $handler->display->display_options['fields']['field_ppc_new_banner_text_top_li']['table'] = 'field_data_field_ppc_new_banner_text_top_li';
  $handler->display->display_options['fields']['field_ppc_new_banner_text_top_li']['field'] = 'field_ppc_new_banner_text_top_li';
  $handler->display->display_options['fields']['field_ppc_new_banner_text_top_li']['label'] = '';
  $handler->display->display_options['fields']['field_ppc_new_banner_text_top_li']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_ppc_new_banner_text_top_li']['element_label_colon'] = FALSE;
  /* Field: Field collection item: PPC Banner Text Top Line Size */
  $handler->display->display_options['fields']['field_ppc_new_banner_text_top_l']['id'] = 'field_ppc_new_banner_text_top_l';
  $handler->display->display_options['fields']['field_ppc_new_banner_text_top_l']['table'] = 'field_data_field_ppc_new_banner_text_top_l';
  $handler->display->display_options['fields']['field_ppc_new_banner_text_top_l']['field'] = 'field_ppc_new_banner_text_top_l';
  $handler->display->display_options['fields']['field_ppc_new_banner_text_top_l']['label'] = '';
  $handler->display->display_options['fields']['field_ppc_new_banner_text_top_l']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_ppc_new_banner_text_top_l']['element_label_colon'] = FALSE;
  /* Field: Field collection item: Banner Text Top Line Color */
  $handler->display->display_options['fields']['field_banner_new_text_top_line_c']['id'] = 'field_banner_new_text_top_line_c';
  $handler->display->display_options['fields']['field_banner_new_text_top_line_c']['table'] = 'field_data_field_banner_new_text_top_line_c';
  $handler->display->display_options['fields']['field_banner_new_text_top_line_c']['field'] = 'field_banner_new_text_top_line_c';
  $handler->display->display_options['fields']['field_banner_new_text_top_line_c']['label'] = '';
  $handler->display->display_options['fields']['field_banner_new_text_top_line_c']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_banner_new_text_top_line_c']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_banner_new_text_top_line_c']['type'] = 'jquery_colorpicker_raw_hex_display';
  /* Field: Field collection item: PPC Banner Text Second Line */
  $handler->display->display_options['fields']['field_ppc_new_banner_text_second']['id'] = 'field_ppc_new_banner_text_second';
  $handler->display->display_options['fields']['field_ppc_new_banner_text_second']['table'] = 'field_data_field_ppc_new_banner_text_second';
  $handler->display->display_options['fields']['field_ppc_new_banner_text_second']['field'] = 'field_ppc_new_banner_text_second';
  $handler->display->display_options['fields']['field_ppc_new_banner_text_second']['label'] = '';
  $handler->display->display_options['fields']['field_ppc_new_banner_text_second']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_ppc_new_banner_text_second']['element_label_colon'] = FALSE;
  /* Field: Field collection item: PPC Banner Text Second Line Size */
  $handler->display->display_options['fields']['field_ppc_new_banner_text_secon']['id'] = 'field_ppc_new_banner_text_secon';
  $handler->display->display_options['fields']['field_ppc_new_banner_text_secon']['table'] = 'field_data_field_ppc_new_banner_text_secon';
  $handler->display->display_options['fields']['field_ppc_new_banner_text_secon']['field'] = 'field_ppc_new_banner_text_secon';
  $handler->display->display_options['fields']['field_ppc_new_banner_text_secon']['label'] = '';
  $handler->display->display_options['fields']['field_ppc_new_banner_text_secon']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_ppc_new_banner_text_secon']['element_label_colon'] = FALSE;
  /* Field: Field collection item: PPC Banner Text Second Line Color */
  $handler->display->display_options['fields']['field_ppc_banner_text_second_lin']['id'] = 'field_ppc_banner_text_second_lin';
  $handler->display->display_options['fields']['field_ppc_banner_text_second_lin']['table'] = 'field_data_field_ppc_banner_text_second_lin';
  $handler->display->display_options['fields']['field_ppc_banner_text_second_lin']['field'] = 'field_ppc_banner_text_second_lin';
  $handler->display->display_options['fields']['field_ppc_banner_text_second_lin']['label'] = '';
  $handler->display->display_options['fields']['field_ppc_banner_text_second_lin']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_ppc_banner_text_second_lin']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ppc_banner_text_second_lin']['type'] = 'jquery_colorpicker_raw_hex_display';
  /* Field: Global: PHP */
  $handler->display->display_options['fields']['php']['id'] = 'php';
  $handler->display->display_options['fields']['php']['table'] = 'views';
  $handler->display->display_options['fields']['php']['field'] = 'php';
  $handler->display->display_options['fields']['php']['label'] = '';
  $handler->display->display_options['fields']['php']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php']['php_output'] = '<?php
$banner_image = $data->_field_data[item_id][entity]->field_ppc_new_banner[und][0][uri];
$banner_text_f = $data->_field_data[item_id][entity]->field_ppc_new_banner_text_top_li[und][0][value];
$banner_text_f_size = $data->_field_data[item_id][entity]->field_ppc_new_banner_text_top_l[und][0][value];
$banner_text_f_color = $data->_field_data[item_id][entity]->field_banner_new_text_top_line_c[und][0][jquery_colorpicker];
$banner_text_s = $data->_field_data[item_id][entity]->field_ppc_new_banner_text_second[und][0][value];
$banner_text_s_size = $data->_field_data[item_id][entity]->field_ppc_new_banner_text_secon[und][0][value];
$banner_text_s_color = $data->_field_data[item_id][entity]->field_ppc_banner_text_second_lin[und][0][jquery_colorpicker];
?>
<?php
print \'<img src=" \'. file_create_url($banner_image) .\' "  class="banner-image" />\';
?>
<div class="banner-text-area-new">

<?php
print "<div class=\'text-title1-new ".$banner_text_f_size."\' style=\'color:#".$banner_text_f_color.";\'>".$banner_text_f. "</div>";
print "<div class=\'text-title2-new ".$banner_text_s_size."\' style=\'color:#".$banner_text_s_color.";\'>".$banner_text_s. "</div>";
?>

</div>';
  $handler->display->display_options['fields']['php']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php']['php_click_sortable'] = '';
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['relationship'] = 'field_ppc_new_top_banner_node';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'ppc-new-banner';
  $translatables['ppc_new_banner'] = array(
    t('Master'),
    t('PPC New Banner'),
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
    t('field_ppc_new_top_banner'),
    t('All'),
    t('Page'),
  );
  $export['ppc_new_banner'] = $view;

  $view = new view();
  $view->name = 'ppc_new_s_s_section';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'field_collection_item';
  $view->human_name = 'PPC New S&S Section';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'PPC New S&S Section';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Field collection item: Entity with the PPC S&amp;S Section Bullet Choices (field_ppc_s_s_section_bullet_cho) */
  $handler->display->display_options['relationships']['field_ppc_s_s_section_bullet_cho_node']['id'] = 'field_ppc_s_s_section_bullet_cho_node';
  $handler->display->display_options['relationships']['field_ppc_s_s_section_bullet_cho_node']['table'] = 'field_collection_item';
  $handler->display->display_options['relationships']['field_ppc_s_s_section_bullet_cho_node']['field'] = 'field_ppc_s_s_section_bullet_cho_node';
  $handler->display->display_options['relationships']['field_ppc_s_s_section_bullet_cho_node']['required'] = TRUE;
  /* Field: Field collection item: PPC S&S Section Bullet Content */
  $handler->display->display_options['fields']['field_ppc_s_s_section_bullet_con']['id'] = 'field_ppc_s_s_section_bullet_con';
  $handler->display->display_options['fields']['field_ppc_s_s_section_bullet_con']['table'] = 'field_data_field_ppc_s_s_section_bullet_con';
  $handler->display->display_options['fields']['field_ppc_s_s_section_bullet_con']['field'] = 'field_ppc_s_s_section_bullet_con';
  $handler->display->display_options['fields']['field_ppc_s_s_section_bullet_con']['label'] = '';
  $handler->display->display_options['fields']['field_ppc_s_s_section_bullet_con']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_ppc_s_s_section_bullet_con']['element_label_colon'] = FALSE;
  /* Field: Field collection item: PPC S&S Section Bullet Content Color */
  $handler->display->display_options['fields']['field_ppc_s_s_sect_bullet_con_co']['id'] = 'field_ppc_s_s_sect_bullet_con_co';
  $handler->display->display_options['fields']['field_ppc_s_s_sect_bullet_con_co']['table'] = 'field_data_field_ppc_s_s_sect_bullet_con_co';
  $handler->display->display_options['fields']['field_ppc_s_s_sect_bullet_con_co']['field'] = 'field_ppc_s_s_sect_bullet_con_co';
  $handler->display->display_options['fields']['field_ppc_s_s_sect_bullet_con_co']['label'] = '';
  $handler->display->display_options['fields']['field_ppc_s_s_sect_bullet_con_co']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_ppc_s_s_sect_bullet_con_co']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ppc_s_s_sect_bullet_con_co']['type'] = 'jquery_colorpicker_raw_hex_display';
  /* Field: Field collection item: PPC S&S Section Bullet Content Size */
  $handler->display->display_options['fields']['field_ppc_s_s_sec_bullet_con_siz']['id'] = 'field_ppc_s_s_sec_bullet_con_siz';
  $handler->display->display_options['fields']['field_ppc_s_s_sec_bullet_con_siz']['table'] = 'field_data_field_ppc_s_s_sec_bullet_con_siz';
  $handler->display->display_options['fields']['field_ppc_s_s_sec_bullet_con_siz']['field'] = 'field_ppc_s_s_sec_bullet_con_siz';
  $handler->display->display_options['fields']['field_ppc_s_s_sec_bullet_con_siz']['label'] = '';
  $handler->display->display_options['fields']['field_ppc_s_s_sec_bullet_con_siz']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_ppc_s_s_sec_bullet_con_siz']['element_label_colon'] = FALSE;
  /* Field: Field collection item: PPC S&S Section Bullet Title */
  $handler->display->display_options['fields']['field_ppc_s_s_section_bullet_tit']['id'] = 'field_ppc_s_s_section_bullet_tit';
  $handler->display->display_options['fields']['field_ppc_s_s_section_bullet_tit']['table'] = 'field_data_field_ppc_s_s_section_bullet_tit';
  $handler->display->display_options['fields']['field_ppc_s_s_section_bullet_tit']['field'] = 'field_ppc_s_s_section_bullet_tit';
  $handler->display->display_options['fields']['field_ppc_s_s_section_bullet_tit']['label'] = '';
  $handler->display->display_options['fields']['field_ppc_s_s_section_bullet_tit']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_ppc_s_s_section_bullet_tit']['element_label_colon'] = FALSE;
  /* Field: Field collection item: PPC S&S Section Bullet Title Color */
  $handler->display->display_options['fields']['field_ppc_ss_sec_bullet_tit_colo']['id'] = 'field_ppc_ss_sec_bullet_tit_colo';
  $handler->display->display_options['fields']['field_ppc_ss_sec_bullet_tit_colo']['table'] = 'field_data_field_ppc_ss_sec_bullet_tit_colo';
  $handler->display->display_options['fields']['field_ppc_ss_sec_bullet_tit_colo']['field'] = 'field_ppc_ss_sec_bullet_tit_colo';
  $handler->display->display_options['fields']['field_ppc_ss_sec_bullet_tit_colo']['label'] = '';
  $handler->display->display_options['fields']['field_ppc_ss_sec_bullet_tit_colo']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_ppc_ss_sec_bullet_tit_colo']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ppc_ss_sec_bullet_tit_colo']['type'] = 'jquery_colorpicker_raw_hex_display';
  /* Field: Field collection item: PPC S&S Section Bullet Title Size */
  $handler->display->display_options['fields']['field_ppc_ss_sec_bullet_tit_siz']['id'] = 'field_ppc_ss_sec_bullet_tit_siz';
  $handler->display->display_options['fields']['field_ppc_ss_sec_bullet_tit_siz']['table'] = 'field_data_field_ppc_ss_sec_bullet_tit_siz';
  $handler->display->display_options['fields']['field_ppc_ss_sec_bullet_tit_siz']['field'] = 'field_ppc_ss_sec_bullet_tit_siz';
  $handler->display->display_options['fields']['field_ppc_ss_sec_bullet_tit_siz']['label'] = '';
  $handler->display->display_options['fields']['field_ppc_ss_sec_bullet_tit_siz']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_ppc_ss_sec_bullet_tit_siz']['element_label_colon'] = FALSE;
  /* Field: Global: PHP */
  $handler->display->display_options['fields']['php']['id'] = 'php';
  $handler->display->display_options['fields']['php']['table'] = 'views';
  $handler->display->display_options['fields']['php']['field'] = 'php';
  $handler->display->display_options['fields']['php']['label'] = '';
  $handler->display->display_options['fields']['php']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php']['php_output'] = '<?php
$ss_title = $data->_field_data[item_id][entity]->field_ppc_s_s_section_bullet_tit[und][0][value];
$ss_title_size = $data->_field_data[item_id][entity]->field_ppc_ss_sec_bullet_tit_siz[und][0][value];
$ss_title_color = $data->_field_data[item_id][entity]->field_ppc_ss_sec_bullet_tit_colo[und][0][jquery_colorpicker];

$ss_content = $data->_field_data[item_id][entity]->field_ppc_s_s_section_bullet_con[und][0][value];
$ss_content_size = $data->_field_data[item_id][entity]->field_ppc_s_s_sec_bullet_con_siz[und][0][value];
$ss_content_color = $data->_field_data[item_id][entity]->field_ppc_s_s_sect_bullet_con_co[und][0][jquery_colorpicker];
$choose_icon_class= $data->_field_data[item_id][entity]->field_ppc_s_s_section_bullet_ico[und][0][value];
$ss_icon_color = $data->_field_data[item_id][entity]->field_ppc_ss_section_bullet_ic_b[und][0][jquery_colorpicker];
?>

<div class="ppc-new-s-s-area">
<?php
print "<div class=\'fa ".$choose_icon_class." 4x\' style=\'color:#".$ss_icon_color.";\'></div>";
print "<div class=\'titlecontent-wrap-new\'>";
print "<div class=\'ppc-ss-new-title\' style=\'color:#".$ss_title_color.";\' class=\' ".$ss_title_size." \'>".$ss_title. "</div>";
print "<div class=\'ppc-ss-new-content\' style=\'color:#".$ss_content_color.";\' class=\' ".$ss_content_size." \'>".$ss_content. "</div>";
print "</div>";
?>
</div>';
  $handler->display->display_options['fields']['php']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php']['php_click_sortable'] = '';
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['relationship'] = 'field_ppc_s_s_section_bullet_cho_node';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'ppc-new-s-s-section';
  $translatables['ppc_new_s_s_section'] = array(
    t('Master'),
    t('PPC New S&S Section'),
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
    t('field_ppc_s_s_section_bullet_cho'),
    t('All'),
    t('Page'),
  );
  $export['ppc_new_s_s_section'] = $view;

  return $export;
}
