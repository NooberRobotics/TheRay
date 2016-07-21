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

class Controller {
    
    bool hasPassenger = false;
    Direction turnDirection = StraightAhead;
    bool navigatorNotInitialized = true;
    
public:
    
    Robot robot = Robot();
    Navigator navigator = Navigator();

    void execution();
};

#endif /* Controller_hpp */


