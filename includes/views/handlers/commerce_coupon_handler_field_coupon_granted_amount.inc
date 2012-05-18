<?php
/**
 * @file
 * Displays the granted amount of a coupon based in each coupon type conditions. 
 */

class commerce_coupon_handler_field_coupon_granted_amount extends views_handler_field {

  function construct() {
    parent::construct();

    $this->additional_fields['coupon_id'] = 'coupon_id';
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function render($values) {
    $amount = '';
    $coupon_id = $this->get_value($values, 'coupon_id');
    // @TODO: get the order id in a better way.
    $values->order_id = $values->commerce_coupon_order_reference_commerce_coupon_order_id;
    $coupon = commerce_coupon_load($coupon_id);

    drupal_alter('commerce_coupon_granted_amount', $amount, $coupon, $values);
    return $amount;
  }

}
