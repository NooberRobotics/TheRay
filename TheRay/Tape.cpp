//
//  Tape.cpp
//  TheRay
//
//  Copyright © 2016 Noober. All rights reserved.
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


int nextIndex(int index) {
    return (index + TAPE_HISTORY_COUNT) % TAPE_HISTORY_COUNT;
}


// Tape-following code, return error term to robot
int Tape::driveCorrection(bool defaultTurnRight) {
    
    if (onMidLeft && onMidRight) error = 0;
    else if (onMidLeft) error = -1; // turn left
    else if (onMidRight) error = +1; // turn right
    else {
        
        if (lastError > 0) error = 5;
        else if (lastError < 0) error = -5;
        
        else if (onLeft) error = -5;
        else if (onRight) error = 5;
        else error = 0;
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
        summation += errors[nextIndex(errorsIndex + j)] / (double)(j+1);
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
   // if (tapePresentCentre()) return tapePresentSides();
   // return false;
    return tapePresentSides();
}

bool Tape::atIntersectionWithUpdate() {
    Tape::update();
    return atIntersection();
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


bool Tape::tapePresentRight() {
    return onRight;
}

bool Tape::tapePresentLeft() {
    return onLeft;
}

Tape::IntersectionType Tape::tapePresentOnSide() {
    if (onRight) return Tape::Right;
    if (onLeft) return Tape::Left;
    return Tape::None;
}

bool Tape::detectedTape(int sensor) {
    return (analogRead(sensor) > THRESH_QRD);
}

void Tape::update(){
    onLeft = detectedTape(QRD_LEFT);
    onMidLeft = detectedTape(QRD_MIDLEFT);
    onMidRight = detectedTape(QRD_MIDRIGHT);
    onRight = detectedTape(QRD_RIGHT);
}