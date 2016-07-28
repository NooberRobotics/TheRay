//
//  IR.cpp
//  TheRay
//
//  Copyright © 2016 Noober. All rights reserved.
//

#include "IR.hpp"

int indexIR = 0;

int readingsIRRight[IR_AVERAGING_SAMPLE_SIZE] = {0};
int readingsIRLeft[IR_AVERAGING_SAMPLE_SIZE] = {0};
int readingsIRMidRight[IR_AVERAGING_SAMPLE_SIZE] = {0};
int readingsIRMidLeft[IR_AVERAGING_SAMPLE_SIZE] = {0};

IR::Result IR::check() {

    int right = checkSensor(readingsIRRight);
    int midRight = checkSensor(readingsIRMidRight);
    int midLeft = checkSensor(readingsIRMidLeft);
    int left = checkSensor(readingsIRLeft);
    
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

void IR::update(){
    
    indexIR = (indexIR + 1) % IR_AVERAGING_SAMPLE_SIZE;

    readingsIRRight[indexIR] = analogRead(IR_RIGHT);
    readingsIRMidRight[indexIR] = analogRead(IR_MIDRIGHT);
    readingsIRMidLeft[indexIR] = analogRead(IR_MIDLEFT);
    readingsIRLeft[indexIR] = analogRead(IR_LEFT);
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
    
    return (int) ((double) average / (double) IR_AVERAGING_SAMPLE_SIZE);

}


