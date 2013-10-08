Commerce Coupon
===============

Description
-----------

Commerce Coupon module provides coupon functionality for Drupal Commerce
(http://drupal.org/project/commerce).

<<<<<<< HEAD
Coupons allow users to redeem discounts for Drupal Commerce products/orders
during checkout.
e.g. '10% off' or '$10 off'

Commerce Coupon is flexible and customisable:
- Multiple coupon types can be created
- Coupons are fieldable entities, meaning that custom fields can be added to
  each coupon type.
- Rules is used to handle the validation and redemption of coupons. As such, the
  default rules can be fully modified and/or new rules can be added to provide
  further coupon control.
=======
This module provides a framework for 

Commerce Coupon is flexible and customisable:
- Coupon code entry is a condition for Commerce Discount application. Discounts 
  that have coupon codes may use any of the other available inline conditions as
  well.
- Coupons are fieldable entities, meaning that custom fields can be added to
  each coupon type.
>>>>>>> 1bfb4a5c1a929d163db345dad4c0d98133252d8f

Dependencies
------------

Drupal Commerce and all of its dependencies
Entity Reference
<<<<<<< HEAD


Installation
------------

Commerce Coupon contains two modules:

- Commerce Coupon
- Commerce Coupon UI

Enable both.

Optional
--------

Whilst not required, you will likely want to install either or both of:

- Commerce coupon fixed amount
  http://drupal.org/project/commerce_coupon_fixed_amount

  Generates a:
  - 'Fixed coupon' coupon type
  - 'Redeem a coupon with fixed amount' rule

- Commerce coupon percentage
  http://drupal.org/project/commerce_coupon_pct

  Generates a:
  - 'Percentage coupon' coupon type
  - 'Calculate coupon with percentage amount' rule

and possibly also:

- Commerce coupon batch
  http://drupal.org/project/commerce_coupon_batch

  Allows mass generation of coupons.

=======
Commerce Discount

Roadmap
-------

Before we tag a release, we will design and implement a coupons UI directly on 
the discounts edit/create page.
>>>>>>> 1bfb4a5c1a929d163db345dad4c0d98133252d8f

Configuration
-------------

<<<<<<< HEAD
- Commerce Coupon permissions

  Home > Administration > People > Permissions
  (admin/people/permissions#module-commerce_coupon)

- The main Commerce Coupon admin page

  Home > Administration > Store > Coupons
  (admin/commerce/coupons)


Coupon logic
------------

Coupons must always be of a coupon type (much like content and content types)

To create a coupon:
- First add a coupon type or install one of the contributed modules that creates
  one for you such as commerce coupon fixed amount or commerce coupon
  percentage.
- Create a coupon of a particular coupon type


Example - Create a '10% off' coupon
-----------------------------------

1) Install modules

   Install:
   - Commerce Coupon
   - Commerce Coupon UI
   - Commerce coupon percentage

2) Create a 'Percentage coupon' coupon

   Go to: Home > Administration > Store > Coupons

   Click 'Create Coupon'

   Choose 'Create Percentage coupon'
   (if you have no other coupon types clicking 'Create Coupon' will redirect to
    the 'Create Percentage coupon' form)

   Create a percentage coupon with the following:

   - Coupon Code: 10%OFF
   - Number of Uses: 1 (change as necessary)
   - Percentage Amount: 10
   - Active: Yes

   Save

3) Enable the 'Coupons' area on one of your Commerce checkout panes

   Go to: Home > Administration > Store > Configuration > Checkout settings

   Move the 'Coupons' item into one of the checkout panes

   Save

4) Test it!
=======
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
>>>>>>> 1bfb4a5c1a929d163db345dad4c0d98133252d8f
