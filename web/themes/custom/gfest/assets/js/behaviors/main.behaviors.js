;(function ($, Drupal, window, document) {
  'use strict';
  Drupal.behaviors.gfestExternalLinks = {
    attach: function (context, settings) {
      $('[rel="external"]', context).attr('target', '_blank');
    }
  };
}(jQuery, Drupal, this, this.document));
