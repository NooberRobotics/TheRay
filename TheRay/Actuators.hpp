//
//  Actuators.hpp
//  TheRay
//
//  Created by Morten Kals on 16/07/2016.
//  Copyright © 2016 Noober. All rights reserved.
//

#ifndef Actuators_hpp
#define Actuators_hpp

#ifndef phys253_h
#define phys253_h
#include "phys253.h"
#endif


#include "Config.hpp"

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
    void drive(Velocity velocity, bool turnRight, Turn turn, bool reverse = false);
    void raiseArm();
    void lowerArm();
    void openClaw();
    void closeClaw();

}


#endif /* Actuators_hpp */
