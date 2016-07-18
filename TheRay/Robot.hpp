//
//  Robot.hpp
//  TheRay
//
//  Copyright © 2016 Noober. All rights reserved.
//

#ifndef Robot_hpp
#define Robot_hpp

#include "Actuators.hpp"
#include "Collision.hpp"
#include "IR.hpp"
#include "Tape.hpp"


class Robot {
    
public:
 
    bool pickUpPassenger(bool rightSide);
    Status drive()
    
    
    
    
    
};

enum Status {
    CollisionRight,
    CollisionLeft,
    IRRight,
    IRLeft,
    Intersection
    
    
};

#endif /* Robot_hpp */
