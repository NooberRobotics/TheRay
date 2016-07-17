//
//  Config.hpp
//  TheRay
//
//  Copyright © 2016 Noober Robotics. All rights reserved.
//

#ifndef Config_hpp
//#define Config_hpp

#define KP 38;
#define KD 47;


// Thresholds

#define THRESH_QRD 150
#define THRESH_IR 5

// QRD (ANALOG)

#define QRD_RIGHT 7
#define QRD_LEFT 4
#define QRD_MIDRIGHT 6
#define QRD_MIDLEFT 5

// IR (ANALOG)

#define IR_RIGHT 3
#define IR_LEFT 0
#define IR_MIDRIGHT 2
#define IR_MIDLEFT 1

// ULTRASONIC (DIGITAL)

#define ULTRASONIC_TRIG 1
#define ULTRASONIC_ECHO 2

// TOUCH SWITCHES (DIGITAL)

#define TOUCH_SWITCH_RIGHT 4
#define TOUCH_SWITCH_LEFT 3
#define TOUCH_SWITCH_BACK 5
#define TOUCH_SWITCH_ARM_UP 2
#define TOUCH_SWITCH_ARM_DOWN 3

// MOTORS

#define MOTOR_SERVO 0
#define MOTOR_RIGHT 1
#define MOTOR_LEFT 0 
#define MOTOR_ARM 2

// Positive for right is forward, negative for left is forward
#define MOTOR_ARM_SIGN_UP 1

// SERVO ANGLES

#define SERVO_OPEN 100
#define SERVO_CLOSED 10

// VELOCITIES

#define METERS_PER_SECOND_MULTIPLIER 0.0001 // multiplier to velocities to obtain m/s

#define VELOCITY_SLOW 100
#define VELOCITY_NORMAL 200
#define VELOCITY_FAST 300

#define VELOCITY_ARM_MAX 100
#define VELOCITY_ARM_INTIAL 30
#define VELOCITY_ARM_INCREASE 1
#define VELOCITY_PICKUP 100 //when checking IR signal

#define TURN_SLIGHT 5
#define TURN_HARD 15

// CALIBRATION

#define FINGER_MOTION_DURATION 500 // in milliseconds
#define PICKUP_CALIBRATION_DISTANCE 0.01 //meters

#endif


   

