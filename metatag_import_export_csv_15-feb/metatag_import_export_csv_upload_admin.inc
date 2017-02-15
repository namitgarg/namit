<?php

/**
 * @file
 * Stores the code for import Process.
 */
define("BLANK", "_blank");

/**
 * Checks CSV for Html and Php.
 */
function metatag_import_export_csv_xss_check($row_data) {
    $flag = TRUE;
    foreach ($row_data as $values) {
        $checked_value = strip_tags($values);
        if ($checked_value != $values) {
            $flag = FALSE;
        }
    }
    return $flag;
}

/**
 * Form for Import operation.
 */
function metatag_import_export_csv_upload_form($form, &$form_state) {
    metatag_import_export_csv_getpath();
    $form['upload_file'] = array(
        '#type' => 'managed_file',
        '#title' => t('Upload File'),
        '#required' => TRUE,
        '#description' => t('Allowed Extensions: csv'),
        '#upload_location' => 'public://metatag_import_export_csv/',
        '#upload_validators' => array(
            'file_validate_extensions' => array('csv'),
            'file_validate_size' => array(1 * 1024 * 1024),
        ),
    );
    $form['delimiter'] = array(
        '#type' => 'textfield',
        '#title' => t('Delimiter'),
        '#description' => t('Enter The delimiter Used for the importation of the CSV'),
        '#default_value' => ',',
        '#maxlength' => 2,
    );
    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t("Import"),
        '#submit' => array('metatag_import_export_csv_upload_submit'),
    );
    return $form;
}

/**
 * Submit Handler for Import Operation.
 */
function metatag_import_export_csv_upload_submit($form, &$form_state) {
    $file = file_load($form_state['values']['upload_file']);
    $file->status = 0;
    file_save($file);
    $fileurl = file_create_url($file->uri);
    $delimeter = $form_state['values']['delimiter'];
    metatag_import_export_csv_read_file($fileurl, $delimeter);
}

/**
 * Reads the CSV file and passes the data to batch operation.
 */
function metatag_import_export_csv_read_file($fileurl, $delimeter) {

    $count = 0;
    $handle = fopen($fileurl, "r");
    $heading_fields = fgetcsv($handle, $length = "", $delimeter);
    $batch = array(
        'operations' => array(),
        'finished' => 'metatag_import_export_csv_finish_batch_upload',
        'title' => t("Processing Nodes for importing Metatags"),
        'init_message' => t("Starting Metatag Import Process"),
        'progress_message' => t("Processed @current out of @total Nodes"),
        'file' => drupal_get_path('module', 'metatag_import_export_csv') . '/metatag_import_export_csv_upload_admin.inc',
        'error_message' => t("Metatag import process has encountered an error."),
    );
    while (!feof($handle)) {
        $count++;
        $data = fgetcsv($handle, $length = "", $delimeter);
        $batch['operations'][] = array('metatag_import_export_csv_start_batch_upload', array(
                $data,
                $heading_fields,
                $count,
            ),
        );
    }
    batch_set($batch);
    if (drupal_is_cli()) {
        $batch = & batch_get();
        $batch['progressive'] = FALSE;
        drush_backend_batch_process();
    } else {
        batch_process('admin/config/search/metatags/import');
    }
}

/**
 * Gets nid of all nodes.
 */
function metatag_import_export_csv_getnid() {
    $query = db_select('node', 'n')
            ->fields('n', array('nid'));
    $results = $query->execute()->fetchAll();
    foreach ($results as $values) {
        $nid_list[] = "node/" . $values->nid;
    }
    return ($nid_list);
}

/**
 * Get URl Alias from database.
 */
function metatag_import_export_csv_getpath() {
    $query2 = db_select('url_alias', 'ua')
            ->fields('ua', array('source', 'alias'));
    $results2 = $query2->execute()->fetchAll();
    foreach ($results2 as $values) {
        $path['source'][] = explode("/", $values->source)[1];
        $path['alias_path'][] = $values->alias;
    }
    return ($path);
}

/**
 * Batch Operation Callback.
 */
function metatag_import_export_csv_start_batch_upload($data, $heading_fields, $keys, &$context) {
    $row_num = $keys + 1;
    $xsscheck = metatag_import_export_csv_xss_check($data);
    if (empty($xsscheck)) {
        drupal_set_message(t("Row %row_num was skipped as it contains PHP or HTML tags", array('%row_num' => $row_num)), 'error');
    } 
    else {
        $nid_db = metatag_import_export_csv_getnid();
        $path_index = array_search('path', $heading_fields);
        preg_match("/node/", $data[$path_index], $path_match);
        $cur_nid = explode("/", $data[$path_index])[1];

        if (!empty($path_match)) {
            if (in_array($data[$path_index], $nid_db)) {
                metatag_import_export_csv_node_processing($cur_nid, $data, $heading_fields, $keys);
                $context['results']['test'][] = $test_data;
                drupal_set_message(t("%path  Metatag on row %row_num updated Successfully", array('%path ' => $path, '%row_num' => $row_num)));
            } else {
                drupal_set_message(t("%path  Metatag on row %row_num does not exists", array('%path' => $path, '%row_num' => $row_num)), 'error');
            }
        } else {
            $pathdb = metatag_import_export_csv_getpath();
            foreach ($pathdb['alias_path'] as $keys => $values) {
                $path_url[] = $values;
                $path_nid[] = $pathdb['source'][$keys];
            }
            $path_search = array_keys($path_url, $path)[0];
            if (!empty($path_nid[$path_search])) {
                metatag_import_export_csv_node_processing($path_nid[$path_search], $meta_title, $meta_description, $meta_abstract, $meta_keywords, $keys);
                drupal_set_message(t("%path  Metatag on row %row_num updated Successfully", array('%path ' => $path, '%row_num' => $row_num)));
            } else {
                drupal_set_message(t("%path  Metatag on row %row_num does not exists", array('%path' => $path, '%row_num' => $row_num)), 'error');
            }
        }
    }
}

/**
 * Batch 'finished' callback for Import Operation.
 */
function metatag_import_export_csv_finish_batch_upload($success, $results, $operations) {
    if ($success) {
        drupal_set_message(t("Finished Importing Metatags"));
    } else {
        $error_operation = reset($operations);
        drupal_set_message(t("An error occurred while processing @operation with arguments : @args", array(
            '@operation' => $error_operation[0],
            '@args' => print_r($error_operation[0], TRUE),
        )));
    }
}

/**
 * Changes the Metatag for the Nodes.
 */
function metatag_import_export_csv_node_processing($cur_nid, $data, $heading_fields, $keys) {
    $node = node_load($cur_nid);
    foreach ($heading_fields as $keys => $values) {
        if (!empty($data[$keys])) {
            if ($data[$keys] == BLANK) {
                $node->metatags[$node->language][$values]['value'] = "";
            } else {
                $node->metatags[$node->language][$values]['value'] = $data[$keys];
            }
        }
    }

    $node->revision = 1;
    $node->log = "Modified by Metatag Import Export Module.";
    node_save($node);
}
