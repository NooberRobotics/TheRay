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
            }
            break;
            
            
        case IRLeft:
            if (!hasPassenger) {
                navigator.returnToDropoff(false);
                robot.pickUpPassenger(false, true);
                turnDirection = StraightAhead;
            }
            break;
            
            
        case Intersection:
            turnDirection = navigator.getTurn();
            break;
            
            
        case PickupSuccessful:
            hasPassenger = true;
            turnDirection = StraightAhead;
            break;
            
            
        case PickupFailed:
            hasPassenger = false;
            turnDirection = StraightAhead;
            break;
            
            
        case DroppedOff:
            hasPassenger = false;
            turnDirection = StraightAhead;
            break;
    }
}

