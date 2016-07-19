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
    
    int driveCorrection(bool defaultTurnRight);
    int driveCorrection();

    bool atIntersection();
    bool tapePresent();
    bool tapePresentSides();
    bool tapePresentCentre();
    bool detectedTape(int sensor);
};


#endif /* Tape_hpp */
