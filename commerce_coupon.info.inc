<?php

/**
 * @file
 * Provides metadata for the coupon entity.
 */

/**
 * Implements hook_entity_property_info().
 */
function commerce_coupon_entity_property_info() {
  $info = array();

  // Add meta-data about the basic commerce_order properties.
  $properties = &$info['commerce_coupon']['properties'];

  $properties['coupon_id'] = array(
    'type' => 'integer',
    'label' => t('Coupon ID', array(), array('context' => 'a drupal commerce coupon')),
    'description' => t('The internal numeric ID of the coupon.'),
    'schema field' => 'coupon_id',
  );
  
  $properties['type'] = array(
    'type' => 'text',
    'label' => t('Type'),
    'description' => t('The human readable name of the coupon type.'),
    'setter callback' => 'entity_property_verbatim_set',
    'options list' => 'commerce_coupon_type_options_list',
    'required' => TRUE,
    'schema field' => 'type',
  );

  return $info;
}
