//
//  Actuators.cpp
//  TheRay
//
//  Copyright © 2016 Noober Robotics. All rights reserved.
//
// This class is for all of our moving parts (motors). This includes
// drivetrain motors, arm motor, and claw servo motor.

#include "Actuators.hpp"

// Allows us to turn without moving forward or backwards, eg do a full 180. Can be done
// for a specified period of time.
void Actuators::turnInPlace(int duration, bool rightTurn) {
    
    Actuators::turnInPlace(rightTurn);
    
    // Delay factor determined experimentally
    delay(duration);
}

// Performs the actual turning done in the previous function. Can be in either direction.
void Actuators::turnInPlace(bool rightTurn) {
    
    // positive angle is CW/right turn
    if (rightTurn) {
        motor.speed(MOTOR_RIGHT, -TURN_IN_PLACE_VELOCITY * MOTOR_RIGHT_SIGN_UP);
        motor.speed(MOTOR_LEFT, TURN_IN_PLACE_VELOCITY * MOTOR_LEFT_SIGN_UP);
    } else {
        motor.speed(MOTOR_RIGHT, TURN_IN_PLACE_VELOCITY * MOTOR_RIGHT_SIGN_UP);
        motor.speed(MOTOR_LEFT, -TURN_IN_PLACE_VELOCITY * MOTOR_LEFT_SIGN_UP);
    }
}

// When we reach an intersection and need to turn.
void Actuators::turnIntersection(bool rightTurn){
    
    if (rightTurn) {
        motor.speed(MOTOR_RIGHT, -KICKBACK * MOTOR_RIGHT_SIGN_UP);
        motor.speed(MOTOR_LEFT, INTERSECTION_TURN_VELOCITY * MOTOR_LEFT_SIGN_UP);
    }
    // left turn
    else {
        motor.speed(MOTOR_RIGHT, INTERSECTION_TURN_VELOCITY * MOTOR_RIGHT_SIGN_UP);
        motor.speed(MOTOR_LEFT, -KICKBACK * MOTOR_LEFT_SIGN_UP);
    }
    delay(INTERSECTION_TURN_DELAY);
}

// Drives forward with a turn correction
void Actuators::drive(int velocity, int turn) {
    motor.speed(MOTOR_LEFT, (velocity + turn) * MOTOR_LEFT_SIGN_UP);
    motor.speed(MOTOR_RIGHT, (velocity - turn) * MOTOR_RIGHT_SIGN_UP);
}

// Allows driving in reverse
void Actuators::drive(int velocity, Actuators::Turn turn, bool reverse) {

    int rightSpeed = velocity - turn;
    int leftSpeed = velocity + turn;
    
    if (reverse) {
        rightSpeed = -rightSpeed;
        leftSpeed = -leftSpeed;
    }
    
    motor.speed(MOTOR_LEFT, leftSpeed * MOTOR_LEFT_SIGN_UP);
    motor.speed(MOTOR_RIGHT, rightSpeed * MOTOR_RIGHT_SIGN_UP);
}

// Returns true if arm is fully up or fully down (depending on input parameter)
bool armNotInPosition(int switchNumber) {
    if (digitalRead(switchNumber)) {
        delay(1);
        //performs a double check just in case motor noise was the cause
        if (digitalRead(switchNumber)) {
            return true;
        }
    }
    return false;
}

//Raises our arm to "fully up" position
void Actuators::raiseArm() {
    unsigned long startTime = millis();
    motor.speed(MOTOR_ARM, VELOCITY_ARM * MOTOR_ARM_SIGN_UP);
    while (armNotInPosition(TOUCH_SWITCH_ARM_UP)){
        if (millis() - startTime > ARM_RAISE_TIME) {
            drive(90, Straight, true);
            delay(80);
            Actuators::stop();
            startTime = millis();
        }
    }
    //Stops the motor when either the endstop switch is pressed or
    //a certain amount of time has passed
    motor.speed(MOTOR_ARM, 0);
}

//Lowers arm to fully down position
void Actuators::lowerArm() {
    motor.speed(MOTOR_ARM, -VELOCITY_ARM * MOTOR_ARM_SIGN_UP);
    while (armNotInPosition(TOUCH_SWITCH_ARM_DOWN)){}
    //stops the motor when the appropriate endstop switch is pressed
    motor.speed(MOTOR_ARM, 0);
}

//moves claw into open position
void Actuators::openClaw() {
    RCServo0.write(SERVO_OPEN);
}

//moves claw into closed position
void Actuators::closeClaw() {
    RCServo0.write(SERVO_CLOSED);
    
}

//stops both drivetrain motors
void Actuators::stop(){
    motor.speed(MOTOR_LEFT, 0);
    motor.speed(MOTOR_RIGHT, 0);
}
