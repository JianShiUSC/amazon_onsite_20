//
//  ShippingCost.hpp
//  amazon_onsite
//
//  Created by shijian on 1/15/17.
//  Copyright © 2017 University of Southern California. All rights reserved.
//

#ifndef ShippingCost_hpp
#define ShippingCost_hpp

#include "misc.h"

class ShippingCost {
private:
    Region shipFrom;
    Region shipTo;
    Method method;
    int costPerItem;
    int days;
    
public:
    ShippingCost(Region shipFrom, Region shipTo, Method method, int costPerItem, int days) {
        this->shipFrom = shipFrom;
        this->shipTo = shipTo;
        this->method = method;
        this->costPerItem = costPerItem;
        this->days = days;
    }
    
    ShippingCost(const ShippingCost& shippingCost) {
        shipFrom = shippingCost.shipFrom;
        shipTo = shippingCost.shipTo;
        method = shippingCost.method;
        costPerItem = shippingCost.costPerItem;
        days = shippingCost.days;
    }
    
    const Region getShipFrom() const { return shipFrom; }
    const Region getShipTo() const { return shipTo; }
    const int getCost() const { return costPerItem; }
    const int getDays() const { return days; }
};

#endif /* ShippingCost_hpp */
