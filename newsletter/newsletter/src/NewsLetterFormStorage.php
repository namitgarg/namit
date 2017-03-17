<?php

namespace Drupal\subscribe_newsletter;

Class NewsLetterFormStorage {

	/**
	 * Save the Values into DB
	 */
	public static function insert($entry){
		$return_value = NULL;
		try {
			$return_value = db_insert('newsletter_data')
			->fields($entry)
			->execute();
		}
		catch (\Exception $e){
			$msg = $e->getMessage();
			if(strpos($msg, 'Duplicate entry') !== true){
				drupal_set_message(t('Your email is already registered with us.'));
			} else {
			    drupal_set_message(t('Newsletter subscription failed due to %message', array(
			    	'%message' => $e->getMessage(),			
				)
				), 'error');
			}
		}
		return $return_value;
	}
	
}