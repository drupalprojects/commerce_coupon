Important! 1.x -> 2.x update instructions

Preliminary notes/caveats:

* The update runs well on sites without much customization to their coupons, 
  but if you have a lot of rules/custom code involved in your previous coupons 
  setup, all bets are off. 
* Take a look at the api files in this module - there are a number of ways to 
  customize the procedure that the batch does when upgrading coupons and orders.
* This modules uses Batch API to update individual coupon and order entities. If
  your site has millions of coupons/orders and/or low memory settings, the 
  updater might fail. Unfortunately taxing conditions like this are not yet 
  supported for upgrade. (Migrate module is probably needed to accomplish this).

Instructions:

* Before you do anything MAKE A BACKUP OF YOUR DATABASE!!
* Run the update function in commerce_coupon.install
* Go to admin/commerce/coupons/upgrade-coupons
* Click "proceed" when you are ready. This will initiate a batch update of your 
  coupon entities. At the end, it disables the obsolete coupon type modules from
  before.
* Go to admin/commerce/coupons/upgrade-orders
* Click "proceed". This time you are updating your orders. NOTE: legacy 
  "commerce_coupon" line items will keep this same line item type even though 
  new orders use discount line items to store their offer-effect. This may 
  disrupt order reporting.