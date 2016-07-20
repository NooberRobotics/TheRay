//
//  Controller.cpp
//  TheRay
//
//  Copyright © 2016 Noober. All rights reserved.
//

#include "Controller.hpp"

void Controller::execution() {
    int randomNumber = analogRead(QRD_MIDRIGHT) % 3;
    
    switch(robot.cruise(nextTurnDirection)){
            
        case Collided:
            
            robot.evade();
            navigator.collisionOccurred();
            nextTurnDirection = navigator.getTurn();
            break;
            
            
        case IRRight:
            if (!hasDoll) {
                robot.pickUpPassenger(true);
                nextTurnDirection = StraightAhead;
            }
            break;
            
            
            
        case IRLeft:
            if (!hasDoll) {
                robot.pickUpPassenger(false);
                nextTurnDirection = navigator.getTurnAfterPickup(false);
            }
            break;
            
            
            
        case Intersection:
            
            nextTurnDirection = navigator.getTurn();
            
            break;
            
            
            
        case PickupSuccessful:
            nextTurnDirection = Left;
            hasDoll = true;
            break;
            
            
            
        case PickupFailed:
            nextTurnDirection = Right;
            hasDoll = false;
            break;
            
            
            
        case DroppedOff:
            hasDoll = false;
            break;
    }
    
    execution();
}

