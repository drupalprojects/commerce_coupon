<?php

/**
 * @file
 * Commerce Coupon type editing UI.
 */

/**
 * Generates the commerce coupon type editing form.
 */
function commerce_coupon_type_form($form, &$form_state, $coupon_type, $op = 'edit') {

  if ($op == 'clone') {
    $coupon_type->label .= ' (cloned)';
    $coupon_type->type = '';
  }

  $form['label'] = array(
    '#title' => t('Label'),
    '#type' => 'textfield',
    '#default_value' => $coupon_type->label,
    '#description' => t('The human-readable name of this coupon type.'),
    '#required' => TRUE,
    '#size' => 30,
  );
  
  // Machine-readable type name.
  $form['type'] = array(
    '#type' => 'machine_name',
    '#default_value' => isset($coupon_type->type) ? $coupon_type->type : '',
    '#maxlength' => 32,
    '#disabled' => $coupon_type->isLocked() && $op != 'clone',
    '#machine_name' => array(
      'exists' => 'commerce_coupon_get_types',
      'source' => array('label'),
    ),
    '#description' => t('A unique machine-readable name for this coupon type. It must only contain lowercase letters, numbers, and underscores.'),
  );

  $form['data']['#tree'] = TRUE;
  
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save coupon type'),
    '#weight' => 40,
  );

  if (!$coupon_type->isLocked() && $op != 'add') {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete coupon type'),
      '#weight' => 45,
      '#limit_validation_errors' => array(),
      '#submit' => array('commerce_coupon_type_form_submit_delete')
    );
  }
  return $form;
}

/**
 * Form API submit callback for the type form.
 */
function commerce_coupon_type_form_submit(&$form, &$form_state) {
  $commerce_coupon_type = entity_ui_form_submit_build_entity($form, $form_state);
  // Save and go back.
  $commerce_coupon_type->save();
  $form_state['redirect'] = 'admin/commerce/coupons/types';
}

/**
 * Form API submit callback for the delete button.
 */
function commerce_coupon_type_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/commerce/coupons/types/manage/' . $form_state['commerce_coupon_type']->type . '/delete';
}




/**
 * Generates the commerce coupon editing form.
 */
function commerce_coupon_form($form, &$form_state, $coupon, $op = 'edit') {

  if ($op == 'clone') {
    $coupon_type->label .= ' (cloned)';
    $coupon_type->type = '';
  }

  $form['amount'] = array(
    '#title' => t('Amount'),
    '#type' => 'textfield',
    '#default_value' => $coupon->amount,
    '#description' => t('The amount of the coupon.'),
    '#required' => TRUE,
    '#size' => 30,
  );
 
  $form['is_percentage'] = array(
    '#title' => t('Percentage'),
    '#type' => 'checkbox',
    '#default_value' => $coupon->is_percentage,
    '#description' => t('Indicates if the amount is a percentage of the order or a fixed amount.'),
  );
  
  $form['code'] = array(
    '#title' => t('Coupon Code'),
    '#type' => 'textfield',
    '#default_value' => $coupon->code,
    '#description' => t('Enter here the code of the coupon. When the customer enter this code, he get the reduction indicated by the amount. Leave it empty to auto generate a code.'),
    '#size' => 30,
  );
  // TODO: add a validation method to check, that the code is not a duplicate!
 
  $form['is_active'] = array(
    '#title' => t('Active'),
    '#type' => 'checkbox',
    '#default_value' => $coupon->is_active,
    '#description' => t('Indicates if the coupon can be used or not.'),
    '#size' => 30,
  );

  // Add the field related form elements.
  $form_state['commerce_coupon'] = $coupon;
  field_attach_form('commerce_coupon', $coupon, $form, $form_state);

  $form['data']['#tree'] = TRUE;
  
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save coupon'),
    '#weight' => 40,
  );

  if ($op != 'add') {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete coupon'),
      '#weight' => 45,
      '#limit_validation_errors' => array(),
      '#submit' => array('commerce_coupon_form_submit_delete')
    );
  }
  return $form;
}

/**
 * Form API submit callback for the type form.
 */
function commerce_coupon_form_submit(&$form, &$form_state) {
  $commerce_coupon = entity_ui_form_submit_build_entity($form, $form_state);
  // Save and go back.
  commerce_coupon_save($commerce_coupon);
  $form_state['redirect'] = 'admin/commerce/coupons';
}

/**
 * Form API submit callback for the delete button.
 */
function commerce_coupon_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/commerce/coupons/manage/' . $form_state['commerce_coupon']->coupon_id . '/delete';
}
