//
//  Robot.cpp
//  TheRay
//
//  Copyright © 2016 Noober. All rights reserved.
//

#include "Robot.hpp"


Status Robot::cruise(Direction direction) {
    
    turnOntoTape(direction);
    
    while (true) {

        switch (IR::check()) { //IR Check
                
            case IR::None:
                driveVelocity = Actuators::Normal;
                break;
                
            case IR::WeakLeft:
                driveVelocity = Actuators::Slow;
                break;
                
            case IR::WeakRight:
                driveVelocity = Actuators::Slow;
                break;
                
            case IR::StrongLeft:
                Actuators::stop();
                return IRLeft;
                break;
                
            case IR::StrongRight:
                Actuators::stop();
                return IRRight;
                break;
        }

        switch (Collision::check()) { //Collision check
            case Collision::None:
                break;
            case Collision::Both:
                return Collided;
                break;
            case Collision::Left:
                return Collided;
                break;
            case Collision::Right:
                return Collided;
                break;
        }
        
        if (Tape::atIntersection()) {
            Actuators::drive(driveVelocity, Actuators::Straight);
            delay(INTERSECTION_DETECTED_DRIVE_DELAY);
            return Intersection;
        }

        Actuators::drive(driveVelocity, Tape::driveCorrection());
    }
}


void Robot::turnOntoTape(Direction direction) {
    
    switch (direction) {
            
        case StraightAhead:
            break;
            
        case Left:
            Actuators::turnInPlace(TURN_OFF_TAPE_DURATION, false);
            while (!Tape::tapePresentCentre()) {}
            break;
            
        case Right:
            Actuators::turnInPlace(TURN_OFF_TAPE_DURATION, true);
            while (!Tape::tapePresentCentre()) {}
            break;
            
        case TurnAround:
            Actuators::turnInPlace(TURN_180, true);
            while (!Tape::tapePresentCentre()) {}
            break;
    }
}

void handleIntersection(Tape::IntersectionType intersection) {
    
}

void Robot::pickUpPassenger(bool turnRightBefore, bool turnRightAfter) {
    
    Actuators::drive(Actuators::Slow, Actuators::Straight);
    delay(DRIVE_FORWARD_BEFORE_TURNING_WHEN_DETECTED_IR);

    int duration = TURN_FOR_PASSENGER_PICKUP_DURATION;
    
    Actuators::turnInPlace(duration, turnRightBefore);
    Actuators::stop();
    
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
    
    bool successful = true; //!IR::frontDetected();
    
    Actuators::drive(velocity, Actuators::Straight, true);
    delay(approachTime);
    
    Actuators::turnInPlace(turnRightAfter);
    while(!Tape::tapePresentCentre()) {}

    Actuators::stop();
}

void Robot::dropOffPassenger(Direction direction, bool rightSideDropOff) {
    
    turnOntoTape(direction);
    
    int time = millis();
    while( (millis() - time) < DROP_OFF_APPROACH_TIME ){
        Actuators::drive(Actuators::Fast, Tape::driveCorrection());
    }
    
    Actuators::turnInPlace(TURN_FOR_PASSENGER_DROPOFF_DURATION, rightSideDropOff);
    
    Actuators::drive(Actuators::Slow, Actuators::Straight);
    delay(DROP_OFF_PASSENGER_DRIVE_OFF_TRACK_DELAY);
    
    Actuators::stop();
    
    Actuators::lowerArm();
    Actuators::openClaw();
    
    delay(OPEN_FINGERS_FOR_PASSENGER_DROP_OFF_DURATION);
    
    Actuators::drive(Actuators::Slow, Actuators::Straight, true);
    
    delay(DROP_OFF_PASSENGER_DRIVE_OFF_TRACK_DELAY);
    
    Actuators::stop();
    
    Actuators::closeClaw();
    Actuators::raiseArm();
    
    Actuators::turnInPlace(!rightSideDropOff);
    while(!Tape::tapePresentCentre()){}
}

void Robot::evade() {
    
    Actuators::drive(Actuators::Slow, Actuators::Straight, true);
    delay(REVERSE_TIME_EVADE);
    
    Actuators::turnInPlace(TURN_180, true);
    while (!Tape::tapePresentCentre()) {}
    
}
