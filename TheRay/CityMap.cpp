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
    
    Serial.println("GET TURN DIRECTION SERIOS ERROR!");
    return StraightAhead;
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

int CityMap::getLeftmostTurnNode(int lastNode, int currentNode, bool actuallyRight) {
    
    int preferenceOrder[3];

    if (actuallyRight) {
        preferenceOrder[0] = 1;
        preferenceOrder[1] = 0;
        preferenceOrder[2] = 3;
        
    } else {
        preferenceOrder[0] = 3;
        preferenceOrder[1] = 0;
        preferenceOrder[2] = 1;
    }
    
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
            
            if (directionNumber == preferenceOrder[0]) {
                leftmostDepartingDirection = heading;
                foundBest = 1;
            } else if (directionNumber == preferenceOrder[1]) {
                if (foundBest != 1) {
                    leftmostDepartingDirection = heading;
                    foundBest = 2;
                }
            } else if (directionNumber == preferenceOrder[2]) {
                if (foundBest != 1 && foundBest != 2) {
                    leftmostDepartingDirection = heading;
                    foundBest = 3;
                }
            } else {
                Serial.println("LEFTMOST MAP SERIOUS ERROR!");
            }
        }
    }
    
//    Serial.print("leftmostDepartingDirection: ");
//    Serial.println(leftmostDepartingDirection);

    int node = departureMap[currentNode][leftmostDepartingDirection];
    
//    Serial.print("Leftmost node: ");
//    Serial.println(node);
        
    return node;
}

bool CityMap::irValid(bool rightSide, int currentNode, int nextNode, unsigned long timeOnEdge){
    
    if (rightSide) { //rightside
        for (int i = 0; i < NUM_EDGES_NO_IR_RIGHT; i++) {
            if (CityMap::noSidewalkOnRight[i][0] == currentNode && CityMap::noSidewalkOnRight[i][1] == nextNode) return false;
        }
        
        //special handling of peninsulas
        if(currentNode == 19 && timeOnEdge > TIME_19_TO_16_MAX_TIME) return false;
        else if(currentNode == 6 && timeOnEdge < TIME_6_TO_1_MIN_TIME) return false;
        else return true;
        
    } else { //leftside
        for (int i = 0; i < NUM_EDGES_NO_IR_LEFT; i++){
            if (CityMap::noSidewalkOnLeft[i][0] == currentNode && CityMap::noSidewalkOnLeft[i][1] == nextNode) return false;
        }
        
        //special handling of peninsulas
        if(currentNode == 1 && timeOnEdge > TIME_1_TO_6_MAX_TIME) return false;
        else if(currentNode == 16 && timeOnEdge < TIME_16_TO_19_MIN_TIME) return false;
        else return true;
    }
}