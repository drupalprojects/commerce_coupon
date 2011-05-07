<?php

/**
 * Alter the views data to enable some additional features for coupons in views
 */
function commerce_coupon_views_data_alter(&$data){
  foreach ($data as $table_name => &$table){
    if ($table_name == 'commerce_coupon_log'){
      if (isset($table['coupon_id'])) {
        $table['coupon_id']['relationship'] = array(
          'base' => 'commerce_coupon',
          'handler' => 'views_handler_relationship',
          'label' => t('Commerce Coupon'),
          'base field' => 'coupon_id',
          'field' => 'coupon_id',
        );
      }
      if (isset($table['order_id'])) {
        $table['order_id']['relationship'] = array(
          'base' => 'commerce_order',
          'handler' => 'views_handler_relationship',
          'label' => t('Commerce Order'),
          'base field' => 'order_id',
          'field' => 'order_id',
        );
      }
    }
    if ($table_name == 'commerce_coupon'){
      $table['operations'] = array(
        'field' => array(
          'title' => t('Operations links'),
          'help' => t('Display all the available operations links for the coupon.'),
          'handler' => 'commerce_coupon_handler_field_coupon_operations',
        ),
      );      
      
    }
  }
}
