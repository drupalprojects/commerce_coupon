<?php

/*
 * Implements hook_default_rules_configuration().
 */
function commerce_coupon_default_rules_configuration() {
  $rules = array();

  $rule = rules_reaction_rule();
  $rule->label = t('Coupon applied to cart success message');
  $rule->tags = array('Commerce Coupon');

  $rule
    ->event('commerce_coupon_applied_to_cart')
    ->action('drupal_message', array(
      'message' => t('Coupon code applied.'),
    ));

  $rules['coupon_cart_sucess_message'] = $rule;

  foreach (commerce_coupon_get_types() as $machine_name => $type) {
    $component_parameter = array(
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
      'data' => array(
        'type' => 'list<list>',
        'label' => t('Data'),
        'optional' => TRUE
      )
    );

    $rule = rules_and($component_parameter);
    $rule->label = t('Conditions for @type coupons', array('@type' => $type['label']));
    $rule->tags = array('Commerce Coupon');

    // Add default conditions to all coupon types.
    $rule
      // Coupon must be active.
      ->condition('data_is', array(
        'data:select' => 'commerce-coupon:status',
        'op' => '==',
        'value' => '1',
      ))
      // Inline conditions must pass.
      ->condition('commerce_coupon_evaluate_coupon_inline_conditions_rule', array(
        'commerce_coupon:select' => 'commerce_coupon'
      ))
      // Permissions for "redeeem" must pass.
      ->condition('commerce_coupon_current_user_may_redeem', array(
        'commerce_coupon:select' => 'commerce_coupon'
      ));
/*
    if ($machine_name == 'discount_coupon') {
      $rule
        // In case the coupon is free shipping, the shipping rules must pass for
        // the current order.
        ->condition('commerce_coupon_check_free_shipping_conditions', array(
          'commerce_coupon:select' => 'commerce_coupon',
          'commerce_order:select' => 'commerce_order'
        ));
    }*/

    // Allow other modules to alter the rule.
    drupal_alter('commerce_coupon_condition_component', $rule, $machine_name);

    $rules[commerce_coupon_conditions_component_name($machine_name)] = $rule;
  }

  return $rules;
}
