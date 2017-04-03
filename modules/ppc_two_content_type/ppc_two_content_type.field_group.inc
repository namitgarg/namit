<?php
/**
 * @file
 * ppc_two_content_type.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function ppc_two_content_type_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_block_area_1|node|ppc_two|form';
  $field_group->group_name = 'group_block_area_1';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ppc_two';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Block 2',
    'weight' => '8',
    'children' => array(
      0 => 'field_ppc_two_help_form_heading',
      1 => 'field_ppc_two_heading_color',
      2 => 'field_ppc_two_help_form_heading_',
      3 => 'field_ppc_two_heading_slogan_col',
      4 => 'field_ppc_two_help_form',
      5 => 'field_ppc_two_help_form_backgrou',
      6 => 'field_ppc2_help_form_heading_siz',
      7 => 'field_pc2_help_form_heading_size',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Block 2',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-block-area-1 field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsible',
    ),
  );
  $export['group_block_area_1|node|ppc_two|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_block_area_2|node|ppc_two|form';
  $field_group->group_name = 'group_block_area_2';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ppc_two';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Block 1a',
    'weight' => '6',
    'children' => array(
      0 => 'field_ppc_two_choose_heading',
      1 => 'field_ppc_two_choose_heading_col',
      2 => 'field_ppc_two_choosing',
      3 => 'field_ppc_two_choose_icon_backgr',
      4 => 'field_ppc_two_choose_heading_siz',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Block 1a',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-block-area-2 field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsible',
    ),
  );
  $export['group_block_area_2|node|ppc_two|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_block_area_3|node|ppc_two|form';
  $field_group->group_name = 'group_block_area_3';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ppc_two';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Block 3',
    'weight' => '9',
    'children' => array(
      0 => 'field_ppc_two_footer_banner_head',
      1 => 'field_ppc_two_banner_heading_col',
      2 => 'field_ppc_two_footer_banner_slog',
      3 => 'field_ppc_two_baner_slogn_colo',
      4 => 'field_ppc_two_footer_banner_text',
      5 => 'field_ppc_two_footer_b_text_colo',
      6 => 'field_ppc_two_bottom_heading',
      7 => 'field_ppc_two_bottom_heading_col',
      8 => 'field_ppc_two_signature',
      9 => 'field_ppc_two_signature_color',
      10 => 'field_ppc_two_read_more',
      11 => 'field_ppc_two_read_more_color',
      12 => 'field_ppc_two_share',
      13 => 'field_ppc_two_bottom_banner_bg_c',
      14 => 'field_ppc2_footer_banner_head_si',
      15 => 'field_ppc2_footer_banner_slog_si',
      16 => 'field_ppc2_footer_banner_text_si',
      17 => 'field_ppc_two_bottom_heading_siz',
      18 => 'field_ppc_two_signature_text_siz',
      19 => 'field_ppc_two_read_more_size',
      20 => 'field_ppc_two_bottom_banner_imag',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Block 3',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-block-area-3 field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsible',
    ),
  );
  $export['group_block_area_3|node|ppc_two|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_footer_area|node|ppc_two|form';
  $field_group->group_name = 'group_footer_area';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ppc_two';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'PPC Two Reviews/Logos/Trust Symbols Section ',
    'weight' => '10',
    'children' => array(
      0 => 'field_ppc_two_review_around_glob',
      1 => 'field_ppc_two_review_around_gl',
      2 => 'field_ppc_two_review',
      3 => 'field_ppc_two_review_background_',
      4 => 'field_ppc_two_review_text_size',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'PPC Two Reviews/Logos/Trust Symbols Section ',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-footer-area field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsible',
    ),
  );
  $export['group_footer_area|node|ppc_two|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_header_area|node|ppc_two|form';
  $field_group->group_name = 'group_header_area';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ppc_two';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Header',
    'weight' => '5',
    'children' => array(
      0 => 'field_ppc_two_logo',
      1 => 'field_ppc_two_call_us',
      2 => 'field_ppc_two_call_us_color',
      3 => 'field_ppc_two_contact',
      4 => 'field_ppc_two_contact_color',
      5 => 'field_ppc_tow_contact_text',
      6 => 'field_ppc_two_contact_text_color',
      7 => 'field_ppc_two_top_banner',
      8 => 'field_ppc_tow_fonts',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-header-area field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_header_area|node|ppc_two|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_ppc_two_footer|node|ppc_two|form';
  $field_group->group_name = 'group_ppc_two_footer';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ppc_two';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'PPC Two Footer',
    'weight' => '11',
    'children' => array(
      0 => 'field_ppc_two_footer',
      1 => 'field_ppc_two_footer_color',
      2 => 'field_ppc_two_footer_text_size',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-ppc-two-footer field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_ppc_two_footer|node|ppc_two|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_practice_area|node|ppc_two|form';
  $field_group->group_name = 'group_practice_area';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ppc_two';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Block 1b',
    'weight' => '7',
    'children' => array(
      0 => 'field_ppc_two_body_text',
      1 => 'field_ppc_two_body_text_backgrou',
      2 => 'field_ppc_two_body_text_color',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Block 1b',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-practice-area field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsible',
    ),
  );
  $export['group_practice_area|node|ppc_two|form'] = $field_group;

  return $export;
}
