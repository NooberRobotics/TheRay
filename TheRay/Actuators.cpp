//
//  Actuators.cpp
//  TheRay
//
//  Copyright © 2016 Noober. All rights reserved.
//


#include "Actuators.hpp"


void Actuators::turnInPlace(int duration, bool rightTurn) {
    
    Actuators::turnInPlace(rightTurn);
    
    // Delay factor determined experimentally
    delay( duration);
}

void Actuators::turnInPlace(bool rightTurn) {
    
    // positive angle -> cv/rigth turn
    if (rightTurn) {
        motor.speed(MOTOR_RIGHT, -TURN_IN_PLACE_VELOCITY * MOTOR_RIGHT_SIGN_UP);
        motor.speed(MOTOR_LEFT, TURN_IN_PLACE_VELOCITY * MOTOR_LEFT_SIGN_UP);
    } else {
        motor.speed(MOTOR_RIGHT, TURN_IN_PLACE_VELOCITY * MOTOR_RIGHT_SIGN_UP);
        motor.speed(MOTOR_LEFT, -TURN_IN_PLACE_VELOCITY * MOTOR_LEFT_SIGN_UP);
    }
}

void Actuators::turnIntersection(bool rightTurn){
    
    if (rightTurn) {
        Serial.println("actuators: Intersection RIGHT");
        motor.speed(MOTOR_RIGHT, -70 * MOTOR_RIGHT_SIGN_UP);
        motor.speed(MOTOR_LEFT, INTERSECTION_TURN_VELOCITY * MOTOR_LEFT_SIGN_UP);
    } else {
        Serial.println("actuators: Intersection LEFT");
        motor.speed(MOTOR_RIGHT, INTERSECTION_TURN_VELOCITY * MOTOR_RIGHT_SIGN_UP);
        motor.speed(MOTOR_LEFT, -70 * MOTOR_LEFT_SIGN_UP);
    }
    delay(INTERSECTION_TURN_DELAY);
}

void Actuators::drive(Actuators::Velocity velocity, int turn) {
    motor.speed(MOTOR_LEFT, (velocity + turn) * MOTOR_LEFT_SIGN_UP);
    motor.speed(MOTOR_RIGHT, (velocity - turn) * MOTOR_RIGHT_SIGN_UP);
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


bool armNotInPosition(int switchNumber) {
    if (digitalRead(switchNumber)) {
        
        delay(1);
        
        if (digitalRead(switchNumber)) {
            return true;
        }
    }
    return false;
}


void Actuators::raiseArm() {
    motor.speed(MOTOR_ARM, VELOCITY_ARM * MOTOR_ARM_SIGN_UP);
    while (armNotInPosition(TOUCH_SWITCH_ARM_UP)){}
    motor.speed(MOTOR_ARM, 0);
}

void Actuators::lowerArm() {
    motor.speed(MOTOR_ARM, -VELOCITY_ARM * MOTOR_ARM_SIGN_UP);
    while (armNotInPosition(TOUCH_SWITCH_ARM_DOWN)){}
    motor.speed(MOTOR_ARM, 0);
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