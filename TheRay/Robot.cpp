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
            
            //pickUpPassenger(false);
            break;
        case IR::StrongRight:
            
            //pickUpPassenger(true);
            break;
    }
    
    switch (Collision::check()) {
        case Collision::None:
            break;
        case Collision::Both:
            evade();
            break;
        case Collision::Left:
            evade();
            break;
        case Collision::Right:
            evade();
            break;
    }
    
    //Tape::Directions intersection = Tape::intersection();
//    if (intersection.left == true || intersection.right == true) {
//        //we have intersection. handle!
//    }
    
    Actuators::drive(Actuators::Normal, Tape::driveCorrection()); //TODO: change speed
    
}

bool Robot::pickUpPassenger(bool rightSide) {
    
    int turnAngle = rightSide ? 90 : -90;
    Actuators::turnInPlace(turnAngle);
    
    Actuators::openClaw();
    Actuators::lowerArm();
    
    int approachStartTime = millis();
    Actuators::Velocity velocity = Actuators::Slow;
    Actuators::drive(velocity, Actuators::Straight);
    
    while (Collision::check() == Collision::None) {} // wait until both are tripped //TODO: change to allow for one tripping...
    
    int approachTime = millis() - approachStartTime;
   
    Actuators::stop();
    
    Actuators::closeClaw();
    
    delay(SERVO_OPERATION_TIME);
    
    Actuators::raiseArm();
    
    bool successful = !IR::frontDetected();
    
    Actuators::drive(velocity, Actuators::Straight, true);
    delay(approachTime);
    
    Actuators::stop();
    
    return successful;
}

void Robot::dropOffPassenger(bool rightSide) {
    
    
}

void Robot::evade() {
    
    Actuators::drive(Actuators::Slow, Actuators::Straight, true);
    delay(500);
    Actuators::turnInPlace(180);
    drive();
}
