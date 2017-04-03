/**
 *  @file
 * Javascript file for redirect_update module.
 */
(function ($) {
Drupal.behaviors.redirectUpdate = {
        attach: function (context, settings) {
          $(':input[name="redirect_updatecheck_uncheck_all"]').click(function() {
           if ($(this).is(':checked')) { //If select all checkbox is checked.
               redirect_update_check_uncheck(true);
            } 
            else {
               redirect_update_check_uncheck(false);
            }
          });
        }
};
})(jQuery);

/**
 * Function to check / uncheck all content type checkboxes.
 * @param bool check
 *   Whether select all checkbox is checked or not.
 */
function redirect_update_check_uncheck(check) {
  jQuery('.redirect-update-all-ccontent-types').find('input[type=checkbox]').each(function() {  //Iterate over each content type checkbox.
    if (check) {
      jQuery(this).attr('checked', true);
    }
    else {
      jQuery(this).attr('checked', false);
    }
  });
}