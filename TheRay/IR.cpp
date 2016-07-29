//
//  IR.cpp
//  TheRay
//
//  Copyright © 2016 Noober Robotics. All rights reserved.
//

#include "IR.hpp"

int indexIR = 0;

int readingsIRRight[IR_AVERAGING_SAMPLE_SIZE] = {0};
int readingsIRLeft[IR_AVERAGING_SAMPLE_SIZE] = {0};
int readingsIRMidRight[IR_AVERAGING_SAMPLE_SIZE] = {0};
int readingsIRMidLeft[IR_AVERAGING_SAMPLE_SIZE] = {0};

IR::Result IR::check() {
    
    int right = averageFromSensor(readingsIRRight);
//    int midRight = averageFromSensor(readingsIRMidRight);
//    int midLeft = averageFromSensor(readingsIRMidLeft);
    int left = averageFromSensor(readingsIRLeft);
    
//    Serial.print("Average right: ");
//    Serial.print(right);
//    Serial.print("   Average left: ");
//    Serial.println(left);
    
    if (left < THRESH_LOW_IR && right < THRESH_LOW_IR){
        return IR::None;
    }
    
    if (right >= left){
        if(right > THRESH_HIGH_IR) { return IR::StrongRight; }
        return IR::WeakRight;
    } else {
        if(left > THRESH_HIGH_IR) { return IR::StrongLeft; }
        return IR::WeakLeft;
    }
}

int readSensor(int sensor) {
    int value = analogRead(IR_RIGHT);
//    Serial.println(value);
    return value > THRESH_CAP_IR ? THRESH_CAP_IR : value;
}


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

int IR::averageFromSensor(int array[]) {
    
    int average = 0;
    
    for (int i = 0; i<IR_AVERAGING_SAMPLE_SIZE; i++) {
        average += array[i];
    }
    
    return average / IR_AVERAGING_SAMPLE_SIZE;
    
}

