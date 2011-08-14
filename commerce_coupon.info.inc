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

  // Add meta-data about the basic commerce_order properties.
  $properties = &$info['commerce_coupon_log']['properties'];

  $properties['log_id'] = array(
    'type' => 'integer',
    'label' => t('Log ID', array(), array('context' => 'a drupal commerce coupon')),
    'description' => t('The internal numeric ID of the coupon.'),
    'schema field' => 'log_id',
  );

  $properties['coupon_id'] = array(
    'type' => 'integer',
    'label' => t('Coupon ID', array(), array('context' => 'a drupal commerce coupon')),
    'description' => t('The internal numeric ID of the coupon.'),
    'schema field' => 'coupon_id',
  );
  
  $properties['uid'] = array(
    'type' => 'integer',
    'label' => t('User ID'),
    'description' => t('The user id of the user which redeemed the coupon.'),
    'schema field' => 'uid',
  );
  
  $properties['order_id'] = array(
    'type' => 'integer',
    'label' => t('Order ID'),
    'description' => t('The order id on which this coupon log relies on.'),
    'schema field' => 'order_id',
  );
  
  $properties['is_accepted'] = array(
    'type' => 'boolean',
    'label' => t('Is Accepted'),
    'description' => t('Indicates if this coupon is accepted in this context (order / coupon).'),
    'schema field' => 'is_accepted',
  );
   
  $properties['is_processed'] = array(
    'type' => 'boolean',
    'label' => t('Is Processed'),
    'description' => t('If this coupon log is processed, this means it is final / the order is complete. It can not be removed any more.'),
    'schema field' => 'is_processed',
  );
  
  
  

  return $info;
}
