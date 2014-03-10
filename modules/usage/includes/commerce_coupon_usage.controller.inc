<?php

/**
 * @file
 * Coupon usage transaction controller class.
 */

class CommerceCouponUsageTransactionEntityController extends DrupalCommerceEntityController {
  
  public $transaction_id;
  
  public $coupon_id;
  
  public $order_id;
  
  public $uid;
  
  public $date;
  

  /**
   * Create a new usage transaction.
   *
   * @param array $values
   *   An array of values to set, keyed by property name.
   * @return
   *   A product object with all default fields initialized.
   */
  public function create(array $values = array()) {
    $values += array(
      'coupon_id' => '',
      'transaction_id' => '',
      'order_id' => '',
      'date' => '',
      'uid' => ''
    );

    return parent::create($values);
  }

  /**
   * Saves a usage transaction
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
    if (empty($entity->is_new)) {
      return parent::save($entity);
    }
    
    // Load the usage
    if (!$entity->coupon_id) {
      throw new Exception('Cannot save a usage transaction without a coupon id');
    }
    
    $max_usage = commerce_coupon_usage_get_max_usage($entity->coupon_id);    
    
    // If the entity is new, we have to use a transaction.
    if (!isset($transaction)) {
      $transaction = db_transaction();
    }
    
    // Load the usage. Since locking mode is pessimistic, this query locks its
    // rows.
    $usage = commerce_coupon_usage_get_usage($entity->coupon_id);
    
    // Only save if the coupon referenced will not exceed its maximum settings.
    if ($max_usage > $usage) {
      return parent::save($entity, $transaction);
    }
    
    // Cancel the transaction if the coupon has no more uses.
    $transaction->rollback();
  }  
}
