<?php

use \Drupal\block_content\BlockContentInterface;

/**
 * Implements hook_theme_suggestions_HOOK_alter().
 */
function gfest_theme_suggestions_node_alter(array &$suggestions, array $variables) {
  $elements = $variables['elements'];
  if (!empty($elements['#node'])) {
    $node = $elements['#node'];
    $content_type = $node->getType();
    if ($content_type == 'page') {
      $page_layout = $node->get('field_page_layout')->getString();
      if (!empty($page_layout)) {
        $suggestions[] = "node__layout__{$page_layout}";
      }
    }
  }
}

/**
 * Implements hook_theme_suggestions_block_alter().
 */
function gfest_theme_suggestions_block_alter(array &$suggestions, array $variables) {
  $elements = $variables['elements'];
  // Block suggestions for custom block bundles.
  if (isset($elements['content']['#block_content']) && $elements['content']['#block_content'] instanceof BlockContentInterface) {
    array_splice($suggestions, 1, 0, 'block__block_content__bundle_' . $elements['content']['#block_content']->bundle());
  }
}

/**
 * Implements hook_theme_suggestions_alter().
 */
function gfest_theme_suggestions_form_alter(array &$suggestions, array $variables) {
  if (isset($variables['element']['#form_id'])) {
    $suggestions[] = 'form__' . $variables['element']['#form_id'];
  }
}

/**
 * Implements hook_theme_suggestions_views_view_unformatted_alter().
 */
function gfest_theme_suggestions_views_view_unformatted_alter(array &$suggestions, array $variables) {
  $suggestions[] = sprintf('views_view_unformatted__%s', $variables['view']->id());
  $suggestions[] = sprintf('views_view_unformatted__%s__%s', $variables['view']->id(), $variables['view']->current_display);
}

/**
 * Implements hook_theme_suggestions_field_alter().
 */
function gfest_theme_suggestions_field_alter(array &$suggestions, array $variables) {
  $elements = $variables['element'];
  $suggestions[] = 'field__' . $elements['#field_name'] . '__' . $elements['#view_mode'];
}
