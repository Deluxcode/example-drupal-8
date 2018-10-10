<?php

use Drupal\Core\Url;
use Drupal\file\Entity\File;
use Drupal\Component\Utility\SafeMarkup;

/**
 * Implements template_preprocess_page().
 * @param $variables
 */
function gfest_preprocess_page(&$variables) {
  if (!empty($variables['node'])) {
    $content_type = $variables['node']->getType();
    $variables['attributes']['class'][] = "{$content_type}_page";
    if ($content_type == 'page') {
      $page_layout = $variables['node']->get('field_page_layout')->getString();
      if (!empty($page_layout)) {
        switch ($page_layout) {
          case 'home':
            $variables['attributes']['class'][] = "main_page";
          case 'services':
            $variables['attributes']['class'][] = "{$page_layout}";
          case 'contacts':
            $variables['attributes']['class'][] = "{$page_layout}_page";
          default:
            $variables['attributes']['class'][] = "{$page_layout}_layout";
        }
      }
    }
  }
}

/**
 * Implements template_preprocess_node().
 * @param $variables
 */
function gfest_preprocess_node(&$variables) {
  // add "time ago" to article full view mode page
  if (!empty($variables['node'])) {
    $node = $variables['node'];
    $node_type = $node->getType();
    if ($node_type == 'article') {
      /** @var \Drupal\Core\Datetime\DateFormatterInterface $formatter */
      $date_formatter = \Drupal::service('date.formatter');
      $node_created = $node->get('created')->getString();
      if (!empty($node_created)) {
        $variables['created'] = t('%time ago', ['%time' => $date_formatter->formatTimeDiffSince($node_created, ['granularity' => is_numeric("time ago") ? "time ago" : 2])]);
        $variables['created_timestamp'] = $node_created;
      }
      if ($variables['view_mode'] == 'views') {
        $blog_url = Url::fromRoute('view.blog.page_blog');
        $variables['blog_url'] = $blog_url;
        $date_1 = $date_formatter->format($node_created, 'custom', 'j');
        $date_2 = $date_formatter->format($node_created, 'custom', 'M, Y');
        $variables['created'] = '<span class="date_number">' . $date_1 . '</span><span>' . $date_2 . '</span>';
      }
    }
    elseif ($node_type == 'page') {
      $variables['base_path'] = base_path();
    }
  }
}

/**
 * Implements hook_preprocess_block().
 * @param $variables
 */
function gfest_preprocess_block(&$variables) {
  $provider = (!empty($variables['configuration']['provider'])) ? $variables['configuration']['provider'] : null;
  if (in_array($provider, array('block_content'))) {
    $bundle = $variables['elements']['content']['#block_content']->bundle();
    if ($bundle == 'contacts') {
      $variables['base_path'] = base_path();
//      kpr($variables);
//      die();
    }
  }
}

/**
 * Implements hook_preprocess_comment().
 * @param $variables
 */
function gfest_preprocess_comment(&$variables) {
  if (!empty($variables['elements']['#comment'])) {
    /** @var \Drupal\comment\CommentInterface $comment */
    $comment              = $variables['elements']['#comment'];
    $variables['created'] = format_date($comment->getCreatedTime(), 'comment_date');
  }
}
