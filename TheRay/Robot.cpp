//
//  Robot.cpp
//  TheRay
//
//  Copyright © 2016 Noober. All rights reserved.
//

#include "Robot.hpp"

void Robot::drive() {
    
    switch (ir.check()) {
        case IR::None:
            
            break;
        case IR::WeakLeft:
            
            break;
        case IR::WeakRight:
            
            break;
        case IR::StrongLeft:
            
            break;
        case IR::StrongRight:
            
            break;
    }
    
    switch (collision.check()) {
        case Collision::None:
            break;
        case Collision::Both:
            
            break;
        case Collision::Left:
            
            break;
        case Collision::Right:
            
            break;
    }
    
    Tape::Directions intersection = tape.intersection();
    if (intersection.left == true || intersection.right == true) {
        //we have intersection. handle!
    }
    
    actuators.drive(Actuators::Normal, tape.driveCorrection()); //TODO: change speed
    
}

void Robot::PickUpPassenger(bool rightSide) {
    
    int turnAngle = rightSide ? -90 : 90;
    actuators.turnInPlace(turnAngle);
    
    actuators.openClaw();
    actuators.lowerArm();
    
    actuators.drive(Actuators::Slow, Actuators::Turn::Straight);
    
    while (collision.check() != Collision::Both) {} // wait until both are tripped //TODO: change to allow for one tripping...
    
    actuators.closeClaw();
    //TODO: add delay to ensure law is closed properly before arm lifts
    actuators.raiseArm();
    
    actuators.drive(Actuators::Slow, Actuators::Straight, true);
    
    // TODO: add delay until any QRD sensor reading
    
    // TODO: initiate tapefollow algorithm with appripriate direction as preffered
        
}
