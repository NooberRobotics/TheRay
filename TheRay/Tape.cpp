//
//  Tape.cpp
//  TheRay
//
//  Copyright © 2016 Noober Robotics. All rights reserved.
//

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

int Tape::driveCorrection(bool defaultTurnRight) {
    
    defaultTurnIsRight = defaultTurnRight;
    defaultTurn = true;
    
    int correction = driveCorrection();
    defaultTurn = false;
    
    return correction;
}

int Tape::driveCorrectionWithUpdate() {
    update();
    return driveCorrection();
}

// Tape-following code, return error term to robot
// Right turn positive
int Tape::driveCorrection() {
    
    if (onMidLeft && onMidRight) error = 0;
    
    else if (onMidRight) error = 1;
    else if (onMidLeft) error = -1;
    
    else if (defaultTurn && defaultTurnIsRight) error = 8;
    else if (defaultTurn && !defaultTurnIsRight) error = -8;
    
    else if (onRight && !onLeft) error = 5;
    else if (onLeft && !onRight) error = -5;
    
    else if (lastError > 0) error = 5;
    else if (lastError < 0) error = -5;
    
    else return TAPE_LOST_ERROR;
    
    if (!tapePresent()) lostCount++;
    else lostCount = 0;
    
    if (lostCount > LOST_COUNT_LIMIT_FOR_SEARCH) return TAPE_LOST_ERROR;
    
    if (error != lastError) {
        lastDifferentError = lastError;
        lastErrorDuration = errorDuration;
        errorDuration = 1;
    }
    
    proportional = error;
    derivative = ((error - lastDifferentError) / (errorDuration + lastErrorDuration) * CLOCK_FREQUENCY);
    integral += error / CLOCK_FREQUENCY;
    
    errorDuration++;
    lastError = error;
    
    return K / 100 * (KP * proportional + KD * derivative + KI * integral);
}

// Intersection detection

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

void Tape::update() {
    onLeft = detectedTape(QRD_LEFT);
    onMidLeft = detectedTape(QRD_MIDLEFT);
    onMidRight = detectedTape(QRD_MIDRIGHT);
    onRight = detectedTape(QRD_RIGHT);
}

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