	<?php
/**
 * @file
 * Returns the HTML for a single Drupal page.
 *
 * Complete documentation for this file is available online.
 * @see https://drupal.org/node/1728148
 */
?>

<div class="detailed-gallery-outer">
<div class="Gallery_body_area">
<div class="image-wrapper">
	<div class="headshot"><?php print render($content['field_headshot']);?></div>
	<div class="before-after-wrapper">
    	<div class="cont1">
<?php if(!empty($content['field_before_image_1'])): ?>
            <div class="before-img"><?php print render($content['field_before_image_1']);?><span class="bef-aft">Before</span></div>
<?php endif; ?>
<?php if(!empty($content['field_after_image_1'])): ?>           
            <div class="after-img"><?php print render($content['field_after_image_1']);?><span class="bef-aft">After</span></div>
<?php endif; ?>
	</div>
	<div class="cont1">
<?php if(!empty($content['field_before_image_2'])): ?>
            <div class="before-img"><?php print render($content['field_before_image_2']);?><span class="bef-aft">Before</span></div>
<?php endif; ?>
<?php if(!empty($content['field_after_image_2'])): ?>           
            <div class="after-img"><?php print render($content['field_after_image_2']);?><span class="bef-aft">After</span></div>
<?php endif; ?>
	</div>
        <div class="cont1">
<?php if(!empty($content['field_before_image_3'])): ?>
            <div class="before-img"><?php print render($content['field_before_image_3']);?><span class="bef-aft">Before</span></div>
<?php endif; ?>
<?php if(!empty($content['field_after_image_3'])): ?>
            <div class="after-img"><?php print render($content['field_after_image_3']);?><span class="bef-aft">After</span></div>
<?php endif; ?>
	</div>
	<div class="cont1">
 <?php if(!empty($content['field_before_image_4'])): ?>
	<div class="before-img"><?php print render($content['field_before_image_4']);?><span class="bef-aft">Before</span></div>
 <?php endif ?>
 <?php if(!empty($content['field_after_image_4'])): ?>
	<div class="after-img"><?php print render($content['field_after_image_4']);?><span class="bef-aft">After</span></div>
  <?php endif ?>
	</div>
	</div>
</div>
	<?php //print render($content['field_gallery_type']);?>
    <div class="before-after-bodytext">
	<?php if ($title): ?> <h1 class="page__title title" id="gallery-page-title"><?php print $title; ?></h1><?php endif; ?>
	<div class="body-text"><p><?php print $node->body['und'][0]['value']; ?></p></div>
    </div>

</div>
</div>
