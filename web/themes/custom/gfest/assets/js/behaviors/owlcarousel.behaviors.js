;(function ($, Drupal, window, document) {
  'use strict';
  Drupal.behaviors.gfestOwlCarousel = {
    attach: function (context, settings) {
      if ($.fn.owlCarousel) {
        $('.js-partners_slider', context).once('partnersSlider').each(function () {
          $(this).owlCarousel({
            loop: true,
            items: 4,
            nav: false,
            dots: false,
            smartSpeed: 1000,
            autoplay: true,
            utoplayTimeout: 1000,
            responsive: {
              0: {
                items: 1
              },
              500: {
                items: 2
              },
              767: {
                items: 3
              },
              1000: {
                items: 4
              },
              1200: {
                items: 6
              }
            }
          });
        });
      }
    }
  };
}(jQuery, Drupal, this, this.document));
