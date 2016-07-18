//
//  Controller.hpp
//  TheRay
//
//  Copyright © 2016 Noober. All rights reserved.
//

#ifndef Controller_hpp
#define Controller_hpp

#include <stdio.h>

class Controller {
    
    void execution();

    enum State { FindingPassenger, PickingUp, FindingDropoff, DroppingOff };
    
    int previousNode;
    int nextNode;
    int targetNode;
    int goalNode;
    
    enum Turn {
        Left, Right, Straight
    };
    
public:
    
    Controller() {
        execution();
    }
};


#endif /* Controller_hpp */
