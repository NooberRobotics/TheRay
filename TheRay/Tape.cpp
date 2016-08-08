//
//  Tape.cpp
//  TheRay
//
//  Copyright © 2016 Noober Robotics. All rights reserved.
//
// This class contains all of our tape checking, sensing, and following algorithms
// It tells the robot, navigator etc when there is tape present and corrections needed
// to stay on the tape.

#include "Tape.hpp"

bool onLeft = false;
bool onMidLeft = false;
bool onMidRight = false;
bool onRight = false;

bool defaultTurnIsRight = true;
bool defaultTurn = false;

float integral = 0;
short proportional = 0;
short derivative = 0;

int error = 0;
int lastError = 0;
int lastDifferentError = 0;

int lastErrorDuration = 0;
int errorDuration = 0;

int lostCount = 0;

// Sets the default turn direction based on the input parameter, also
// returns the current correction value
int Tape::driveCorrection(bool defaultTurnRight) {
    
    defaultTurnIsRight = defaultTurnRight;
    defaultTurn = true;
    
    int correction = driveCorrection();
    defaultTurn = false;
    
    return correction;
}

// A return function for the robot that returns the correction value
// but also updates the QRD's (makes them read again)
int Tape::driveCorrectionWithUpdate() {
    update();
    return driveCorrection();
}

// Tape-following code, returns error term to robot
// Note: right turn defined as positive
int Tape::driveCorrection() {
    
    //both QRD's on tape
    if (onMidLeft && onMidRight) error = 0;
    
    //Right QRD on tape but left not, must turn slightly right
    else if (onMidRight) error = 1;

    //Left QRD on tape but right not, must turn slightly left
    else if (onMidLeft) error = -1;
    
    //We have lost tape completeley, need a kick to either side based
    //on our default turn
    else if (defaultTurn && defaultTurnIsRight) error = 8;
    else if (defaultTurn && !defaultTurnIsRight) error = -8;
    
    //More checking
    else if (onRight && !onLeft) error = 5;
    else if (onLeft && !onRight) error = -5;
    
    //Based on last error we can guess which side we need to kick
    else if (lastError > 0) error = 5;
    else if (lastError < 0) error = -5;
    
    //if none of these states occur
    else return TAPE_LOST_ERROR;
    
    //keeps track of how long we have been lost for
    if (!tapePresent()) lostCount++;

    //found tape, reset counter
    else lostCount = 0;
    
    //if we have been lost for too long
    if (lostCount > LOST_COUNT_LIMIT_FOR_SEARCH) return TAPE_LOST_ERROR;
    
    //updates previous error
    if (error != lastError) {
        lastDifferentError = lastError;
        lastErrorDuration = errorDuration;
        errorDuration = 1;
    }
    
    //three components of PID

    //proportional just the current error
    proportional = error;

    //derivative using the immediate change
    derivative = ((error - lastDifferentError) / (errorDuration + lastErrorDuration) * CLOCK_FREQUENCY);

    //integral continuously updates, uses long history
    integral += error / CLOCK_FREQUENCY;
    
    errorDuration++;
    lastError = error;
    
    //scaling constants K, KP, KD, KI set by turning
    return K / 100 * (KP * proportional + KD * derivative + KI * integral);
}

// All intersection detection functions

bool Tape::atIntersection() {
    return lostCount < LOST_COUNT_LIMIT_FOR_INTERSECTION_DETECTION ? tapePresentSides() : false;
}

bool Tape::tapePresentCentre() {
    return onMidLeft || onMidRight;
}

bool Tape::tapePresentCentreWithUpdate() {
    onMidLeft = detectedTape(QRD_MIDLEFT);
    onMidRight = detectedTape(QRD_MIDRIGHT);
    return tapePresentCentre();
}


bool Tape::tapePresentSides() {
    return onLeft || onRight;
}

bool Tape::tapePresent() {
    return onMidLeft || onMidRight ||  onLeft || onRight;
}

bool Tape::tapePresentOnSide(bool rightSide) {
    return rightSide ? onRight : onLeft;
}

Tape::IntersectionType Tape::tapePresentOnSide() {
    if (onRight) return Tape::Right;
    if (onLeft) return Tape::Left;
    return Tape::None;
}

bool Tape::detectedTape(int sensor) {
    return analogRead(sensor) > THRESH_QRD;
}

//Determines where tape can be seen (which QRD's are over tape)
void Tape::update() {
    onLeft = detectedTape(QRD_LEFT);
    onMidLeft = detectedTape(QRD_MIDLEFT);
    onMidRight = detectedTape(QRD_MIDRIGHT);
    onRight = detectedTape(QRD_RIGHT);
}

//clears all error terms so that we don't accidentally kick when we shouldn't
//(for example right after a pickup)
void Tape::resetErrors() {
    integral = 0;
    proportional = 0;
    derivative = 0;
    
    error = 0;
    lastError = 0;
    lastDifferentError = 0;
    
    lastErrorDuration = 0;
    errorDuration = 0;
}
