//
//  Navigator.cpp
//  TheRay
//
//  Created by Morten Kals on 20/07/2016.
//  Copyright © 2016 Noober. All rights reserved.
//

#include "Navigator.hpp"
#include <Arduino.h>

Direction Navigator::getTurn() {
    
    lastNode = currentNode;
    currentNode = nextNode;
    
    if (returningToDropoff) {
        nextNode = CityMap::getNextNodeToGoal(currentNode, primaryPath);
    } else {
        nextNodeIndex = CityMap::getNextNodeIndex(nextNodeIndex);
        nextNode = CityMap::getNextNodeToSearch(nextNodeIndex, primaryPath);
    }
    
//    Serial.print("Last Node: ");
//    Serial.print(lastNode);
//    Serial.print(" Current Node: ");
//    Serial.print(currentNode);
//    Serial.print(" Next Node: ");
//    Serial.print(nextNode);
//    Serial.print(" Turn: ");
//    
    
    Direction turn = CityMap::getTurnDirection(lastNode, currentNode, nextNode);
//    Serial.println(turn);
    
    return turn;
}

void Navigator::collisionOccurred() {
        
    bool expected = false;
    
    for (int i = 0; i<7; i++) {
        if (nextNode == CityMap::collisionNodes[i]) expected = true;
    }
    
    if (expected) {
        nextNodeIndex = CityMap::getNextNodeIndex(nextNodeIndex);
    } else {
        primaryPath = !primaryPath;
    }
    
    int temp = nextNode;
    nextNode =  currentNode;
    currentNode = temp;
}

void Navigator::returnToDropoff(bool turnRightForPickup) {
    primaryPath = true;
    returningToDropoff = true;
    
    //TODO: determine first
}

void Navigator::searchForPassenger() {
    primaryPath = true;
    returningToDropoff = false;
}