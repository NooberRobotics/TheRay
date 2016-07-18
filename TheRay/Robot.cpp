//
//  Robot.cpp
//  TheRay
//
//  Copyright © 2016 Noober. All rights reserved.
//

#include "Robot.hpp"

void Robot::drive() {
    
    switch (IR::check()) {
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
    
    switch (Collision::check()) {
        case Collision::None:
            break;
        case Collision::Both:
            
            break;
        case Collision::Left:
            
            break;
        case Collision::Right:
            
            break;
    }
    
    Tape::Directions intersection = Tape::intersection();
    if (intersection.left == true || intersection.right == true) {
        //we have intersection. handle!
    }
    
    Actuators::drive(Actuators::Normal, Tape::driveCorrection()); //TODO: change speed
    
}

void Robot::PickUpPassenger(bool rightSide) {
    
    int turnAngle = rightSide ? 90 : -90;
    
    
    Actuators::turnInPlace(turnAngle);
    
    Actuators::openClaw();
    Actuators::lowerArm();
    
    int approachStartTime = millis();
    Actuators::drive(Actuators::Slow, Actuators::Straight);
    
    while (Collision::check() != Collision::Both) {} // wait until both are tripped //TODO: change to allow for one tripping...
    int approachTime = millis() - approachStartTime;
    Actuators::stop();
    
    Actuators::closeClaw();
    
    //TODO: add delay to ensure claw is closed properly before arm lifts
    
    delay(SERVO_OPERATION_TIME);
    
    Actuators::raiseArm();
    
    IR::check();
    
    Actuators::drive(Actuators::Slow, Actuators::Straight, true);
    delay(approachTime);
    Actuators::stop();
    
    
    
    // TODO: add delay until any QRD sensor reading
    
    // TODO: initiate tapefollow algorithm with appripriate direction as preffered
        
}
