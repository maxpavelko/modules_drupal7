<?php

/**
 * Implements hook_views_data_alter().
 *   This is because commerce_line_item uses hook_views_data() so we have
 *   to extend it.
 */
function yg_wishlist_views_data_alter(&$data) {
  $data['commerce_wishlist']['w_store_id'] = array(
    'title' => t('Wishlist Store ID'),
    'help' => t('The two letter store ID associated with wishlist item.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_field',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
}
