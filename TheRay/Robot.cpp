//
//  Robot.cpp
//  TheRay
//
//  Copyright © 2016 NooberRobotics. All rights reserved.
//

#include "Robot.hpp"

unsigned long currentTime() {
    return millis();
}

unsigned long lastIntersectionTime = currentTime();


Status Robot::cruise(Direction direction) {
    
    handleIntersection(direction);
    
    while (true) {
        
        Collision::update();
        Tape::update();
        IR::update();
        
        switch (IR::check()) { //IR Check
                
            case IR::None:
                break;
                
            case IR::WeakLeft:
                setVelocity(VELOCITY_SLOW);
                break;
                
            case IR::WeakRight:
                setVelocity(VELOCITY_SLOW);
                break;
                
            case IR::StrongLeft:
                Actuators::stop();
                resetVelocity();
                return IRLeft;
                break;
                
            case IR::StrongRight:
                Actuators::stop();
                resetVelocity();
                return IRRight;
                break;
        }
        
        if (Collision::occured()){
            resetVelocity();
            return Collided;
        }
        
        if (Tape::atIntersection() && (currentTime() - lastIntersectionTime) > TIME_QRD_FREE_OF_INTERSECTION) {
            lastIntersectionTime = millis();
            currentVelocity = START_VELOCITY;
            return Intersection;
        }
        
        Actuators::drive(currentVelocity, Tape::driveCorrection());
    }
}


void Robot::handleIntersection(Direction direction){
    
    unsigned long time = currentTime();
    
    switch (direction) {
        case StraightAhead:
            //            delay(60);
            break;
            
        case Left:
            turnAtIntersection(false, time);
            break;
            
        case Right:
            turnAtIntersection(true, time);
            break;
            
        case TurnAround:
            currentVelocity = START_VELOCITY;
            turnOntoTape(direction);
            break;
    }
}

void Robot::turnAtIntersection(bool turnRight, unsigned long time) {
    velocity(START_VELOCITY);
    
    // wait for correct road on intersection to appear
    Tape::update();
    while (!Tape::tapePresentOnSide(turnRight) && (currentTime() - time) < TIME_IN_INTERSECTION) {
        Tape::update();
        Actuators::drive(velocity(), Tape::driveCorrection(turnRight));
    }
    
    // turn onto tape
    Actuators::turnIntersection(turnRight);
    while (!Tape::tapePresentCentreWithUpdate()) {}
}


void turnOntoTape(bool turnRight) {
    if (turnRight) turnOntoTape(Right);
    else turnOntoTape(Left);
}


void Robot::turnOntoTape(Direction direction) {
    
    switch (direction) {
            
        case StraightAhead:
            break;
            
        case Left:
            Actuators::turnInPlace(TURN_OFF_TAPE_DURATION, false);
            while (!Tape::tapePresentCentreWithUpdate()) {}
            break;
            
        case Right:
            Actuators::turnInPlace(TURN_OFF_TAPE_DURATION, true);
            while (!Tape::tapePresentCentreWithUpdate()) {}
            break;
            
        case TurnAround:
            Actuators::turnInPlace(TURN_180, true);
            while (!Tape::tapePresentCentreWithUpdate()) {}
            break;
    }
}

void Robot::pickUpPassenger(bool turnRightBefore, bool turnRightAfter) {
    
    Actuators::drive(VELOCITY_SLOW, Actuators::Straight);
    delay(DRIVE_FORWARD_BEFORE_TURNING_WHEN_DETECTED_IR);

    int duration = TURN_FOR_PASSENGER_PICKUP_DURATION;
    
    Actuators::turnInPlace(duration, turnRightBefore);
    Actuators::stop();
    
    Actuators::openClaw();
    Actuators::lowerArm();
    
    unsigned long approachStartTime = currentTime();
    int velocity = VELOCITY_SLOW;
    
    Actuators::drive(velocity, Actuators::Straight);
    
    while (!Collision::occuredWithUpdate()) {} // wait until both are tripped
    
    unsigned long approachTime = currentTime() - approachStartTime;
   
    Actuators::stop();
    
    Actuators::closeClaw();
    
    delay(SERVO_OPERATION_TIME);
    
    Actuators::raiseArm();
    
    bool successful = true; //!IR::frontDetected();
    
    Actuators::drive(velocity, Actuators::Straight, true);
    
    unsigned long backupStartTime = currentTime();
    
    while(currentTime() - backupStartTime < (approachTime)){
        Tape::update();
        if (Tape::tapePresent()) break;
    }
    
    turnOntoTape(turnRightAfter);
    
    Actuators::stop();
}

bool Robot::dropOffPassenger(Direction direction, bool rightSideDropOff) {
    
    handleIntersection(direction);

    unsigned long time = currentTime();
    
    while( (currentTime() - time) < DROP_OFF_APPROACH_TIME ){
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
    
    Actuators::turnInPlace(TURN_OFF_TAPE_DURATION, true);
    while (!Tape::tapePresentCentreWithUpdate()) {}
}
