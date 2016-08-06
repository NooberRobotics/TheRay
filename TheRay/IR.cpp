//
//  IR.cpp
//  TheRay
//
//  Copyright © 2016 Noober Robotics. All rights reserved.
//
// Has all of our functions for detecting IR light (emmitted by the passengers).

#include "IR.hpp"

int indexIR = 0;

int readingsIRRight[IR_AVERAGING_SAMPLE_SIZE] = {0};
int readingsIRLeft[IR_AVERAGING_SAMPLE_SIZE] = {0};
int readingsIRMidRight[IR_AVERAGING_SAMPLE_SIZE] = {0};
int readingsIRMidLeft[IR_AVERAGING_SAMPLE_SIZE] = {0};

//we determine if the average of our previous few readings is above
//a threshold to determine if a passenger is present or if we are close
//to a passenger.
IR::Result IR::check() {
    
    //checks the average of previous few readings to avoid erronous trips due to
    //motor noise.
    int right = averageFromSensor(readingsIRRight);

    int left = averageFromSensor(readingsIRLeft);
    
//    Serial.print("Average right: ");
//    Serial.print(right);
//    Serial.print("   Average left: ");
//    Serial.println(left);
    
    //there is no substantial IR signal
    if (left < THRESH_LOW_IR && right < THRESH_LOW_IR){
        return IR::None;
    }
    
    //there is an IR signal, determine if it is weak or strong and which side it is on.
    if (right >= left){
        if(right > THRESH_HIGH_IR) { return IR::StrongRight; }
        return IR::WeakRight;
    } else {
        if(left > THRESH_HIGH_IR) { return IR::StrongLeft; }
        return IR::WeakLeft;
    }
}

//reads the analog value from a given IR sensor
int readSensor(int sensor) {
    int value = analogRead(sensor);
//    Serial.println(value);

    // we have a maximum cap which we return for any value higher than the cap.
    return value > THRESH_CAP_IR ? THRESH_CAP_IR : value;
}


//moves the index of our previous readings over one so that we can take a new reading
void IR::update() {
    
    indexIR = (indexIR + 1) % IR_AVERAGING_SAMPLE_SIZE;
    
//    Serial.print("Right IR: ");
    readingsIRRight[indexIR] = readSensor(IR_RIGHT);
//    Serial.print("MidRigh IR: ");
//    readingsIRMidRight[indexIR] = readSensor(IR_MIDRIGHT);
//    Serial.print("MidLeft IR: ");
//    readingsIRMidLeft[indexIR] = readSensor(IR_MIDLEFT);
//    Serial.print("LeftIR: ");
    readingsIRLeft[indexIR] = readSensor(IR_LEFT);
}

bool IR::checkLeftWithUpdate(){
    indexIR = (indexIR + 1) % IR_AVERAGING_SAMPLE_SIZE;
    readingsIRLeft[indexIR] = analogRead(IR_LEFT);
    
    if (averageFromSensor(readingsIRLeft) > THRESH_LOW_IR) return true;
    return false;
}

//returns the average of previous readings
int IR::averageFromSensor(int array[]) {
    
    int average = 0;
    
    for (int i = 0; i<IR_AVERAGING_SAMPLE_SIZE; i++) {
        average += array[i];
    }
    
    return average / IR_AVERAGING_SAMPLE_SIZE;
    
}

//clears previous readings
void IR::resetIR() {
    for (int i = 0; i<IR_AVERAGING_SAMPLE_SIZE; i++) {
        readingsIRLeft[i] = 0;
        readingsIRMidLeft[i] = 0;
        readingsIRMidRight[i] = 0;
        readingsIRRight[i] = 0;
    }
}
