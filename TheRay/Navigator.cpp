//
//  Navigator.cpp
//  TheRay
//
//  Created by Morten Kals on 20/07/2016.
//  Copyright © 2016 Noober. All rights reserved.
//

#include "Navigator.hpp"
#include <Arduino.h>

void Navigator::changeStartingPositionToRightTurnFirst() {
    currentNode = 18;
    nextNode = 19;
    primaryPath = false;
}


Direction Navigator::getTurn() {
    
    lastNode = currentNode;
    currentNode = nextNode;
    
    Direction turn;
    
    Serial.print("Current Node: ");
    Serial.println(currentNode);
    
    if (returningToDropoff) {
        
        nextNodeIndex++;
        nextNode = CityMap::getNextNodeToGoal(startNodeIndex, nextNodeIndex, primaryPath);

        turn = CityMap::getTurnDirection(lastNode, currentNode, nextNode);
        
        if (nextNode == 11) {
            if(currentNode == 7) {
                dropOffTurnRight = true;
                nextNode = 17;
                lastNode = 7;
            } else if (currentNode == 17){
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
        
        if(nextNode == 11){
            if(currentNode == 7) {
                nextNodeIndex = CityMap::getNextNodeIndex(nextNodeIndex);
                nextNode = 17;
                lastNode = 7;
            } else if(currentNode == 17) {
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
        
        startNodeIndex = currentNode;
        nextNodeIndex = 0;
        
    } else {
        if (expected) {
            nextNodeIndex = CityMap::getNextNodeIndex(nextNodeIndex);
        } else {
            primaryPath = !primaryPath;
            nextNodeIndex = CityMap::updateNodeIndex(nextNode, primaryPath);
        }
    }
}

void Navigator::returnToDropoff(bool turnRightForPickup) {
    primaryPath = true;
    returningToDropoff = true;
    
    // Setting up for handeling of secondary path
    startNodeIndex = currentNode;
    nextNodeIndex = 0;
}

void Navigator::passengerDroppedOff(){
    
    nextNodeIndex = CityMap::updateNodeIndex(currentNode, nextNode == 7);
    dropOffNow = false;
    returningToDropoff = false;
}