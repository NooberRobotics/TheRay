//
//  IR.cpp
//  TheRay
//
//  Copyright © 2016 Noober. All rights reserved.
//

#include "IR.hpp"

enum Signal { None = 0, Weak = THRESH_LOW_IR, Strong = THRESH_HIGH_IR };

Signal sensorReading(int sensor) {
    
    int sensorReading = analogRead(sensor);
    
    if (sensorReading == 0) {
        return None;
    } else if (sensorReading > THRESH_LOW_IR) {
        return Weak;
    } else {
        return Strong;
    }
}

Signal filteredSensorReading(int sensor) {
    
    Signal firstReading = sensorReading(sensor);
    
    if (firstReading != Signal::None) {
        delay(1);
        
        Signal secondReading = sensorReading(sensor);
        
        if (secondReading != Signal::None) {
            delay(1);
            
            Signal thirdReading = sensorReading(sensor);
            
            if ( (firstReading + secondReading + thirdReading) >= (THRESH_HIGH_IR + 2*THRESH_LOW_IR) ) {
                return Strong;
            } else {
                return Weak;
            }
        }
    }
}

IR::Result IR::check() {
    Signal right = filteredSensorReading(IR_RIGHT);
    Signal left = filteredSensorReading(IR_LEFT);
    
    if (right > left) {
        if (right == Signal::Weak) return IR::WeakRight;
        if (right == Signal::Strong) return IR::StrongRight;
    } else {
        if (left == Signal::Weak) return IR::WeakLeft;
        if (left == Signal::Strong) return IR::StrongLeft;
    }
    return None;
}

bool IR::frontDetected() {
    
    Signal midRight = filteredSensorReading(IR_MIDRIGHT);
    Signal midLeft = filteredSensorReading(IR_MIDLEFT);

    return (midRight == Signal::None) && (midLeft == Signal::None) ? false : true;

}


//void serialPrint() {
//    Serial.print(analogRead(IR_LEFT));
//    Serial.print(" ");
//    Serial.print(analogRead(IR_MIDLEFT));
//    Serial.print(" ");
//    Serial.print(analogRead(IR_MIDRIGHT));
//    Serial.print(" ");
//    Serial.println(analogRead(IR_RIGHT));
//}
