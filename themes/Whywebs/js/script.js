/**
 * @file
 * A JavaScript file for the theme.
 *
 * In order for this JavaScript to be loaded on pages, see the instructions in
 * the README.txt next to this file.
 */

// JavaScript should be made compatible with libraries other than jQuery by
// wrapping it with an "anonymous closure". See:
// - https://drupal.org/node/1446420
// - http://www.adequatelygood.com/2010/3/JavaScript-Module-Pattern-In-Depth
(function ($, Drupal, window, document, undefined) {

  //Add class to intro text if there's an image to avoid text wrapping 
  Drupal.behaviors.introText = {
	  attach: function(context, settings) {		 
		  if( $('.view-intro .views-field-field-image-intro').length ) {
  		  $('.view-intro .views-field-field-body').addClass('left');
		  } 
	  }
	};
		function popupOpenClose(popup) {
	
	/* Add div inside popup for layout if one doesn't exist */
	if ($(".wrapper").length == 0){
		$(popup).wrapInner("<div class='wrapper'></div>");
	}
	
	/* Open popup */
	$(popup).show();

	/* Close popup if user clicks on background */
	$(popup).click(function(e) {
		if ( e.target == this ) {
			if ($(popup).is(':visible')) {
				$(popup).hide();
			}
		}
	});

	/* Close popup and remove errors if user clicks on cancel or close buttons */
	$(popup).find("button[name=close]").on("click", function() {
		if ($(".formElementError").is(':visible')) {
			$(".formElementError").remove();
		}
		$(popup).hide();
	});
}

$(document).ready(function () {
	$("[data-js=open]").on("click", function() {
		popupOpenClose($(".popup"));
	});
});

$(function() {
    $(".bgCollection").change(function() {
        if ($("#edit-field-student-or-tutor-und-6").is(":checked")) {
            $("#modalContent").css('backgroundColor', "red");
        }
        if ($("#edit-field-student-or-tutor-und-5").is(":checked")) {
            $("#modalContent").css('backgroundColor', "blue");
        }
    });
});

$(window).scroll(function(){
      if ($(this).scrollTop() > 500) {
          $('#header').addClass('menu-left');
          $('#block-menu-menu-homepage').addClass('menu-left');
          $('#right-menu').addClass('show-menu-right');
          $('body').addClass('menu-left');
      } else {
          $('#header').removeClass('menu-left');
          $('#block-menu-menu-homepage').removeClass('menu-left');
          $('#right-menu').removeClass('show-menu-right');
          $('body').removeClass('menu-left');
      }
  });
	
})(jQuery, Drupal, this, this.document);
