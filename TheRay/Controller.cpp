//
//  Controller.cpp
//  TheRay
//
//  Copyright © 2016 Noober Robotics. All rights reserved.
//

#include "Controller.hpp"

void Controller::execution() {
    
    bool robotEvadeRight;
    
    switch (robot.cruise(turnDirection)) {
            
        case Collided:
            turnDirection = StraightAhead;
            robotEvadeRight = navigator.collisionOccurred();
            robot.evade(robotEvadeRight); // passes true if right is turn-direction
            break;
            
        case IRRight:
            if (!robot.hasPassenger && (navigatorNotInitialized || navigator.shouldPerformPickup(true))) {
                initializePickup(true);
            }
            turnDirection = StraightAhead;
            break;
            
        case IRLeft:
            if (!robot.hasPassenger && (navigatorNotInitialized || navigator.shouldPerformPickup(false))) {
                initializePickup(false);
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
    if(startOnOppositePath){
        navigator.changePrimaryPath();
    }

    navigatorNotInitialized = false;
}

void Controller::initializePickup(bool rightSidePickup) {
    bool turnRightAfterPickup = navigator.returnToDropoff(rightSidePickup);
    robot.pickUpPassenger(rightSidePickup, turnRightAfterPickup);
    robot.hasPassenger = true;
}

void Controller::initializeDropoff() {
    if (robot.dropOffPassenger(turnDirection, navigator.dropOffTurnRight)) {
        robot.hasPassenger = false;
        navigator.passengerDroppedOff();
    } else {
        navigator.collisionOccurred();
        robot.evade();
    }
    turnDirection = StraightAhead;
}