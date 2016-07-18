//
//  Actuators.cpp
//  TheRay
//
//  Copyright © 2016 Noober. All rights reserved.
//


#include "Actuators.hpp"


void Actuators::turnInPlace(int turnAngle) {
    
    // positive angle -> cv/rigth turn
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

void Actuators::drive(Actuators::Velocity velocity, int turn) {
    motor.speed(MOTOR_LEFT, velocity + turn);
    motor.speed(MOTOR_RIGHT, velocity - turn);
}

void Actuators::drive(Actuators::Velocity velocity, Actuators::Turn turn, bool reverse) {

    int rightSpeed = velocity - turn;
    int leftSpeed = velocity + turn;
    
    if (reverse) {
        rightSpeed = -rightSpeed;
        leftSpeed = -leftSpeed;
    }
    
    motor.speed(MOTOR_LEFT, leftSpeed * MOTOR_LEFT_SIGN_UP);
    motor.speed(MOTOR_RIGHT, rightSpeed * MOTOR_RIGHT_SIGN_UP);
}

void Actuators::raiseArm() {
    while ( !TOUCH_SWITCH_ARM_UP ){
        motor.speed(MOTOR_ARM, VELOCITY_ARM * MOTOR_ARM_SIGN_UP);
    }
}

void Actuators::lowerArm() {
    while ( !TOUCH_SWITCH_ARM_DOWN ){
        motor.speed(MOTOR_ARM, -VELOCITY_ARM * MOTOR_ARM_SIGN_UP);
    }
}

void Actuators::openClaw() {
    RCServo0.write(SERVO_OPEN);
}

void Actuators::closeClaw() {
    RCServo0.write(SERVO_CLOSED);
    
}
void Actuators::stop(){
    motor.speed(MOTOR_LEFT, 0);
    motor.speed(MOTOR_RIGHT, 0);
}