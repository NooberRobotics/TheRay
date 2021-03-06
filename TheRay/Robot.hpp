//
//  Robot.hpp
//  TheRay
//
//  Copyright © 2016 Noober Robotics. All rights reserved.
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
    
    void followTape(bool defaultTurn = false, bool turnRight = false);
    
    void turnOntoTape(bool turnRight);
    void turnOntoTape(Direction direction);
    
    void findTape();
    
    void handleIntersection(Direction direction);
    void turnAtIntersection(bool rightTurn, unsigned long time);
    
    void resetVelocity() {
        currentVelocity = START_VELOCITY;
        targetVelocity = VELOCITY_NORMAL;
    }
    
    int setVelocity(int velocity) {
        targetVelocity = velocity;
    }
    
    int velocity() {
        if (currentVelocity < targetVelocity) currentVelocity = currentVelocity + ACCELERATION_FACTOR;
        else if (currentVelocity > targetVelocity) currentVelocity = currentVelocity - ACCELERATION_FACTOR;
        return currentVelocity;
    }
    
private:
    double currentVelocity = START_VELOCITY;
    int targetVelocity = VELOCITY_NORMAL;
    
public:
    
    bool hasPassenger = false;
    
    Tape::IntersectionType lastIntersection = Tape::None;
    
    Robot() {
        Actuators::closeClaw();
        Actuators::raiseArm();
    }
    
    Status cruise(Direction direction);
    void pickUpPassenger(bool rightSideBefore, bool turnRightAfter);
    bool dropOffPassenger(Direction turn, bool rightSideDropOff);
    void evade(bool rightTurn = true);
};


#endif /* Robot_hpp */
