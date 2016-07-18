//
//  IR.cpp
//  TheRay
//
//  Copyright © 2016 Noober. All rights reserved.
//

#include "IR.hpp"


IR::Result IR::check() {
    
    int left = analogRead(IR_LEFT);
    int right = analogRead(IR_RIGHT);
    
    if (left < THRESH_LOW_IR && right < THRESH_LOW_IR){
        return IR::Result(None);
    }
    
    if (right >= left){
        if(right > THRESH_HIGH_IR) return IR::Result(StrongRight);
        return IR::Result(WeakRight);
    }
    else if(left > right){
        if(left > THRESH_HIGH_IR) return IR::Result(StrongLeft);
        return IR::Result(WeakLeft);
    }
}