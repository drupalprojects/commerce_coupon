<?php

class CommerceCoupon extends Entity {

  public $is_active = true;
  public $type;
  
  public function __construct($values = array()) {
    parent::__construct($values, 'commerce_coupon');
  }
}

