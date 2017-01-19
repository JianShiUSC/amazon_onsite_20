//
//  main.cpp
//  amazon_onsite
//
//  Created by shijian on 1/15/17.
//  Copyright © 2017 University of Southern California. All rights reserved.
//

#include "misc.h"
#include "data.h"

typedef pair<ProductInventory*, int> InventoryMincost;  // ProductInventory to min days

struct ProductInventoryCost {
    ProductInventory* piptr;
    vector<ShippingCost> sc;
    ProductInventoryCost(ProductInventory& pi) : piptr(&pi) {};
};

struct ShippingPlan {
    Order order;
    vector<ProductInventoryCost> costs;
    ShippingPlan(const Order& _order) : order(_order) {};
};

struct InventoryPairComparator {    // cost大(天数多)的在前
    bool operator()(const InventoryMincost& ip1, const InventoryMincost& ip2) {
        return ip1.second < ip2.second;
    }
};

static bool OrderComparator(const Order& order1, const Order& order2) { // 数量少的优先, greedy 尽可能满足多的 orders
    return order1.getQuantity() < order2.getQuantity();
}

void myPrint(const ProductInventory *piptr, int num, int time) {
    cout << "product id: " << piptr->getPid() << " shipped: " << num << " inventory remains: " << piptr->getQuantity() << endl;
    cout << "Used time " << time << endl;
}

ShippingPlan solution1(Order order) {
    ShippingPlan sp(order);
    int pid = order.getPid();
    Region shipTo = order.getDestination();
    
    for(ProductInventory& pi : productInventories) {
        ProductInventoryCost pic(pi);
        if(pi.getPid() == pid) {
            Region shipFrom = pi.getRegion();
            for(ShippingCost sc_temp : shippingCosts) {
                if(sc_temp.getShipFrom() == shipFrom && sc_temp.getShipTo() == shipTo) {
                    pic.sc.push_back(sc_temp);
                }
            }
        }
        if(!pic.sc.empty()) sp.costs.push_back(pic);
    }
    return sp;
}

void solution2() {
    vector<Order> data(orders);
    sort(data.begin(), data.end(), OrderComparator);
    
    for(Order oit : data) {
        priority_queue<InventoryMincost, vector<InventoryMincost>, InventoryPairComparator> pq;
        ShippingPlan plan = solution1(oit); // 每个order 对应一个 shipping plan，shipping plan中表明了从 某个仓库 发货， 对应的shipping cost
        if(plan.costs.empty()) continue;
        
        int sumOfProduct = 0;   // sum of products we have in all of our inventories
        for(ProductInventoryCost& pic : plan.costs) {   // 对于每个plan 有很多 仓库
            if(pic.sc.empty()) continue;
            int minDays = INT_MAX;
            for(ShippingCost scit : pic.sc) {   // 每个仓库有很多shipping costs，找到 该仓库 对应的 shipping cost 中 天数最少的 shipping cost days
                if(scit.getDays() < minDays) minDays = scit.getDays();
            }
            InventoryMincost imc;
            imc.first = pic.piptr;
            imc.second = minDays;
            
            if(pic.piptr->getQuantity()) pq.push(imc);
            sumOfProduct += pic.piptr->getQuantity();
        }
        
        if(sumOfProduct < oit.getQuantity()) continue;
        int toBeSent = oit.getQuantity();
        
        while(toBeSent > 0 && !pq.empty()) {
            InventoryMincost headInventoryMinCost = pq.top();
            pq.pop();
            
            int sentNum = min(toBeSent, headInventoryMinCost.first->getQuantity());
            toBeSent -= sentNum;
            headInventoryMinCost.first->reduceQuantity(sentNum);
            myPrint(headInventoryMinCost.first, sentNum, headInventoryMinCost.second);
        }
    }
}

int main() {
//    for(Order oit : orders) {
//        ShippingPlan res = solution1(oit);
//        cout << "Order: " << res.order.getPid() << endl;
//        for (ProductInventoryCost pit : res.costs) {
//            if (pit.piptr->getRegion() == north) cout << '\t' << "Region: North" << endl;
//            else cout << '\t' << "Region: Unknown" << endl;
//            for (ShippingCost scit : pit.sc) {
//                cout << '\t' << '\t' << "Cost: days: "<< scit.getDays() << " money: " << scit.getCost() << endl;
//            }
//        }
//    }
    solution2();
}
