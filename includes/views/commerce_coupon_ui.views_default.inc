<?php

/**
 * @file
 * Coupon..
 *
 * Views for the default order UI.
 */

/**
 * Implements hook_views_default_views().
 */
function commerce_coupon_ui_views_default_views() {
  $views = array();

  // Coupon admin list at admin/commerce/coupons.
  $view = new view();
  $view->name = 'commerce_coupons';
  $view->description = 'Display a list of coupons for the store admin.';
  $view->tag = 'commerce';
  $view->base_table = 'commerce_coupon';
  $view->human_name = 'Coupons';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Coupons';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer coupons';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '50';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'coupon_id' => 'coupon_id',
    'commerce_coupon_code' => 'commerce_coupon_code',
    'type' => 'type',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'coupon_id' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'commerce_coupon_code' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'type' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
  );
  /* Relationship: Commerce Coupon: Type */
  $handler->display->display_options['relationships']['type']['id'] = 'type';
  $handler->display->display_options['relationships']['type']['table'] = 'commerce_coupon';
  $handler->display->display_options['relationships']['type']['field'] = 'type';
  $handler->display->display_options['relationships']['type']['required'] = TRUE;
  /* Field: Commerce Coupon: Coupon Code */
  $handler->display->display_options['fields']['commerce_coupon_code']['id'] = 'commerce_coupon_code';
  $handler->display->display_options['fields']['commerce_coupon_code']['table'] = 'field_data_commerce_coupon_code';
  $handler->display->display_options['fields']['commerce_coupon_code']['field'] = 'commerce_coupon_code';
  /* Field: Commerce Coupon: Type */
  $handler->display->display_options['fields']['type']['id'] = 'type';
  $handler->display->display_options['fields']['type']['table'] = 'commerce_coupon';
  $handler->display->display_options['fields']['type']['field'] = 'type';
  /* Field: Commerce Coupon: Operations */
  $handler->display->display_options['fields']['operations']['id'] = 'operations';
  $handler->display->display_options['fields']['operations']['table'] = 'commerce_coupon';
  $handler->display->display_options['fields']['operations']['field'] = 'operations';
  /* Field: Commerce Coupon: Is active */
  $handler->display->display_options['fields']['is_active']['id'] = 'is_active';
  $handler->display->display_options['fields']['is_active']['table'] = 'commerce_coupon';
  $handler->display->display_options['fields']['is_active']['field'] = 'is_active';
  $handler->display->display_options['fields']['is_active']['label'] = 'Active';
  $handler->display->display_options['fields']['is_active']['type'] = 'unicode-yes-no';
  $handler->display->display_options['fields']['is_active']['not'] = 0;
  /* Filter criterion: Commerce Coupon Type: Coupon type status */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'commerce_coupon_type';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['relationship'] = 'type';
  $handler->display->display_options['filters']['status']['value'] = '1';

  /* Display: Admin page */
  $handler = $view->new_display('page', 'Admin page', 'page');
  $handler->display->display_options['display_description'] = 'Manage the coupons.';
  $handler->display->display_options['path'] = 'admin/commerce/coupons/list';
  $handler->display->display_options['menu']['type'] = 'default tab';
  $handler->display->display_options['menu']['title'] = 'List';
  $handler->display->display_options['menu']['weight'] = '-10';
  $handler->display->display_options['tab_options']['type'] = 'normal';
  $handler->display->display_options['tab_options']['title'] = 'Coupons';
  $handler->display->display_options['tab_options']['description'] = 'Manage coupons in the store.';
  $handler->display->display_options['tab_options']['weight'] = '';
  $handler->display->display_options['tab_options']['name'] = 'management';

  $views[$view->name] = $view;

  // Coupon log admin view.
  $view = new view();
  $view->name = 'commerce_coupon_review_pane';
  $view->description = '';
  $view->tag = 'commerce';
  $view->base_table = 'commerce_coupon_log';
  $view->human_name = 'Commerce Coupon Review Pane';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['query']['options']['query_tags'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'log_id' => 'log_id',
    'code' => 'code',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'log_id' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'code' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
  );
  /* Relationship: Commerce Coupon Log: Order order_id */
  $handler->display->display_options['relationships']['order']['id'] = 'order';
  $handler->display->display_options['relationships']['order']['table'] = 'commerce_coupon_log';
  $handler->display->display_options['relationships']['order']['field'] = 'order';
  $handler->display->display_options['relationships']['order']['required'] = TRUE;
  /* Relationship: Commerce Coupon Log: Coupon coupon_id */
  $handler->display->display_options['relationships']['commerce_coupon']['id'] = 'commerce_coupon';
  $handler->display->display_options['relationships']['commerce_coupon']['table'] = 'commerce_coupon_log';
  $handler->display->display_options['relationships']['commerce_coupon']['field'] = 'commerce_coupon';
  /* Field: Commerce Coupon: Coupon Code */
  $handler->display->display_options['fields']['commerce_coupon_code']['id'] = 'commerce_coupon_code';
  $handler->display->display_options['fields']['commerce_coupon_code']['table'] = 'field_data_commerce_coupon_code';
  $handler->display->display_options['fields']['commerce_coupon_code']['field'] = 'commerce_coupon_code';
  $handler->display->display_options['fields']['commerce_coupon_code']['relationship'] = 'commerce_coupon';
  /* Field: Commerce Coupon Log: Coupon Granted Amount */
  $handler->display->display_options['fields']['commerce_granted_amount']['id'] = 'commerce_granted_amount';
  $handler->display->display_options['fields']['commerce_granted_amount']['table'] = 'field_data_commerce_granted_amount';
  $handler->display->display_options['fields']['commerce_granted_amount']['field'] = 'commerce_granted_amount';
  $handler->display->display_options['fields']['commerce_granted_amount']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['commerce_granted_amount']['click_sort_column'] = 'amount';
  $handler->display->display_options['fields']['commerce_granted_amount']['type'] = 'commerce_price_formatted_amount';
  $handler->display->display_options['fields']['commerce_granted_amount']['settings'] = array(
    'calculation' => FALSE,
  );
  /* Contextual filter: Commerce Order: Order ID */
  $handler->display->display_options['arguments']['order_id']['id'] = 'order_id';
  $handler->display->display_options['arguments']['order_id']['table'] = 'commerce_order';
  $handler->display->display_options['arguments']['order_id']['field'] = 'order_id';
  $handler->display->display_options['arguments']['order_id']['relationship'] = 'order';
  $handler->display->display_options['arguments']['order_id']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['order_id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['order_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['order_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['order_id']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Commerce Coupon: Is active */
  $handler->display->display_options['filters']['is_active']['id'] = 'is_active';
  $handler->display->display_options['filters']['is_active']['table'] = 'commerce_coupon';
  $handler->display->display_options['filters']['is_active']['field'] = 'is_active';
  $handler->display->display_options['filters']['is_active']['relationship'] = 'commerce_coupon';
  $handler->display->display_options['filters']['is_active']['value'] = '1';

  $views[$view->name] = $view;

  // Coupon log
  $view = new view();
  $view->name = 'commerce_coupon_log';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'commerce_coupon_log';
  $view->human_name = 'Commerce Coupon Log';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Coupon log';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer coupons';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['query']['options']['query_tags'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '25';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'created' => 'created',
    'commerce_coupon_code' => 'commerce_coupon_code',
    'commerce_coupon_number_of_uses' => 'commerce_coupon_number_of_uses',
    'commerce_granted_amount' => 'commerce_granted_amount',
    'is_accepted' => 'is_accepted',
    'view_order' => 'view_order',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'created' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'commerce_coupon_code' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'commerce_coupon_number_of_uses' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'commerce_granted_amount' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'is_accepted' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'view_order' => array(
      'align' => '',
      'separator' => '',
    ),
  );
  /* Relationship: Commerce Coupon Log: Order order_id */
  $handler->display->display_options['relationships']['order']['id'] = 'order';
  $handler->display->display_options['relationships']['order']['table'] = 'commerce_coupon_log';
  $handler->display->display_options['relationships']['order']['field'] = 'order';
  $handler->display->display_options['relationships']['order']['required'] = TRUE;
  /* Relationship: Commerce Coupon Log: Coupon coupon_id */
  $handler->display->display_options['relationships']['commerce_coupon']['id'] = 'commerce_coupon';
  $handler->display->display_options['relationships']['commerce_coupon']['table'] = 'commerce_coupon_log';
  $handler->display->display_options['relationships']['commerce_coupon']['field'] = 'commerce_coupon';
  $handler->display->display_options['relationships']['commerce_coupon']['required'] = TRUE;
  /* Field: Commerce Coupon: Coupon Code */
  $handler->display->display_options['fields']['commerce_coupon_code']['id'] = 'commerce_coupon_code';
  $handler->display->display_options['fields']['commerce_coupon_code']['table'] = 'field_data_commerce_coupon_code';
  $handler->display->display_options['fields']['commerce_coupon_code']['field'] = 'commerce_coupon_code';
  $handler->display->display_options['fields']['commerce_coupon_code']['relationship'] = 'commerce_coupon';
  /* Field: Commerce Coupon: Type */
  $handler->display->display_options['fields']['type']['id'] = 'type';
  $handler->display->display_options['fields']['type']['table'] = 'commerce_coupon';
  $handler->display->display_options['fields']['type']['field'] = 'type';
  $handler->display->display_options['fields']['type']['relationship'] = 'commerce_coupon';
  /* Field: Commerce Coupon Log: Creation date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'commerce_coupon_log';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  /* Field: Commerce Coupon Log: Coupon Granted Amount */
  $handler->display->display_options['fields']['commerce_granted_amount']['id'] = 'commerce_granted_amount';
  $handler->display->display_options['fields']['commerce_granted_amount']['table'] = 'field_data_commerce_granted_amount';
  $handler->display->display_options['fields']['commerce_granted_amount']['field'] = 'commerce_granted_amount';
  $handler->display->display_options['fields']['commerce_granted_amount']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['commerce_granted_amount']['click_sort_column'] = 'amount';
  $handler->display->display_options['fields']['commerce_granted_amount']['type'] = 'commerce_price_formatted_amount';
  $handler->display->display_options['fields']['commerce_granted_amount']['settings'] = array(
    'calculation' => FALSE,
  );
  /* Field: Commerce Order: Link */
  $handler->display->display_options['fields']['view_order']['id'] = 'view_order';
  $handler->display->display_options['fields']['view_order']['table'] = 'commerce_order';
  $handler->display->display_options['fields']['view_order']['field'] = 'view_order';
  $handler->display->display_options['fields']['view_order']['relationship'] = 'order';
  $handler->display->display_options['fields']['view_order']['label'] = 'Order';
  /* Sort criterion: Commerce Coupon Log: Creation date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'commerce_coupon_log';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/commerce/coupons/coupon-log';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Coupon log';
  $handler->display->display_options['menu']['weight'] = '0';

  $views[$view->name] = $view;

  return $views;
}
