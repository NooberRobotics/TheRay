//
//  Robot.cpp
//  TheRay
//
//  Copyright © 2016 Noober. All rights reserved.
//

#include "Robot.hpp"


Status Robot::cruise(Direction direction) {
    
    switch (direction) {
        case Left:
            Actuators::turnInPlace(TURN_SLIGHTLY_DURATION, false);
            
            Actuators::turnInPlace(false);
            while (!Tape::detectedTape(QRD_MIDLEFT)) {}
            
            break;
            
        case Right:
            Actuators::turnInPlace(TURN_SLIGHTLY_DURATION, true);
            
            Actuators::turnInPlace(true);
            while (!Tape::detectedTape(QRD_MIDRIGHT)) {}

            break;
            
        case StraightAhead:
            
            break;
            
        case TurnAround:
            
            Actuators::turnInPlace(TURN_180, true);
            
            Actuators::turnInPlace(true);
            while (!Tape::detectedTape(QRD_MIDRIGHT)) {}
            
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
                return IRLeft;
                break;
                
            case IR::StrongRight:
                return IRRight;
                break;
        }
        
        switch (Collision::check()) {
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
        
        if( Tape::atIntersection() ){
            return Intersection;
        }
        
        Actuators::drive(driveVelocity, Tape::driveCorrection());
        
    }
    
}

Status Robot::pickUpPassenger(bool rightSide) {
    int duration = TURN_FOR_PASSENGER_PICKUP_DURATION;
    int turnDuration = rightSide ? duration : -duration;
    
    Actuators::turnInPlace(turnDuration, rightSide);
    
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
    
    if(successful){
        return PickupSuccessful;
    }
    return PickupFailed;
}

Status Robot::dropOffPassenger(bool rightSide) {
    
    
}

bool Robot::evade() {
    
    Actuators::drive(Actuators::Slow, Actuators::Straight, true);
    delay(REVERSE_TIME_EVADE);
    Actuators::turnInPlace(TURN_180, true);
    return true;
}
