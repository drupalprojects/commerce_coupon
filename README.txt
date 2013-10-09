Commerce Coupon
===============

Description
-----------

Commerce Coupon module provides coupon functionality for Drupal Commerce
(http://drupal.org/project/commerce).

This module provides a framework for

Commerce Coupon is flexible and customisable:
- Coupon code entry is a condition for Commerce Discount application. Discounts
  that have coupon codes may use any of the other available inline conditions as
  well.
- Coupons are fieldable entities, meaning that custom fields can be added to
  each coupon type.

Dependencies
------------

Drupal Commerce and all of its dependencies
Entity Reference
Commerce Discount

Roadmap
-------

Before we tag a release, we will design and implement a coupons UI directly on
the discounts edit/create page.

Configuration
-------------

Commerce Coupon provides the default "Discount Coupon" type, which is used for
tracking coupon codes that confer Commerce Discounts.

Configuration options for Discount coupons can be found at: Store > Coupons >
Coupon Types > Discount Coupon.

There is no longer a UI for creating new coupon types. This must now be done in
code.

To set up a Discount Coupon:

- Create a discount (Store > Discounts, "create discount").
- Create a Discount Coupon (Store > Coupons > Create Coupon > Discount Coupon).
- In the discount reference field, select the Discount that you just created.
- Save Coupon. The discount now will not take effect until the correct coupon
  code has been entered.
