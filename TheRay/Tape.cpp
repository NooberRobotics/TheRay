//
//  Tape.cpp
//  TheRay
//
//  Copyright © 2016 Noober. All rights reserved.
//

#include "Tape.hpp"

int error = 0;
int lastError = 0;
int recentError = 0;

int kp = KP;
int kd = KD;

int q = 0;
int m = 0;

// temporary valuable initialization
int p;
int d;
int con;

bool left;
bool right;

bool sensorRead(int sensor) {
    return (analogRead(sensor) > THRESH_QRD);
}

// Tape-following code, return error term to robot
int Tape::driveCorrection() {
    
    left = sensorRead(QRD_MIDLEFT);
    right = sensorRead(QRD_MIDRIGHT);
    
    if (!left && !right) { // both off
        
        if (lastError >= 0) error = 5;
        else if (lastError < 0) error = -5;
        
    } else { // tape found
        if (left && right) error = 0;
        else if (left && !right) error = -1; // turn left
        else if (!left && right) error = +1; // turn right
    }
    
    if (error != lastError) {
        recentError = lastError;
        q = m;
        m = 1;
    }
    
    p = kp * error;
//    d = (int)((float)kd * (float)(error - recentError) / (float)(q + m));
//    con = p + d;
    
    m++;
    lastError = error;
    
    return p;
}



// Intersection handeling

int readingsRight[3] = {0};
int readingsLeft[3] = {0};

int currentIndex = 0;

int intersectionRight;
int intersectionLeft;


void resetIntersectionArrays() {
    readingsLeft[0] = 0;
    readingsLeft[1] = 0;
    readingsLeft[2] = 0;
    readingsRight[0] = 0;
    readingsRight[1] = 0;
    readingsRight[2] = 0;
}


Tape::IntersectionType Tape::atIntersection() {
    
    currentIndex = (currentIndex + 1) % 3;
    
    readingsRight[currentIndex] = analogRead(IR_RIGHT);
    readingsLeft[currentIndex] = analogRead(IR_LEFT);
    
    intersectionRight = (readingsRight[0] + readingsRight[1] + readingsRight[2])/3;
    intersectionLeft = (readingsLeft[0] + readingsLeft[1] + readingsLeft[2])/3;
    
    if (intersectionRight > THRESH_QRD) {
        resetIntersectionArrays();
        return Tape::Right;
        
    } else if (intersectionLeft > THRESH_QRD) {
        resetIntersectionArrays();
        return Tape::Left;
    }
    
    return Tape::None;
}

Tape::IntersectionType Tape::tapePresentSides() {
    if (sensorRead(QRD_RIGHT)) return Tape::Right;
    if (sensorRead(QRD_LEFT)) return Tape::Left;
    return Tape::None;
}

bool Tape::tapePresentCentre() {
    return sensorRead(QRD_MIDLEFT) || sensorRead(QRD_MIDRIGHT);
}

bool Tape::tapePresent() {
    return sensorRead(QRD_MIDLEFT) || sensorRead(QRD_MIDRIGHT) ||  sensorRead(QRD_LEFT) || sensorRead(QRD_RIGHT);
}

