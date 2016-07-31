//
//  Tape.hpp
//  TheRay
//
//  Copyright © 2016 Noober Robotics. All rights reserved.
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
    int driveCorrectionWithUpdate();

    bool atIntersection();
    
    bool tapePresent();
    bool tapePresentOnSide(bool rightSide);

    bool tapePresentCentre();
    bool tapePresentCentreWithUpdate();
    bool tapePresentSides();
    
    IntersectionType tapePresentOnSide();

    bool detectedTape(int sensor);
    void update();
    void resetErrors();
};


#endif /* Tape_hpp */
