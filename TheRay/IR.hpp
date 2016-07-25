//
//  IR.hpp
//  TheRay
//
//  Copyright © 2016 Noober. All rights reserved.
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
};


#endif /* IR_hpp */
