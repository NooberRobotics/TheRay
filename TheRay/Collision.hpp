//
//  Collision.hpp
//  TheRay
//
//  Copyright © 2016 Noober. All rights reserved.
//

#ifndef Collision_hpp
#define Collision_hpp

#include "Config.hpp"
#include <Arduino.h>

namespace Collision {
    
    enum Result {
        None,
        Left,
        Right,
        Both,
        Back
    };
    
    Result check();
}



#endif /* Collision_hpp */
