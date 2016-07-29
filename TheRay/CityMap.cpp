//
//  Map.cpp
//  TheRay
//
//  Copyright © 2016 Noober Robotics. All rights reserved.
//

#include "CityMap.hpp"


int CityMap::getNextNodeToGoal(int startNodeIndex, int nextNodeIndex, bool primaryPath) {
    if (primaryPath) {
        return CityMap::primaryDropOffPath[startNodeIndex][nextNodeIndex];
    } else {
        return CityMap::secondaryDropOffPath[startNodeIndex][nextNodeIndex];
    }
}


int CityMap::getNextNodeIndex(int currentNodeIndex) {
    int index = currentNodeIndex + 1;
    return index < TRAVERSAL_MAP_SIZE ? index : index - TRAVERSAL_MAP_SIZE;
}

int CityMap::getNextNodeToSearch(int currentNodeIndex, bool primaryPath) {
    if (primaryPath) {
        return CityMap::primaryTraversalPath[currentNodeIndex];
    } else {
        return CityMap::secondaryTraversalPath[currentNodeIndex];
    }
}

Direction CityMap::getTurnDirection(int lastNode, int currentNode, int nextNode){
    int arriving = -1;
    int departing = -1;
    
    for (int heading = 0; heading < 4; heading++){
        if (CityMap::arrivalMap[currentNode][heading] == lastNode) {
            arriving = heading;
        }
        if (CityMap::departureMap[currentNode][heading] == nextNode) {
            departing = heading;
        }
    }
    
    int directionNumber = ((departing - arriving) + 4) % 4;
    
    if (directionNumber == 0) return StraightAhead;
    if (directionNumber == 1) return Right;
    if (directionNumber == 2) return TurnAround;
    if (directionNumber == 3) return Left;
    return StraightAhead; // Error state
}

int CityMap::updateNodeIndex(int nextNode, bool primaryPath){
    if (primaryPath){
        for (int i = 0; i < TRAVERSAL_MAP_SIZE; i++){
            if (nextNode == CityMap::primaryTraversalPath[i]) return i;
        }
    } else {
        for (int i = 0; i < TRAVERSAL_MAP_SIZE; i++){
            if (nextNode == CityMap::secondaryTraversalPath[i]) return i;
        }
    }
    return -1;
}

int CityMap::getLeftmostTurnNode(int lastNode, int currentNode) {
    
    int arriving = -1;
    
    for (int heading = 0; heading < 4; heading++){
        if (CityMap::arrivalMap[currentNode][heading] == lastNode) {
            arriving = heading;
            break;
        }
    }
    
    int leftmostDepartingDirection = -1;
    int foundBest = -1;
    
    for (int heading = 0; heading < 4; heading++) {

        int testDepartingNode = CityMap::departureMap[currentNode][heading];
        
        if (testDepartingNode != -1) {
            
            int directionNumber = ((heading - arriving) + 4) % 4;
            
            if (directionNumber == 3) {
                leftmostDepartingDirection = heading;
                foundBest = 1;
            } else if (directionNumber == 0) {
                if (foundBest != 1) {
                    leftmostDepartingDirection = heading;
                    foundBest = 2;
                }
            } else if (directionNumber == 1) {
                if (foundBest != 1 && foundBest != 2) {
                    leftmostDepartingDirection = heading;
                    foundBest = 3;
                }
            } else {
                Serial.println("LEFTMOST MAP SERIOUS ERROR!");
            }
        }
    }
    
    Serial.print("Leftmost Direction: ");
    Serial.println(leftmostDepartingDirection);

    int node = departureMap[currentNode][leftmostDepartingDirection];

    
    Serial.print("Leftmost node: ");
    Serial.println(node);
    
    
    return node;
}