//
//  Navigator.cpp
//  TheRay
//
//  Copyright © 2016 Noober. All rights reserved.
//
// This class keeps track of where we are at all times as well as where
// we should be going. Note: it does not know what the map actually looks like.
// It asks the city map what the next node is.

#include "Navigator.hpp"
#include <Arduino.h>

//If we start on the right side (from top view), we need to change from default
void Navigator::changeStartingPositionToRightTurnFirst() {
    currentNode = 18;
    nextNode = 19;
    
    if (returningToDropoff) {
        startNodeIndex = nextNode;
        nextNodeIndex = 0;
        primaryPath = true;
    } else {
        primaryPath = false;
    }
}

//switches to the opposite path that we are currently on
void Navigator::changePrimaryPath(){

    if (!returningToDropoff) {
        primaryPath = !primaryPath;
        nextNodeIndex = CityMap::updateNodeIndex(nextNode, primaryPath);
    }
}

//Determines what happens when we collide with another robot
void Navigator::checkAndHandleCollisionOnTape() {
    
    unsigned long timeFromIntersectionToCollision = timeOfCollision - timeOfIntersection;
//    Serial.print("timeFromIntersectionToCollision: ");
//    Serial.println(timeFromIntersectionToCollision);
    
    if (timeFromIntersectionToCollision < TIME_FREE_OF_INTERSECTION) {
        //we have not cleared the intersection and are likely still over it
        unsigned long timeSinceCollision = millis() - timeOfCollision;
//        Serial.print("timeSinceCollision: ");
//        Serial.println(timeSinceCollision);
        
        if ( timeSinceCollision > timeFromIntersectionToCollision + TIME_MIN_BETWEEN_INTERSECTIONS ) { //we've broken into a collision near intersection
            
            //swaps nodes since we will be facing a different direction
            lastNode = currentNode;
            currentNode = nextNode;
 
            //determines which path we most likely took
            nextNode = CityMap::getLeftmostTurnNode(lastNode, currentNode, turnAroundOppositeDirection);

//            Serial.print("In collisionOnTapeHandler: lastNode: ");
//            Serial.print(lastNode);
//            Serial.print(" currentNode: ");
//            Serial.print(currentNode);
//            Serial.print(" nextNode: ");
//            Serial.print(nextNode);
            
            //special case handling for "expected collisions"
            if (lastNode == 3 || lastNode == 4 || lastNode == 13 || lastNode == 15 ) {
                primaryPath = !primaryPath;
            }
            
            //resets our path to dropoff from our new next node
            if (returningToDropoff) {
                startNodeIndex = nextNode;
                nextNodeIndex = 0;
                
            } else {
                nextNodeIndex = CityMap::updateNodeIndex(nextNode, primaryPath);
            }
        }
    }
    
    //resets flags
    collisionHasOccurred = false;
    turnAroundOppositeDirection = false;
}

//determines our next turn when we get to an intersection
Direction Navigator::getTurn() {
    
    //we collided with another robot
    if (collisionHasOccurred) checkAndHandleCollisionOnTape();
    
    timeOfIntersection = millis();
//    Serial.print("timeOfIntersection: ");
//    Serial.println(timeOfIntersection);
    
    Direction turn;
    
    //we have got to an intersection, so we have reached our previous nextNode
    lastNode = currentNode;
    currentNode = nextNode;
    
    bool slightLeftAt7 = false;
    //special case for odd angled intersection
    if (lastNode == 6 && currentNode == 7 && nextNode == 11) slightLeftAt7 = true;
    
    if (returningToDropoff) {
        
        //finds how to get to the dropoff point from our current location
        nextNode = CityMap::getNextNodeToGoal(startNodeIndex, nextNodeIndex, primaryPath);

        //how to get to our next node from where we are
        turn = CityMap::getTurnDirection(lastNode, currentNode, nextNode);
        
        nextNodeIndex++;

        if (nextNode == 11) {
            //on dropoff stretch

            if (currentNode == 7) {
                //sets the direction we have to turn to drop it off
                dropOffTurnRight = true;
                nextNode = 17;
                lastNode = 7;
            } else if (currentNode == 17) {
                dropOffTurnRight = false;
                nextNode = 7;
                lastNode = 17;
            }
            //we can initialize dropoff sequence
            dropOffNow = true;
            currentNode = 11;
        }
        
    } else {
        //we are not returning to dropoff, we are searching for a passenger

        nextNodeIndex = CityMap::getNextNodeIndex(nextNodeIndex);
        nextNode = CityMap::getNextNodeToSearch(nextNodeIndex, primaryPath);
        
        turn = CityMap::getTurnDirection(lastNode, currentNode, nextNode);
        
        //there is not actually an intersection at node 11, so we have some special handling
        if (nextNode == 11) {
            if(currentNode == 7) {
                nextNodeIndex = CityMap::getNextNodeIndex(nextNodeIndex);
                nextNode = 17;
                lastNode = 7;
            } else if (currentNode == 17) {
                nextNodeIndex = CityMap::getNextNodeIndex(nextNodeIndex);
                nextNode = 7;
                lastNode = 17;
            }
            currentNode = 11;
        }
    }
    
    //special cases for odd angled intersections
    if (lastNode == 14 && currentNode == 16 && turn == StraightAhead) return SlightRight;
    if (lastNode == 8 && currentNode == 6 && nextNode == 7) return SlightLeft;
    if (slightLeftAt7) return SlightLeft;
    
//    Serial.print("Last Node: ");
//    Serial.print(lastNode);
//    Serial.print(" Current Node: ");
//    Serial.print(currentNode);
//    Serial.print(" Next Node: ");
//    Serial.print(nextNode);
//    Serial.print(" Turn: ");
//    Serial.println(turn);
    
    return turn;
}

