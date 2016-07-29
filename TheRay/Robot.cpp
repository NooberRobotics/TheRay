//
//  Robot.cpp
//  TheRay
//
//  Copyright © 2016 NooberRobotics. All rights reserved.
//

#include "Robot.hpp"

unsigned long lastIntersectionTime = millis();


Status Robot::cruise(Direction direction) {
    
    handleIntersection(direction);
    Tape::resetErrors();
    
    while (true) {
        
        Collision::update();
        Tape::update();
        IR::update();
        
//        switch (IR::check()) { //IR Check
//                
//            case IR::None:
//                setVelocity(VELOCITY_NORMAL);
//                break;
//                
//            case IR::WeakLeft:
//                setVelocity(VELOCITY_SLOW);
//                break;
//                
//            case IR::WeakRight:
//                setVelocity(VELOCITY_SLOW);
//                break;
//                
//            case IR::StrongLeft:
//                Actuators::stop();
//                resetVelocity();
//                IR::resetIR();
//                return IRLeft;
//                break;
//                
//            case IR::StrongRight:
//                Actuators::stop();
//                resetVelocity();
//                IR::resetIR();
//                return IRRight;
//                break;
//        }
        
        if (Collision::occured()) {
            resetVelocity();
            return Collided;
        }
        
        if (Tape::atIntersection() && (millis() - lastIntersectionTime) > TIME_QRD_FREE_OF_INTERSECTION) {
            lastIntersectionTime = millis();
            resetVelocity();
            Actuators::stop();
            return Intersection;
        }
        
        Actuators::drive(velocity(), Tape::driveCorrection());
    }
}


void Robot::handleIntersection(Direction direction){
    
    switch (direction) {
        case StraightAhead:
            break;
            
        case Left:
            turnAtIntersection(false, millis());
            break;
            
        case Right:
            turnAtIntersection(true, millis());
            break;
            
        case TurnAround:
            resetVelocity();
            turnOntoTape(direction);
            break;
    }
}

void Robot::turnAtIntersection(bool turnRight, unsigned long time) {
    
    // wait for correct road on intersection to appear
    Tape::resetErrors();
    Tape::update();
    while (!Tape::tapePresentOnSide(turnRight) && (millis() - time) < TIME_IN_INTERSECTION) {
        Tape::update();
        Actuators::drive(velocity(), Tape::driveCorrection(turnRight));
    }
    
    // turn onto tape
    Actuators::turnIntersection(turnRight);
    while (!Tape::tapePresentCentreWithUpdate()) {}
}


void Robot::turnOntoTape(bool turnRight) {
    if (turnRight) turnOntoTape(Right);
    else turnOntoTape(Left);
}


void Robot::turnOntoTape(Direction direction) {
    
    switch (direction) {
            
        case StraightAhead:
            break;
            
        case Left:
            resetVelocity();
            Actuators::turnInPlace(TURN_OFF_TAPE_DURATION, false);
            while (!Tape::tapePresentCentreWithUpdate()) {}
            break;
            
        case Right:
            resetVelocity();
            Actuators::turnInPlace(TURN_OFF_TAPE_DURATION, true);
            while (!Tape::tapePresentCentreWithUpdate()) {}
            break;
            
        case TurnAround:
            resetVelocity();
            Actuators::turnInPlace(TURN_180, true);
            while (!Tape::tapePresentCentreWithUpdate()) {}
            break;
    }
}

void Robot::pickUpPassenger(bool turnRightBefore, bool turnRightAfter) {
    
    Actuators::drive(VELOCITY_SLOW, Actuators::Straight);
    delay(DRIVE_FORWARD_BEFORE_TURNING_WHEN_DETECTED_IR);
    
    Actuators::turnInPlace(TURN_FOR_PASSENGER_PICKUP_DURATION, turnRightBefore);
    Actuators::stop();
    
    Actuators::openClaw();
    Actuators::lowerArm();
    
    unsigned long approachStartTime = millis();
    
    Actuators::drive(VELOCITY_PICKUP, Actuators::Straight);
    
    while (!Collision::occuredWithUpdate() || (millis() - approachStartTime ) < APPROACH_MAX_TIME) {}
    
    unsigned long approachTime = millis() - approachStartTime;
   
    Actuators::stop();
    
    Actuators::closeClaw();
    delay(SERVO_OPERATION_TIME);
    
    Actuators::raiseArm();
    
    bool successful = true; //!IR::frontDetected();
    
    Actuators::drive(VELOCITY_SLOW, Actuators::Straight, true);
    
    unsigned long backupStartTime = millis();
    
    while(millis() - backupStartTime < (approachTime)) {}
    
    turnOntoTape(turnRightAfter);
    
    Actuators::stop();
}

bool Robot::dropOffPassenger(Direction direction, bool rightSideDropOff) {
    
    handleIntersection(direction);

    unsigned long time = millis();
    Tape::resetErrors();

    while( (millis() - time) < DROP_OFF_APPROACH_TIME ){
        Tape::update();
        Actuators::drive(VELOCITY_NORMAL, Tape::driveCorrection());
        
        if (Collision::occuredWithUpdate()) return false;
    }
    
    Actuators::turnInPlace(TURN_FOR_PASSENGER_DROPOFF_DURATION, rightSideDropOff);
    
    Actuators::drive(VELOCITY_SLOW, Actuators::Straight); //drive up to drop off platform
    delay(DROP_OFF_PASSENGER_DRIVE_OFF_TRACK_DELAY);
    
    Actuators::stop();
    
    Actuators::lowerArm();
    Actuators::openClaw();
    
    delay(OPEN_FINGERS_FOR_PASSENGER_DROP_OFF_DURATION);
    
    Actuators::drive(VELOCITY_SLOW, Actuators::Straight, true); //get back onto track
    
    delay(DROP_OFF_PASSENGER_DRIVE_OFF_TRACK_DELAY);
    
    Actuators::stop();
    
    Actuators::closeClaw();
    Actuators::raiseArm();
    
    turnOntoTape(!rightSideDropOff);
    
    return true;
}

void Robot::evade() {
    
    Actuators::drive(VELOCITY_SLOW, Actuators::Straight, true);
    delay(REVERSE_TIME_EVADE);
    
    turnOntoTape(true);
}
