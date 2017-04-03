<?php
/**
 * @file
 * ppc_content_type.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function ppc_content_type_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_block_area_1|node|ppc|form';
  $field_group->group_name = 'group_block_area_1';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ppc';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Block 2',
    'weight' => '8',
    'children' => array(
      0 => 'field_ppc_help_form',
      1 => 'field_ppc_help_form_heading',
      2 => 'field_heading_color',
      3 => 'field_ppc_help_form_heading_slog',
      4 => 'field_heading_slogan_color',
      5 => 'field_ppc_help_form_background_c',
      6 => 'field_ppc_help_form_heading_text',
      7 => 'field_help_form_heading_slog_siz',
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
  $export['group_block_area_1|node|ppc|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_block_area_2|node|ppc|form';
  $field_group->group_name = 'group_block_area_2';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ppc';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Block 1a',
    'weight' => '6',
    'children' => array(
      0 => 'field_ppc_choose_heading',
      1 => 'field_choose_heading_color',
      2 => 'field_ppc_choosing',
      3 => 'field_ppc_choose_icon_background',
      4 => 'field_ppc_choose_heading_text_si',
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
  $export['group_block_area_2|node|ppc|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_block_area_3|node|ppc|form';
  $field_group->group_name = 'group_block_area_3';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ppc';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Block 3',
    'weight' => '9',
    'children' => array(
      0 => 'field_ppc_banner_footer',
      1 => 'field_ppc_footer_banner_text',
      2 => 'field_ppc_signature',
      3 => 'field_ppc_share',
      4 => 'field_ppc_footer_banner_heading',
      5 => 'field_ppc_footer_banner_slogan',
      6 => 'field_banner_heading_color',
      7 => 'field_banner_slogan_color',
      8 => 'field_ppc_bottom_heading',
      9 => 'field_bottom_heading_color',
      10 => 'field_ppc_signature_color',
      11 => 'field_ppc_read_more',
      12 => 'field_ppc_footer_banner_text_col',
      13 => 'field_ppc_read_more_color',
      14 => 'field_ppc_banner_footer_bg_color',
      15 => 'field_footer_banner_heading_size',
      16 => 'field_footer_banner_slogan_size',
      17 => 'field_ppc_footer_banner_text_siz',
      18 => 'field_ppc_signature_text_size',
      19 => 'field_ppc_bottom_heading_text_si',
      20 => 'field_ppc_read_more_size',
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
  $export['group_block_area_3|node|ppc|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_footer_area|node|ppc|form';
  $field_group->group_name = 'group_footer_area';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ppc';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'PPC Two Reviews/Logos/Trust Symbols Section	',
    'weight' => '10',
    'children' => array(
      0 => 'field_ppc_review',
      1 => 'field_review_background_color',
      2 => 'field_ppc_review_around_globe',
      3 => 'field_review_around_globe_color',
      4 => 'field_text_size',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'PPC Two Reviews/Logos/Trust Symbols Section	',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-footer-area field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsible',
    ),
  );
  $export['group_footer_area|node|ppc|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_header_area|node|ppc|form';
  $field_group->group_name = 'group_header_area';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ppc';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Header',
    'weight' => '5',
    'children' => array(
      0 => 'field_ppc_logo',
      1 => 'field_ppc_contact',
      2 => 'field_ppc_contact_text',
      3 => 'field_ppc_contact_color',
      4 => 'field_ppc_contact_text_color',
      5 => 'field_ppc_top_banner',
      6 => 'field_ppc_call_us',
      7 => 'field_ppc_call_us_color',
      8 => 'field_ppc_fonts',
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
  $export['group_header_area|node|ppc|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_ppc_footer|node|ppc|form';
  $field_group->group_name = 'group_ppc_footer';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ppc';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'PPC Footer',
    'weight' => '11',
    'children' => array(
      0 => 'field_ppc_footer',
      1 => 'field_ppc_footer_color',
      2 => 'field_ppc_footer_text_size',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-ppc-footer field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_ppc_footer|node|ppc|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_practice_area_block|node|ppc|form';
  $field_group->group_name = 'group_practice_area_block';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ppc';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Block 1b',
    'weight' => '7',
    'children' => array(
      0 => 'field_ppc_body_text',
      1 => 'field_ppc_body_text_background_c',
      2 => 'field_ppc_body_text_color',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Block 1b',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-practice-area-block field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsible',
    ),
  );
  $export['group_practice_area_block|node|ppc|form'] = $field_group;

  return $export;
}