//we collided, determines if we need to turn right or left to escape
//returns true for a right turn, false for a left turn. Also handles all
//node and path updates.
bool Navigator::collisionOccurred() {
    
    dropOffNow = false;
    
    bool expected = false;

    //checks if the collision was expected
    for (int i = 0; i<7; i++) {
        if (nextNode == CityMap::collisionNodes[i]) expected = true;
    }
    
    if (expected || (collisionHasOccurred && (nextNode == 5 || nextNode == 14))) {
        checkAndHandleCollisionOnTape();
    }
    
    //flips nodes
    int temp = nextNode;
    lastNode = currentNode;
    nextNode =  currentNode;
    currentNode = temp;
    
    if (returningToDropoff) {
        
        if (!expected) {
            primaryPath = !primaryPath;
        }
        
        //special handling for collisions near node 11
        if (nextNode == 11) {            
            if(currentNode == 7) {
                nextNode = 17;
                lastNode = 7;
            } else if (currentNode == 17) {
                nextNode = 7;
                lastNode = 17;
            }
            
            currentNode = 11;
        }

        startNodeIndex = nextNode;
        nextNodeIndex = 0;
        
    } else {
        //we collided while we were searching

        if (expected) {
            nextNodeIndex = CityMap::getNextNodeIndex(nextNodeIndex);
        } else {
            //was an unexpected collision

            //special handling for collisions near node 11
            if (nextNode == 11) {
                if(currentNode == 7) {
                    nextNodeIndex = CityMap::getNextNodeIndex(nextNodeIndex);
                    nextNode = 17;
                    lastNode = 7;
                } else if (currentNode == 17) {
                    nextNodeIndex = CityMap::getNextNodeIndex(nextNodeIndex);
                    nextNode = 7;
                    lastNode = 17;
                }
                currentNode = 11;
            }
            
            primaryPath = !primaryPath;
            nextNodeIndex = CityMap::updateNodeIndex(nextNode, primaryPath);
        }
    }
    
    timeOfCollision = millis();
//    Serial.print("timeOfCollision: ");
//    Serial.println(timeOfCollision);
    
    collisionHasOccurred = true;
    
    //special cases for when we need to turn in the non default direction
    if ((currentNode == 13 && nextNode == 14) || (currentNode == 4 && nextNode == 5)) {
        turnAroundOppositeDirection = true;
        return false; // mechanically turning to the left
    }
    
    if ((currentNode == 20 && nextNode == 17) || (currentNode == 6 && nextNode == 7)) {
        turnAroundOppositeDirection = true;
        return false; // mechanically turning to the left
    }
    
    if (currentNode == 19 && nextNode == 16) {
        turnAroundOppositeDirection = true;
        return false; // mechanically turning to the left
    }
    
    return true; // mechanically turning to the right
}


//gets us to dropoff when we have just picked up a doll. Returns whether
//we should turn right just after picking up based on where we need to go
//along the path.
bool Navigator::returnToDropoff(bool turnRightForPickup) {
    
    primaryPath = true;
    returningToDropoff = true;
    
    bool turnRightAfterPickup;
    
    // Determine next turn-direction and reverse travel drection to avoid turning arround at next node if required
    if(currentNode == 11){
        startNodeIndex = nextNode;
        nextNodeIndex = 0;
        return !turnRightForPickup;
    }
    
    int testNextNode = CityMap::getNextNodeToGoal(nextNode, 0, primaryPath);
    
    //figures out where we need to go to get to next node on dropoff path
    Direction nextTurn = CityMap::getTurnDirection(currentNode, nextNode, testNextNode);
    
    if (nextTurn == TurnAround) {
        int tempNode = currentNode;
        currentNode = nextNode;
        nextNode = tempNode;
        
        turnRightAfterPickup = turnRightForPickup;
    } else {
        turnRightAfterPickup = !turnRightForPickup;
    }
    
    startNodeIndex = nextNode;
    nextNodeIndex = 0;

    return turnRightAfterPickup;
}

//hanldes node updates in the case where a passenger was just dropped off
void Navigator::passengerDroppedOff() {
    //determines if we should be on primary or secondary path
    primaryPath = (nextNode == 7);

    //updates node index
    nextNodeIndex = CityMap::updateNodeIndex(nextNode, primaryPath);

    //resets flags
    dropOffNow = false;
    returningToDropoff = false;
}

//figures out if we should pickup the doll we see. Returns false if it is on
//an edge with invalid IR (eg off the side) or if we have just collided (since we
//do not know where we are until we get to the next intersection).
bool Navigator::shouldPerformPickup(bool rightSide){
    unsigned long timeFromCurrentNode;
    
    if (collisionHasOccurred) return false;
    else timeFromCurrentNode = millis() - timeOfIntersection;
    
    return CityMap::irValid(rightSide, currentNode, nextNode, timeFromCurrentNode );
}
