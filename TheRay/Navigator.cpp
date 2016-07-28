//
//  Navigator.cpp
//  TheRay
//
//  Created by Morten Kals on 20/07/2016.
//  Copyright © 2016 Noober. All rights reserved.
//

#include "Navigator.hpp"
#include <Arduino.h>


bool collisionHasOccurred = false;

unsigned long currentTime() {
    return millis();
}

void Navigator::changeStartingPositionToRightTurnFirst() {
    currentNode = 18;
    nextNode = 19;
    primaryPath = false;
}

void Navigator::checkAndHandleCollisionOnTape() {
    
    
    unsigned long timeFromIntersectionToCollision = timeOfCollision - timeOfIntersection;
    
//    Serial.println("in 1");
//    
//    Serial.print("intersection: ");
//    Serial.println(timeOfIntersection);
//    
//    Serial.print("collision: ");
//    Serial.println(timeOfCollision);
//    
//    Serial.print("time from intersection to collision: ");
//    Serial.println(timeFromIntersectionToCollision);
    
    
    if (timeFromIntersectionToCollision < TIME_FREE_OF_INTERSECTION) {
        
//        Serial.println("in 2");
        
        unsigned long timeSinceCollision = currentTime() - timeOfCollision;
//        
//        Serial.print("Time since collision: ");
//        Serial.println(timeSinceCollision);
//        
        if ( timeSinceCollision > timeFromIntersectionToCollision + TIME_MIN_BETWEEN_INTERSECTIONS ) {
            
//            Serial.println("in 3");
            
            // we got to another intersection, so must've taken the most immediate left turn at the previous intersection
            
            lastNode = currentNode;
            currentNode = nextNode;
            nextNode = CityMap::getLeftmostTurnNode(lastNode, currentNode);
            
            if (returningToDropoff) {
                startNodeIndex = nextNode;
                nextNodeIndex = 0;
            } else {
                nextNodeIndex = CityMap::updateNodeIndex(nextNode, primaryPath);
            }
        }
    }
}

Direction Navigator::getTurn() {
    
    if (collisionHasOccurred) checkAndHandleCollisionOnTape();
    collisionHasOccurred = false;
    
    timeOfIntersection = currentTime();
    
    Serial.print("Setting time: ");
    Serial.println(timeOfIntersection);
    
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
    
    Serial.print("Last Node: ");
    Serial.print(lastNode);
    Serial.print(" Current Node: ");
    Serial.print(currentNode);
    Serial.print(" Next Node: ");
    Serial.print(nextNode);
    Serial.print(" Turn: ");
    Serial.println(turn);
    
    return turn;
}

void Navigator::collisionOccurred() {
    
    timeOfCollision = currentTime();
    collisionHasOccurred = true;
    
    bool expected = false;

    for (int i = 0; i<7; i++) {
        if (nextNode == CityMap::collisionNodes[i]) expected = true;
    }
    
    int temp = nextNode;
    nextNode =  currentNode;
    currentNode = temp;
    
    if (returningToDropoff) {
        if (!expected) {
            primaryPath = !primaryPath;
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
}

bool Navigator::returnToDropoff(bool turnRightForPickup) {
    
    primaryPath = true;
    returningToDropoff = true;
    
    bool turnRightAfterPickup;
    
    // Setting up for handling of dropoff path
    
    // Determine next turn-direction and reverse travel drection to avoid turning arround at next node if required
    
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