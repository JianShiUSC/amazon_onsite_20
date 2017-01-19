//
//  ProductInventory.hpp
//  amazon_onsite
//
//  Created by shijian on 1/15/17.
//  Copyright © 2017 University of Southern California. All rights reserved.
//

#ifndef ProductInventory_hpp
#define ProductInventory_hpp

#include "misc.h"

class ProductInventory {
private:
    int productId;
    int quantity;
    Region region;
    
public:
    ProductInventory(int productId, int quantity, Region region) {
        this->productId = productId;
        this->quantity = quantity;
        this->region = region;
    }
    
    ProductInventory(const ProductInventory& productInventory) {
        this->productId = productInventory.productId;
        this->quantity = productInventory.quantity;
        this->region = productInventory.region;
    }
    
    const int getPid() const { return productId; }
    const int getQuantity() const { return quantity; }
    void reduceQuantity(int val) { quantity -= val; }
    const Region getRegion() const { return region; }
};

#endif /* ProductInventory_hpp */
