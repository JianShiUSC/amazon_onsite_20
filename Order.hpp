//
//  Order.hpp
//  amazon_onsite
//
//  Created by shijian on 1/15/17.
//  Copyright © 2017 University of Southern California. All rights reserved.
//

#ifndef Order_hpp
#define Order_hpp

#include "misc.h"

class Order {
private:
    int productId;
    int quantity;
    int expectedDays;
    Region region;
    double date;
public:
    Order(int productId, int quantity, int expectedDays, Region region, double date) {
        this->productId = productId;
        this->quantity = quantity;
        this->expectedDays = expectedDays;
        this->region = region;
        this->date = date;
    }
    
    Order(const Order& order) {
        this->productId = order.productId;
        this->quantity = order.quantity;
        this->expectedDays = order.expectedDays;
        this->region = order.region;
        this->date = order.date;
    }
    
    const int getPid() const { return productId; }
    const int getQuantity() const { return quantity; }
    const Region getDestination() const { return region; }
};

#endif /* Order_hpp */
