//
//  Actuators.cpp
//  TheRay
//
//  Created by Morten Kals on 16/07/2016.
//  Copyright © 2016 Noober. All rights reserved.
//

#include "Actuators.hpp"


void turnInPlace(int turnAngle) {
    // positive angle -> cv/rigth turn
  
    motorClass motor = motorClass();
    if (turnAngle > 0) {
    motor.speed(MOTOR_RIGHT, -TURN_IN_PLACE_VELOCITY);
        motor.speed(MOTOR_LEFT, TURN_IN_PLACE_VELOCITY);
    } else {
        motor.speed(MOTOR_RIGHT, TURN_IN_PLACE_VELOCITY);
        motor.speed(MOTOR_LEFT, -TURN_IN_PLACE_VELOCITY);
    }

    // Delay factor determined experimentally
    delay(turnAngle * 10);
    
    // TODO: Determining duration: set in state, count down to it
    // not linear - more time to go trough first degrees..
}

void drive(Actuators::Velocity velocity, int turn) {
    
}

void drive(Actuators::Velocity velocity, bool turnRight, Actuators::Turn turn, bool reverse = false) {
    
}

void raiseArm() {
    motorClass motor = motorClass();
    while ( !TOUCH_SWITCH_ARM_UP ){
        motor.speed(MOTOR_ARM, VELOCITY_ARM);
    }
}

void lowerArm() {
    motorClass motor = motorClass();
    while ( !TOUCH_SWITCH_ARM_DOWN ){
        motor.speed(MOTOR_ARM, -VELOCITY_ARM);
    }
}

void openClaw() {
    
}

void closeClaw() {
    
}