//
//  Controller.cpp
//  TheRay
//
//  Copyright © 2016 Noober. All rights reserved.
//

#include "Controller.hpp"

void Controller::execution() {
    
    Direction turnDirection = navigator.getTurn();
    
    switch(robot.cruise(turnDirection)){
            
        case Collided:
            robot.evade();
            navigator.collisionOccurred();
            break;
            
            
        case IRRight:
            if (!hasPassenger) {
                navigator.returnToDropoff(true);
                robot.pickUpPassenger(true, navigator.getTurn());
            }
            break;
            
            
        case IRLeft:
            if (!hasPassenger) {
                navigator.returnToDropoff(false);
                robot.pickUpPassenger(false, navigator.getTurn());
            }
            break;
            
            
        case Intersection:
            
            break;
            
            
        case PickupSuccessful:
            nextTurnDirection = Left;
            hasPassenger = true;
            break;
            
            
        case PickupFailed:
            nextTurnDirection = Right;
            hasPassenger = false;
            break;
            
            
        case DroppedOff:
            hasPassenger = false;
            break;
    }
}

