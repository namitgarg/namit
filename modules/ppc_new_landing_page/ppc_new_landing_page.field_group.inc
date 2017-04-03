<?php
/**
 * @file
 * ppc_new_landing_page.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function ppc_new_landing_page_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_block_2|node|ppc_new_landing_page|form';
  $field_group->group_name = 'group_block_2';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ppc_new_landing_page';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Block One',
    'weight' => '6',
    'children' => array(
      0 => 'field_ppc_form_title_line_1_cont',
      1 => 'field_ppc_form_title_line_1_c',
      2 => 'field_ppc_form_title_line_1_colo',
      3 => 'field_ppc_form_title_line_2_text',
      4 => 'field_ppc_form_title_line_2_txt',
      5 => 'field_ppc_form_title_line_2_txts',
      6 => 'field_ppc_formsite_embed_code',
      7 => 'field_ppc_form_background_color',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Block One',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-block-2 field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsible',
    ),
  );
  $export['group_block_2|node|ppc_new_landing_page|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_block_three|node|ppc_new_landing_page|form';
  $field_group->group_name = 'group_block_three';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ppc_new_landing_page';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Block Three',
    'weight' => '9',
    'children' => array(
      0 => 'field_ppc_s_s_section_bullet_cho',
      1 => 'field_ppc_ss_section_bullet_cho',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-block-three field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_block_three|node|ppc_new_landing_page|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_block_two|node|ppc_new_landing_page|form';
  $field_group->group_name = 'group_block_two';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ppc_new_landing_page';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => ' Block Two',
    'weight' => '8',
    'children' => array(
      0 => 'field_ppc_shapes_symbols_section',
      1 => 'field_ppc_s_s_section_title_text',
      2 => 'field_ppc_ss_section_title_txt_c',
      3 => 'field_ppc_ss_section_title_desc',
      4 => 'field_ppc_s_s_section_descriptio',
      5 => 'field_ppc_ss_section_descr_size',
      6 => 'field_ppc_ss_section_desc_color',
      7 => 'field_ppc_ss_section_desc_link_c',
      8 => 'field_ppc_ss_sec_desc_link_size',
      9 => 'field_ppc_s_s_section_title_hori',
      10 => 'field_ppc_s_s_section_title_bord',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-block-two field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_block_two|node|ppc_new_landing_page|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_footer_right|node|ppc_new_landing_page|form';
  $field_group->group_name = 'group_footer_right';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ppc_new_landing_page';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_footer';
  $field_group->data = array(
    'label' => 'PPC Footer Right',
    'weight' => '85',
    'children' => array(
      0 => 'field_ppc_address',
      1 => 'field_ppc_address_text_size',
      2 => 'field_ppc_address_line_2_',
      3 => 'field_ppc_address_line_2_text_si',
      4 => 'field_ppc_address_line_1_text_co',
      5 => 'field_ppc_address_line_2_text_co',
      6 => 'field_ppc_footer_right_backgroun',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-footer-right field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_footer_right|node|ppc_new_landing_page|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_footer|node|ppc_new_landing_page|form';
  $field_group->group_name = 'group_footer';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ppc_new_landing_page';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'PPC Footer',
    'weight' => '10',
    'children' => array(
      0 => 'field_ppc_bottom_banner_share_ad',
      1 => 'field_ppc_footer_content',
      2 => 'field_ppc_bottom_banner_share_ba',
      3 => 'field_ppc_footer_content_text_si',
      4 => 'field_ppc_footer_content_text_co',
      5 => 'group_footer_right',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-footer field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_footer|node|ppc_new_landing_page|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_header|node|ppc_new_landing_page|form';
  $field_group->group_name = 'group_header';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ppc_new_landing_page';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Header',
    'weight' => '5',
    'children' => array(
      0 => 'field_ppc_new_fonts',
      1 => 'field_ppc_new_logo',
      2 => 'field_ppc_new_upper_right_text',
      3 => 'field_ppc_upper_right_text_color',
      4 => 'field_ppc_phone_number',
      5 => 'field_ppc_phone_number_color',
      6 => 'field_ppc_upper_right_text_line_',
      7 => 'field_ppc_upper_right_text_ln_co',
      8 => 'field_ppc_new_top_banner',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-header field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_header|node|ppc_new_landing_page|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_one_a|node|ppc_new_landing_page|form';
  $field_group->group_name = 'group_one_a';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ppc_new_landing_page';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Block One (a)',
    'weight' => '7',
    'children' => array(
      0 => 'field_ppc_new_wysiwyg_section',
      1 => 'field_ppc_new_wysiwyg_section_te',
      2 => 'field_ppc_new_wysiwyg_section_ba',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-one-a field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_one_a|node|ppc_new_landing_page|form'] = $field_group;

  return $export;
}
