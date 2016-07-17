//
//  IR.hpp
//  TheRay
//
//  Created by Morten Kals on 16/07/2016.
//  Copyright © 2016 Noober. All rights reserved.
//

#ifndef IR_hpp
#define IR_hpp

#include "Config.hpp"
#include "Arduino.h"

namespace IR {
    
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
