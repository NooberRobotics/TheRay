//
//  Controller.cpp
//  TheRay
//
//  Copyright © 2016 Noober Robotics. All rights reserved.
//
// This class controls the highest level operations of the robot. It is the class
// that tells the other classes when to execute their functions based on the inputs
// it receives.

#include "Controller.hpp"

//The main function that is executed every loop. This function decides on a turn direction,
//and also calls functions in other classes based on what is going on.
void Controller::execution() {
    
    // A local flag to handle certain collision cases.
    bool robotEvadeRight;
    
    // Gets sensor inputs from the Robot class. This includes IR being detected (passengers),
    // collisions with other robots, or intersections reached.
    switch (robot.cruise(turnDirection)) {
            
        //We collided with a sidewalk, wall, or other robot
        case Collided:
            //resets turn direction to its default
            turnDirection = StraightAhead;

            //determines whether it should evade (turn away) to the right or to the left
            robotEvadeRight = navigator.collisionOccurred();

            //tells the robot to turn around and get away from the site of collision
            robot.evade(robotEvadeRight);
            break;
            
        //A passenger was detected on the right side
        case IRRight:
            // determines whether pickup is a valid option
            if (!robot.hasPassenger && (navigatorNotInitialized || navigator.shouldPerformPickup(true))) {
                initializePickup(true);
            }
            //resets turn direction to default
            turnDirection = StraightAhead;
            break;

        //A passenger was detected on the left side
        case IRLeft:
            //determines whether pickup is a valid option
            if (!robot.hasPassenger && (navigatorNotInitialized || navigator.shouldPerformPickup(false))) {
                initializePickup(false);
            }
            //resets turn direction to default
            turnDirection = StraightAhead;
            break;

        // An intersection was reached and we need to decide which path to take.
        case Intersection:
            
            //If it is the first intersection, we begin the navigator
            if (navigatorNotInitialized) initializeNavigator();
            
            //the navigator tells us where to go, and therefore what our turn direction should be
            turnDirection = navigator.getTurn();
            
            //begins dropping off algorithm when needed
            if (navigator.dropOffNow) initializeDropoff();
            
            break;
    }
}

//When we hit the first intersection of the course, this funciton is called.
//Based on which side we see a path, we can determine which node we are at
//and therefore what side we started on (as we do not know this beforehand).
void Controller::initializeNavigator() {
    
    //We saw tape on right, so we started on right side (if looking down at map).
    //Note: our default is the opposite (starting on left).
    if (Tape::tapePresentOnSide() == Tape::Right) {
        navigator.changeStartingPositionToRightTurnFirst();
    }
    //A feature we can use to start on the secondary path if it would be more
    //efficient to do so (based on doll placement at start of match).
    if(startOnOppositePath){
        navigator.changePrimaryPath();
    }
    //assures we do not perform this function again
    navigatorNotInitialized = false;
}

//We detected a passenger and must now pick it up, can be on the left side
//or right side (determined by input parameter).
void Controller::initializePickup(bool rightSidePickup) {

    //determines whether we should continue along the way we were going or
    //go the opposite way after we return to tape
    bool turnRightAfterPickup = navigator.returnToDropoff(rightSidePickup);

    //actually performs the pickup. We now have a passenger and therefore cannot
    //pick up another one.
    robot.pickUpPassenger(rightSidePickup, turnRightAfterPickup);
    robot.hasPassenger = true;
}

//We are at the dropoff point and need to place the passenger down
void Controller::initializeDropoff() {

    //determines which direction we were going and therefore which way we must turn
    //to be facing the dropoff
    if (robot.dropOffPassenger(turnDirection, navigator.dropOffTurnRight)) {
        robot.hasPassenger = false;
        navigator.passengerDroppedOff();
    } else {
        //if we collide before we can dropoff, we turn around and go another route
        //to the dropoff point.
        navigator.collisionOccurred();
        robot.evade();
    }
    //resets turn direction to default
    turnDirection = StraightAhead;
}
