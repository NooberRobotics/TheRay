//
//  Tape.cpp
//  TheRay
//
//  Created by Morten Kals on 16/07/2016.
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

// Constructs for intersection detection

enum Position { Left = QRD_LEFT, MidLeft = QRD_MIDLEFT, MidRight = QRD_MIDRIGHT, Right = QRD_RIGHT};

class Sensor {
public:
    Sensor(Position position) {
        this->position = position;
    }
    
    void update() {
        
        if (analogRead(position) > THRESH_QRD) {
            lastDetected = millis();
            onTape = true;
        } else if (INTERSECTION_TIME > (millis() - this->lastDetected)) {
            onTape = true;
        } else {
            onTape = false;
        }
    }
    
    Position position;
    int lastDetected;
    bool onTape;
};

Sensor sensors[] = { Sensor(Left), Sensor(MidLeft), Sensor(MidRight), Sensor(Right) };

// Intersection detection call, returns structure containing whether left sensor, right sensor or either center sensor has been on tape within the INTERSECTION_TIME

Tape::Directions Tape::intersection() {
    
    Tape::Directions directions = Directions();
    
    for (int i = 0; i<4; i++) {
        
        sensors[i].update();
        
        if (sensors[i].onTape) {
            switch (sensors[i].position) {
                case Left:
                    directions.left = true;
                    break;
                case MidLeft:
                    directions.centre = true;
                    break;
                case MidRight:
                    directions.centre = true;
                    break;
                case Right:
                    directions.right = true;
                    break;
            }
        }
    }
    
    return directions;
}


