<?php



/**
 * Generates the commerce coupon editing form.
 */
function commerce_coupon_form($form, &$form_state, $coupon, $op = 'edit') {

  if ($op == 'clone') {
    $coupon_type->label .= ' (cloned)';
    $coupon_type->type = '';
  }
  
  $form['batch_size'] = array(
    '#title' => t('Batch Size'),
    '#type' => 'textfield',
    '#default_value' => $coupon->code,
    '#description' => t('Enter the number of coupons which should be generated.'),
    '#size' => 30,
  );

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
  $size = (int)$form_state['values']['batch_size'];
  $commerce_coupon = entity_ui_form_submit_build_entity($form, $form_state);
  
  if($size > 0) {
    for ($i = 0; $i < $size; $i++) {
      $coupon = clone $commerce_coupon;
      $coupon->code = commerce_coupon_generate_coupon_code();
      
      // Save 
      commerce_coupon_save($coupon);
    }
  }
  // Go back.
  $form_state['redirect'] = 'admin/commerce/coupons';
}

