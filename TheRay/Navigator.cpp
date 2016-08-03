//
//  Navigator.cpp
//  TheRay
//
//  Copyright © 2016 Noober. All rights reserved.
//

#include "Navigator.hpp"
#include <Arduino.h>



void Navigator::changeStartingPositionToRightTurnFirst() {
    currentNode = 18;
    nextNode = 19;
    primaryPath = false;
}

void Navigator::checkAndHandleCollisionOnTape() {
    
    unsigned long timeFromIntersectionToCollision = timeOfCollision - timeOfIntersection;
//    Serial.print("timeFromIntersectionToCollision: ");
//    Serial.println(timeFromIntersectionToCollision);
    
    if (timeFromIntersectionToCollision < TIME_FREE_OF_INTERSECTION) {
        
        unsigned long timeSinceCollision = millis() - timeOfCollision;
//        Serial.print("timeSinceCollision: ");
//        Serial.println(timeSinceCollision);
        
        if ( timeSinceCollision > timeFromIntersectionToCollision + TIME_MIN_BETWEEN_INTERSECTIONS ) { //we've broken into a collision near intersection
            
            
            lastNode = currentNode;
            currentNode = nextNode;
            
//            Serial.print("lastNode: );
//            Serial.print(lastNode);
//            Serial.print(" currentNode: ");
//            Serial.println(currentNode);
            
            nextNode = CityMap::getLeftmostTurnNode(lastNode, currentNode, turnAroundOppositeDirection);
            
            if (lastNode == 3 || lastNode == 4 || lastNode == 13 || lastNode == 15 ) {
                primaryPath = !primaryPath;
            }
            
            if (returningToDropoff) {
                startNodeIndex = nextNode;
                nextNodeIndex = 0;
            } else {
                nextNodeIndex = CityMap::updateNodeIndex(nextNode, primaryPath);
            }
        }
    }
    
    collisionHasOccurred = false;
    turnAroundOppositeDirection = false;
}

Direction Navigator::getTurn() {
    
    if (collisionHasOccurred) checkAndHandleCollisionOnTape();
    
    timeOfIntersection = millis();
    
    Direction turn;
    
    lastNode = currentNode;
    currentNode = nextNode;
    
    if (returningToDropoff) {
        
        nextNode = CityMap::getNextNodeToGoal(startNodeIndex, nextNodeIndex, primaryPath);

        turn = CityMap::getTurnDirection(lastNode, currentNode, nextNode);
        
        nextNodeIndex++;
        if (nextNode == 11) {
            if (currentNode == 7) {
                dropOffTurnRight = true;
                nextNode = 17;
                lastNode = 7;
            } else if (currentNode == 17) {
                dropOffTurnRight = false;
                nextNode = 7;
                lastNode = 17;
            }
            dropOffNow = true;
            currentNode = 11;
        }
        
    } else {
        nextNodeIndex = CityMap::getNextNodeIndex(nextNodeIndex);
        nextNode = CityMap::getNextNodeToSearch(nextNodeIndex, primaryPath);
        
        turn = CityMap::getTurnDirection(lastNode, currentNode, nextNode);
        
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


bool Navigator::collisionOccurred() {
    
    dropOffNow = false;
    
    bool expected = false;
    for (int i = 0; i<7; i++) {
        if (nextNode == CityMap::collisionNodes[i]) expected = true;
    }
    
    if (expected || (collisionHasOccurred && (nextNode == 5 || nextNode == 14))) {
        checkAndHandleCollisionOnTape();
    }
    
    int temp = nextNode;
    lastNode = currentNode;
    nextNode =  currentNode;
    currentNode = temp;
    
    if (returningToDropoff) {
        
        if (!expected) {
            primaryPath = !primaryPath;
        }
        
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
        if (expected) {
            nextNodeIndex = CityMap::getNextNodeIndex(nextNodeIndex);
        } else {
            
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
    collisionHasOccurred = true;
    
    if ((currentNode == 13 && nextNode == 14) || (currentNode == 4 && nextNode == 5)) {
        turnAroundOppositeDirection = true;
        return false; // mechanically turning to the left
    }
    
    return true; // mechanically turning to the right
}

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

void Navigator::passengerDroppedOff(){
    primaryPath = (nextNode == 7);
    nextNodeIndex = CityMap::updateNodeIndex(nextNode, primaryPath);
    dropOffNow = false;
    returningToDropoff = false;
}

bool Navigator::shouldPerformPickup(bool rightSide){
    
    if (collisionHasOccurred) return false;
    else unsigned long timeFromCurrentNode = millis() - timeOfIntersection;
    
    return CityMap::irValid(rightSide, currentNode, nextNode, timeFromCurrentNode );
}