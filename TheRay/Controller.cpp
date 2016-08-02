//
//  Controller.cpp
//  TheRay
//
//  Copyright © 2016 Noober Robotics. All rights reserved.
//

#include "Controller.hpp"

void Controller::execution() {
    
    switch (robot.cruise(turnDirection)) {
            
        case Collided:
            turnDirection = StraightAhead;
            robot.evade(navigator.collisionOccurred()); // passes true if right is turn-direction
            break;
            
        case IRRight:
            if (!hasPassenger) {
                if (navigatorNotInitialized || (!navigatorNotInitialized && navigator.shouldPerformPickup(true))) {
                    initializePickup(true);
                }
            }
            turnDirection = StraightAhead;
            break;
            
        case IRLeft:
            if (!hasPassenger) {
                if (navigatorNotInitialized || (!navigatorNotInitialized && navigator.shouldPerformPickup(false))) {
                    initializePickup(false);
                }
            }
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
    if (robot.dropOffPassenger(turnDirection, navigator.dropOffTurnRight)) {
        hasPassenger = false;
        turnDirection = StraightAhead;
        navigator.passengerDroppedOff();
    } else {
        robot.evade();
        navigator.collisionOccurred();
    }
}