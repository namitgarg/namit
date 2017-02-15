<?php

/**
 * Alter list of fields that are added to the csv for every entity.
 */
function hook_metatag_import_export_csv_additional_fields_alter(&$fields) {
  $fields[] = '_created';
}

/**
 * Alter values of additional fields added to each row of the csv.
 */
function hook_metatag_import_export_csv_additional_values_alter(&$values, $node) {
  $values['_created'] = date('y-m-d', $node->created);
}
