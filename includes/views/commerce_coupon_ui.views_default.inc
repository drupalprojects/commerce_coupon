<?php

/**
 * Views for the default order UI.
 */

/**
 * Implements hook_views_default_views().
 */
function commerce_coupon_ui_views_default_views() {
  $views = array();

  // Coupon admin list at admin/commerce/coupons.
  $view = new view;
  $view->name = 'commerce_coupons';
  $view->description = 'Display a list of coupons for the store admin.';
  $view->tag = 'commerce';
  $view->base_table = 'commerce_coupon';
  $view->human_name = 'Coupons';
  $view->core = 7;
  $view->api_version = '3.0-alpha1';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Coupons';
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
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
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  $handler->display->display_options['style_options']['empty_table'] = 0;
  /* Field: Commerce Coupon: Coupon Code */
  $handler->display->display_options['fields']['commerce_coupon_code']['id'] = 'commerce_coupon_code';
  $handler->display->display_options['fields']['commerce_coupon_code']['table'] = 'field_data_commerce_coupon_code';
  $handler->display->display_options['fields']['commerce_coupon_code']['field'] = 'commerce_coupon_code';
  $handler->display->display_options['fields']['commerce_coupon_code']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['commerce_coupon_code']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['commerce_coupon_code']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['commerce_coupon_code']['alter']['external'] = 0;
  $handler->display->display_options['fields']['commerce_coupon_code']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['commerce_coupon_code']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['commerce_coupon_code']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['commerce_coupon_code']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['commerce_coupon_code']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['commerce_coupon_code']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['commerce_coupon_code']['alter']['html'] = 0;
  $handler->display->display_options['fields']['commerce_coupon_code']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['commerce_coupon_code']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['commerce_coupon_code']['hide_empty'] = 0;
  $handler->display->display_options['fields']['commerce_coupon_code']['empty_zero'] = 0;
  $handler->display->display_options['fields']['commerce_coupon_code']['field_api_classes'] = 0;
  /* Field: Commerce Coupon: Type */
  $handler->display->display_options['fields']['type']['id'] = 'type';
  $handler->display->display_options['fields']['type']['table'] = 'commerce_coupon';
  $handler->display->display_options['fields']['type']['field'] = 'type';
  $handler->display->display_options['fields']['type']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['type']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['type']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['type']['alter']['external'] = 0;
  $handler->display->display_options['fields']['type']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['type']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['type']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['type']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['type']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['type']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['type']['alter']['html'] = 0;
  $handler->display->display_options['fields']['type']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['type']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['type']['hide_empty'] = 0;
  $handler->display->display_options['fields']['type']['empty_zero'] = 0;
  /* Field: Commerce Coupon: Operations links */
  $handler->display->display_options['fields']['operations']['id'] = 'operations';
  $handler->display->display_options['fields']['operations']['table'] = 'commerce_coupon';
  $handler->display->display_options['fields']['operations']['field'] = 'operations';
  $handler->display->display_options['fields']['operations']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['external'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['operations']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['operations']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['html'] = 0;
  $handler->display->display_options['fields']['operations']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['operations']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['operations']['hide_empty'] = 0;
  $handler->display->display_options['fields']['operations']['empty_zero'] = 0;

  /* Display: Adminpage */
  $handler = $view->new_display('page', 'Adminpage', 'page');
  $handler->display->display_options['display_description'] = 'Manage the coupons.';
  $handler->display->display_options['path'] = 'admin/commerce/coupons/list';
  $handler->display->display_options['menu']['type'] = 'default tab';
  $handler->display->display_options['menu']['title'] = 'Coupons';
  $handler->display->display_options['menu']['weight'] = '-14';
  $handler->display->display_options['tab_options']['type'] = 'normal';
  $handler->display->display_options['tab_options']['title'] = 'Coupons';
  $handler->display->display_options['tab_options']['description'] = 'Manage coupons in the store.';
  $handler->display->display_options['tab_options']['weight'] = '';
  $handler->display->display_options['tab_options']['name'] = 'management';
  $translatables['commerce_coupons'] = array(
    t('Master'),
    t('Coupons'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('Coupon Code'),
    t('Type'),
    t('Operations links'),
    t('Adminpage'),
    t('Manage the coupons.'),
  );
  $views[$view->name] = $view;

  $view = new view;
  $view->name = 'commerce_coupon_review_pane';
  $view->description = '';
  $view->tag = 'commerce';
  $view->base_table = 'commerce_coupon_log';
  $view->human_name = 'Commerce Coupon Review Pane';
  $view->core = 7;
  $view->api_version = '3.0-alpha1';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
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
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  $handler->display->display_options['style_options']['empty_table'] = 0;
  /* Relationship: Commerce Coupon Log: Coupon_id */
  $handler->display->display_options['relationships']['coupon_id']['id'] = 'coupon_id';
  $handler->display->display_options['relationships']['coupon_id']['table'] = 'commerce_coupon_log';
  $handler->display->display_options['relationships']['coupon_id']['field'] = 'coupon_id';
  $handler->display->display_options['relationships']['coupon_id']['required'] = 1;
  /* Field: Commerce Coupon: Coupon Code */
  $handler->display->display_options['fields']['commerce_coupon_code']['id'] = 'commerce_coupon_code';
  $handler->display->display_options['fields']['commerce_coupon_code']['table'] = 'field_data_commerce_coupon_code';
  $handler->display->display_options['fields']['commerce_coupon_code']['field'] = 'commerce_coupon_code';
  $handler->display->display_options['fields']['commerce_coupon_code']['relationship'] = 'coupon_id';
  $handler->display->display_options['fields']['commerce_coupon_code']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['commerce_coupon_code']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['commerce_coupon_code']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['commerce_coupon_code']['alter']['external'] = 0;
  $handler->display->display_options['fields']['commerce_coupon_code']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['commerce_coupon_code']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['commerce_coupon_code']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['commerce_coupon_code']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['commerce_coupon_code']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['commerce_coupon_code']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['commerce_coupon_code']['alter']['html'] = 0;
  $handler->display->display_options['fields']['commerce_coupon_code']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['commerce_coupon_code']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['commerce_coupon_code']['hide_empty'] = 0;
  $handler->display->display_options['fields']['commerce_coupon_code']['empty_zero'] = 0;
  $handler->display->display_options['fields']['commerce_coupon_code']['field_api_classes'] = 0;
  /* Field: Commerce Coupon Log: Coupon Granted Amount */
  $handler->display->display_options['fields']['commerce_granted_amount']['id'] = 'commerce_granted_amount';
  $handler->display->display_options['fields']['commerce_granted_amount']['table'] = 'field_data_commerce_granted_amount';
  $handler->display->display_options['fields']['commerce_granted_amount']['field'] = 'commerce_granted_amount';
  $handler->display->display_options['fields']['commerce_granted_amount']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['commerce_granted_amount']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['commerce_granted_amount']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['commerce_granted_amount']['alter']['external'] = 0;
  $handler->display->display_options['fields']['commerce_granted_amount']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['commerce_granted_amount']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['commerce_granted_amount']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['commerce_granted_amount']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['commerce_granted_amount']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['commerce_granted_amount']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['commerce_granted_amount']['alter']['html'] = 0;
  $handler->display->display_options['fields']['commerce_granted_amount']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['commerce_granted_amount']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['commerce_granted_amount']['hide_empty'] = 0;
  $handler->display->display_options['fields']['commerce_granted_amount']['empty_zero'] = 0;
  $handler->display->display_options['fields']['commerce_granted_amount']['click_sort_column'] = 'amount';
  $handler->display->display_options['fields']['commerce_granted_amount']['type'] = 'commerce_price_formatted_amount';
  $handler->display->display_options['fields']['commerce_granted_amount']['settings'] = array(
    'calculation' => FALSE,
  );
  $handler->display->display_options['fields']['commerce_granted_amount']['field_api_classes'] = 0;
  /* Contextual filter: Commerce Coupon Log: Order_id */
  $handler->display->display_options['arguments']['order_id']['id'] = 'order_id';
  $handler->display->display_options['arguments']['order_id']['table'] = 'commerce_coupon_log';
  $handler->display->display_options['arguments']['order_id']['field'] = 'order_id';
  $handler->display->display_options['arguments']['order_id']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['order_id']['exception']['value'] = '';
  $handler->display->display_options['arguments']['order_id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['order_id']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['order_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['order_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['order_id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['order_id']['specify_validation'] = 1;
  $handler->display->display_options['arguments']['order_id']['validate']['type'] = 'numeric';
  $handler->display->display_options['arguments']['order_id']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['order_id']['not'] = 0;
  $translatables['commerce_coupon_review_pane'] = array(
    t('Master'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Commerce Coupon'),
    t('Coupon Code'),
    t('Coupon Granted Amount'),
    t('All'),
  );


  $views[$view->name] = $view;

  return $views;
}
