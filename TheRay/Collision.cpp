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
    
    if (checkSensors() == Collision::None) {
        return Collision::None;
    }
    
    delay(1);
    
    if (checkSensors() == Collision::None) {
        return Collision::None;
    }
    
    delay(1);
    
    return checkSensors();
}
