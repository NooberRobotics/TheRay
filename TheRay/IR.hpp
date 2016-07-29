//
//  IR.hpp
//  TheRay
//
//  Copyright © 2016 Noober Robotics. All rights reserved.
//

#ifndef IR_hpp
#define IR_hpp

#include "Config.hpp"
#include <Arduino.h>

namespace IR {
    
    enum Result {
        None,
        WeakLeft,
        WeakRight,
        StrongLeft,
        StrongRight
    };
  
    Result check();

    void update();
    void resetIR();
    
    int averageFromSensor(int array[]);
    bool checkLeftWithUpdate();
};


#endif /* IR_hpp */
