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
        return IR::None;
    }
    
    if (right >= left){
        if(right > THRESH_HIGH_IR) { return IR::StrongRight; }
        return IR::WeakRight;
    } else {
        if(left > THRESH_HIGH_IR) { return IR::StrongLeft; }
        return IR::WeakLeft;
    }
}

bool IR::frontDetected() {
    return (analogRead(IR_MIDLEFT) > THRESH_FRONT_IR) || (analogRead(IR_MIDRIGHT) > THRESH_FRONT_IR);
}