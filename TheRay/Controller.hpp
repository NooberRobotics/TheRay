//
//  Controller.hpp
//  TheRay
//
//  Copyright © 2016 Noober. All rights reserved.
//

#ifndef Controller_hpp
#define Controller_hpp

#include "Robot.hpp"
#include <stdio.h>


class Controller {
    
public:
    
    Controller(){
        
        robot = Robot();
        execution();
        
    }

    Robot robot;
    void execution();
    Direction getNextTurn(int lastNode, int currentNode, int nextNode);

    enum State { FindingPassenger, PickingUp, FindingDropoff, DroppingOff };
    
    int previousNode;
    int nextNode;
    int targetNode;
    int goalNode;
    int arrivalMap[21][4];
    int departureMap[21][4];
    
    
//    enum Turn {
//        Left, Right, Straight
//    };

};

#endif /* Controller_hpp */


