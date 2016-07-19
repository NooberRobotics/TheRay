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

Intersection intersection() {
    return (analogRead(QRD_LEFT) > THRESH_QRD) ||  (analogRead(QRD_RIGHT) > THRESH_QRD);
}


bool tapePresent() {
    
}

/*

 default returns none
 when first detecting something on left or right, return detecting
 after given delay, return what is found
 
*/

