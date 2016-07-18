//
//  Collision.cpp
//  TheRay
//
//  Copyright © 2016 Noober. All rights reserved.
//

#include "Collision.hpp"

Collision::Result Collision::check() {
    
    bool left = analogRead(TOUCH_SWITCH_LEFT);
    bool right = analogRead(TOUCH_SWITCH_RIGHT);
    bool back = analogRead(TOUCH_SWITCH_BACK);
    
    if (left && right) return Collision::Both;
    else if (left) return Collision::Left;
    else if (right) return Collision::Right;
    else return Collision::None;
}