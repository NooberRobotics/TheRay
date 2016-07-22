//
//  Config.hpp
//  TheRay
//
//  Copyright © 2016 Noober Robotics. All rights reserved.
//

#ifndef Config_hpp
#define Config_hpp

// Tape
#define THRESH_QRD 300

#define KP 14;
#define KD 5;


// IR
#define THRESH_LOW_IR 2
#define THRESH_HIGH_IR 40

#define THRESH_FRONT_IR 65

#define IR_AVERAGING_SAMPLE_SIZE 2


// Robot operations

// Collision
#define REVERSE_TIME_EVADE 500

// Intersection
#define INTERSECTION_DETECTED_DRIVE_DELAY 225

// Pickup
#define TURN_FOR_PASSENGER_PICKUP_DURATION 870
#define DRIVE_FORWARD_BEFORE_TURNING_WHEN_DETECTED_IR 480


// Dropoff
#define DROP_OFF_APPROACH_TIME 2000
#define TURN_FOR_PASSENGER_DROPOFF_DURATION 870
#define DROP_OFF_PASSENGER_DRIVE_OFF_TRACK_DELAY 400
#define OPEN_FINGERS_FOR_PASSENGER_DROP_OFF_DURATION 400


// Velocities
#define TURN_IN_PLACE_VELOCITY 100

#define VELOCITY_SLOW 75
#define VELOCITY_NORMAL 200
#define VELOCITY_FAST 255

#define VELOCITY_ARM 100

// Turns
#define TURN_SLIGHT 5
#define TURN_HARD 15

#define TURN_OFF_TAPE_DURATION 300

#define TURN_90 400
#define TURN_180 900
#define TURN_OFF_TAPE_FACTOR 900


// Pin connectors

// SERVO ANGLES

#define SERVO_OPEN 50
#define SERVO_CLOSED 150
#define SERVO_OPERATION_TIME 500 //millis

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
#define MOTOR_ARM_SIGN_UP 1
#define MOTOR_LEFT_SIGN_UP 1
#define MOTOR_RIGHT_SIGN_UP 1


#endif

   

