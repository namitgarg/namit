<?php

/**
 * @file
 * This file is used to create CSV file with all meta details.
 */

/**
 * Creating Csv file from database using fileid.
 */
function get_metatags_generate_metatags_csv($file_id) {
  $sql = db_select('get_metatags', 'gm');
  $sql->fields('gm');
  $sql->condition('gm.fid', $file_id);
  $sql->execute();
  $download_csv = $sql->execute();
  $filename = db_select('file_managed', 'fm');
  $filename->fields('fm', array('filename'));
  $filename->condition('fm.fid', $file_id);
  $fname = $filename->execute()->fetchField();
  $file_name = basename($fname, ".csv");
  $metatag_name  = "metatags";
  $file_result = $file_name . "_" . $metatag_name;
  drupal_add_http_header('Content-Type', 'text/csv; utf-8');
  drupal_add_http_header('Content-Disposition', "attachment; filename =$file_result.csv", TRUE);
  drupal_add_http_header('Cache-Control', 'max-age=300; must-revalidate');
  $fh = fopen('php://output', 'w');
  fputcsv($fh, array('Site url', 'H1', 'Page Title', 'Description', 'keywords'));
  foreach ($download_csv as $metacsv) {
    fputcsv($fh, array($metacsv->site_url,
                   $metacsv->h1,
                   $metacsv->page_title,
                   $metacsv->description,
                   $metacsv->keywords));
  }fclose($fh);
  db_delete('get_metatags')->condition('fid', $file_id)->execute();

  exit;
}

$file_id = $_REQUEST['fid'];
get_metatags_generate_metatags_csv($file_id);
