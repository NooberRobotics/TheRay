//
//  Controller.hpp
//  TheRay
//
//  Copyright © 2016 Noober Robotics. All rights reserved.
//

#ifndef Controller_hpp
#define Controller_hpp

#include "Robot.hpp"
#include "Direction.hpp"
#include "Navigator.hpp"

class Controller {
    
    
    Direction turnDirection = StraightAhead;
    bool navigatorNotInitialized = true;
    
    
    void initializeNavigator();
    void initializePickup(bool rightSidePickup);
    void initializeDropoff();
    bool startOnOppositePath = false;
public:
    
    Controller(){
        robot = Robot();
        navigator = Navigator();
        
        if(Collision::occuredWithUpdate()){
            startOnOppositePath = true;
            Actuators::openClaw();
            delay(OPEN_FINGERS_FOR_PASSENGER_DROP_OFF_DURATION); //lift hand off!
            Actuators::closeClaw();
            while(Collision::occuredWithUpdate()){}
            delay(300);
        }
    }
    
    Robot robot;
    Navigator navigator;

    void execution();
};

#endif /* Controller_hpp */


