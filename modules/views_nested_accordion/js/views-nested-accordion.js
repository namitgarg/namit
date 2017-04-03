/**
 * @file
 * JS for Nested Accordion.
 */


(function ($) {

Drupal.behaviors.views_nested_accordion = {
  attach: function(context, settings) {
    if(Drupal.settings.views_nested_accordion){

        $.each(Drupal.settings.views_nested_accordion, function(id) {
          /* Our Nested Accordion Settings */
          var viewname = this.viewname;
          var viewopen = this.rowstartopen;
          var display = this.display;
          
          /* the selectors we have to play with */
          var displaySelector = '.view-id-' + viewname + '.view-display-id-' + display + ' > .view-content';
          /* Add Class to the Row which need to be open by default On Page Load */
	  if(viewopen) {
            $('.view-id-' + viewname + ' .view-grouping:nth-child(' + viewopen +') .view-grouping-header').next().addClass('nested-accordion');
	  }
          //$('.view-grouping-content .ui-accordion-content').css({'height':'auto'});
          $('.view-grouping .view-grouping-content').css({'display':'none'});
          $('.view-grouping .nested-accordion').css({'display':'block'});
          /* Generate Accordion Effect on Outer Header Click */
          $('.view-id-' + viewname + ' .view-grouping h3').click(function() {
		  var cheight = $(this).next().prop('scrollHeight');
                  $(this).parent().children('.ui-accordion-content').css({'display':'none'});
                  $(this).next().css({'display':'block','height':cheight+'px'});
          });
          $('.view-id-' + viewname + ' .view-grouping .view-grouping-header').click(function() {

                  if($(this).hasClass("nested-accordion")) {
                    /* If Accordion is Open, then Clicking on it will close the Accordion. */
                    $(this).removeClass("nested-accordion");
                    $(this).siblings('.view-grouping-content').slideUp();
                  } else {
                    /* Clicking on Header will Open the Accordion */
                    $(this).addClass('nested-accordion');
                    $(this).siblings('.view-grouping-content').slideDown();
                    $(this).parents('.view-grouping').siblings('.view-grouping').children('.view-grouping-header').removeClass('nested-accordion');
                    $(this).parents('.view-grouping').siblings('.view-grouping').children('.view-grouping-content').slideUp();
                  }

          });

        });
    }
  }
};

})(jQuery);
