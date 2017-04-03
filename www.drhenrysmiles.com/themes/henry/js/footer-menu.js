
(function($) {
     "use strict";
     $.fn.footermenu = function(options) {
          var defaults = {
               fooMenuTarget: jQuery(this), // Target the current HTML markup you wish to replace
               fooMenuContainer: 'body', // Choose where foomenu will be placed within the HTML
               fooMenuClose: "X", // single character you want to represent the close menu button
               fooMenuCloseSize: "18px", // set font size of close button
               fooMenuOpen: "<span /><span /><span />", // text/markup you want when menu is closed
               fooRevealPosition: "left", // left right or center positions
               fooRevealPositionDistance: "0", // Tweak the position of the menu
               fooRevealColour: "", // override CSS colours for the reveal background
               fooScreenWidth: "1099", // set the screen width you want foomenu to kick in at
               fooNavPush: "", // set a height here in px, em or % if you want to budge your layout now the navigation is missing.
               fooShowChildren: true, // true to show children in the menu, false to hide them
               fooExpandableChildren: true, // true to allow expand/collapse children
               fooExpand: "+", // single character you want to represent the expand for ULs
               fooContract: "-", // single character you want to represent the contract for ULs
               fooRemoveAttrs: false, // true to remove classes and IDs, false to keep them
               onePage: false, // set to true for one page sites
               fooDisplay: "block", // override display method for table cell based layouts e.g. table-cell
               removeElements: "" // set to hide page elements
          };
          options = $.extend(defaults, options);

          // get browser width
          var currentWidth = window.innerWidth || document.documentElement.clientWidth;

          return this.each(function() {
               var fooMenu = options.fooMenuTarget;
               var fooContainer = options.fooMenuContainer;
               var fooMenuClose = options.fooMenuClose;
               var fooMenuCloseSize = options.fooMenuCloseSize;
               var fooMenuOpen = options.fooMenuOpen;
               var fooRevealPosition = options.fooRevealPosition;
               var fooRevealPositionDistance = options.fooRevealPositionDistance;
               var fooRevealColour = options.fooRevealColour;
               var fooScreenWidth = options.fooScreenWidth;
               var fooNavPush = options.fooNavPush;
               var fooRevealClass = ".foomenu-reveal";
               var fooShowChildren = options.fooShowChildren;
               var fooExpandableChildren = options.fooExpandableChildren;
               var fooExpand = options.fooExpand;
               var fooContract = options.fooContract;
               var fooRemoveAttrs = options.fooRemoveAttrs;
               var onePage = options.onePage;
               var fooDisplay = options.fooDisplay;
               var removeElements = options.removeElements;

               //detect known mobile/tablet usage
               var isMobile = false;
               if ((navigator.userAgent.match(/iPhone/i)) || (navigator.userAgent.match(/iPod/i)) || (navigator.userAgent.match(/iPad/i)) || (navigator.userAgent.match(/Android/i)) || (navigator.userAgent.match(/Blackberry/i)) || (navigator.userAgent.match(/Windows Phone/i))) {
	isMobile = true;
               }

               if ((navigator.userAgent.match(/MSIE 8/i)) || (navigator.userAgent.match(/MSIE 7/i))) {
	// add scrollbar for IE7 & 8 to stop breaking resize function on small content sites
	jQuery('html').css("overflow-y", "scroll");
               }

               var fooRevealPos = "";
               var fooCentered = function() {
	if (fooRevealPosition === "center") {
	     var newWidth = window.innerWidth || document.documentElement.clientWidth;
	     var fooCenter = ((newWidth / 2) - 22) + "px";
	     fooRevealPos = "left:" + fooCenter + ";right:auto;";

	     if (!isMobile) {
	          jQuery('.foomenu-reveal').css("left", fooCenter);
	     } else {
	          jQuery('.foomenu-reveal').animate({
	               left: fooCenter
	          });
	     }
	}
               };

               var menuOn = false;
               var fooMenuExist = false;


               if (fooRevealPosition === "right") {
	fooRevealPos = "right:" + fooRevealPositionDistance + ";left:auto;";
               }
               if (fooRevealPosition === "left") {
	fooRevealPos = "left:" + fooRevealPositionDistance + ";right:auto;";
               }
               // run center function
               fooCentered();

               // set all styles for foo-reveal
               var $navreveal = "";

               var fooInner = function() {
	// get last class name
	if (jQuery($navreveal).is(".foomenu-reveal.fooclose")) {
	     $navreveal.html(fooMenuClose);
	} else {
	     $navreveal.html(fooMenuOpen);
	}
               };

               // re-instate original nav (and call this on window.width functions)
               var fooOriginal = function() {
	jQuery('.foo-bar,.foo-push').remove();
	jQuery(fooContainer).removeClass("foo-container");
	jQuery(fooMenu).css('display', fooDisplay);
	menuOn = false;
	fooMenuExist = false;
	jQuery(removeElements).removeClass('foo-remove');
               };

               // navigation reveal
               var showMeanMenu = function() {
	var fooStyles = "background:" + fooRevealColour + ";color:" + fooRevealColour + ";" + fooRevealPos;
	if (currentWidth <= fooScreenWidth) {
	     jQuery(removeElements).addClass('foo-remove');
	     fooMenuExist = true;
	     // add class to body so we don't need to worry about media queries here, all CSS is wrapped in '.foo-container'
	     jQuery(fooContainer).addClass("foo-container");
	     jQuery('.foo-container').prepend('<div class="foo-bar"><a href="#nav" class="foomenu-reveal" style="' + fooStyles + '">Show Navigation</a><nav class="foo-nav"></nav></div>');

	     //push fooMenu navigation into .foo-nav
	     var fooMenuContents = jQuery(fooMenu).html();
	     jQuery('.foo-nav').html(fooMenuContents);

	     // remove all classes from EVERYTHING inside foomenu nav
	     if (fooRemoveAttrs) {
	          jQuery('nav.foo-nav ul, nav.foo-nav ul *').each(function() {
	               // First check if this has foo-remove class
	               if (jQuery(this).is('.foo-remove')) {
		jQuery(this).attr('class', 'foo-remove');
	               } else {
		jQuery(this).removeAttr("class");
	               }
	               jQuery(this).removeAttr("id");
	          });
	     }

	     // push in a holder div (this can be used if removal of nav is causing layout issues)
	     jQuery(fooMenu).before('<div class="foo-push" />');
	     jQuery('.foo-push').css("margin-top", fooNavPush);

	     // hide current navigation and reveal foo nav link
	     jQuery(fooMenu).hide();
	     jQuery(".foomenu-reveal").show();

	     // turn 'X' on or off
	     jQuery(fooRevealClass).html(fooMenuOpen);
	     $navreveal = jQuery(fooRevealClass);

	     //hide foo-nav ul
	     jQuery('.foo-nav > ul').hide();

	     // hide sub nav
	     if (fooShowChildren) {
	          // allow expandable sub nav(s)
	          if (fooExpandableChildren) {
	               jQuery('.foo-nav > ul ul').each(function() {
		if (jQuery(this).children().length) {
		     jQuery(this, 'li:first').parent().append('<a class="foo-expand" href="#" style="font-size: ' + fooMenuCloseSize + '">' + fooExpand + '</a>');
		}
	               });
	               jQuery('.foo-expand').on("click", function(e) {
		e.preventDefault();
		if (jQuery(this).hasClass("foo-clicked")) {
		     jQuery(this).text(fooExpand);
		     jQuery(this).prev('ul').slideUp(300, function() {
		     });
		} else {
		     jQuery(this).text(fooContract);
		     jQuery(this).prev('ul').slideDown(300, function() {
		     });
		}
		jQuery(this).toggleClass("foo-clicked");
	               });
	          } else {
	               jQuery('.foo-nav > ul ul').show();
	          }
	     } else {
	          jQuery('.foo-nav > ul ul').hide();
	     }

	     // add last class to tidy up borders
	     jQuery('.foo-nav > ul li').last().addClass('foo-last');
	     $navreveal.removeClass("fooclose");
	     jQuery($navreveal).click(function(e) {
	          e.preventDefault();
	          if (menuOn === false) {
	               $navreveal.css("text-align", "left");
	               $navreveal.css("text-indent", "0");
	               $navreveal.css("font-size", fooMenuCloseSize);
	               jQuery('.foo-nav > ul:first').slideDown();
	               menuOn = true;
	          } else {
	               jQuery('.foo-nav > ul:first').slideUp();
	               menuOn = false;
	          }
	          $navreveal.toggleClass("fooclose");
	          fooInner();
	          jQuery(removeElements).addClass('foo-remove');
	     });

	     // for one page websites, reset all variables...
	     if (onePage) {
	          jQuery('.foo-nav > ul > li > a:first-child').on("click", function() {
	               jQuery('.foo-nav > ul:first').slideUp();
	               menuOn = false;
	               jQuery($navreveal).toggleClass("fooclose").html(fooMenuOpen);
	          });
	     }
	} else {
	     fooOriginal();
	}
               };

               if (!isMobile) {
	// reset menu on resize above fooScreenWidth
	jQuery(window).resize(function() {
	     currentWidth = window.innerWidth || document.documentElement.clientWidth;
	     if (currentWidth > fooScreenWidth) {
	          fooOriginal();
	     } else {
	          fooOriginal();
	     }
	     if (currentWidth <= fooScreenWidth) {
	          showMeanMenu();
	          fooCentered();
	     } else {
	          fooOriginal();
	     }
	});
               }

               jQuery(window).resize(function() {
	// get browser width
	currentWidth = window.innerWidth || document.documentElement.clientWidth;

	if (!isMobile) {
	     fooOriginal();
	     if (currentWidth <= fooScreenWidth) {
	          showMeanMenu();
	          fooCentered();
	     }
	} else {
	     fooCentered();
	     if (currentWidth <= fooScreenWidth) {
	          if (fooMenuExist === false) {
	               showMeanMenu();
	          }
	     } else {
	          fooOriginal();
	     }
	}
               });

               // run main menuMenu function on load
               showMeanMenu();
          });
     };
})(jQuery);
