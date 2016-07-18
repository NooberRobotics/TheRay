//
//  Collision.cpp
//  TheRay
//
//  Copyright © 2016 Noober. All rights reserved.
//

#include "Collision.hpp"


Collision::Result checkSensors() {
    bool left = digitalRead(TOUCH_SWITCH_LEFT);
    bool right = digitalRead(TOUCH_SWITCH_RIGHT);
    bool back = digitalRead(TOUCH_SWITCH_BACK);
    
    if (!left && !right) return Collision::Both;
    else if (!left) return Collision::Left;
    else if (!right) return Collision::Right;
    else return Collision::None;
}

Collision::Result Collision::check() {
    Collision::Result firstCheck = checkSensors();
    
    if (firstCheck == Collision::None) {
        return firstCheck;
    } else {
        Collision::Result secondCheck = checkSensors();
        if (secondCheck != Collision::None) {
            return secondCheck;
        }
    }
    return Collision::None;
    
}
