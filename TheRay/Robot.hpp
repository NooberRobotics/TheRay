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

enum Direction {
    Left,
    Right,
    TurnAround,
    StraightAhead,
};


class Robot {
    
public:
    
        
    Robot() {
        Actuators::closeClaw();
        Actuators::raiseArm();
    }
    
    Actuators::Velocity driveVelocity = Actuators::Normal;
    
    Status cruise(Direction direction);
    Status pickUpPassenger(bool rightSide);
    Status dropOffPassenger(bool rightSide);
    bool evade();
};


#endif /* Robot_hpp */
