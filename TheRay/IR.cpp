//
//  IR.cpp
//  TheRay
//
//  Copyright © 2016 Noober. All rights reserved.
//

#include "IR.hpp"

int readingsRight[IR_AVERAGING_SAMPLE_SIZE];
int readingsLeft[IR_AVERAGING_SAMPLE_SIZE];

int currentIndex = 0;

IR::Result IR::check() {
    
    currentIndex = (currentIndex + 1) % IR_AVERAGING_SAMPLE_SIZE;
    
    readingsRight[currentIndex] = analogRead(IR_RIGHT);
    readingsLeft[currentIndex] = analogRead(IR_LEFT);
    
    int right = 0;
    int left = 0;

    for (int i = 0; i<IR_AVERAGING_SAMPLE_SIZE; i++) {
        right += readingsRight[i];
        left += readingsLeft[i];
    }
    
    Serial.print("Right: ");
    Serial.print(right);
    Serial.print("Left: ");
    Serial.println(left);
    
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

//bool IR::frontDetected() {
//    return (analogRead(IR_MIDLEFT) > THRESH_FRONT_IR) || (analogRead(IR_MIDRIGHT) > THRESH_FRONT_IR);
//}
//

