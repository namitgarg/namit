<?php
/**
	* @file
	* Returns the HTML for a single Drupal page.
	*
	* Complete documentation for this file is available online.
	* @see https://drupal.org/node/1728148
	*/
?>
<?php
//echo "<pre>";
//print_r($node);
//echo "</pre>";
//exit;
//$get_nodes = node_load($node->nid);
//$get_nodes;
//exit;
?>
<div class="location-wrapper-main">
	<?php	if	(!empty($content['field_upper_body'])):	?>
		<div class="wrapper-upper-body"><?php	print	render($content['field_upper_body']);	?></div>
	<?php	endif;	?>

	<?php	if	(!empty($content['field_location_form'])):	?>
		<div class="wrapper-location-form"><?php	print	render($content['field_location_form']);	?></div>
	<?php	endif;	?>


	<div class="map-address-container">
		<div class="map">
			<?php	if	(!empty($content['field_embedded_map'])):	?>
				<div class="embedded-map"><?php	print	render($content['field_embedded_map']);	?></div>
			<?php	endif;	?>
		</div>
		<div class="address">
			<div class="wrapper-buss-main">

				<?php	if	(!empty($content['field_business_name'])):	?>
					<div class="wrapper-busi-name"><?php	print	render($content['field_business_name']);	?></div>
				<?php	endif;	?>

				<?php	if	(!empty($content['field_address_line_1'])):	?>           
					<div class="wrapper-addr-1"><?php	print	render($content['field_address_line_1']);	?></div>
				<?php	endif;	?>

				<?php	if	(!empty($content['field_address_line_2'])):	?>           
					<div class="wrapper-addr-2"><?php	print	render($content['field_address_line_2']);	?></div>
				<?php	endif;	?>

				<?php	if	(!empty($content['field_city'])):	?>           
					<div class="wrapper-city"><?php	print	render($content['field_city']);	?></div>
				<?php	endif;	?>

				<?php	if	(!empty($content['field_state'])):	?>           
					<div class="wrapper-state"><?php	print	render($content['field_state']);	?></div>
				<?php	endif;	?>

				<?php	if	(!empty($content['field_zip_code'])):	?>           
					<div class="wrapper-zip"><?php	print	render($content['field_zip_code']);	?></div>
				<?php	endif;	?>

				<?php
				$get_node_phone	=	$node->field_phone['und'][0]['value'];
				$find	=	array("(",	")",	"-",	" ");
				$replace	=	"";
				$phone	=	str_replace($find,	$replace,	$get_node_phone);

				if	(!empty($content['field_phone'])):
					?>               

					<div class="wrapper-phone"><div class="field field-label-inline"><div class="field-label">Phone:&nbsp;</div></div><a href="tel:+1<?php	print	$phone;	?>"><?php	print	render($content['field_phone']);	?></a></div>
				<?php	endif;	?>

				<?php	if	(!empty($content['field_fax'])):	?>           
					<div class="wrapper-fax"><?php	print	render($content['field_fax']);	?></div>
				<?php	endif;	?>

				<?php	if	(!empty($content['field_map_link'])):	?>           
					<div class="wrapper-map-link"><?php	print	render($content['field_map_link']);	?></div>
         <?php	endif;	?>
          </div>

			<div class="office-hour-main">
				<?php	if	(!empty($content['field_office_hours_headline'])):	?>           
					<div class="wrapper-office-hour-headline"><?php	print	render($content['field_office_hours_headline']);	?></div>
				<?php	endif;	?>

				<?php	if	(!empty($content['field_office_hours_1'])):	?>           
					<div class="wrapper-office-hour1"><?php	print	render($content['field_office_hours_1']);	?></div>
        <?php	endif;	?>


				<?php	if	(!empty($content['field_office_hours_2'])):	?>           
					<div class="wrapper-office-hour2"><?php	print	render($content['field_office_hours_2']);	?></div>
        <?php	endif;	?>
          
          <?php	if	(!empty($content['field_office_hours_3'])):	?>           
					<div class="wrapper-office-hour2"><?php	print	render($content['field_office_hours_3']);	?></div>
        <?php	endif;	?>
          <?php	if	(!empty($content['field_office_hours_4'])):	?>           
					<div class="wrapper-office-hour2"><?php	print	render($content['field_office_hours_4']);	?></div>
        <?php	endif;	?>
		 <?php	if	(!empty($content['field_office_hours_5'])):	?>           
					<div class="wrapper-office-hour2"><?php	print	render($content['field_office_hours_5']);	?></div>
        <?php	endif;	?>
		 <?php	if	(!empty($content['field_office_hours_6'])):	?>           
					<div class="wrapper-office-hour2"><?php	print	render($content['field_office_hours_6']);	?></div>
        <?php	endif;	?>
          </div>


			<div class="social-medi-main">
				<?php	if	(!empty($content['field_social_media_headline'])):	?>           
					<div class="wrapper-social-headline"><?php	print	render($content['field_social_media_headline']);	?></div>
				<?php	endif;	?>

				<?php	if	(!empty($content['field_social_link1'])):	?>           
					<div class="wrapper-social"><?php	print	render($content['field_social_link1']);	?></div>
				<?php	endif;	?>

				<?php	if	(!empty($content['field_social_link2'])):	?>           
					<div class="wrapper-social"><?php	print	render($content['field_social_link2']);	?></div>
				<?php	endif;	?>

				<?php	if	(!empty($content['field_social_link3'])):	?>           
					<div class="wrapper-social"><?php	print	render($content['field_social_link3']);	?></div>
				<?php	endif;	?>

				<?php	if	(!empty($content['field_social_link4'])):	?>           
					<div class="wrapper-social"><?php	print	render($content['field_social_link4']);	?></div>
				<?php	endif;	?>

				<?php	if	(!empty($content['field_social_link5'])):	?>           
					<div class="wrapper-social"><?php	print	render($content['field_social_link5']);	?></div>
				<?php	endif;	?>

				<?php	if	(!empty($content['field_social_link6'])):	?>           
					<div class="wrapper-social"><?php	print	render($content['field_social_link6']);	?></div>
<?php	endif;	?>
			</div>


			<?php	if	(!empty($content['field_practice_area_link'])):	?>           
				<div class="wrapper-pra-link"><?php	print	render($content['field_practice_area_link']);	?></div>
        <?php	endif;	?>
		</div>
	</div>


	<?php	if	(!empty($content['body'])):	?>
		<div class="wrapper-lower-body"><?php	print	render($content['body']);	?></div>      
  <?php	endif;	?>





</div>



