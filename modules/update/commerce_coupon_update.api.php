<?php

/**
 * Alter an order before it is updated.
 * 
 * @param stdClass $original_order
 *  The legacy order entity
 * 
 * @param stdClass $order
 *  The updated order entity
 */
function hook_commerce_coupon_update_order_pre_update($original_order, $order) {
  // No example.
}


/**
 * Alter an coupon before it is updated.
 * 
 * @param CommerceCoupon $original_coupon
 *  The legacy coupon entity
 * 
 * @param CommerceCoupon $coupon
 *  The updated coupon entity
 * 
 * @param CommerceDiscount $discount
 *  The discount (if found) for the new version of the coupon
 */
function hook_commerce_coupon_update_pre_update($original_coupon, $coupon, $discount = NULL) {
  // No example.
}
