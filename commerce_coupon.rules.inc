<?php

/*
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
        'label' => t('Order')
      ),
      'commerce_discount' => array(
        'label' => t('Commerce Discount'),
        'type' => 'token',
        'options list' => 'commerce_discount_entity_list',
      )
    )
  );
  
  $conditions['commerce_coupon_evaluate_coupon_inline_conditions_rule'] = array(
    'label' => t('Coupon inline conditions pass'),
    'group' => t('Commerce Coupon'),
    'parameter' => array(
      'commerce_coupon' => array(
        'type' => 'commerce_coupon',
        'label' => t('Coupon'),
        'wrapped' => TRUE
      ),
      'continuous_only' => array(
        'type' => 'boolean',
        'label' => t('Evaluate only continuous coupon conditions'),      
        'optional' => TRUE
      )
    )
  );  

  return $conditions;
}

/*
 * Implements hook_rules_action_info().
 */
function commerce_coupon_rules_action_info() {
  $actions['commerce_coupon_add_coupon_to_order'] = array(
    'label' => t('Add coupon to order'),
    'group' => t('Commerce Coupon'),
    'parameter' => array(
      'commerce_coupon' => array(
        'type' => 'commerce_coupon',
        'label' => t('Coupon'),
        'wrapped' => TRUE  
      ),
      'commerce_order' => array(
        'type' => 'commerce_order',
        'label' => t('Order'),
        'wrapped' => TRUE          
      ),
    )
  );
  
  return $actions;
}

/*
 * Implements hook_rules_event_info().
 */
function commerce_coupon_rules_event_info() {
  $events['commerce_coupon_redeem'] = array(
    'label' => t('User redeems a coupon during checkout'),
    'group' => t('Commerce Coupon'),
    'variables' => array(
      'commerce_coupon' => array(
        'type' => 'commerce_coupon',
        'label' => t('Coupon'),
        'wrapped' => TRUE
      ),        
      // Skip-save is set because we need to force the order to save immediately
      // so the checkout pane can load it when it embeds the view.
      'commerce_order' => array(
        'type' => 'commerce_order',
        'label' => t('Order'),
        'wrapped' => TRUE,
        'skip save' => TRUE
      ),
    )
  );
  
  return $events;
}

/*
 * Rules condition callback: evaluate a coupon's inline conditions.
 */
function commerce_coupon_evaluate_coupon_inline_conditions_rule($coupon_wrapper, $continuous_only = FALSE) {
  return commerce_coupon_evaluate_inline_conditions($coupon_wrapper, $continuous_only);
}

/*
 * Rules condition callback: determine whether a coupon code attached to a
 * particular discount has been saved on an order.
 */
function commerce_coupon_discount_coupon_codes_exist_on_order($order_wrapper, $discount_name) {
  $discount_wrapper = entity_metadata_wrapper('commerce_discount', $discount_name);
  
  // It is possible for the order to be null. This happens if we are dealing
  // with a dummy line item created just to run pricing rules. In this case we
  // do not let the discount proceed.
  if (!$order_wrapper->value() || !$discount_wrapper->value()) {
    return; 
  }
  
  // Determine if this discount uses coupons.
  $has_coupons = $discount_wrapper->coupon_count->value();
  
  if ($order_wrapper->commerce_coupons->value()) {
    // At least one of the coupon codes granting this discount must be 1) active
    // and 2) pass its inline conditions.
    foreach ($order_wrapper->commerce_coupons as $coupon_wrapper) {
      if (commerce_coupon_code_grants_discount($coupon_wrapper->code->value(), $discount_wrapper->discount_id->value())) {
        $has_coupons = TRUE;
        $outcome = FALSE;
        
        if (commerce_coupon_evaluate_inline_conditions($coupon_wrapper, TRUE) && commerce_coupon_access('redeem', $coupon_wrapper->value())) {
          $outcome = TRUE;
        }
        
        // Allow other modules to set validity.
        drupal_alter('commerce_coupon_coupon_still_valid', $outcome, $order_wrapper, $coupon_wrapper);
        
        if ($outcome) {
          return TRUE;
        }
      }
    }
  }
  
  // If no valid coupons were found, return FALSE if the discount is linked to
  // any coupons.
  return !$has_coupons;
}

/*
 * Rules action callback: add a coupon to an order
 */
function commerce_coupon_add_coupon_to_order($coupon_wrapper, $order_wrapper) {
  // Add the coupon to the order.
  $order_wrapper->commerce_coupons[] = $coupon_wrapper->value();
    
  commerce_order_save($order_wrapper->value());
}
