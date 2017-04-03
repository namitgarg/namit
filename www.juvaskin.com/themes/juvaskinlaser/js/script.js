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
	function incrDecrCount() {
		var plusbtn = $('.cart-wrapper .button-plus').detach();
		var minusbtn = $('.cart-wrapper .button-minus').detach();
		plusbtn.insertAfter('#edit-qty');
		minusbtn.insertBefore('#edit-qty');
		$('.cart-wrapper .button-plus').on('click', function() {
			var $qty = $('#edit-qty');
			var currentVal = parseInt($qty.val());
			if (!isNaN(currentVal)) {
				$qty.val(currentVal + 1);
			}
		});
		$('.cart-wrapper .button-minus').on('click', function() {
			var $qty = $('#edit-qty');
			var currentVal = parseInt($qty.val());
			if (!isNaN(currentVal) && currentVal > 0) {
				$qty.val(currentVal - 1);
			}
		});
	}
	function breakLine() {
    var path = jQuery('#block-views-location-block-1 .view-location .view-content .views-row .views-field-title a');
    path.each(function(i) {
      var html = $(this).html().split(" ");     
        html = html.slice(0, 2).join(" ") + "<br />" + html.slice(2).join(" ");   
      $(this).html(html);
    });
  }
	function centerPosition() {
		var windowWidth = $(window).width();
		var path1 = jQuery('#block-block-7');
		var path2 = jQuery('#block-views-association-logos-block');
		var x = (windowWidth - 1200) / 2;
		if (windowWidth <= 1023) {
			path1.css('padding-left', 19 + 'px');
			path2.css('padding-right', 19 + 'px');
		}
		if (windowWidth >= 1024) {
			path1.css('padding-left', 20 + 'px');
			path2.css('padding-right', 20 + 'px');
		}
		if (windowWidth >= 1200) {
			path1.css('padding-left', x + 'px');
			path2.css('padding-right', x + 'px');
		}
	}
	function addMapVideoClass() {
		var video = jQuery("#content iframe[src*='//www.youtube.com/embed']");
		var map = jQuery("#content iframe[src*='//www.google.com/maps/embed']");
		$.each($(video), function() {
			var _that = $(this);
			_that.wrap("<p class='video-container' />");
		});
		$.each($(map), function() {
			var _that = $(this);
			_that.wrap("<p class='map-container' />");
		});
	}
	function wrappedImg() {
		jQuery('.node-type-gallery .node-gallery .field-type-text-with-summary').after('<div class="img-wrapper" />');
		jQuery('.node-type-gallery .node-gallery .field-type-image').appendTo('.img-wrapper');
	}

	jQuery(document).ready(function() {
		addMapVideoClass();  // used on youtube iframe.
		wrappedImg();  // used on gallery node page.
		centerPosition();	// used for center position on mini form and association logos block (1024px between above).		
		incrDecrCount();  // used on add to cart on products page.
		//breakLine();

//================for mobile menu block=============== 
		if ($("#block-nice-menus-1").length > 0) {
			$('#block-nice-menus-1').meanmenu({
				meanMenuContainer: '#navigation .region-primary-menu',
				meanScreenWidth: "1024",
				meanRemoveAttrs: true,
				meanDisplay: "table",
				meanMenuOpen: "<span></span><span></span><span></span><strong class='mobile-text'>Menu</strong>",
				meanRevealPosition: "left",
				meanMenuClose: "<small>X</small><strong class='mobile-text'>Menu</strong>"
			});
		}

//================for header search block=============== 

		if ($(this).width() > 0) {
			jQuery("#block-search-form .block-title").click(function(e) {
				jQuery("#search-block-form").toggle("fast");
				jQuery('#search-block-form .form-text').focus();
				e.stopPropagation();
			});
			var mouse_is_inside = false;
			jQuery('#block-search-form, #search-block-form').hover(function() {
				mouse_is_inside = true;
			}, function() {
				mouse_is_inside = false;
			});
			jQuery("body").click(function() {
				if (!mouse_is_inside) {
					jQuery("#search-block-form").hide();
				}
			});
		}

		//===============For wapper on products page section===============================
		
		jQuery('.order-review-table').wrap('<div class="review-table-wrapper" />');
		jQuery('#user-login .captcha').wrap('<div class="captcha-wrapper" />');
		jQuery('.views-field-uc-product-image').find('img').addClass('product-pic');
		jQuery('.field-name-uc-product-image').find('img').addClass('product-pic');

//==========================================Code for Read More link==============================
		jQuery('#toggle-text').click(function() {
			if (jQuery('#content-text').hasClass('.open')) {
				jQuery('#content-text').hide('slow').removeClass('.open');
				jQuery('#toggle-text').html('Read More');
			} else {
				jQuery('#content-text').addClass('.open').show('slow');
				jQuery('#toggle-text').html('Read Less');
			}
		});

// ======================Code for google translator that add class to body.========================

		$('#google_translate_element').on('change load', 'select.goog-te-combo', function() {
			// To remove iframe of google translator in top
			$("iframe.goog-te-banner-frame").css("display", "none");
			var curr_lang = jQuery(this).val();
			switch (curr_lang) {
				case 'en':
					$('body').removeClass('russian spanish french chinese arabic');
					break;
				case 'es':
					$('body').removeClass('russian french chinese arabic').addClass('spanish');
					break;
				case 'ru':
					$('body').removeClass('french chinese arabic spanish').addClass('russian');
					break;
				case 'fr':
					$('body').removeClass('russian chinese arabic spanish').addClass('french');
					break;
				case 'zh-CN':
					$('body').removeClass('russian french arabic spanish').addClass('chinese');
					break;
				case 'ar':
					$('body').removeClass('spanish russian french chinese').addClass('arabic');
					break;
				default:
					$('body').removeClass('russian spanish french chinese arabic');
					break;
			}
		});

//    ===============Back to Top section===============================
		$('#block-block-76 a[href^=#],#block-multiblock-16 a[href^=#]').click(function(event) {
			$('html, body').animate({
				scrollTop: $($.attr(this, 'href')).offset().top
			}, 1000);
			event.preventDefault();
		});
//    ===============For march height on products page section===============================
		$('.view-juva-in-the-media .views-row .views-field-title').matchHeight();
		$('.views-field-uc-product-image').matchHeight();	
		$('.view-juva-store-product-type .views-row .views-field-title').matchHeight();		
		
		//    ===============For remove video icon on products page section===============================
		$('.node-type-videos .node-videos').find('.field-name-field-youtube-url').prev('.field-name-field-video-icon').remove();	 

		jQuery('#block-views-video-block-1 .view-video .views-row').on('click tap','.views-field-field-video-icon', function(ev) {
					jQuery('#block-views-video-block-1 .view-video .views-row').each(function(){
						   var imgsrc=$(this).find('#youtube-field-player').attr('src'); 									
									jQuery(this).find('#youtube-field-player').attr('src',imgsrc.replace("&autoplay=1",""));
									jQuery(this).find('.views-field-field-video-icon .icon-wrapper,.views-field-field-video-icon .video-wrapper').css('z-index','2');
									jQuery(this).find('.views-field-field-video-icon .video-wrapper').css('z-index','0');
					});
					var _this = jQuery(this);
					var imgsrc=$(_this).parent().find('#youtube-field-player').attr('src').replace("&autoplay=0",'');			
					jQuery(_this).parent().find('#youtube-field-player').attr("src",imgsrc += "&autoplay=1");						
					jQuery(_this).parent().find('.views-field-field-video-icon .icon-wrapper').css('z-index','0');						
					jQuery(_this).parent().find('.views-field-field-video-icon .video-wrapper').css('z-index','2');						
					ev.preventDefault();
   });
	});

