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
    IntersectionType firstIntersectionDirectionStored();

    int driveCorrection(bool defaultTurnRight);
    int driveCorrection();

    bool atIntersection();
    
    IntersectionType tapePresentSide();
    
    bool tapePresent();
    bool tapePresentCentre();
    
    bool detectedTape(int sensor);
};


#endif /* Tape_hpp */
