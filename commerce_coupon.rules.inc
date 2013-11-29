<?php

/*
 * Implements hook_rules_condition_info().
 */
function commerce_coupon_rules_condition_info() {
  $conditions['commerce_coupon_discount_coupon_codes_exist_on_order'] = array(
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
function commerce_coupon_discount_coupon_codes_exist_on_order($order_wrapper, $discount_name) {
  // It is possible for the order to be null. This happens if we are dealing
  // with a dummy line item created just to run pricing rules. In this case we
  // do not let the discount proceed.
  if (!$order_wrapper->value()) {
    return; 
  }
  
  $has_coupons = FALSE;  
  $discount_wrapper = entity_metadata_wrapper('commerce_discount', $discount_name);
  
  if ($discount_wrapper->value() && $order_wrapper->commerce_coupons->value()) {
    // At least one of the coupon codes granting this discount must be 1) active
    // and 2) pass its inline conditions.
    foreach ($order_wrapper->commerce_coupons as $coupon_wrapper) {
      if (commerce_coupon_code_grants_discount($coupon_wrapper->code->value(), $discount_wrapper->discount_id->value())) {
        $has_coupons = TRUE;
        
        if (commerce_coupon_evaluate_inline_conditions($coupon_wrapper, 'post_redeem')) {
          return TRUE;
        }
      }
    }
  }
  
  // If no valid coupons were found, return FALSE if the discount is linked to
  // any coupons.
  return !$has_coupons;
}
