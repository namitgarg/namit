/**
 * @file
 * A JavaScript file for the theme.
 *
 * In order for this JavaScript to be loaded on pages, see the instructions in
 * the README.txt next to this file.
 */

// JavaScript should be made compatible with libraries other than jQuery by
// wrapping it with an "anonymous closure". See:
// - http://drupal.org/node/1446420
// - http://www.adequatelygood.com/2010/3/JavaScript-Module-Pattern-In-Depth
(function($, Drupal, window, document, undefined) {
    
 $(document).ready( function(){
     
       if($("#block-nice-menus-1").length > 0){ 
        $('#block-nice-menus-1').meanmenu({
         meanMenuContainer: '#navigation .region-navigation',
         meanScreenWidth: "1199",
         meanRemoveAttrs: true,
         meanDisplay: "table",
         meanMenuOpen: "<span></span><span></span><span></span><strong class='mobile-text'>Menu</strong>",
         meanRevealPosition: "left",
         meanMenuClose: "<small>X</small><strong class='mobile-text'>Menu</strong>"
        }); 
       }
      
        jQuery.noConflict();
        jQuery('#block-menu-block-3 .menu-block-wrapper').footermenu({
         fooMenuContainer: '.region-footer',
         fooScreenWidth: "1199",
         fooRemoveAttrs: true,
         fooDisplay: "block",
         fooMenuOpen: "<span></span><span></span><span></span><strong class='foo-mobile-text'>Menu</strong>",
         fooRevealPosition: "left",
         fooMenuClose: "<small>X</small><strong class='foo-mobile-text'>Menu</strong>"
        });
       
        jQuery("#block-block-9 .search-icon").click(function(){
           jQuery("#block-search-form").slideToggle();
          
       });
      
    });
// Place your code here.
})(jQuery, Drupal, this, this.document);

