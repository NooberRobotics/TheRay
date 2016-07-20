//
//  Navigator.cpp
//  TheRay
//
//  Created by Morten Kals on 20/07/2016.
//  Copyright © 2016 Noober. All rights reserved.
//

#include "Navigator.hpp"


Direction Navigator::getTurn() {
    
    lastNode = currentNode;
    currentNode = nextNode;
    
    if (returningToDropoff) {
        nextNode = CityMap::getNextNodeToGoal(currentNode, primaryPath);
    } else {
        nextNodeIndex = CityMap::getNextNodeIndex(nextNodeIndex);
        nextNode = CityMap::getNextNodeToSearch(nextNodeIndex, primaryPath);
    }
    
    return CityMap::getTurnDirection(lastNode, currentNode, nextNode);
}

void Navigator::collisionOccurred() {
    int temp = nextNode;
    nextNode =  currentNode;
    currentNode = temp;
    
    primaryPath = !primaryPath;
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