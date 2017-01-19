//
//  data.h
//  amazon_onsite
//
//  Created by shijian on 1/15/17.
//  Copyright © 2017 University of Southern California. All rights reserved.
//

#ifndef data_h
#define data_h

#include "Order.hpp"
#include "ProductInventory.hpp"
#include "ShippingCost.hpp"

const static vector<Order> orders {
    Order(1, 6, 4, center, 0.3),    // product id, quantity, expected days, region, date
    Order(1, 3, 2, west, 0.0),
    Order(1, 4, 0, east, 0.2),
    Order(3, 100, 0, center, 0.1),
    Order(2, 6, 4, center, 0.3)
};

static vector<ProductInventory> productInventories {
    ProductInventory(1, 7, north),  // product id, quantity, region
    ProductInventory(3, 70, north),
    ProductInventory(3, 20, north),
    ProductInventory(3, 40, east),
    ProductInventory(3, 30, north)
};

const static vector<ShippingCost> shippingCosts {
    ShippingCost(north, west, express, 3, 10),  // ship from, ship to, method, cost per item, days
    ShippingCost(north, west, ground, 1, 15),
    ShippingCost(north, east, ground, 2, 20),
    ShippingCost(north, center, express, 2, 5),
    ShippingCost(north, center, express, 2, 4)
};

#endif /* data_h */
