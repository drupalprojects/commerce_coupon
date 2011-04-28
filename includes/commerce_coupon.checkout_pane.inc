<?php

/**
 * Payment pane: form callback.
 */
function commerce_coupon_pane_checkout_form($form, &$form_state, $checkout_pane, $order) {
  $pane_form = array();

  // Store the payment methods in the form for validation purposes.
  $pane_form['coupon_code'] = array(
    '#type' => 'textfield',
    '#title' => 'Coupon Code',
    '#description' => 'Enter here your coupon code.',
  );

  return $pane_form;
}

function commerce_coupon_pane_checkout_form_validate($form, &$form_state, $checkout_pane, $order) {
  
  // Check if it is empty
  if (empty($form_state['values']['commerce_coupon']['coupon_code'])) {
    return true;
  }
  
  // Valdiate the coupon code
  if (commerce_coupon_code_is_valid($form_state['values']['commerce_coupon']['coupon_code'], $order)) {
    return true;
  }
  else {
    form_set_error('commerce_coupon][coupon_code', t('Your coupon code is not valid.'));
    return false;
  }
  
}


function commerce_coupon_pane_checkout_form_submit($form, &$form_state, $checkout_pane, $order) {  
  $code = $form_state['values']['commerce_coupon']['coupon_code'];
  
  $coupon = commerce_coupon_load_by_code($code);
  commerce_coupon_redeem_coupon($coupon, $order);
}
