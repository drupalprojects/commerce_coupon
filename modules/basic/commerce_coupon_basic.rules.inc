<?php

/**
 * @file
 * Rules integration for the Basic coupon module.
 */

/**
 * Implements hook_rules_action_info().
 */
function commerce_coupon_basic_rules_action_info() {
  $actions = array();


  $actions['commerce_coupon_basic_apply_to_item_line'] = array(
    'label' => t('Apply a percentage coupon to a line item'),
    'parameter' => array(
      'line_item' => array(
        'type' => 'commerce_line_item',
        'label' => t('Line item'),
      ),
      'coupon' => array(
        'type' => 'commerce_coupon',
        'label' => t('Coupon'),
      ),
      'component_name' => array(
        'type' => 'text',
        'label' => t('Price component type'),
        'description' => t('Choose which price component will be used as the basis for the percentage adjustment.'),
        'options list' => 'commerce_price_component_titles',
        'default value' => 'base_price',
      ),
      'round_mode' => array(
        'type' => 'integer',
        'label' => t('Price rounding mode'),
        'description' => t('Round the resulting price amount after performing this operation.'),
        'options list' => 'commerce_round_mode_options_list',
        'default value' => COMMERCE_ROUND_HALF_UP,
      ),
    ),
    'base' => 'commerce_coupon_basic_apply_percentage_coupon_to_item_line',
    'group' => t('Commerce Coupon'),
  );

  return $actions;
}

function commerce_coupon_basic_apply_percentage_coupon_to_item_line($line_item, $coupon, $price_component_type, $round_mode) {
  if (!($coupon instanceof EntityMetadataWrapper)) {
    $coupon = entity_metadata_wrapper('commerce_coupon', $coupon);
  }

  $fields = $coupon->getPropertyInfo();
  if (isset($fields['commerce_coupon_percent_amount'])
      && $coupon->commerce_coupon_percent_amount->value() > 0
      ) {
    $line_item_wrapper = entity_metadata_wrapper('commerce_line_item', $line_item);

    $rate = $coupon->commerce_coupon_percent_amount->value();
    if ($rate > 1) {
      // Ensure that the rate is never bigger then 100%
      $rate = $rate / 100;
    }
    else {
      return;
    }

    // Calculate the total granted amount for this line item
    $unit_price = commerce_price_wrapper_value($line_item_wrapper, 'commerce_unit_price', TRUE);
    $amount = commerce_round($round_mode, $unit_price['amount'] * $rate * -1);
    $price_component = array(
      'amount' => $amount,
      'currency_code' => $unit_price['currency_code'],
      'data' => array(),
    );
    $line_item_wrapper->commerce_unit_price->amount = $line_item_wrapper->commerce_unit_price->amount->value() + $amount;

    // Update the data array with the tax component.
    $line_item_wrapper->commerce_unit_price->data = commerce_price_component_add(
      $line_item_wrapper->commerce_unit_price->value(),
      'commerce_coupon_' . $coupon->type->type->value(),
      $price_component,
      TRUE
    );
  }
}
