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
    
    Actuators actuators = Actuators();
    Collision collision = Collision();
    IR ir = IR();
    Tape tape = Tape();
    
public:
    
    void drive();
    void PickUpPassenger(bool rightSide);
    
    
};

#endif /* Robot_hpp */
