//
//  Config.hpp
//  TheRay
//
//  Copyright © 2016 Noober Robotics. All rights reserved.
//

#ifndef Config_hpp
#define Config_hpp

// Tape
#define THRESH_QRD 400

#define KP 18
#define KD 100
#define KI 2
#define K 76

#define TAPE_HISTORY_COUNT 3


// IR
#define THRESH_LOW_IR 10
#define THRESH_HIGH_IR 25
#define THRESH_CAP_IR 30

#define THRESH_FRONT_IR 65

#define IR_AVERAGING_SAMPLE_SIZE 3


// Robot operations

// Collision
#define REVERSE_TIME_EVADE 250

#define NUMBER_OF_SWITCH_CHECKS 2


// Intersection
#define INTERSECTION_DETECTED_DRIVE_DELAY 235
#define TIME_MIN_BETWEEN_INTERSECTIONS 1000
#define TIME_FREE_OF_INTERSECTION 1000
#define TIME_QRD_FREE_OF_INTERSECTION 200
#define TIME_IN_INTERSECTION 200


// Pickup
#define TURN_FOR_PASSENGER_PICKUP_DURATION 450
#define DRIVE_FORWARD_BEFORE_TURNING_WHEN_DETECTED_IR 300


// Dropoff
#define DROP_OFF_APPROACH_TIME 900
#define TURN_FOR_PASSENGER_DROPOFF_DURATION 450
#define DROP_OFF_PASSENGER_DRIVE_OFF_TRACK_DELAY 300
#define OPEN_FINGERS_FOR_PASSENGER_DROP_OFF_DURATION 400


// Velocities
#define VELOCITY_SLOW 100
#define VELOCITY_NORMAL 165
#define VELOCITY_FAST 220
#define VELOCITY_NITROUS 255

#define ACCELERATION_FACTOR 10

#define VELOCITY_ARM 100

// Turns

#define TURN_IN_PLACE_VELOCITY 100
#define TURN_OFF_TAPE_DURATION 140
#define TURN_180 900

#define INTERSECTION_TURN_VELOCITY 150
#define INTERSECTION_TURN_DELAY 250

#define TURN_SLIGHT 5
#define TURN_HARD 15



// Pin connectors

// SERVO ANGLES

#define SERVO_OPEN 20
#define SERVO_CLOSED 105
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
#define TOUCH_SWITCH_ARM_UP 4 //lower switch
#define TOUCH_SWITCH_ARM_DOWN 5 //upper switch

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

   

