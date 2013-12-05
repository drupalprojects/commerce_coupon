<?php

/*
 * Implements hook_default_rules_configuration().
 */
function commerce_coupon_default_rules_configuration() {
  $rule = rules_reaction_rule();
  $rule->label = t('Redeem coupon during checkout');
  $rule->tags = array('Commerce Coupon');
  
  $rule
    ->event('commerce_coupon_redeem')
    ->condition('commerce_coupon_evaluate_coupon_inline_conditions_rule', array(
      'commerce_coupon:select' => 'commerce_coupon'
    ))
    ->action('commerce_coupon_add_coupon_to_order', array(
      'commerce_coupon:select' => 'commerce_coupon',
      'commerce_order:select' => 'commerce_order'        
    ))
    ->action('drupal_message', array(
      'message' => t('Coupon code applied'),
      'type' => 'status'
    ));
  
  $rules['redeem_coupon_during_checkout'] = $rule;
  return $rules;
}
