<?php

/**
 * @file
 * Basic coupon default rules.
 */

/**
 * Implements hook_default_rules_configuration().
 */
function commerce_coupon_basic_default_rules_configuration() {
  $rules = array();

  $rule = rules_reaction_rule();
  $rule->label = t('Apply percentage coupons to line item');
  $rule->active = TRUE;

  $rule
    ->event('commerce_product_calculate_sell_price')
    ->action('commerce_coupon_action_get_coupons_for_order', array(
      'commerce_order:select' => 'commerce-line-item:order',
      'order_coupons:label' => 'Coupons attached to this order',
      'order_coupons:var' => 'order_coupons',
    ));

  $loop = rules_loop(array(
    'list:select' => 'order-coupons',
    'item:var' => 'list_item',
    'item:label' => t('Current list item'),
  ))
    ->action('commerce_coupon_basic_apply_to_item_line', array(
      'line_item:select' => 'commerce-line-item',
      'coupon:select' => 'list-item',
      'component_name' => 'base_price',
      'round_mode' => '1',
    ));

  $rule->action($loop);

  $rules['commerce_coupon_basic_apply_percentage_coupons_to_line_item'] = $rule;

  // Create fixed amount rule
  $rule = rules_reaction_rule(array(), array(
    'commerce_coupon_line_item' => array(
      'type' => 'commerce_coupon_line_item',
      'label' => 'commerce coupon line item')
    )
  );

  $rule->label = t('Calculate coupon with fixed amount');
  $rule->active = TRUE;

  $rule
  ->event('commerce_coupon_redeem')
  ->condition('entity_has_field', array('entity:select' => 'coupon', 'field' => 'commerce_coupon_fixed_amount'))
  ->condition(rules_and()->condition('data_is_empty', array('data:select' => 'coupon:commerce-coupon-fixed-amount'))->negate() )
  ->condition('data_is', array('data:select' => 'coupon:commerce-coupon-fixed-amount:amount', 'op' => '>', 'value' => 0))
  ->action('commerce_coupon_action_create_coupon_line_item', array(
    'commerce_coupon:select' => 'coupon',
    'commerce_order:select' => 'commerce-order',
    'amount:select' => 'coupon:commerce-coupon-fixed-amount:amount',
    'currency_code:select' => 'coupon:commerce-coupon-fixed-amount:currency-code'
  ))
  ->action('commerce_coupon_action_set_granted_amount', array(
    'commerce_coupon_log:select' => 'coupon-log',
    'amount:select' => 'coupon:commerce-coupon-fixed-amount:amount',
    'currency_code:select' => 'coupon:commerce-coupon-fixed-amount:currency-code'
  ));

  $rules['commerce_coupon_basic_fixed_amount'] = $rule;


  // Add validation rule component to check the number of uses of a coupon
  $rule = rule(array(
    'commerce_coupon' => array(
      'type' => 'commerce_coupon',
      'label' => t('Coupon'),
    ),
    'number_of_redemptions' => array(
      'type' => 'integer',
      'label' => t('Number Of Redemptions'),
    ),
  ));

  $rule->label = t('Coupon Validation: Set the coupon as invalid if number of uses is reached');

  $rule
  ->condition('entity_has_field', array('entity:select' => 'commerce_coupon', 'field' => 'commerce_coupon_number_of_uses'))
  ->condition(rules_and()->condition(
      rules_or()->condition('data_is', array('data:select' => 'commerce_coupon:commerce-coupon-number-of-uses', 'op' => '<', 'value:select' => 'number-of-redemptions'))
      ->condition('data_is', array('data:select' => 'commerce_coupon:commerce-coupon-number-of-uses', 'value:select' => 'number-of-redemptions'))
    )
  );

  $rule->action('drupal_message', array(
    'message' => 'Sorry, the maximum number of redemptions for this coupon has been reached.',
    'type' => 'error',
  ));

  $rule->action('commerce_coupon_action_is_invalid_coupon', array());
  $rules['commerce_coupon_basic_validate_uses_of_coupon_component'] = $rule;

  // Reaction on the validation event for check uses of coupons:
  $rule = rules_reaction_rule();
  $rule->label = t('Coupon Validation: Check the number of redemptions');
  $rule->active = TRUE;

  $rule
  ->event('commerce_coupon_validate')
  ->condition('entity_has_field', array('entity:select' => 'coupon', 'field' => 'commerce_coupon_number_of_uses'))
  ->action('commerce_coupon_action_get_coupon_uses', array('commerce_coupon:select' => 'coupon'))
  ->action('component_commerce_coupon_basic_validate_uses_of_coupon_component', array(
    'commerce_coupon:select' => 'coupon',
    'number_of_redemptions:select' => 'number-of-uses'
  ));

  $rules['commerce_coupon_basic_validate_uses_of_coupon'] = $rule;

  return $rules;
}
