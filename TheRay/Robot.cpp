//
//  Robot.cpp
//  TheRay
//
//  Copyright © 2016 NooberRobotics. All rights reserved.
//

#include "Robot.hpp"

unsigned long lastIntersectionTime = millis();


//int clockCycles = 0;

Status Robot::cruise(Direction direction) {
    
    handleIntersection(direction);
    
    while (true) {
        
        Tape::update();
        followTape();
        
        if (Tape::atIntersection() && (millis() - lastIntersectionTime) > TIME_MIN_BETWEEN_INTERSECTIONS) {
            lastIntersectionTime = millis();
            Actuators::stop();

            return Intersection;
        }
        
        
        Collision::update();
        
        if (Collision::occured()) {
            resetVelocity();
            return Collided;
        }
        
        IR::update();
        
        switch (IR::check()) {
                
            case IR::None:
                setVelocity(VELOCITY_NORMAL);
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
                IR::resetIR();
                return IRLeft;
                break;
                
            case IR::StrongRight:
                Actuators::stop();
                resetVelocity();
                IR::resetIR();
                return IRRight;
                break;
        }
    }
}

void Robot::followTape(bool defaultTurn, bool turnRight) {
    
    int correction = defaultTurn ? Tape::driveCorrection(turnRight) : Tape::driveCorrection();
    
    if (correction == TAPE_LOST_ERROR) findTape();
    else Actuators::drive(velocity(), correction);
}

void Robot::handleIntersection(Direction direction){
    
    switch (direction) {
        case StraightAhead:
            break;
            
        case Left:
            Tape::resetErrors();
            resetVelocity();
            turnAtIntersection(false, millis());
            break;
            
        case Right:
            Tape::resetErrors();
            resetVelocity();
            turnAtIntersection(true, millis());
            break;
            
        case TurnAround:
            Tape::resetErrors();
            resetVelocity();
            turnOntoTape(direction);
            break;
            
        case SlightRight:
            Actuators::drive(velocity(), SLIGHT_RIGHT_AT_SPECIAL_INTERSECTION_TURN);
            delay(SLIGHT_RIGHT_AT_SPECIAL_INTERSECTION_DURATION);
           
            Actuators::stop();
            delay(200);

            Tape::resetErrors();
            resetVelocity();
            
            findTape();
            break;
    }
}

void Robot::turnAtIntersection(bool turnRight, unsigned long time) {
    
    // wait for correct road on intersection to appear
    Tape::update();
    while (!Tape::tapePresentOnSide(turnRight) && (millis() - time) < TIME_IN_INTERSECTION) {
        Tape::update();
        followTape(true, turnRight);
    }
    
    // turn onto tape
    Actuators::turnIntersection(turnRight);
    while (!Tape::tapePresentCentreWithUpdate()) {}
}


void Robot::findTape() {
    
    int duration = INTIAL_FIND_TAPE_DURATION;
    bool rightDirection = true;
    
    while (true) {
        unsigned long time = millis();
        Actuators::turnInPlace(rightDirection);
        
        while ((millis() - time) < duration) {
            if (Tape::tapePresentCentreWithUpdate()) return;
        }
        
        duration *= 2;
        rightDirection = !rightDirection;
    }
}

void Robot::turnOntoTape(bool turnRight) {
    
    resetVelocity();
    Actuators::turnInPlace(turnRight);
    
    delay(TURN_OFF_TAPE_DURATION);
    while (Tape::tapePresentCentreWithUpdate()) {}
    delay(10);
    
    unsigned long timeStamp = millis();
    
    while (!Tape::tapePresentCentreWithUpdate()) {
        if (millis() - timeStamp > GETTING_UNSTUCK_STARTING_TIME) {
            Actuators::drive(VELOCITY_SLOW, Actuators::Straight);
            delay(GETTING_UNSTUCK_DELAY);
            timeStamp = millis();
            Actuators::turnInPlace(turnRight);
        }
    }
}


void Robot::turnOntoTape(Direction direction) {
    
    switch (direction) {
            
        case StraightAhead:
            break;
            
        case Left:
            turnOntoTape(false);
            break;
            
        case Right:
            turnOntoTape(true);
            break;
            
        case TurnAround:
            resetVelocity();
            Actuators::turnInPlace(TURN_180_DURATOIN, true);
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
    Actuators::lowerArm();
    
    unsigned long approachStartTime = millis();
    
    Actuators::drive(VELOCITY_PICKUP, Actuators::Straight);
    
    while (!Collision::occuredWithUpdate() && (millis() - approachStartTime ) < APPROACH_MAX_TIME) {}
    
    unsigned long approachTime = millis() - approachStartTime;
   
    Actuators::stop();
    
    Actuators::closeClaw();
    delay(SERVO_OPERATION_TIME);
    
    Actuators::raiseArm();
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
        followTape();
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

void Robot::evade(bool rightTurn) {
    
    Actuators::drive(VELOCITY_SLOW, Actuators::Straight, true);
    delay(REVERSE_TIME_EVADE);
    
    turnOntoTape(rightTurn);
}

//void printLoopTime() {
//    if (++clockCycles > 10000) {
//        
//        int timeClock = millis() - lastIntersectionTime;
//        
//        Serial.println("Clock time for 10000 cycles: ");
//        Serial.println(timeClock);
//        
//        lastIntersectionTime = millis();
//        clockCycles = 0;
//    }
//}