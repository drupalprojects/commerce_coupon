<?php

/**
 * @file
 * Coupon controller class.
 */

class CommerceCouponEntityController extends DrupalCommerceEntityController {

  /**
   * Create a default coupon.
   *
   * @param array $values
   *   An array of values to set, keyed by property name.
   * @return
   *   A product object with all default fields initialized.
   */
  public function create(array $values = array()) {
    $values += array(
      'coupon_id' => '',
      'type' => '',
      'is_active' => TRUE,
      'created' => '',
      'changed' => '',
    );

    return parent::create($values);
  }

  /**
   * Saves a coupon.
   *
   * @param $commerce_coupon
   *   The full coupon object to save.
   * @param $transaction
   *   An optional transaction object.
   *
   * @return
   *   SAVED_NEW or SAVED_UPDATED depending on the operation performed.
   */
  public function save($entity, DatabaseTransaction $transaction = NULL) {
    $transaction = isset($transaction) ? $transaction : db_transaction();

    // Hardcode the changed time.
    $entity->changed = REQUEST_TIME;

    if (empty($entity->{$this->idKey}) || !empty($entity->is_new)) {
      // Set the creation timestamp if not set, for new entities.
      if (empty($entity->created)) {
        $entity->created = REQUEST_TIME;
      }
    }
    
    // Generate a code if no is set:
    $code = field_get_items('commerce_coupon', $entity, 'commerce_coupon_code');
    if (!isset($code) || empty($code)) {
      $entity->commerce_coupon_code[LANGUAGE_NONE][0]['value'] = commerce_coupon_generate_coupon_code();
    }
    return parent::save($entity);
  }
}

