<?php

/**
 * @file
 * Coupon rules integration file.
 */

/**
 * Implements hook_rules_event_info().
 */
function commerce_coupon_rules_event_info() {
  $events = array();

  $events['commerce_coupon_validate'] = array(
    'label' => t('Validate a coupon'),
    'group' => t('Commerce Coupon'),
    'variables' => array(
      'coupon' => array(
        'type' => 'commerce_coupon',
        'label' => t('commerce coupon to validate')
      ),
      'commerce_order' => array(
        'type' => 'commerce_order',
        'label' => t('Order'),
      ),
    ),
    'access callback' => 'commerce_order_rules_access',
  );

  $events['commerce_coupon_redeem'] = array(
    'label' => t('Redeem a coupon'),
    'group' => t('Commerce Coupon'),
    'variables' => array(
      'coupon' => array(
        'type' => 'commerce_coupon',
        'label' => t('commerce coupon to redeem')
      ),
      'coupon_log' => array(
        'type' => 'commerce_coupon_log',
        'label' => t('commerce coupon log')
      ),
      'commerce_order' => array(
        'type' => 'commerce_order',
        'label' => t('Order'),
      ),
    ),
    'access callback' => 'commerce_order_rules_access',
  );

  return $events;
}

/**
 * Implements hook_rules_action_info().
 */
function commerce_coupon_rules_action_info() {
  $actions = array();

  $actions['commerce_coupon_action_is_valid_coupon'] = array(
    'label' => t('Set coupon as valid'),
    'parameter' => array(
      'override' => array(
        'type' => 'boolean',
        'label' => t('Override'),
        'description' => t('Normaly the validation result is concatenated by an AND operator. Here you can bypass this and set the value to true.'),
      ),
    ),
    'group' => t('Commerce Coupon'),
    'base' => 'commerce_coupon_action_is_valid_coupon',
    'callbacks' => array(
      'execute' => 'commerce_coupon_action_is_valid_coupon',
    ),
  );

  $actions['commerce_coupon_action_is_invalid_coupon'] = array(
    'label' => t('Set coupon as invalid'),
    'group' => t('Commerce Coupon'),
    'base' => 'commerce_coupon_action_is_invalid_coupon',
    'callbacks' => array(
      'execute' => 'commerce_coupon_action_is_invalid_coupon',
    ),
  );

  $actions['commerce_coupon_action_set_granted_amount'] = array(
    'label' => t('Set granted coupon amount'),
    'parameter' => array(
      'commerce_coupon_log' => array(
        'type' => 'commerce_coupon_log',
        'label' => t('Commerce Coupon Log'),
      ),
      'amount' => array(
        'type' => 'decimal',
        'label' => t('Granted Amount'),
      ),
      'currency_code' => array(
        'type' => 'text',
        'label' => t('Currency Code'),
      ),
    ),
    'group' => t('Commerce Coupon'),
    'base' => 'commerce_coupon_action_is_invalid_coupon',
    'callbacks' => array(
      'execute' => 'commerce_coupon_action_set_granted_amount',
    ),
  );

  $actions['commerce_coupon_action_get_coupons_for_order'] = array(
    'label' => t('Get coupons for order'),
    'parameter' => array(
      'commerce_order' => array(
        'type' => 'commerce_order',
        'label' => t('Commerce order'),
      ),
    ),
    'provides' => array(
      'order_coupons' => array(
        'type' => 'list<commerce_coupon>',
        'label' => 'Coupons attached to this order',
      ),
    ),
    'group' => t('Commerce Coupon'),
    'base' => 'commerce_coupon_action_get_coupons_for_order',
  );

  $actions['commerce_coupon_action_create_coupon_line_item'] = array(
    'label' => t('Create coupon line item'),
    'parameter' => array(
      'commerce_coupon' => array(
        'type' => 'commerce_coupon',
        'label' => t('Commerce Coupon'),
      ),
      'commerce_order' => array(
        'type' => 'commerce_order',
        'label' => t('commerce order'),
      ),
      'amount' => array(
        'type' => 'decimal',
        'label' => t('coupon amount'),
      ),
      'currency_code' => array(
        'type' => 'text',
        'label' => t('coupon amount currency code'),
      ),
    ),
    'provides' => array(
      'commerce_coupon_line_item' => array(
        'type' => 'commerce_line_item',
        'label' => t('commerce coupon line item'),
      ),
    ),
    'group' => t('Commerce Coupon'),
    'base' => 'commerce_coupon_action_create_coupon_line_item',
    'callbacks' => array(
      'execute' => 'commerce_coupon_action_create_coupon_line_item',
    ),
  );


  $actions['commerce_coupon_action_get_coupon_uses'] = array(
    'label' => t('Get the redemption number of a coupon'),
    'parameter' => array(
      'commerce_coupon' => array(
        'type' => 'commerce_coupon',
        'label' => t('Commerce Coupon'),
      ),
    ),
    'group' => t('Commerce Coupon'),
    'provides' => array(
      'number_of_uses' => array(
        'type' => 'integer',
        'label' => t('number of uses'),
      ),
    ),
  );

  $actions['commerce_coupon_action_remove_coupon_from_order'] = array(
    'label' => t('Remove a coupon from an order'),
    'parameter' => array(
      'commerce_order' => array(
        'type' => 'commerce_order',
        'label' => t('Commerce Order'),
      ),
      'commerce_coupon' => array(
        'type' => 'commerce_coupon',
        'label' => t('Commerce Coupon'),
      ),
    ),
    'group' => t('Commerce Coupon'),
  );


  return $actions;
}