//check for the orientation event and bind accordingly
	$(window).on('orientationchange resize', function(event) {
		if (event.orientation) {
			if (event.orientation == 'portrait') {
				// do something											
				centerPosition();// used for center position on mini form and association logos block (1024px between above).					
			} else if (event.orientation == 'landscape') {
				// do something else
				centerPosition();// used for center position on mini form and association logos block (1024px between above).					
			}
		} else {
			// optional... PC-version javascript for example																		
			centerPosition();// used for center position on mini form and association logos block (1024px between above).				
		}
		
		

	});

	jQuery(window).load(function() {
		
		// To remove logo of google translator in top
		$("#google_translate_element .goog-te-gadget").contents().eq(1).wrap('<span style="display:none;"/>');
		$("#google_translate_element .goog-te-gadget").contents().eq(2).wrap('<span style="display:none;"/>');

		// To remove iframe of google translator in top
		$("iframe.goog-te-banner-frame").css("display", "none");
		var curr_lang = jQuery('select.goog-te-combo').val();
		switch (curr_lang) {
			case 'en':
				$('body').removeClass('russian spanish french chinese arabic');
				break;
			case 'es':
				$('body').removeClass('russian french chinese arabic').addClass('spanish');
				break;
			case 'ru':
				$('body').removeClass('french chinese arabic spanish').addClass('russian');
				break;
			case 'fr':
				$('body').removeClass('russian chinese arabic spanish').addClass('french');
				break;
			case 'zh-CN':
				$('body').removeClass('russian french arabic spanish').addClass('chinese');
				break;
			case 'ar':
				$('body').removeClass('spanish russian french chinese').addClass('arabic');
				break;
			default:
				$('body').removeClass('russian spanish french chinese arabic');
				break;
		}
	});
	jQuery(window).resize(function() {
$('.mean-nav span:contains("More Conditions")').closest('li').addClass('hidden-group').css('display','none');
	});
})(jQuery, Drupal, this, this.document);



