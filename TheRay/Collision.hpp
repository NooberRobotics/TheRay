//
//  Collision.hpp
//  TheRay
//
//  Created by Morten Kals on 16/07/2016.
//  Copyright © 2016 Noober. All rights reserved.
//

#ifndef Collision_hpp
#define Collision_hpp

#include "Config.hpp"
#include <Arduino.h>

#ifndef phys253_h
#define phys253_h
#include "phys253.h"
#endif

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
