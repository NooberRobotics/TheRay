//
//  Robot.hpp
//  TheRay
//
//  Copyright © 2016 Noober. All rights reserved.
//

#ifndef Robot_hpp
#define Robot_hpp

#include "Actuators.hpp"
#include "Collision.hpp"
#include "IR.hpp"
#include "Tape.hpp"
#include <Arduino.h>

enum Status {
    Collided,
    IRRight,
    IRLeft,
    Intersection,
    PickupSuccessful,
    PickupFailed,
    DroppedOff
};


class Robot {
    
public:
    
        
    Robot() {
        Actuators::closeClaw();
        Actuators::raiseArm();
    }
    
    Status cruise();
    Status pickUpPassenger(bool rightSide);
    Status dropOffPassenger(bool rightSide);
    void evade();
};


#endif /* Robot_hpp */
