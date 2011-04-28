<?php

function commerce_coupon_rules_event_info() {
  $events = array();

  $events['commerce_coupon_validate'] = array(
    'label' => t('Validate a coupon'),
    'group' => t('Commerce Coupon'),
    'variables' => array(
      'coupon' => array('type' => 'commerce_coupon', 'label' => t('commerce coupon to validate')),
    ) + commerce_order_rules_event_variables(t('Order', array(), array('context' => 'a drupal commerce order'))),
    'access callback' => 'commerce_order_rules_access',
  );

  $events['commerce_coupon_validated'] = array(
    'label' => t('A coupon is validated'),
    'group' => t('Commerce Coupon'),
    'variables' => array(
      'coupon' => array('type' => 'commerce_coupon', 'label' => t('commerce coupon to validate')),
    ) + commerce_order_rules_event_variables(t('Order', array(), array('context' => 'a drupal commerce order'))),
    'access callback' => 'commerce_order_rules_access',
  );

  return $events;
}




/**
 * Implements hook_rules_action_info().
 */
function commerce_coupon_rules_action_info() {
  $actions = array();

  $actions['commerce_coupon_is_valid'] = array(
    'label' => t('Set coupon as valid'),
    'parameter' => array(
      'override' => array(
        'type' => 'boolean',
        'label' => t('Override'),
        'description' => t('Normaly the validation result is concatenated by an AND operator. Here you can bypass this and set the value to true.'), 
      ),
    ),
    'group' => t('Commerce Coupon'),
    'base' => 'commerce_coupon_valid_action',
    'callbacks' => array(
      'execute' => 'commerce_coupon_action_is_valid_coupon',
    ),
  );

  $actions['commerce_coupon_is_invalid'] = array(
    'label' => t('Set coupon as invalid'),
    'group' => t('Commerce Coupon'),
    'base' => 'commerce_coupon_invalid_action',
    'callbacks' => array(
      'execute' => 'commerce_coupon_action_is_invalid_coupon',
    ),
  );

  $actions['commerce_coupon_apply_to_item_line'] = array(
    'label' => t('Apply a coupon to a line item'),
    'parameter' => array(
      'line_item' => array(
        'type' => 'commerce_line_item',
        'label' => t('Line item'),
      ),
      'coupon' => array(
        'type' => 'commerce_coupon',
        'label' => t('Coupon'),
      ),
    ),
    'group' => t('Commerce Coupon'),
  );

  $actions['commerce_coupon_calculate_percentage_amount'] = array(
    'label' => t('Calculates a percentage coupon amount'),
    'parameter' => array(
      'line_item' => array(
        'type' => 'commerce_line_item',
        'label' => t('Line item'),
      ),
    ),
    'group' => t('Commerce Coupon'),
  );

  return $actions;
}


function commerce_coupon_action_is_valid_coupon($override = false) {
  $validation_results = &drupal_static('commerce_coupon_action_validation_results');
  
  if(isset($validation_results) && $override == false) {
    $validation_results = $validation_results && true;
  }
  else {
    $validation_results[$commerce_coupon->coupon_id] = true;
  }
  
}

function commerce_coupon_action_is_invalid_coupon($commerce_coupon) {
  
  $validation_results = &drupal_static('commerce_coupon_action_validation_results');
  
  $validation_results = false;
  
}

function commerce_coupon_calculate_percentage_amount($line_item) {
  
  $order_id = $line_item->order_id;
  $coupons = commerce_coupon_get_coupons_by_order($order_id);
  $components = rules_get_components(FALSE, 'action');
  
  foreach($coupons as $coupon) {
    $coupon = entity_metadata_wrapper('commerce_coupon', $coupon);
    $component_name = 'commerce_coupon_apply_' . $coupon->type->value() . '_to_item_line';
    
    if($coupon->is_percentage->value() && isset($components[$component_name])) {
      // Invoke it with the line item.
      rules_invoke_component($component_name, $line_item, $coupon);      
    }
    
    
  }
}


function commerce_coupon_apply_to_item_line($line_item, $coupon) {
  
  
  if(!($coupon instanceof EntityMetadataWrapper)) {
    $coupon = entity_metadata_wrapper('commerce_coupon', $coupon);
  }
  
  if($coupon->is_percentage->value()) {
    $line_item_wrapper = entity_metadata_wrapper('commerce_line_item', $line_item);
    
    
    $rate = $coupon->amount->value();
    if($rate > 1) {
      // Ensure that the rate is never bigger then 100%
      $rate = $rate / 100;
    }
    
    // TODO: Ensure that the coupon is only applied once!
      
    // Update the data array with the tax component.
    $line_item_wrapper->commerce_unit_price->data = commerce_price_component_add(
      $line_item_wrapper->commerce_unit_price->value(),
      'commerce_coupon_' . $coupon->type->value(),
      
      // TODO: Replace the calcuation by a callback method of the type
      array(
        'amount' => $line_item_wrapper->commerce_unit_price->amount->value() * $rate * -1,
        'currency_code' => $line_item_wrapper->commerce_unit_price->currency_code->value(),
        'data' => array(
          'coupon' => array(
            'coupon_id' => $coupon->coupon_id->value(),
            'type' => $coupon->type->value(),
            'rate' => $rate,
            'code' => $coupon->code->value(),
          ),
        ),
      ),
      false
    );
    
      
  }  
}





