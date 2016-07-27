//
//  IR.cpp
//  TheRay
//
//  Copyright © 2016 Noober. All rights reserved.
//

#include "IR.hpp"

int readingsRight[IR_AVERAGING_SAMPLE_SIZE] = {0};
int readingsLeft[IR_AVERAGING_SAMPLE_SIZE] = {0};

int currentIndex = 0;

int right = 0;
int left = 0;
int midLeft = 0;
int midRight = 0;

IR::Result IR::check() {
    
    currentIndex = (currentIndex + 1) % IR_AVERAGING_SAMPLE_SIZE;
    
    readingsRight[currentIndex] = right;
    readingsLeft[currentIndex] = left;
    
    int right = 0;
    int left = 0;

    for (int i = 0; i<IR_AVERAGING_SAMPLE_SIZE; i++) {
        right += readingsRight[i];
        left += readingsLeft[i];
    }
    
    right = right / IR_AVERAGING_SAMPLE_SIZE;
    left = left / IR_AVERAGING_SAMPLE_SIZE;
    
//    Serial.print("Right: ");
//    Serial.print(right);
//    Serial.print("Left: ");
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

void IR::update(){
    right = analogRead(IR_RIGHT);
    left = analogRead(IR_LEFT);
    midLeft = analogRead(IR_MIDLEFT);
    midRight = analogRead(IR_MIDRIGHT);
}

bool IR::checkLeftWithUpdate(){
    currentIndex = (currentIndex + 1) % IR_AVERAGING_SAMPLE_SIZE;
    
    left = analogRead(IR_LEFT);
    readingsLeft[currentIndex] = left;
    
    int average = 0;
    
    for (int i = 0; i<IR_AVERAGING_SAMPLE_SIZE; i++) {
        average += readingsLeft[i];
    }
    average = average / IR_AVERAGING_SAMPLE_SIZE;
    if(average > THRESH_LOW_IR){
        return true;
    }
    return false;
}


