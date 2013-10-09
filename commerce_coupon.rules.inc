<?php

/*
 * Implements hook_rules_condition_info().
 */
function commerce_coupon_rules_condition_info() {
  $conditions['commerce_coupon_order_has_discount_coupon_code'] = array(
    'label' => t('Coupon code for a particular discount has been added to an order'),
    'group' => t('Commerce Coupon'),
    'parameter' => array(
      'order' => array(
        'type' => 'commerce_order',
        'wrapped' => TRUE,
        'label' => t('Order')
      ),
      'commerce_discount' => array(
        'label' => t('Commerce Discount'),
        'type' => 'token',
        'options list' => 'commerce_discount_entity_list',
      )
    )
  );

  return $conditions;
}

/*
 * Rules condition callback: determine whether a coupon code attached to a
 * particular discount has been saved on an order.
 */
function commerce_coupon_order_has_discount_coupon_code($order_wrapper, $discount_name) {
  // It is possible for the order to be null. This happens if we are dealing
  // with a dummy line item created just to run pricing rules. In this case we
  // do not let the discount proceed.
  if (!$order_wrapper->value()) {
    return;
  }

  $discount_wrapper = entity_metadata_wrapper('commerce_discount', $discount_name);
  if ($discount_wrapper->coupons->value()) {
    if ($order_wrapper->commerce_coupons->value()) {
      // Return true if any of the discount coupons are on the order.
      return array_intersect($discount_wrapper->coupons->raw(), $order_wrapper->commerce_coupons->raw());
    }
  }
  else {
    // It only gets here if some one deletes/disables a coupon.
    return TRUE;
  }
}