function commerce_coupon_action_is_valid_coupon($override = FALSE) {
  $validation_results = &drupal_static('commerce_coupon_action_validation_results');

  if (isset($validation_results) && $override == FALSE) {
    $validation_results = $validation_results && TRUE;
  }
  else {
    $validation_results[$commerce_coupon->coupon_id] = TRUE;
  }
}

function commerce_coupon_action_is_invalid_coupon() {
  $validation_results = &drupal_static('commerce_coupon_action_validation_results');
  $validation_results = FALSE;
}

function commerce_coupon_action_set_granted_amount($coupon_log, $amount, $currency_code) {
  if (!($coupon_log instanceof EntityMetadataWrapper)) {
    $coupon_log = entity_metadata_wrapper('commerce_coupon_log', $coupon_log);
  }

  $coupon = $coupon_log->commerce_coupon;

  // Get the price component to use in this price.
  $price_component_name = 'commerce_coupon_' . $coupon->type;
  drupal_alter('commerce_coupon_price_component_name', $price_component_name, $coupon);

  // Set the unit price on the line item object.
  $coupon_log->commerce_granted_amount->amount = $amount;
  $coupon_log->commerce_granted_amount->currency_code = $currency_code;


  // Add the base price to the components array.
  if (!commerce_price_component_load($coupon_log->commerce_granted_amount->value(), $price_component_name)) {
    $coupon_log->commerce_granted_amount->data = commerce_price_component_add(
        $coupon_log->commerce_granted_amount->value(), $price_component_name, $coupon_log->commerce_granted_amount->value(), TRUE, FALSE
    );
  }

  commerce_coupon_log_save($coupon_log->value());
}

function commerce_coupon_action_get_coupons_for_order($coupon) {
  if (!$coupon) {
    return array();
  }
  return array('order_coupons' => commerce_coupon_get_coupons_by_order($coupon->order_number));
}

function commerce_coupon_action_create_coupon_line_item($commerce_coupon, $commerce_order, $amount, $currency_code) {
  if (!($commerce_order instanceof EntityMetadataWrapper)) {
    $commerce_order = entity_metadata_wrapper('commerce_order', $commerce_order);
  }

  // Get the price component to use in this price.
  $price_component_name = 'commerce_coupon_' . $commerce_coupon->type;
  drupal_alter('commerce_coupon_price_component_name', $price_component_name, $commerce_coupon);

  $line_item = commerce_coupon_line_item_new($commerce_coupon, $commerce_order->order_id->value());
  $line_item_wrapper = entity_metadata_wrapper('commerce_line_item', $line_item);

  // Set the unit price on the line item object.
  $line_item_wrapper->commerce_unit_price->amount = $amount * -1;
  $line_item_wrapper->commerce_unit_price->currency_code = $currency_code;

  // Add the base price to the components array.
  if (!commerce_price_component_load($line_item_wrapper->commerce_unit_price->value(), $price_component_name)) {
    $line_item_wrapper->commerce_unit_price->data = commerce_price_component_add(
        $line_item_wrapper->commerce_unit_price->value(), $price_component_name, $line_item_wrapper->commerce_unit_price->value(), TRUE, FALSE
    );
  }

  commerce_line_item_save($line_item);

  $commerce_order->commerce_line_items[] = $line_item;
  $commerce_order->save();

  return array('commerce_coupon_line_item' => $line_item);
}

function commerce_coupon_action_get_coupon_uses($coupon) {
  return array('number_of_uses' => commerce_coupon_get_number_of_uses($coupon->coupon_id));
}

function commerce_coupon_action_remove_coupon_from_order($order, $coupon) {
  if (empty($coupon) || empty($order)) {
    return array();
  }
  commerce_coupon_remove_coupon_from_order($order, $coupon);
}