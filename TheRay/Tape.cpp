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


// Tape-following code, return error term to robot

int Tape::driveCorrection() {
    
    int left = analogRead(QRD_MIDLEFT);
    int right = analogRead(QRD_MIDRIGHT);
    
    if ((left < THRESH_QRD) && (right < THRESH_QRD)) { //both off
        
        if (lastError > 0) error = 5;
        if (lastError <= 0) error = -5;
        
    } else { //path not lost
        
        if ((left > THRESH_QRD) && (right > THRESH_QRD)) error = 0;
        else if ((left > THRESH_QRD) && (right < THRESH_QRD)) error = -1; // turn left
        else if ((left < THRESH_QRD) && (right > THRESH_QRD)) error = +1; // turn right
    }
    
    if (error != lastError) {
        recentError = lastError;
        q = m;
        m = 1;
    }
    
    int p = kp * error;
    int d = (int)((float)kd * (float)(error - recentError) / (float)(q + m));
    int con = p + d;
    
    m++;
    lastError = error;
    
    return con;
}

// Intersection detection

bool detectedTape(int sensor) {
    return (analogRead(sensor) > THRESH_QRD);
}

bool atIntersection() {
    return detectedTape(QRD_LEFT) || detectedTape(QRD_RIGHT);
}

bool tapePresent() {
    return detectedTape(QRD_MIDLEFT) || detectedTape(QRD_MIDRIGHT) || atIntersection();
}
