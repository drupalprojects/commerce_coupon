<?php

/*
 * Implements hook_entity_property_info_alter().
 */
function commerce_coupon_entity_property_info_alter(&$info) {
  if (isset($info['commerce_discount'])) {
    $info['commerce_discount']['properties']['coupons'] = array(
      'type' => 'list<commerce_coupon>',
      'label' => t('Coupons'),
      'getter callback' => 'commerce_coupon_get_discount_properties'
    );
  }
}
