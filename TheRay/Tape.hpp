//
//  Tape.hpp
//  TheRay
//
//  Copyright © 2016 Noober. All rights reserved.
//

#ifndef Tape_hpp
#define Tape_hpp

#include "Config.hpp"
#include <Arduino.h>

namespace Tape {
    
    enum Intersection { None, Right, Left };
    
    int driveCorrection(bool defaultTurnRight);
    int driveCorrection();

    Intersection atIntersection();
    
    Intersection tapePresentSides();
    bool tapePresent();
    bool tapePresentCentre();
    
    bool detectedTape(int sensor);
};


#endif /* Tape_hpp */
