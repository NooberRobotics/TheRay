//
//  IR.cpp
//  TheRay
//
//  Copyright © 2016 Noober. All rights reserved.
//

#include "IR.hpp"

void serialPrint() {
    Serial.print(analogRead(IR_LEFT));
    Serial.print(" ");
    Serial.print(analogRead(IR_MIDLEFT));
    Serial.print(" ");
    Serial.print(analogRead(IR_MIDRIGHT));
    Serial.print(" ");
    Serial.println(analogRead(IR_RIGHT));
}

IR::Result irCheck() {
    int left = analogRead(IR_LEFT);
    int right = analogRead(IR_RIGHT);
    
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
    serialPrint();
}


IR::Result IR::check() {
    IR::Result firstRead = irCheck();
    delay(1);
    IR::Result secondRead = irCheck();
    
    if (firstRead == secondRead) {
        return firstRead;
    }
    return IR::check();
}

bool IR::frontDetected() {
    return (analogRead(IR_MIDLEFT) > THRESH_FRONT_IR) || (analogRead(IR_MIDRIGHT) > THRESH_FRONT_IR);
}

