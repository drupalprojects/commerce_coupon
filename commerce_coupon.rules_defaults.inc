<?php

/**
 * @file
 * Defines default tax components and rules.
 */

/**
 * Implements hook_default_rules_configuration().
 */
function commerce_coupon_default_rules_configuration() {
  $rules = array();

  foreach(commerce_coupon_get_types() as $type => $coupon_type) {

    // Create a new rules component.
    $rule = rule(commerce_coupon_component_variables());

    $rule->label = t('Calculate @title amount', array('@title' => $coupon_type->label));

    // Add the action to apply the current tax.
    $rule->action('commerce_coupon_apply_to_item_line', array(
      'line_item:select' => 'line-item',
      'coupon:select' => 'coupon',
    ));

    $rules['commerce_coupon_apply_' . $type . '_to_item_line'] = $rule;
    
  }

  // Loop over every tax type and define a pricing rules to calculate taxes of
  // that type.
  foreach(commerce_coupon_get_types() as $type => $coupon_type) {
    // Create a new product pricing rule.
    $rule = rules_reaction_rule();

    $rule->label = t('Calculate coupon amount: @title', array('@title' => $coupon_type->label));
    $rule->active = TRUE;

    // Add the action to invoke every coupon component matching this type.
    $rule
      ->event('commerce_product_calculate_sell_price')
      ->action('commerce_coupon_calculate_percentage_amount', array(
        'line_item:select' => 'line-item',
      )
    );

    $rules['commerce_coupon_calculate_' . $type . '_amount'] = $rule;
  }


  return $rules;
}

/**
 * Returns an array of variables for use in tax rate components.
 */
function commerce_coupon_component_variables() {
  return array(
    'line_item' => array(
      'type' => 'commerce_line_item',
      'label' => t('Line item'),
    ),
    'coupon' => array(
      'type' => 'commerce_coupon',
      'label' => t('Coupon'),
    ), 
  );
}
