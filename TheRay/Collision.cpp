//
//  Collision.cpp
//  TheRay
//
//  Copyright © 2016 Noober Robotics. All rights reserved.
//
// This class is for when we collide with another robot or a sidewalk/wall.

#include "Collision.hpp"

bool leftSwitches[NUMBER_OF_SWITCH_CHECKS] = {true};
bool rightSwitches[NUMBER_OF_SWITCH_CHECKS] = {true};
int currentSwitchIndex = 0;

void Collision::update() {
    currentSwitchIndex = (currentSwitchIndex + 1) % NUMBER_OF_SWITCH_CHECKS;
    
    leftSwitches[currentSwitchIndex] = digitalRead(TOUCH_SWITCH_LEFT);
    rightSwitches[currentSwitchIndex] = digitalRead(TOUCH_SWITCH_RIGHT);
}

bool Collision::occured() {
    bool collision = true;
    
    for (int i=0; i<NUMBER_OF_SWITCH_CHECKS; i++) {
        if (rightSwitches[i] && leftSwitches[i]) collision = false;
    }
    
    return collision;
}

bool Collision::occuredWithUpdate() {
    update();
    return occured();
}
