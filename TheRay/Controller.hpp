//
//  Controller.hpp
//  TheRay
//
//  Copyright © 2016 Noober. All rights reserved.
//

#ifndef Controller_hpp
#define Controller_hpp

#include "CityMap.hpp"
#include "Robot.hpp"
#include "QueueArray.h"




#include "phys253.h" //TODO:REMOVE after fuse of random nuvmer for detection determining!!!


class Controller {
    
public:
    
    
    
    Controller() {
        
        cityMap = CityMap();
        
        robot = Robot();
        
        nextTurnDirection = StraightAhead;
        
        execution();
    }

    bool hasDoll = false;
    
    Robot robot;
    CityMap cityMap;
    void execution();
        
    Direction nextTurnDirection;

    enum State { FindingPassenger, PickingUp, FindingDropoff, DroppingOff };
    
    
    int previousNode;
    int nextNode;
    int targetNode;
    int goalNode;
   
    
    
//    enum Turn {
//        Left, Right, Straight
//    };

};

#endif /* Controller_hpp */


