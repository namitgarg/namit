<?php

namespace Drupal\subscribe_newsletter\Controller;

use Drupal\Core\Controller\ControllerBase;
use Drupal\subscribe_newsletter\NewsLetterFormStorage;

/**
 * Controller for Newsletter Listing.
 */
class NewsLetterController extends ControllerBase {
	
	/*
	 * Getting the Listing of Subscribed Emails
	 */
	 
	public function listSubscribtion(){
		$content = array();
		$content['message'] = array(
		  '#markup' => $this->t('Generate a list of all entries in the database. There is no filter in the query.'),
		);
		$rows = array();
		$headers = array(array('data' => $this->t('EMAIL'), 'field' => 'email', 'sort' => 'asc'),
						array('data' => $this->t('CREATED'), 'field' => 'created', 'sort' => 'asc'),
					);	
		$select = db_select('newsletter_data', 'newsletter');
		$query = $select->fields('newsletter',array('email','created'));
		$table_sort = $query->extend('Drupal\Core\Database\Query\TableSortExtender')->orderByHeader($headers);
		$pager = $table_sort->extend('Drupal\Core\Database\Query\PagerSelectExtender')->limit(50);
		$result = $pager->execute();
		foreach($result as $row) {
          //$rows[] = array('data' => (array) $row);
		  $datetime = \Drupal\Core\Datetime\DrupalDateTime::createFromTimestamp($row->created);
		  //$datetime = $datetime->format('d.m.y');
		  $datetime = date('d, M Y h:i:s a',$row->created);
		  $rows[] = array('data' => array(
					'email' => $row->email,
					'created' => $datetime,
		  ));
		}

		$content['table'] = array(
		  '#type' => 'table',
		  '#header' => $headers,
		  '#rows' => $rows,
		  '#empty' => t('No entries available.'),
		);
		$content['pager'] = array(
			'#type' => 'pager',
		);
		// Don't cache this page.
		$content['#cache']['max-age'] = 0;
		//$markup = drupal_render($content);

		return $content;
	}
}