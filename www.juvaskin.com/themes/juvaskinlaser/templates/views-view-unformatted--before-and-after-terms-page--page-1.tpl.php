<?php

/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
?>

<div class="views-row">

	<!-- This will output the Parent Term (The Hyperlink Term) --> 
	<?php if (!empty($title)): ?>
		<div class ="views-field"><?php print $title; ?></div>
	<?php endif; ?>
	<!-- End Parent Term --> 
	
	<!-- This will iterate for each term present in the vocabulary except Parent Term -->
	<div class="views-field list-section">
		<ul class="parent-list">
			<?php foreach ($rows as $id => $value): ?>
			  	<li <?php  if ($classes_array[$id]) { print ' class="' . $classes_array[$id] .'"';  } ?>>
			    	<?php  print_r($value); ?>
					
		    	<?php
					// Getting term id of the taxonomy
		    		$get_tname = strip_tags($value);
			    	$term_name = taxonomy_get_term_by_name($get_tname);	
			    	$term_name1 = reset($term_name);				
			    	$term_id = $term_name1->tid;
					
			    	//Getting taxonomy child data
			    	$term_child_data[] = taxonomy_get_children($term_id);
			    	$term_child_filter[] = reset($term_child_data);
					
			    	if (taxonomy_get_children($term_id)){ ?>

			    		<ul class="child-list">
						<?php foreach ($term_child_filter as $child_value_filter):
								foreach ($child_value_filter as $child_value): ?>
								
			    			<li <?php if ($classes_array[$id]) { print ' class="' . $classes_array[$id] .'"';  } ?>>
			    				<?php
									print $child_value->name; //child data name								
			    					if (taxonomy_get_children($child_value->tid)){ ?>
										<ul class="sub-child-list">
											<?php
												// Nested child data search
												$child_child_data[] = taxonomy_get_children($child_value->tid);
												$child_child_filter[] = reset($child_child_data);
												foreach ($child_child_filter as $child_value_filter):
													foreach ($child_value_filter as $child_child_value):
											?>					
											
												<li <?php if ($classes_array[$id]) { print ' class="' . $classes_array[$id] .'"';  } ?>>
													<?php print $child_child_value->name; //nested child data name ?>
												</li>
												<?php endforeach; 
													endforeach; ?>
										</ul>
								<?php 	}?>
		    				</li>
						<?php endforeach; 
							endforeach; ?>
			    		</ul>

			    	<?php } ?>  				
			  </li>
				<?php endforeach; ?>
		</ul>
	</div>
	<!-- End of each term iteration present in the vocabulary except Parent Term -->
</div>
