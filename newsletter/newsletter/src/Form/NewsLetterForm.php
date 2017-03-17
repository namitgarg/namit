<?php

/**
 * @file
 * Contains \Drupal\newsletter\Form\NewsLetterForm.
 */
 
namespace Drupal\subscribe_newsletter\Form;

use Drupal\Core\Form\FormBase;
use Drupal\Core\Form\FormStateInterface;
use Drupal\subscribe_newsletter\NewsLetterFormStorage;
use Drupal\Component\Utility\SafeMarkup;
use Drupal\Core\Mail\MailManagerInterface;
use Symfony\Component\DependencyInjection\ContainerInterface;
use Drupal\Core\Language\LanguageManagerInterface;

/**
 * Implements Newsletter Form
 */

Class NewsLetterForm extends FormBase {
	
	/**
	 * {@inheritdoc}
	 */
	public function getFormId(){
		return 'subscribe_newsletter_form';
	}
	
	/**
	 * {@inheritdoc}
	 */
	public function buildForm(array $form, FormStateInterface $form_state){
		$form['stat_msg'] = array(
		  '#tree' => TRUE,
          '#prefix' => '<div id="newsletter-message">',
          '#suffix' => '</div>'
		);
		$form['nl_email'] = array(
		  '#type' => 'email',
		  '#required' => TRUE,
		  '#placeholder' => $this->t('Sign up for our Newsletter'),
		  '#attributes' => array(
		    'title' => t('Enter you Email to Subscribe')
		  ),
		);
		$form['subscribe'] = array(
		  '#type' => 'submit',
		  '#name' => 'subscribe_button',
		  '#value' => $this->t('Subscribe'),
		);
		return $form;
	}

	/**
	 * {@inheritdoc}
	 */
	public function submitForm(array &$form, FormStateInterface $form_state) {
		// add email entry to database table.
		//drupal_set_message('<pre>'.print_r($form_state['values'],true).'</pre>');
		$date = \Drupal\Core\Datetime\DrupalDateTime::createFromTimestamp(time());
		$timestamp = $date->getTimestamp();
		$entry = array(
			'email' => $form_state->getValue('nl_email'),
			'created' => $timestamp,
		);
		$return = NewsLetterFormStorage::insert($entry);
		if ($return) {
			//drupal_set_message(t('Created entry @entry', array('@entry' => print_r($entry, TRUE))));
			drupal_set_message($this->t('Thanks for Newsletter Subscription, Your Email "@mail" registered with us.', array('@mail' => $form_state->getValue('nl_email'))));
		}
		$form_values = $form_state->getValues();
		$module = 'newsletter';
		$key = 'subscribe_newsletter_form';
		$to = $form_values['nl_email'];
		$langcode = \Drupal::currentUser()->getPreferredLangcode();
		$params = array(
		  'body' => t('You have a new Newsletter Subcription. ').$to.t(' Subscribed for our Newsletter.'),
		  'subject' => t('News Letter Subscription request'),
		  'langcode' => $langcode
		);
		
		$send = TRUE;
		$mailManager = \Drupal::service('plugin.manager.mail');
		$result = $mailManager->mail($module, $key, $to, $langcode, $params, NULL, $send);
		if ($result['result'] == TRUE && $return) {
		  drupal_set_message(t('Your message has been sent.'));
		}
		else {
		  drupal_set_message(t('There was a problem sending your message and it was not sent.'), 'error');
		}
	}
} 
