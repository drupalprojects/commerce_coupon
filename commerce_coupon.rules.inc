<?php

/**
 * @file
 * Rules definitions for Commerce Coupon.
 */

/**
 * Implements hook_rules_action_info().
 */
function commerce_coupon_rules_action_info() {
  $actions['commerce_coupon_discount_get_coupons_list'] = array(
    'label' => t('List of all coupon codes related referencing this discount.'),
    'group' => t('Commerce Coupon'),
    'parameter' => array(
      'commerce_order' => array(
        'type' => 'commerce_order',
        'wrapped' => TRUE,
        'label' => t('Order'),
      ),
      'commerce_discount' => array(
        'label' => t('Commerce Discount'),
        'type' => 'token',
        'options list' => 'commerce_discount_entity_list',
      ),
    ),
    'provides' => array(
      'discount_coupons' => array(
        'type' => 'list<commerce_coupon>',
        'label' => t('List of coupons of this discount'),
        'save' => FALSE,
      ),
    ),
  );
  return $actions;
}

/**
 * Implements hook_rules_condition_info().
 */
function commerce_coupon_rules_condition_info() {
  $conditions['commerce_coupon_discount_coupon_codes_exist_on_order'] = array(
    'label' => t('Coupon code for a particular discount has been added to an order'),
    'group' => t('Commerce Coupon'),
    'parameter' => array(
      'commerce_order' => array(
        'type' => 'commerce_order',
        'wrapped' => TRUE,
        'label' => t('Order'),
      ),
      'commerce_discount' => array(
        'label' => t('Commerce Discount'),
        'type' => 'token',
        'options list' => 'commerce_discount_entity_list',
      ),
    ),
  );

  $conditions['commerce_coupon_evaluate_coupon_inline_conditions_rule'] = array(
    'label' => t('Coupon inline conditions pass'),
    'group' => t('Commerce Coupon'),
    'parameter' => array(
      'commerce_coupon' => array(
        'type' => 'commerce_coupon',
        'label' => t('Coupon'),
        'wrapped' => TRUE,
      ),
      'continuous_only' => array(
        'type' => 'boolean',
        'label' => t('Evaluate only continuous coupon conditions'),
        'optional' => TRUE,
      ),
    ),
  );

  $conditions['commerce_coupon_current_user_may_redeem'] = array(
    'label' => t('Current user may redeem coupon'),
    'group' => t('Commerce Coupon'),
    'parameter' => array(
      'commerce_coupon' => array(
        'type' => 'commerce_coupon',
        'label' => t('Coupon'),
        'wrapped' => TRUE,
      ),
      'commerce_order' => array(
        'type' => 'commerce_order',
        'label' => t('Order'),
        'wrapped' => TRUE,
      ),
    ),
  );

  return $conditions;
}

/**
 * Implements hook_rules_event_info().
 */
function commerce_coupon_rules_event_info() {
  $events['commerce_coupon_applied_to_cart'] = array(
    'label' => t('User has applied a coupon to a cart order'),
    'group' => t('Commerce Coupon'),
    'variables' => array(
      'commerce_coupon' => array(
        'type' => 'commerce_coupon',
        'label' => t('Coupon'),
      ),
      'commerce_order' => array(
        'type' => 'commerce_order',
        'label' => t('Order'),
      ),
    ),
  );

  return $events;
}

/**
 * Rules condition callback: evaluate a coupon's inline conditions.
 */
function commerce_coupon_evaluate_coupon_inline_conditions_rule($coupon_wrapper, $continuous_only = FALSE) {
  return commerce_coupon_evaluate_inline_conditions($coupon_wrapper, $continuous_only);
}

/**
 * Rules condition callback.
 *
 * Evaluate whether the current user has the required permissions to redeem a
 * coupon.
 */
function commerce_coupon_current_user_may_redeem($coupon_wrapper) {
  $coupon = $coupon_wrapper->value();
  return commerce_coupon_access('redeem', $coupon);
}

/**
 * Fetches the coupons related to a discount from an order.
 *
 * If the bool parameter is set the function will return TRUE if there are any
 * valid coupons for the discount on the order.
 *
 * @param EntityMetadataWrapper $order_wrapper
 *   The wrapped order.
 * @param string $discount_name
 *   The discount name to look for.
 * @param bool $bool
 *   Whether or not to return just a boolean to indicate that there's a valid
 *   coupon for the discount on the order.
 *
 * @return array|bool
 *   By default a list of valid coupons on the order for the discount is
 *   returned. But If the bool parameter is set the function will return a
 *   boolean to indicate if there are any valid coupons on the order.
 */
function commerce_coupon_discount_extract_coupons($order_wrapper, $discount_name, $bool = FALSE) {
  $discount_coupons = array();
  // Create list of coupons related to this discount if the condition matches.
  $discount_wrapper = entity_metadata_wrapper('commerce_discount', $discount_name);

  // It is possible for the order to be null. This happens if we are dealing
  // with a dummy line item created just to run pricing rules. In this case we
  // do not let the discount proceed.
  if (!$order_wrapper->value() || !$discount_wrapper->value() || !commerce_coupon_order_allows_coupons($order_wrapper->value())) {
    if ($bool) {
      return FALSE;
    }
    return $discount_coupons;
  }

  // Determine if this discount uses coupons. If not, this condition passes.
  if (!$discount_wrapper->coupon_count->value()) {
    if ($bool) {
      return TRUE;
    }
    return $discount_coupons;
  }

  if ($order_wrapper->commerce_coupons->value()) {
    foreach ($order_wrapper->commerce_coupons as $coupon_wrapper) {
      if (!$coupon_wrapper->value()) {
        continue;
      }

      $code = $coupon_wrapper->code->value();
      $discount_id = $discount_wrapper->discount_id->value();

      // The condition passes if the code grants the discount being looked at,
      // and if the coupon-specific conditions pass.
      if (commerce_coupon_code_grants_discount($code, $discount_id) && commerce_coupon_evaluate_conditions($coupon_wrapper, $order_wrapper)) {
        $discount_coupons[] = $coupon_wrapper->getIdentifier();
        if ($bool) {
          return TRUE;
        }
      }
    }
  }
  if ($bool) {
    return FALSE;
  }
  return $discount_coupons;
}

/**
 * Assert the list of coupons related to this discount.
 */
function commerce_coupon_discount_get_coupons_list($order_wrapper, $discount_name) {
  return array('discount_coupons' => commerce_coupon_discount_extract_coupons($order_wrapper, $discount_name));
}

/**
 * Rules condition callback.
 *
 * Determine whether a coupon code attached to a particular discount has been
 * saved on an order.
 */
function commerce_coupon_discount_coupon_codes_exist_on_order($order_wrapper, $discount_name) {
  return commerce_coupon_discount_extract_coupons($order_wrapper, $discount_name, TRUE);
}

