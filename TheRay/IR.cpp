//
//  IR.cpp
//  TheRay
//
//  Copyright © 2016 Noober. All rights reserved.
//

#include "IR.hpp"

int irReadingsRight[4] = {0};
int irReadingsLeft[4] = {0};

int irCurrentIndex = 0;

int irRight;
int irLeft;

IR::Result IR::check() {
    
    irCurrentIndex = (irCurrentIndex + 1) % 4;
    
    irReadingsRight[irCurrentIndex] = analogRead(IR_RIGHT);
    irReadingsLeft[irCurrentIndex] = analogRead(IR_LEFT);
    
    irRight = (irReadingsRight[0] + irReadingsRight[1] + irReadingsRight[2] + irReadingsRight[3])/4;
    irLeft = (irReadingsLeft[0] + irReadingsLeft[1] + irReadingsLeft[2] + irReadingsLeft[3])/4;
    
//    Serial.print("Right: ");
//    Serial.print(irRight);
//    Serial.print("Left: ");
//    Serial.println(irLeft);
    
    if (irLeft < THRESH_LOW_IR && irRight < THRESH_LOW_IR){
        return IR::None;
    }
    
    if (irRight >= irLeft){
        if(irRight > THRESH_HIGH_IR) { return IR::StrongRight; }
        return IR::WeakRight;
    } else {
        if(irLeft > THRESH_HIGH_IR) { return IR::StrongLeft; }
        return IR::WeakLeft;
    }
}

//bool IR::frontDetected() {
//    return (analogRead(IR_MIDLEFT) > THRESH_FRONT_IR) || (analogRead(IR_MIDRIGHT) > THRESH_FRONT_IR);
//}


