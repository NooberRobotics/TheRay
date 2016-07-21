//
//  Robot.cpp
//  TheRay
//
//  Copyright © 2016 Noober. All rights reserved.
//

#include "Robot.hpp"


Status Robot::cruise(Direction direction) {
    
    switch (direction) {
            
        case StraightAhead:
            break;
            
        case Left:
            Actuators::turnInPlace(TURN_SLIGHTLY_DURATION, false);
            while (!Tape::tapePresentCentre()) {}
            break;
            
        case Right:
            Actuators::turnInPlace(TURN_SLIGHTLY_DURATION, true);
            while (!Tape::tapePresentCentre()) {}
            break;
            
        case TurnAround:
            Actuators::turnInPlace(TURN_180, true);
            while (!Tape::tapePresentCentre()) {}
            break;
    }
    
    while (true) {

        switch (IR::check()) {
                
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
        
        Tape::Intersection intersection = Tape::atIntersection();
        
        if ( intersection != Tape::None ) {
            lastIntersection = intersection;
            
            Actuators::drive(driveVelocity, 0);
            delay(INTERSECTION_DETECTED_DRIVE_DELAY);
            
            return Intersection;
        }
        
        switch (Collision::check()) {
            case Collision::None:
                break;
            case Collision::Both:
                Actuators::stop();
                return Collided;
                break;
            case Collision::Left:
                Actuators::stop();
                return Collided;
                break;
            case Collision::Right:
                Actuators::stop();
                return Collided;
                break;
        }
        
        Actuators::drive(driveVelocity, Tape::driveCorrection());
    }
}

Status Robot::pickUpPassenger(bool turnRightBefore, bool turnRightAfter) {
    
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

    return successful ? PickupSuccessful : PickupFailed;
}

Status Robot::dropOffPassenger(Direction turn, bool rightSideDropOff) {
    
    switch (turn) {
            
        case StraightAhead:
            break;
            
        case Left:
            Actuators::turnInPlace(TURN_SLIGHTLY_DURATION, false);
            while (!Tape::tapePresentCentre()) {}
            break;
            
        case Right:
            Actuators::turnInPlace(TURN_SLIGHTLY_DURATION, true);
            while (!Tape::tapePresentCentre()) {}
            break;
            
        case TurnAround:
            Actuators::turnInPlace(TURN_180, true);
            while (!Tape::tapePresentCentre()) {}
            break;
    }
    
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
    
    Actuators::turnInPlace(TURN_OFF_TAPE_FACTOR, true);
    while (!Tape::tapePresentCentre()) {}
    
}

void Robot::stop(int duration) {
    Actuators::stop();
    delay(duration);
    
}

