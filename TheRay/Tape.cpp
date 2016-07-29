//
//  Tape.cpp
//  TheRay
//
//  Copyright © 2016 Noober Robotics. All rights reserved.
//

#include "Tape.hpp"

int errors[TAPE_HISTORY_COUNT] = {0};
int errorsIndex = 0;

int error = 0;
int lastError = 0;
int lastDifferentError = 0;

int lastErrorDuration = 0;
int errorDuration = 0;

bool onLeft = false;
bool onMidLeft = false;
bool onMidRight = false;
bool onRight = false;

bool defaultTurnRight = true;

int nextIndex(int index) {
    return (index + TAPE_HISTORY_COUNT) % TAPE_HISTORY_COUNT;
}


// Tape-following code, return error term to robot

Tape::IntersectionType defaultTurnDirection = Tape::None;

int Tape::driveCorrection(bool defaultTurnRight) {
    
    if (defaultTurnRight) defaultTurnDirection = Right;
    else defaultTurnDirection = Left;
    
    int correction = driveCorrection();
    
    defaultTurnDirection = None;
    
    return correction;
}


int Tape::driveCorrection() {
    
    if (onMidLeft && onMidRight) {
        error = 0;
        defaultTurnDirection = None;
    }
    else if (onMidLeft) error = -1; // turn left
    else if (onMidRight) error = +1; // turn right
    else {
        
        if (lastError > 0) error = 5;
        else if (lastError < 0) error = -5;
        else {
            switch (defaultTurnDirection) {
                case Left:
                    error = -10;
                    break;
                    
                case Right:
                    error = 10;
                    break;
                    
                case None:
                    
                    if (onLeft) {
                        defaultTurnDirection = Left;
                        error = -10;
                    }
                    else if (onRight) {
                        defaultTurnDirection = Right;
                        error = 10;
                    }
                    else error = 0;
                    
                    break;
            }

        }
    }
    
    if (error != lastError) {
        lastDifferentError = lastError;
        lastErrorDuration = errorDuration;
        errorDuration = 1;
    }
    
    int p = KP * error;
    int d = (int)(KD * (error - lastDifferentError) / (float)(errorDuration + lastErrorDuration));
    
    double summation = 0;
    for (int j = 0; j < TAPE_HISTORY_COUNT; j++) {
        summation += errors[nextIndex(errorsIndex + j)] / (float)(j+1);
    }
    
    int i = (int) ((KI * summation)/1000);
    
    int con = K*(p + d + i)/100;
    
    errorDuration++;
    lastError = error;
    
    errorsIndex = nextIndex(errorsIndex);
    errors[errorsIndex] = con;
    
    return con;
}


// Intersection detection

bool Tape::atIntersection() {
    return tapePresentSides();
}

bool Tape::atIntersectionWithUpdate() {
    Tape::update();
    return error < 10 ? atIntersection() : false;
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
    return (analogRead(sensor) > THRESH_QRD);
}

void Tape::update() {
    onLeft = detectedTape(QRD_LEFT);
    onMidLeft = detectedTape(QRD_MIDLEFT);
    onMidRight = detectedTape(QRD_MIDRIGHT);
    onRight = detectedTape(QRD_RIGHT);
}