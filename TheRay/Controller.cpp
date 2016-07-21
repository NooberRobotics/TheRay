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
                robot.pickUpPassenger(true, false);
                turnDirection = StraightAhead;
                hasPassenger = true;
            }
            break;
            
            
        case IRLeft:
            if (!hasPassenger) {
                navigator.returnToDropoff(false);
                robot.pickUpPassenger(false, true);
                turnDirection = StraightAhead;
                hasPassenger = true;
            }
            break;
            
            
        case Intersection:
            turnDirection = navigator.getTurn();
            
            if (navigator.dropOffNow) {
                Serial.println("Dropping off");
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

