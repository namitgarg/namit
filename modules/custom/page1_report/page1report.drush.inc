<?php

/**
 * Implements hook_drush_command().
 */
function page1report_drush_command() {
    $items['metatag-check'] = array(
        'description' => 'Check if the cache setting is corrct or not',
        'aliases' => array('meta-check'),
    );
    $items['module-list'] = array(
        'description' => 'check if module is enabled or not',
        'aliases' => array('module-list'),
    );
    return $items;
}

function drush_page1report_metatag_check() {
    $query = db_select('metatag_config', 'mc')
            ->fields('mc', array('instance', 'config'))
            ->condition('instance', 'node');
    $results = $query->execute()->fetchAll();
    foreach ($results as $values) {
        $meta_name = $values->instance;
        $meta_data = unserialize($values->config);
        $og_url[$meta_name] = $meta_data['og:url']['value'];
        print("," . $meta_name . "," . $meta_data['og:url']['value']);
    }
}

function drush_page1report_module_list() {
    $file_path = "/tmp/custom_drush/";
    $filename = "module_list.csv";
    $file_url = $file_path . $filename;
//    $file = file_save_data('', $file_url, FILE_EXISTS_REPLACE);
//    drupal_add_http_header('Content-Type', 'text/csv');
//    drupal_add_http_header('Content-Disposition', 'attachment;filename=' . $filename);

    $module_list = array(
        'site_name' => variable_get('file_private_path'),
        'content_access' => 'Content Access',
        'content_access_rules' => 'Content Access Rules Integrations',
        'nodeaccess' => 'Nodeaccess',
        'acquia_agent' => 'Acquia agent',
        'acquia_search' => 'Acquia search',
        'acquia_spi' => 'Acquia Site Profile Information',
        'actions_permissions' => 'Actions permissions',
        'admin_devel' => 'Administration Development tools',
        'admin_menu' => 'Administration menu',
        'admin_menu_toolbar' => 'Administration menu Toolbar style',
        'menu_admin_per_menu' => 'Menu Admin per Menu',
        'module_missing_message_fixer' => 'Module Missing Message Fixer',
        'advagg_font' => 'AdvAgg Async Font Loader',
        'advagg_bundler' => 'AdvAgg Bundler',
        'advagg_css_cdn' => 'AdvAgg CDN CSS',
        'advagg_js_cdn' => 'AdvAgg CDN Javascript',
        'advagg_css_compress' => 'AdvAgg Compress CSS',
        'advagg_js_compress' => 'AdvAgg Compress Javascript',
        'advagg_validator' => 'AdvAgg CSS/JS Validator',
        'advagg_ext_compress' => 'AdvAgg External Compression',
        'advagg_mod' => 'AdvAgg Modifier',
        'advagg_sri' => 'AdvAgg Suybresource Integrity',
        'advagg' => 'Advanced CSS/JS Aggregation',
        'blogger_importer' => 'Blogger Importer',
        'bulk_export' => 'Bulk Export',
        'ctools' => 'Chaos tools',
        'ctools_ajax_sample' => ',CTools AJAX Example',
        'ctools_plugin_example' => 'Chaos Tools( CTools Plugin Example )',
        'ctools_custom_content' => 'Custom content panes',
        'ctools_access_ruleset' => 'Custom rulesets',
        'page_manager' => 'Page manager',
        'stylizer' => 'Stylizer',
        'term_depth' => 'Term Depth access',
        'views_content' => 'Views content panes',
        'context' => 'Context',
        'context_layouts' => 'Context layouts',
        'context_ui' => 'Context UI',
        'aggregator' => 'Aggregator',
        'block' => 'Block',
        'blog' => 'Blog',
        'book' => 'Book',
        'color' => 'Color',
        'comment' => 'Comment',
        'contact' => 'Contact',
        'translation' => 'Content translation',
        'contextual' => 'Contextual links',
        'dashboard' => 'Dashboard',
        'dblog' => 'Database logging',
        'field' => 'Field',
        'field_sql_storage' => 'Field SQL storage',
        'field_ui' => 'Field UI',
        'file' => 'File',
        'filter' => 'Filter',
        'forum' => 'Forum',
        'help' => 'Help',
        'image' => 'Image',
        'list' => 'List',
        'locale' => 'Locale',
        'menu' => 'Menu',
        'node' => 'Node',
        'number' => 'Number',
        'openid' => 'OpenID',
        'options' => 'Options',
        'overlay' => 'Overlay',
        'path' => 'Path',
        'php' => 'PHP filter',
        'poll' => 'Poll',
        'rdf' => 'RDF',
        'search' => 'Search',
        'shortcut' => 'Shortcut',
        'statistics' => 'Statistics',
        'syslog' => 'Syslog',
        'system' => 'System',
        'taxonomy' => 'Taxonomy',
        'simpletest' => 'Testing',
        'text' => 'Text',
        'toolbar' => 'Toolbar',
        'tracker' => 'Tracker',
        'trigger' => 'Trigger',
        'update' => 'Update manager',
        'user' => 'User',
        'all_around' => 'All Around Views Style',
        'enhanced_browscap' => 'Enhanced Browscap',
        'gallery_pager' => 'gallery_pager',
        'calendar' => 'Calendar',
        'date' => 'Date',
        'date_all_day' => 'Date All Day',
        'date_api' => 'Date API',
        'date_context' => 'Date Context',
        'date_popup' => 'Date Popup',
        'date_popup_authored' => 'Date Popup Authored',
        'date_repeat' => 'Date Repeat API',
        'date_repeat_field' => 'Date Repeat Field',
        'date_tools' => 'Date Tools',
        'date_views' => 'Date Views',
        'devel' => 'Devel',
        'devel_generate' => 'Devel generate',
        'devel_node_access' => 'Devel node access',
        'hacked' => 'Hacked!',
        'location_generate' => 'Location Generate',
        'menu_import' => 'Menu import',
        'metatag_devel' => 'Metatag: Devel',
        'migrate' => 'Migrate',
        'migrate_example' => 'Migrate Example',
        'migrate_extras' => 'Migrate Extras',
        'migrate_ui' => 'Migrate UI',
        'wordpress_migrate' => 'Migration from WordPress',
        'xhprof' => 'xhprof',
        'xhprof_mongodb' => 'XHProf MongoDB',
        'domain_theme' => 'Domain Theme',
        'event_calendar' => 'Event Calendar',
        'event_calendar_colors' => 'Event Calendar Colors',
        'event_popup' => 'Event Pop-up',
        'variable_example' => 'Variable example',
        'all_clients' => 'All Clients',
        'cosmetic_client' => 'Cosmetic Client',
        'date_migrate_example' => 'Date Migration Example',
        'features' => 'Features',
        'features_page1_workbench' => 'features_page1_workbench',
        'image_styles_presets' => 'image_styles_presets',
        'internal_banner_select' => 'Internal Banner select',
        'legal_client' => 'Legal Client',
        'location_content_type' => 'Location Content Type',
        'ppc_content_type' => 'PPC Content Type',
        'ppc_new_landing_page' => 'PPC New Landing Page',
        'ppc_two_content_type' => 'PPC Two Content Type',
        'feeds' => 'Feeds',
        'feeds_ui' => 'Feeds Admin UI',
        'feeds_import' => 'Feeds Import',
        'feeds_news' => 'Feeds News',
        'bundle_copy' => 'Bundle copy',
        'conditional_fields' => 'Conditional Fields',
        'field_countdown' => 'Countdown Timer Field',
        'email' => 'Email',
        'entityreference' => 'Entity Reference',
        'entityreference_behavior_example' => 'Entity Reference Behavior Example',
        'entityreference_view_widget' => 'Entity Reference View Widget',
        'field_collection' => 'Field collection',
        'field_group' => 'Field Group',
        'field_permissions' => 'Field Permissions',
        'link' => 'Link',
        'location_cck' => 'Location CCK',
        'smart_trim' => 'Smart Trim',
        'youtube' => 'YouTube Field',
        'flag' => 'Flag',
        'flag_actions' => 'Flag actions',
        'flexslider' => 'FlexSlider',
        'flexslider_example' => 'FlexSlider Example',
        'flexslider_fields' => 'FlexSlider Fields',
        'flexslider_views_slideshow' => 'FlexSlider Views Slideshow',
        'flexslider_views' => 'FlexSlider Views Style',
        'image_resize_filter' => 'Image resize filter',
        'jreject' => 'jReject',
        'labjs' => 'LABjs',
        'gmap' => 'GMap',
        'gmap_location' => 'GMap Location',
        'gmap_macro_builder' => 'GMap Macro Builder',
        'gmap_style_bubbles' => 'Gmap Style Bubbles',
        'gmap_taxonomy' => 'GMap Taxonomy Markers',
        'location' => 'Location',
        'location_gmap_find_address' => 'location gmap find address button',
        'location_addanother' => 'Location Add Another',
        'location_email' => 'Location Email',
        'location_entity' => 'Location Entity',
        'location_fax' => 'Location Fax',
        'location_phone' => 'Location Phone',
        'location_search' => 'Location Search',
        'location_taxonomy' => 'Location Taxonomy',
        'location_node' => 'Node Locations',
        'location_user' => 'User Locations',
        'mailsystem' => 'Mail System',
        'mimemail' => 'Mime Mail',
        'mimemail_action' => 'Mime Mail Action',
        'mimemail_compress' => 'Mime Mail CSS Compressor',
        'cs_adaptive_image' => 'Client-side adaptive image',
        'file_entity' => 'File entity',
        'image_effects_text' => 'Image Effects Text',
        'image_effects_text_test' => 'Image Effects Text test',
        'image_styles_admin' => 'Image styles admin',
        'imagecache_actions' => 'Imagecache Actions',
        'imagecache_autorotate' => 'Imagecache Autorotate',
        'imagecache_canvasactions' => 'Imagecache Canvas Actions',
        'imagecache_coloractions' => 'Imagecache Color Actions',
        'imagecache_customactions' => 'Imagecache Custom Actions',
        'imagecache_testsuite' => 'Imagecache_actions Test Suite',
        'imce' => 'IMCE',
        'imce_filefield' => 'IMCE for File Field',
        'video' => 'Video',
        'video_embed_facebook' => 'Video Embed Facebook',
        'video_embed_field' => 'Video Embed Field',
        'video_ui' => 'Video UI',
        'zencoderapi' => 'Zencoder API',
        'messaging_htmlmail' => 'HTML Mail',
        'messaging' => 'Messaging',
        'messaging_template' => 'Messaging template',
        'messaging_mail' => 'Simple Mail',
        'messaging_simple' => 'Web messaging',
        'metatags_quick_extra' => 'Extra functionality',
        'metatags_quick' => 'Meta tags quick',
        'metatags_quick_import' => 'Upgrade from nodewords',
        'get_metatags' => 'Get Meta Tags',
        'sitedir_migrate_blocks' => 'Migrate Blocks',
        'sitedir_migrate_cck_filefield' => 'Migrate File Fields',
        'sitedir_migrate_imagecache' => 'Migrate Imagecache',
        'sitedir_migrate_body' => 'Migrate Node Body',
        'sitedir_migrate_panels' => 'Migrate Panels',
        'sitedir_migrate' => 'Site Directory Migrate',
        'migrate_example_oracle' => 'Migrate example - Oracle',
        'migrate_extras_media' => 'Migrate Extras Media',
        'migrate_extras_pathauto' => 'Migrate Extras Pathauto Example',
        'migrate_extras_profile2' => 'Migrate Extras Profile2 Example',
        'migrate_example_baseball' => 'migrate_example_baseball',
        'i18n_panels' => 'Panels translation',
        'profile2_i18n' => 'Profile2 translation',
        'rules_i18n' => 'Rules translation',
        'notifications_content' => 'Content Notifications',
        'notifications' => 'Notifications',
        'notifications_scheduler' => 'Notifications scheduler',
        'notifications_ui' => 'Notifications UI',
        'notifications_views' => 'Notifications Views',
        'notifications_tags' => 'Taxonomy Notifications',
        'notifications_account' => 'User account tabs',
        'notifications_user' => 'User subscriptions',
        'profile2_og_access' => 'Profile2 group access',
        'adaptive_image' => 'Adaptive Image',
        'add_js' => 'Add JS',
        'autoassignrole' => 'Auto Assign Role',
        'better_formats' => 'Better Formats',
        'block_titlelink' => 'Block Title Link',
        'blog_category_fix' => 'Blog Category fix',
        'browscap' => 'Browscap',
        'browscap_block' => 'Browscap Block',
        'browserclass' => 'Browser class',
        'colorbox' => 'Colorbox',
        'diff' => 'Diff',
        'easy_social' => 'Easy Social',
        'entity' => 'Entity API',
        'entity_token' => 'Entity tokens',
        'exclude_node_title' => 'Exclude node title',
        'gallery_alias' => 'gallery_alias',
        'html_title' => 'HTML title',
        'image_crop_fix' => 'image crop fix',
        'image_field_caption' => 'Image Field Caption',
        'image_url_formatter' => 'Image URL Formatter',
        'imagemagick' => 'ImageMagick',
        'imagemagick_advanced' => 'ImageMagick Advanced',
        'job_scheduler' => 'Job Scheduler',
        'job_scheduler_trigger' => 'Job Scheduler Trigger',
        'jquery_colorpicker' => 'Jquery Colorpicker',
        'libraries' => 'Libraries',
        'login_destination' => 'Login Destination',
        'logintoboggan' => 'LoginToboggan',
        'logintoboggan_content_access_integration' => 'LoginToboggan Content Access Integration',
        'logintoboggan_rules' => 'LoginToboggan Rules Integration',
        'logintoboggan_variable' => 'LoginToboggan Variable Integration',
        'menu_attributes' => 'Menu attributes',
        'menu_block' => 'Menu Block',
        'menu_block_export' => 'Menu Block Export',
        'menu_html' => 'Menu HTML',
        'metatag_import_export_csv' => 'Metatag Import Export CSV',
        'metatag_replace' => 'Metatag Replace',
        'modules_weight' => 'Modules Weight',
        'multiblock' => 'MultiBlock',
        'nice_menus' => 'Nice Menus',
        'clone' => 'Node clone',
        'node_convert' => 'Node Convert',
        'node_generator' => 'Node Generator',
        'pg1help' => 'Page 1 Solutions',
        'pathauto' => 'Pathauto',
        'profile2' => 'Profile2',
        'profile2_page' => 'Profile2 pages',
        'quicktabs' => 'Quicktabs',
        'quicktabs_tabstyles' => 'Quicktabs Styles',
        'redirect' => 'Redirect',
        'r4032login' => 'Redirect 403 to User Login',
        'path_redirect_import' => 'Redirect Import',
        'remove_inline_attribute' => 'Remove inline attribute image',
        'resp_img' => 'Responsive images and styles',
        'revision_all' => 'Revision All',
        'revisioning' => 'Revisioning',
        'revisioning_scheduler' => 'Revisioning Scheduler',
        'revisioning_ux' => 'Revisioning UX',
        'robotstxt' => 'robots.txt',
        'scanner' => 'Scanner',
        'scheduler' => 'Scheduler',
        'search_replace_blocks_menus' => 'Search and Replace Blocks Menus',
        'securesite' => 'Secure Site',
        'simple_pass_reset' => 'Simple Password Reset',
        'site_map' => 'Site map',
        'site_verify' => 'Site Verification',
        'special_menu_items' => 'Special menu items',
        'stage_file_proxy' => 'Stage File Proxy',
        'stringoverrides' => 'String Overrides',
        'stringoverrides_migrate' => 'String Overrides Migrate',
        'strongarm' => 'Strongarm',
        'text_resize' => 'Text Resize',
        'token' => 'Token',
        'tvi' => 'TVI: Taxonomy View Integrator',
        'update_external_links' => 'Update External Link',
        'views_block_area' => 'Views block area',
        'owlcarousel' => 'Owl Carousel',
        'owlcarousel_fields' => 'Owl Carousel Fields',
        'owlcarousel_ui' => 'Owl Carousel UI',
        'owlcarousel_views' => 'Owl Carousel Views',
        'alias_checker' => 'Alias Checker',
        'before_after_importer' => 'Before After Custom Importer',
        'page1solution_gallery' => 'Before After Gallery',
        'panels_mini' => 'Mini panels',
        'panels_node' => 'Panel nodes',
        'panels' => 'Panels',
        'panels_ipe' => 'Panels In-Place Editor',
        'globalredirect' => 'Global Redirect',
        'expire' => 'Cache Expiration',
        'httprl' => 'HTTP Parallel Request Library',
        'memcache' => 'Memcache',
        'memcache_admin' => 'Memcache Admin',
        'print_pdf' => 'PDF version',
        'print' => 'Printer-friendly pages',
        'print_mail' => 'Send by email',
        'qpcache' => 'QPCache',
        'querypath' => 'QueryPath',
        'querypath_examples' => 'QueryPath Examples',
        'qpa' => 'QueryPath for Arrays',
        'quickbar' => 'Quickbar',
        'quickbar_extras' => 'Quickbar: Extras',
        'quickbar_help' => 'Quickbar: Help',
        'rules' => 'Rules',
        'rules_scheduler' => 'Rules Scheduler',
        'rules_admin' => 'Rules UI',
        'schemaorg' => 'Schema.org',
        'schemaorg_event' => 'Schema.org example: Event',
        'schemaorg_person' => 'Schema.org example: Person',
        'schemaorg_recipe' => 'Schema.org example: Recipe',
        'schemaorg_contrib' => 'Schema.org support for contributed modules',
        'schemaorg_ui' => 'Schema.org UI',
        'custom_search' => 'Custom Search',
        'custom_search_blocks' => 'Custom Search Blocks',
        'custom_search_i18n' => 'Custom Search Internationalization',
        'custom_search_taxonomy' => 'Custom Search Taxonomy',
        'google_authorship' => 'Google Authorship',
        'h2' => 'h2',
        'logo_alttext' => 'logo alt text',
        'metatag' => 'Metatag',
        'metatag_importer' => 'Metatag Importer',
        'metatag_app_links' => 'Metatag: App Links',
        'metatag_context' => 'Metatag: Context',
        'metatag_dc' => 'Metatag: Dublin Core',
        'metatag_dc_advanced' => 'Metatag: Dublin Core Advanced',
        'metatag_facebook' => 'Metatag: Facebook',
        'metatag_favicons' => 'Metatag: favicons',
        'metatag_google_plus' => 'Metatag: Google+',
        'metatag_hreflang' => 'Metatag: hreflang',
        'metatag_mobile' => 'Metatag: Mobile & UI Adjustments',
        'metatag_opengraph' => 'Metatag: OpenGraph',
        'metatag_panels' => 'Metatag: Panels',
        'metatag_twitter_cards' => 'Metatag: Twitter Cards',
        'metatag_verification' => 'Metatag: Verification',
        'metatag_views' => 'Metatag: Views',
        'metatag_opengraph_products' => 'Metatag:OpenGraph Products',
        'page_title' => 'Page Title',
        'redirect_update' => 'Redirect Update',
        'simple_page_title' => 'Simple Page Title',
        'sitemap_priority_changer' => 'Sitemap Priority Changer',
        'shortcode' => 'Shortcode',
        'shortcode_basic_tags' => 'Shortcode Basic Tags',
        'shortcode_embed_content' => 'Shortcode Embed Content Tag',
        'embed_view_shortcodes' => 'Shortcode to Display View and Block Data',
        'slick' => 'Slick',
        'slick_devel' => 'Slick development',
        'slick_example' => 'Slick example',
        'slick_fields' => 'Slick fields',
        'slick_views' => 'Slick views',
        'slick_slideshow' => 'Slick Responsive Slideshow',
        'captcha' => 'CAPTCHA',
        'honeypot' => 'Honeypot',
        'image_captcha' => 'Image CAPTCHA',
        'recaptcha' => 'reCAPTCHA',
        'spamicide' => 'Spamicide',
        'googleanalytics' => 'Google Analytics',
        'google_tag' => 'Google Tag Manager',
        'subscriptions_blog_ui' => 'Blog Subscriptions UI',
        'subscriptions_content' => 'Content Subscriptions',
        'subscriptions' => 'Subscriptions',
        'subscriptions_mail' => 'Subscriptions Mail',
        'subscriptions_ui' => 'Subscriptions UI',
        'subscriptions_taxonomy' => 'Taxonomy Subscriptions',
        'taxonomy_access_fix' => 'Taxonomy access fix',
        'taxonomy_manager' => 'Taxonomy Manager',
        'taxonomy_menu' => 'Taxonomy menu',
        'tb_megamenu' => 'TB Mega Menu',
        'role_theme_switcher' => 'Role Theme Switcher',
        'ckeditor' => 'CKEditor',
        'ckeditor_image' => 'CKEditor Image',
        'ckeditor_link' => 'CKEditor Link',
        'ckeditor_link_file' => 'CKEditor�Link for Files',
        'imce_wysiwyg' => 'IMCE Wysiwyg API bridge',
        'jcarousel' => 'jCarousel',
        'jquery_update' => 'jQuery Update',
        'lightbox2' => 'Lightbox2',
        'superfish' => 'Superfish',
        'tinynav' => 'Tiny Nav js',
        'wysiwyg' => 'Wysiwyg',
        'variable' => 'Variable',
        'variable_admin' => 'Variable admin',
        'variable_realm' => 'Variable realm',
        'variable_store' => 'Variable store',
        'variable_views' => 'Variable views',
        'draggableviews' => 'Draggableviews',
        'menu_views' => 'Menu Views',
        'sgrid' => 'Sortable Grid',
        'views' => 'Views',
        'views_accordion' => 'Views Accordion',
        'views_bulk_operations' => 'Views Bulk Operations',
        'views_conditional' => 'Views Conditional',
        'views_ical' => 'Views iCal',
        'views_nested_accordion' => 'Views Nested Accordion',
        'views_php' => 'Views PHP',
        'entityreference_filter' => 'Views Reference Filter',
        'views_responsive_grid' => 'Views Responsive Grid',
        'views_slideshow' => 'Views Slideshow',
        'views_slideshow_cycle' => 'Views Slideshow: Cycle',
        'views_slideshow_j360' => 'Views Slideshow: j360',
        'views_tree' => 'Views Tree',
        'views_ui' => 'Views UI',
        'webform' => 'Webform',
        'workbench' => 'Workbench',
        'workbench_email' => 'Workbench Email',
        'workbench_moderation' => 'Workbench Moderation',
        'workbench_scheduler' => 'Workbench Scheduler',
        'workbench_custom' => 'Workbench_custom',
        'xmlsitemap' => 'XML sitemap',
        'xmlsitemap_custom' => 'XML sitemap custom',
        'xmlsitemap_engines' => 'XML sitemap engines',
        'xmlsitemap_i18n' => 'XML sitemap internationalization',
        'xmlsitemap_menu' => 'XML sitemap menu',
        'xmlsitemap_node' => 'XML sitemap node',
        'xmlsitemap_taxonomy' => 'XML sitemap taxonomy',
        'xmlsitemap_user' => 'XML sitemap user',
    );

    $fp = fopen($file_url, 'a+');

    if (!$fp) {
        drupal_set_message(t('Unable open file for writing. Check permissions and try again.'), 'error');
        return;
    }
    $delimeter = ',';
//fputcsv($fp, $module_list, $delimeter);
    foreach ($module_list as $keys => $values) {
        if (module_exists($keys)) {
            $status[] = "YES";
        } else {
            if($keys == 'site_name')
            {
            $status[] = $module_list['site_name'];
            }
            else
            $status[] = "NO";
            
        }
    }
   // file_put_contents($file_url, $status, FILE_APPEND);
    fputcsv($fp, $status, $delimeter);

 
    fclose($fp);
//    $file->filesize = filesize($file->uri);
//    file_save($file);
//    if (drupal_is_cli()) {
//        drupal_set_message(dt("A File is created at  %file_url ", array('%file_url' => $file_url)));
//        return ($file);
//    }
}