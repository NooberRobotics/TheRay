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

class IR {
    
public:
    
    enum Result {
        None,
        WeakLeft,
        WeakRight,
        StrongLeft,
        StrongRight
    };
  
    Result check();
    
}


#endif /* IR_hpp */
