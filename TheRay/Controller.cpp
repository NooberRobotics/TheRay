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
            //tell navigator doll was detected
            turnDirection = StraightAhead;
            break;
            
        case IRLeft:
            if (!hasPassenger) initializePickup(false);
            // tell navigator doll was detected
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
    
    if (Tape::tapePresentOnSide() == Tape::Right) {
        navigator.changeStartingPositionToRightTurnFirst();
    }

    navigatorNotInitialized = false;
}

void Controller::initializePickup(bool rightSidePickup) {
    bool turnRightAfterPickup = navigator.returnToDropoff(rightSidePickup);
    robot.pickUpPassenger(rightSidePickup, turnRightAfterPickup);
    hasPassenger = true;
}

void Controller::initializeDropoff() {
    robot.dropOffPassenger(turnDirection, navigator.dropOffTurnRight);
    turnDirection = StraightAhead;
    hasPassenger = false;
    navigator.passengerDroppedOff();
}
