<?php

/**
 * @file
 * Contains the feeds atom RDF parser class.
 */


/**
 * Parses Atom RDF feeds.
 */
class FeedsAtomRDFParser extends FeedsParser {

  /**
   * Implementation of FeedsParser::parse().
   */
  public function parse(FeedsSource $source, FeedsFetcherResult $fetcher_result) {

    require_once DRUPAL_ROOT . '/' . drupal_get_path('module', 'feeds_atom') . '/libraries/atomrdf_parser.inc';
    $result = new FeedsParserResult;
    $raw = atomrdf_parser_parse($fetcher_result->getRaw());

    // @todo, probably a better way to do this transfer from array to object.
    $attributes = array(
      'items',
      'description',
      'link',
      'title',
    );

    foreach ($attributes as $attribute) {
      if (!empty($raw[$attribute])) {
        $result->{$attribute} = $raw[$attribute];
      }
    }

    return $result;
  }

  /**
   * Return mapping sources.
   *
   * At a future point, we could expose data type information here,
   * storage systems like Data module could use this information to store
   * parsed data automatically in fields with a correct field type.
   */
  public function getMappingSources() {

    $return =  array(
      'title' => array(
        'name' => t('Title'),
        'description' => t('Title of the feed item.'),
      ),
      'description' => array(
        'name' => t('Description'),
        'description' => t('Description of the feed item.'),
      ),
      'author_name' => array(
        'name' => t('Author name'),
        'description' => t('Name of the feed item\'s author.'),
      ),
      'author_email' => array(
        'name' => t('Author email'),
        'description' => t('Email of the feed item\'s author.'),
      ),
      'author_uri' => array(
        'name' => t('Author url'),
        'description' => t('Url of the feed item\'s author.'),
      ),
      'timestamp' => array(
        'name' => t('Published date'),
        'description' => t('Published date as UNIX time GMT of the feed item.'),
      ),
      'url' => array(
        'name' => t('Item URL (link)'),
        'description' => t('URL of the feed item.'),
      ),
      'guid' => array(
        'name' => t('Item GUID'),
        'description' => t('Global Unique Identifier of the feed item.'),
      ),
      'tags' => array(
        'name' => t('Categories'),
        'description' => t('An array of categories that have been assigned to the feed item.'),
      ),
      'status' => array(
        'name' => t('Published'),
        'description' => t('A 1 or 0 for the published status.'),
      ),
    );

    $fields = field_info_fields();
    foreach($fields as $field_name => $field_info) {
      $return[$field_name] = array(
        'name' => $field_name,
        'description' => t('This parser will check the incoming data for raw representations of fields currently on this site. You do not have to set these mappings as they will apply automatically to corresponding fields.'),
      );
    }

    return $return;
  }

  public function getSourceElement(FeedsSource $source, FeedsParserResult $result, $element_key) {

    $item = $result->currentItem();
    if (!empty($item['rdf'][$element_key])) {
      return $item['rdf'][$element_key];
    } else {
      return parent::getSourceElement($source, $result, $element_key);
    }
  }
}
