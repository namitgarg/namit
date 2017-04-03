<?php

/**
 * @file
 * Contains the feeds atom RDF processor class.
 */

/**
 * Creates nodes from feed items.
 */
class FeedsAtomRDFProcessor extends FeedsNodeProcessor {

  /**
   * Process the result of the parsing stage.
   *
   * @param FeedsSource $source
   *   Source information about this import.
   * @param FeedsParserResult $parser_result
   *   The result of the parsing stage.
   */
  public function process(FeedsSource $source, FeedsParserResult $parser_result) {
    $state = $source->state(FEEDS_PROCESS);

    while ($item = $parser_result->shiftItem()) {
      if (!($entity_id = $this->existingEntityId($source, $parser_result)) ||
           ($this->config['update_existing'] != FEEDS_SKIP_EXISTING)) {

        // Only proceed if item has actually changed.
        $hash = $this->hash($item);

        if (!empty($entity_id) && $hash == $this->getHash($entity_id)) {
          continue;
        }

        try {
          // Assemble node, map item to it, save.
          if (empty($entity_id)) {
            $entity = $this->newEntity($source);
            $this->newItemInfo($entity, $source->feed_nid, $hash);
          }
          else {
            $entity = $this->entityLoad($source, $entity_id);
            // The feeds_item table is always updated with the info for the most recently processed entity.
            // The only carryover is the entity_id.
            $this->newItemInfo($entity, $source->feed_nid, $hash);
            $entity->feeds_item->entity_id = $entity_id;
          }
          if (!empty($item['deleted'])) {
            $this->entityDeleteMultiple(array($entity_id));
            $state->deleted++;
          } else {
          $this->map($source, $parser_result, $entity);

          // Set this boolean so that validate and save operations know this is
          // coming from Feeds Atom. This property is also declared in
          // feeds_atom_entity_property_info_alter() making the property available to Rules.
          $entity->feeds_atom_import = 1;

          $this->entityValidate($entity);

          // Allow modules to alter the entity before saving.
          module_invoke_all('feeds_presave', $source, $entity);
          if (module_exists('rules')) {
            rules_invoke_event('feeds_import_'. $source->importer()->id, $entity);
          }

          $this->entitySave($entity);

          // Track progress.
          if (empty($entity_id)) {
            $state->created++;
          }
          else {
            $state->updated++;
          }
          }
        }
        catch (Exception $e) {
          $state->failed++;
          drupal_set_message($e->getMessage(), 'warning');
          $message = $e->getMessage();
          $message .= '<h3>Original item</h3>';
          $message .= '<pre>' . var_export($item, TRUE) . '</pre>';
          $message .= '<h3>Entity</h3>';
          $message .= '<pre>' . var_export($entity, TRUE) . '</pre>';
          $source->log('import', $message, array(), WATCHDOG_ERROR);
        }
      }
    }

    // Set messages if we're done.
    if ($source->progressImporting() != FEEDS_BATCH_COMPLETE) {
      return;
    }
    $info = $this->entityInfo();
    $tokens = array(
      '@entity' => strtolower($info['label']),
      '@entities' => strtolower($info['label plural']),
    );
    $messages = array();
    if ($state->deleted) {
      $messages[] = array(
       'message' => format_plural(
          $state->deleted,
          'Deleted @number @entity.',
          'Deleted @number @entities.',
          array('@number' => $state->deleted) + $tokens
        ),
      );
    }
    if ($state->created) {
      $messages[] = array(
       'message' => format_plural(
          $state->created,
          'Created @number @entity.',
          'Created @number @entities.',
          array('@number' => $state->created) + $tokens
        ),
      );
    }
    if ($state->updated) {
      $messages[] = array(
       'message' => format_plural(
          $state->updated,
          'Updated @number @entity.',
          'Updated @number @entities.',
          array('@number' => $state->updated) + $tokens
        ),
      );
    }
    if ($state->failed) {
      $messages[] = array(
       'message' => format_plural(
          $state->failed,
          'Failed importing @number @entity.',
          'Failed importing @number @entities.',
          array('@number' => $state->failed) + $tokens
        ),
        'level' => WATCHDOG_ERROR,
      );
    }
    if (empty($messages)) {
      $messages[] = array(
        'message' => t('There are no new @entities.', array('@entities' => strtolower($info['label plural']))),
      );
    }
    foreach ($messages as $message) {
      drupal_set_message($message['message']);
      $source->log('import', $message['message'], array(), isset($message['level']) ? $message['level'] : WATCHDOG_INFO);
    }
  }

