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
    delay(turnAngle * TURN_IN_PLACE_DURATION + TURN_IN_PLACE_CONSTANT);
}

void drive(Actuators::Velocity velocity, int turn) {
    motorClass motor = motorClass();

    motor.speed(MOTOR_LEFT, velocity + turn);
    motor.speed(MOTOR_RIGHT, velocity - turn);
}

void drive(Actuators::Velocity velocity, bool turnRight, Actuators::Turn turn, bool reverse = false) {
    motorClass motor = motorClass();

    int rightSpeed = velocity;
    int leftSpeed = velocity;
    
    if (turnRight) {
        rightSpeed = rightSpeed - turn;
        leftSpeed = leftSpeed + turn;
    } else {
        rightSpeed = rightSpeed + turn;
        leftSpeed = leftSpeed - turn;
    }
    
    if (reverse) {
        rightSpeed = -rightSpeed;
        leftSpeed = -leftSpeed;
    }
    
    motor.speed(MOTOR_LEFT, leftSpeed * MOTOR_LEFT_SIGN_UP);
    motor.speed(MOTOR_RIGHT, rightSpeed * MOTOR_RIGHT_SIGN_UP);
}

void raiseArm() {
    motorClass motor = motorClass();
    while ( !TOUCH_SWITCH_ARM_UP ){
        motor.speed(MOTOR_ARM, VELOCITY_ARM * MOTOR_ARM_SIGN_UP);
    }
}

void lowerArm() {
    motorClass motor = motorClass();
    while ( !TOUCH_SWITCH_ARM_DOWN ){
        motor.speed(MOTOR_ARM, -VELOCITY_ARM * MOTOR_ARM_SIGN_UP);
    }
}

void openClaw() {
    
}

void closeClaw() {
    
}