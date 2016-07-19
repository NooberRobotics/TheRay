//
//  Config.hpp
//  TheRay
//
//  Copyright © 2016 Noober Robotics. All rights reserved.
//

#ifndef Config_hpp
#define Config_hpp

#define KP 38;
#define KD 47;


// Thresholds

#define THRESH_QRD 150
#define THRESH_LOW_IR 5
#define THRESH_HIGH_IR 70
#define THRESH_FRONT_IR 30

// QRD (ANALOG)

#define QRD_RIGHT 7
#define QRD_LEFT 4
#define QRD_MIDRIGHT 6
#define QRD_MIDLEFT 5

// IR (ANALOG)

#define IR_RIGHT 0
#define IR_MIDRIGHT 1
#define IR_MIDLEFT 2
#define IR_LEFT 3

// ULTRASONIC (DIGITAL)

#define ULTRASONIC_TRIG 1
#define ULTRASONIC_ECHO 2

// TOUCH SWITCHES (DIGITAL)

#define TOUCH_SWITCH_RIGHT 0
#define TOUCH_SWITCH_LEFT 1
#define TOUCH_SWITCH_BACK 5
#define TOUCH_SWITCH_ARM_UP 5 //lower switch
#define TOUCH_SWITCH_ARM_DOWN 4 //upper switch

// MOTORS

#define MOTOR_SERVO 0
#define MOTOR_RIGHT 2
#define MOTOR_LEFT 1
#define MOTOR_ARM 0

// Positive for right is forward, negative for left is forward
#define MOTOR_ARM_SIGN_UP -1
#define MOTOR_LEFT_SIGN_UP 1
#define MOTOR_RIGHT_SIGN_UP 1

// SERVO ANGLES

#define SERVO_OPEN 50
#define SERVO_CLOSED 150
#define SERVO_OPERATION_TIME 500 //millis

// VELOCITIES

#define METERS_PER_SECOND_MULTIPLIER 0.0001 // multiplier to velocities to obtain m/s

#define VELOCITY_SLOW 75
#define VELOCITY_NORMAL 200
#define VELOCITY_FAST 300

#define VELOCITY_ARM 100
#define VELOCITY_PICKUP 100 //when checking IR signal

#define TURN_SLIGHT 5
#define TURN_HARD 15

#define TURN_IN_PLACE_VELOCITY 100
#define TURN_FOR_PASSENGER_PICKUP_DURATION 500;

#define STOP_FOR_TURNING_DURATION 1000

// CALIBRATION


#define FINGER_MOTION_DURATION 500 // in milliseconds
#define PICKUP_CALIBRATION_DISTANCE 0.01 //meters

#define INTERSECTION_TIME 500 // in milliseconds, duration for intersection sensing to be remembered and passed as active when queried to account for intersections with skewed angles


#endif

   