  /**
   * Override parent::map() to load all available add-on mappers.
   *
   * We also add a $source parameter that contains the FeedsSource object that
   * controls this feed.
   */
  protected function map(FeedsSource $source, FeedsParserResult $result, $target_item = NULL) {

    $fields = field_info_fields();
    foreach($fields as $field_name => $field_info) {
      // @todo Should check to make sure that no existing mappings are overridden.
      $this->config['mappings'][] = array(
        'source' => $field_name,
         'target' => '__' . $field_name,
         'unique' => 0,
      );
    }

    $target_item = parent::map($source, $result, $target_item);

    // Create a context variable for drupal_alter to use.
    // Use $context instead of passing directly because drupal_alter has a
    // limit on parameters and these should not be altered.
    $context = array(
      'result' => $result,
      'source' => $source,
      'processor' => $this,
    );

    // Allow other modules to add additional mapping.
    drupal_alter('feeds_atom_rdf_map', $target_item, $context);
    return $target_item;
  }

  /**
   * Override setTargetElement to operate on a target item that is a node.
   */
  public function setTargetElement(FeedsSource $source, $target_node, $target_element, $value) {

    if (strpos($target_element, '__') === 0) {
      $field_name = substr($target_element, 2);
      // Allow other modules to change the value of the imported item.
      // Invokes hook_feeds_atom_set_target_element_value_alter().
      // If there is a need to pass target_node or source, they should be passed in the same variable
      // Since drupal_alter() has a limit on parameters.
      drupal_alter('feeds_atom_set_target_element_value', $value, $field_name);
      $target_node->{$field_name} = $value;
    } else {
      parent::setTargetElement($source, $target_node, $target_element, $value);
    }
  }

}

/**
 * Specialized version of FeedsEnclosure to ensure uniqueness when saving.
 *
 * @todo, This class was necessary in D6 however in D7 it seems that saveTo() might
 * not be called.
 *
 */
class FeedsEnclosureUnique extends FeedsEnclosure {

  /**
   * Saves the file represented by this enclosure to disk.
   *
   * If the file already exists, based on its sha1() hash, then we will simply
   * reuse the existing file rather than saving a new one.
   *
   * @param $target_dir
   *   The directory to which to save the file.  Note that if the file has already
   *   been imported it is possible that it will not be in the requested directory,
   *   in which case this method returns the existing file info in its existing
   *   location.
   * @return
   *   The file info array as defined by filefield of the file that we just saved,
   *   or of the pre-existing file that should be used instead.
   */
  public function saveTo($target_dir) {
    $new_file_hash = sha1_file($this->file);

    $fid = db_query("SELECT fid FROM {feeds_atom_file_import} WHERE sha1 = :sha1", array(':sha1' => $new_file_hash))->fetchField();
    if ($fid) {
      // Pull the info for the existing file and return that. We won't save
      // the new file at all.
      $info = field_file_load($fid);

      return $info;
    }
    else {
      // Save the new file, and record its hash for later matching.
      $info = field_file_save_file($this->file, array(), $target_dir);
      // @todo Please review the conversion of this statement to the D7 database API syntax.
      /* db_query("INSERT INTO {feeds_atom_file_import} (fid, sha1) VALUES (%d, '%s')", $info['fid'], $new_file_hash) */
      $id = db_insert('feeds_atom_file_import')
  ->fields(array(
        'fid' => $info['fid'],
        'sha1' => $new_file_hash,
      ))
  ->execute();

      return $info;
    }
  }
}

