<?php

class commerce_coupon_handler_field_discount_value_display extends views_handler_field {
  function construct() {
    parent::construct();

    $this->additional_fields['coupon_id'] = 'coupon_id';
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }
  
  function render($values) {        
    // Determine if there is an order id argument. If multiple are present, use 
    // the first found.
    $order = _commerce_coupon_load_argument_order($this);
    $coupon = commerce_coupon_load($this->get_value($values, 'coupon_id'));
    
    // Don't show anything if there are no discounts belonging to this coupon
    // present on the order.
    if ($order && $coupon) {
      $discounts = commerce_coupon_order_coupon_code_discounts($coupon->code, $order);
      
      if ($discounts) {
        $items = array();       

        // Coupon codes may be linked to multiple discounts, so we have a hook that
        // lets discount type/offer modules define what value gets shown for each
        // coupon that has a discount  
        foreach ($discounts as $discount) {
          $display = '';
          drupal_alter('commerce_coupon_discount_savings_value', $display, $discount, $order);
          if ($display) {
            $items[] = $display;
          }
        }
      }
      $variables = array(
        'items' => $items,
        'type' => 'ul',
        'title' => '',
        'attributes' => array()
      );

      return theme_item_list($variables);
    }
  }
}