//
//  Actuators.hpp
//  TheRay
//
//  Copyright © 2016 Noober. All rights reserved.
//

#ifndef Actuators_hpp
#define Actuators_hpp

#include "Config.hpp"

#include "motor.h"
#include <Arduino.h>
#include "ServoTINAH.h"

namespace Actuators {
    
    enum Velocity : int {
        Stop = 0,
        Slow = VELOCITY_SLOW,
        Normal = VELOCITY_NORMAL,
        Fast = VELOCITY_FAST
    };
    
    enum Turn : int {
        Straight = 0,
        SlightRight = TURN_SLIGHT,
        SlightLeft = -TURN_SLIGHT,
        HardRight = TURN_HARD,
        HardLeft = -TURN_HARD
    };
    
    void turnInPlace(int turnAngle);
    void drive(Velocity velocity, int turn);
    void drive(Velocity velocity, bool turnRight, Turn turn, bool reverse = false);
    void raiseArm();
    void lowerArm();
    void openClaw();
    void closeClaw();

}


#endif /* Actuators_hpp */
