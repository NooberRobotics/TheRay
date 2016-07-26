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
};

class Robot {
    
    void turnOntoTape(Direction direction);
    Actuators::Velocity driveVelocity = Actuators::Normal;

public:
        
    Tape::IntersectionType lastIntersection = Tape::None;
    
    Robot() {
        Actuators::closeClaw();
        Actuators::raiseArm();
    }
    
    Status cruise(Direction direction);
    void pickUpPassenger(bool rightSideBefore, bool turnRightAfter);
    void dropOffPassenger(Direction turn, bool rightSideDropOff);
    void evade();
};


#endif /* Robot_hpp */
