//
//  Collision.cpp
//  TheRay
//
//  Copyright © 2016 Noober. All rights reserved.
//

#include "Collision.hpp"

bool leftSwitches[NUMBER_OF_SWITCH_CHECKS] = {false};
bool rightSwitches[NUMBER_OF_SWITCH_CHECKS] = {false};
int currentSwitchIndex = 0;

void Collision::update() {
    currentSwitchIndex = (currentSwitchIndex + 1) % NUMBER_OF_SWITCH_CHECKS;
    leftSwitches[currentSwitchIndex] = digitalRead(TOUCH_SWITCH_LEFT);
    rightSwitches[currentSwitchIndex] = digitalRead(TOUCH_SWITCH_RIGHT);
}

bool Collision::occured() {
    bool collision = true;
    
    for (int i=0; i<NUMBER_OF_SWITCH_CHECKS; i++) {
        if (!rightSwitches[i] && !leftSwitches[i]) collision = false;
    }
    
    return collision;
}
