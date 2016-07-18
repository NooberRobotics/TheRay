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
       
    
    class Directions {
    public:
        
        Directions();
        
        Directions(bool left, bool centre, bool right) {
            this->left = left;
            this->centre = centre;
            this->right = right;
        }
        
        bool left = false;
        bool centre = false;
        bool right = false;
    };
    
    int driveCorrection();
    Directions intersection();
};


#endif /* Tape_hpp */
