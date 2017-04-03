<?php

/* 
Blog Category fix This will insert enteries into taxanomy_index table so that they can be viewd on Category listing page
 */

function taxonomy_fix()
{
      $query = db_select('field_data_field_category', 'gd')
      ->fields('gd', array('entity_id','field_category_tid'))
      ->condition('bundle', 'blog');
  $results = $query->execute()->fetchAll();
      
  foreach ($results as $values)
  {
      
      $nnid=$values->entity_id;
      $node1=node_load($nnid);
      taxonomy_build_node_index($node1);
drupal_set_message($nnid);

  }
  return("Blog category are fixed Just create a test Blog and assign to each category to rebuild Menu Block");
}