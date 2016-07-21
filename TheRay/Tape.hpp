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
    
    enum IntersectionType { None, Right, Left };
    
    int driveCorrection(bool defaultTurnRight);
    int driveCorrection();

    IntersectionType atIntersection();
    
    IntersectionType tapePresentSides();
    bool tapePresent();
    bool tapePresentCentre();
};


#endif /* Tape_hpp */
