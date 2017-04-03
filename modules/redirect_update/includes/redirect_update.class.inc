<?php


/**
 * @file
 * Class file for href attribute replacement.
 */

class RedirectUpdate {
    private $type;
    private $id;
    private $context;
    private $source;
    private $redirect;
    
    /**
     * Constructor to initialised the properties.
     * @param string $type
     *   Set whether block or node.
     * @param int $id  Id of Block / Node.
     * @param string $source  Source url that need to be replaced.
     * @param string $redirect  Redirect url from which source url updated.
     * @param array $context Contains memory reference to be used for status message.
     */
    function __construct($type, $id, $source, $redirect, &$context) {
        $this->type = $type;
        $this->id = $id;
        $this->context = $context;
        $this->source = $source;
        $this->redirect = $redirect;
    }
    
    /**
     * Method to set the id ( node id / block id ).
     * @param int $id
     *   Sets the id for Block / Node.
     */
    function _set_id($id) {
      $this->id = $id;
    }
    
    /**
     * Method to set the finished message for the batch processing for each replace/update.
     * @param bool $src
     *   True if source url is absolute else false.
     * @param bool $red
     *   True if redirection url is absolute else false.
     */
    function _set_finished_message($src, $red) {
      global $base_url;
      $source = $src ? $base_url . '/' . $this->source : $this->source;
      $redirect = $red ? $this->redirect : url($this->redirect);
      if ($this->type == 'body') {
        $this->context['results']['body'][] = t('Updated the redirect from \'@source\' to \'@redirect\' in node @id', array('@source' => $source, '@redirect' => $redirect, '@id' => $this->id));
        $this->_set_total_update_count($this->type);
      }
      elseif ($this->type == 'block') {
        $this->context['results']['block'][] = t('Updated the redirect from \'@source\' to \'@redirect\' in block id @id', array('@source' => $source, '@redirect' => $redirect, '@id' => $this->id));
        $this->_set_total_update_count($this->type);
      }
    }
    
    /**
     * Method to set the total number of changes/updations in nodes and blocks. 
     * @param string $type
     *   Update the count of number of anchors (url) updated in node / block.
     */
    function _set_total_update_count($type) {
      if (isset($this->context['results']['total'][$type])) {
          $this->context['results']['total'][$type] ++; 
      }
      else {
          $this->context['results']['total'][$type] = 1;
      }
    }
    
    /**
     * Method to check whether the url is alias of given url or not.
     * If alias then return the actual url else return empty string.
     * @param String $url Url that need to be checked.
     * @return String Returns the actual url of alias if exists else empty string.
     */
    function _get_actual_url($url) {
      $actual_path = '';
      $isAlias = drupal_lookup_path('source', $url);
      if ($isAlias) {
        return $isAlias;
      }
      return $actual_path;
    }

    /**
     * Method to check and update redirect anchors.
     * @param array $match
     *   Array contains the full anchor tag and href part of anchor tag.
     * @return String Returns the updated / Modified anchor tag.
     */
    public function _callback_replace($match) {
     global $base_url;
     $anchor = $match[0]; //Full anchor tag.
     $href = $match[1];  //Href of anchor.
     $output = $anchor;
     $absolute_source = valid_url(trim($href), TRUE); //Whether the replaced anchor url is relative or absolute
     $absolute_redirection = valid_url(trim($this->redirect), TRUE); //Whether the redirected anchor url is relative or absolute
     $alias_check = $this->_get_actual_url($this->source);
     if (trim($href) == trim($this->source) || trim($href) == ($base_url . '/' . $this->source) || trim($href) == trim($alias_check) || trim($href) == trim('/' . $this->source)) { //If match found
       if (!$absolute_redirection) { //If our resulted url (url to which redirection is made) is not absolute url.
         $output = preg_replace('!href=[\'"]([^\'"]+)[\'"]!', 'href="' . url($this->redirect) . '"', $anchor);  //Update href with adding base_url.
       }
       else {
         $output = preg_replace('!href=[\'"]([^\'"]+)[\'"]!', 'href="' . $this->redirect . '"', $anchor);  //Update href without adding base url (as this can be external url).
       }
       $this->_set_finished_message($absolute_source, $absolute_redirection); //Set the finished message.
     }
     return $output;
   }
}
