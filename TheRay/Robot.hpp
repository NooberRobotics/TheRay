//
//  Robot.hpp
//  TheRay
//
//  Copyright © 2016 Noober. All rights reserved.
//

#ifndef Robot_hpp
#define Robot_hpp

#include "Direction.hpp"
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
    
    Actuators::Velocity driveVelocity = Actuators::Normal;
    
    Status cruise(Direction direction);
    Status pickUpPassenger(bool rightSideBefore, bool turnRightAfter);
    Status dropOffPassenger(bool rightSide);
    void evade();
    void stop(int duration);
};


#endif /* Robot_hpp */
