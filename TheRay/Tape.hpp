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

    int driveCorrection(bool defaultTurnRight = true);

    bool atIntersection();
    bool atIntersectionWithUpdate();
    
    bool tapePresent();
    bool tapePresentRight();
    bool tapePresentLeft();

    bool tapePresentCentre();
    bool tapePresentCentreWithUpdate();
    bool tapePresentSides();
    
    
    IntersectionType tapePresentOnSide();

    bool detectedTape(int sensor);
    void update();
};


#endif /* Tape_hpp */
