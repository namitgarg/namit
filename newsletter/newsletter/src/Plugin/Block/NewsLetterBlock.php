<?php
/**
 * Custom Newsletter Form Block
 *
 */
namespace Drupal\subscribe_newsletter\Plugin\Block;

use Drupal\Core\Block\BlockBase;
use Drupal\Core\Block\BlockPluginInterface;


/**
 * Provides a 'NewsLetter' Block
 *
 * @Block(
 *   id = "newsletterblock",
 *   admin_label = @Translation("Newsletter Block"),
 * )
 */

class NewsLetterBlock extends BlockBase{
	/**
    * {@inheritdoc}
    */
	
	public function build(){
		$form = \Drupal::formBuilder()->getForm('Drupal\subscribe_newsletter\Form\NewsLetterForm');
		return $form;
	}

}