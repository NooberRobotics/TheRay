//
//  Controller.hpp
//  TheRay
//
//  Copyright © 2016 Noober. All rights reserved.
//

#ifndef Controller_hpp
#define Controller_hpp

#include "Robot.hpp"
#include "Direction.hpp"
#include "Navigator.hpp"
//#include "QueueArray.h"




#include "phys253.h" //TODO:REMOVE after fuse of random nuvmer for detection determining!!!


class Controller {
    
    bool hasPassenger = false;
    
public:
    
    Robot robot = Robot();
    Navigator navigator = Navigator(false);

    void execution();
};

#endif /* Controller_hpp */


