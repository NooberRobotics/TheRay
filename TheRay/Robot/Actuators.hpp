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

#ifndef Config_hpp
#define Config_hpp
#include "Config.hpp"
#endif

void turnInPlace(int turnAngle);
void drive(Velocity velocity, bool turnRight, Turn turn, bool reverse = false);

enum Velocity {
    Stop = 0,
    Slow = VELOCITY_SLOW,
    Normal = VELOCITY_NORMAL,
    Fast = VELOCITY_FAST
};

enum Turn {
    Straight = 0,
    SlightRight = 0,
    SlightLeft = 0,
    HardRight = 0
};


#endif /* Actuators_hpp */
