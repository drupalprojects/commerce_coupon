<?php

/**
 * @file
 * Coupon..
 *
 * This file contains...
 */

class CommerceCoupon extends Entity {

  public $is_active = TRUE;
  public $type;
  
  public function __construct($values = array()) {
    parent::__construct($values, 'commerce_coupon');
  }
}

