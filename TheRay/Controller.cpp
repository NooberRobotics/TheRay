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
            if (!hasPassenger) {
                navigator.returnToDropoff(true);
                robot.pickUpPassenger(true, false); //true, true?
                hasPassenger = true;
            }
            turnDirection = StraightAhead;

            break;
            
            
        case IRLeft:
            if (!hasPassenger) {
                navigator.returnToDropoff(false);
                robot.pickUpPassenger(false, true); // false, false?
                hasPassenger = true;
            }
            turnDirection = StraightAhead;

            break;
            
            
        case Intersection:
            
            if (navigatorNotInitialized) {
                if (robot.lastIntersection == Tape::Right) {
                    navigator.calibrateTrackPosition(true);
                } else if (robot.lastIntersection == Tape::Left) {
                    navigator.calibrateTrackPosition(false);
                }
                
                navigatorNotInitialized = false;
            }
            
            turnDirection = navigator.getTurn();
            
            if (navigator.dropOffNow) {
                robot.dropOffPassenger(turnDirection, navigator.dropOffTurnRight);
                turnDirection = StraightAhead;
                hasPassenger = false;
                navigator.passengerDroppedOff();
            }
            
            break;
            
            
        case PickupSuccessful:
            hasPassenger = true;
            turnDirection = StraightAhead;
            break;
            
            
        case PickupFailed:
            turnDirection = StraightAhead;
            break;
            
    }
}

