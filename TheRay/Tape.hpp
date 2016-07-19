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
    
    int driveCorrection();
    
    bool atIntersection();
    bool tapePresent();
};


#endif /* Tape_hpp */
