
#include "Controller.hpp"

#include <phys253.h>

LiquidCrystal LCD(26,27,28,16, 17, 18, 19,20,21,22,23);

motorClass motor ;

ServoTINAH RCServo0;    // declare variables for up to eight servos.   Replaced old Servo253 implementation 2015Jan2
ServoTINAH RCServo1;
ServoTINAH RCServo2;

void setup() {
    #include <phys253setup.txt>
    Serial.begin(9600);
    
    RCServo0.write(70);
}

void loop() {

    Robot robot = Robot();
    robot.drive();
}
