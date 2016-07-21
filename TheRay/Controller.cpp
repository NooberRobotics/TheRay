//
//  Controller.cpp
//  TheRay
//
//  Copyright © 2016 Noober. All rights reserved.
//

#include "Controller.hpp"

void Controller::execution() {
    
    switch(robot.cruise(turnDirection)){
            
        case Collided:
            turnDirection = StraightAhead;
            robot.evade();
            navigator.collisionOccurred();
            break;
            
        case IRRight:
            if (!hasPassenger) initializePickup(true);
            turnDirection = StraightAhead;
            break;
            
        case IRLeft:
            if (!hasPassenger) initializePickup(false);
            turnDirection = StraightAhead;
            break;
            
        case Intersection:
            
            if (navigatorNotInitialized) initializeNavigator();
            
            turnDirection = navigator.getTurn();
            if (navigator.dropOffNow) initializeDropoff();
            
            break;
    }
}

void Controller::initializeNavigator() {
    if (robot.lastIntersection == Tape::Right) {
        navigator.calibrateTrackPosition(true);
    } else if (robot.lastIntersection == Tape::Left) {
        navigator.calibrateTrackPosition(false);
    }
    navigatorNotInitialized = false;
}

void Controller::initializePickup(bool rightSidePickup) {
    navigator.returnToDropoff(false);
    robot.pickUpPassenger(rightSidePickup, !rightSidePickup);
    hasPassenger = true;
}

void Controller::initializeDropoff() {
    robot.dropOffPassenger(turnDirection, navigator.dropOffTurnRight);
    turnDirection = StraightAhead;
    hasPassenger = false;
    navigator.passengerDroppedOff();
}
