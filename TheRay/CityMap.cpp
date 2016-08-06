//
//  Map.cpp
//  TheRay
//
//  Copyright © 2016 Noober Robotics. All rights reserved.
//
// This class represents our internal map. It tells us which nodes are connected to which nodes,
// where each node represents an intersection, and their directions relative to each other. Also
// determines how to get to the dropoff point from any node, as well as distinguishes between the
// primary and secondary paths.

#include "CityMap.hpp"

// gives us the next node along the dropoff path. Works for both primary and secondary paths,
// we just need the indices to start at and of the next node
int CityMap::getNextNodeToGoal(int startNodeIndex, int nextNodeIndex, bool primaryPath) {
    if (primaryPath) {
        return CityMap::primaryDropOffPath[startNodeIndex][nextNodeIndex];
    } else {
        return CityMap::secondaryDropOffPath[startNodeIndex][nextNodeIndex];
    }
}

// returns the index of the next node based on the index of the current node.
int CityMap::getNextNodeIndex(int currentNodeIndex) {
    int index = currentNodeIndex + 1;
    //loops around through the map if the index exceeds the size of the map.
    return index < TRAVERSAL_MAP_SIZE ? index : index - TRAVERSAL_MAP_SIZE;
}

// determines our next node while we are in searching for passenger mode
int CityMap::getNextNodeToSearch(int currentNodeIndex, bool primaryPath) {
    if (primaryPath) {
        return CityMap::primaryTraversalPath[currentNodeIndex];
    } else {
        return CityMap::secondaryTraversalPath[currentNodeIndex];
    }
}

// determines which direction we need to turn to get to our next node, based on what
// our current and last nodes were.
Direction CityMap::getTurnDirection(int lastNode, int currentNode, int nextNode){
    int arriving = -1;
    int departing = -1;
    
    //loops through arrival map to determine the direction we are facing
    for (int heading = 0; heading < 4; heading++){
        if (CityMap::arrivalMap[currentNode][heading] == lastNode) {
            arriving = heading;
        }
        if (CityMap::departureMap[currentNode][heading] == nextNode) {
            departing = heading;
        }
    }
    
    int directionNumber = ((departing - arriving) + 4) % 4;
    
    //the turns we make
    if (directionNumber == 0) return StraightAhead;
    if (directionNumber == 1) return Right;
    if (directionNumber == 2) return TurnAround;
    if (directionNumber == 3) return Left;
    
    //should never be called, safeguard during testing
    Serial.println("GET TURN DIRECTION SERIOUS ERROR!");

    //default in case other cases fail (should never happen)
    return StraightAhead;
}

//sets our index along either the primary or secondary path based on our next node
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

//if we collide while over an intersection, we will turn until we latch onto tape. This
// determines which path we would have taken.
int CityMap::getLeftmostTurnNode(int lastNode, int currentNode, bool actuallyRight) {
    
    int preferenceOrder[3];

    //these correspond to direction numbers, in the order we would have hit them
    // (if they exist)
    if (actuallyRight) {
        preferenceOrder[0] = 1; //right
        preferenceOrder[1] = 0; //straight
        preferenceOrder[2] = 3; //left
        
    } else {
        preferenceOrder[0] = 3; //left
        preferenceOrder[1] = 0; //straight
        preferenceOrder[2] = 1; //right
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
                break;
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

//We should not detect IR on certain sides of certain edges (eg on sides where there is no sidewalk). This function
//determines whether an IR signal is valid on the current edge based on the direction we are going
bool CityMap::irValid(bool rightSide, int currentNode, int nextNode, unsigned long timeOnEdge){
    
    if (rightSide) { //rightside
        for (int i = 0; i < NUM_EDGES_NO_IR_RIGHT; i++) {
            if (CityMap::noSidewalkOnRight[i][0] == currentNode && CityMap::noSidewalkOnRight[i][1] == nextNode) return false;
        }
        
        //special handling of peninsulas, as to not detect signals if we are not on the correct edge for them
        if(currentNode == 1 && nextNode == 6 && timeOnEdge > TIME_1_TO_6_MAX_TIME_RIGHT) return false;
        else if(currentNode == 19 && nextNode == 16 && timeOnEdge > TIME_19_TO_16_MAX_TIME) return false;
        else if(currentNode == 6 && nextNode == 1 && timeOnEdge < TIME_6_TO_1_MIN_TIME) return false;
        else if(currentNode == 16 && nextNode == 17 && timeOnEdge < TIME_16_TO_17_MIN_TIME) return false;
        else if(currentNode == 7 && nextNode == 6 && timeOnEdge > TIME_7_TO_6_MAX_TIME) return false;
        else if(currentNode == 8 && nextNode == 12 && (timeOnEdge > TIME_12_TO_8_MAX_TIME || timeOnEdge < TIME_12_TO_8_MIN_TIME)) return false;
        else if(currentNode == 12 && nextNode == 10 && timeOnEdge > TIME_12_TO_10_MAX_TIME) return false;
        else if(currentNode == 7 && nextNode == 2 && timeOnEdge > TIME_7_TO_2_MAX_TIME) return false;
        else if(currentNode == 6 && nextNode == 5 && timeOnEdge < TIME_16_TO_14_MIN_TIME) return false;
        else if(currentNode == 7 && nextNode == 2 && timeOnEdge < TIME_7_TO_2_MIN_TIME) return false;

        return true;
        
    } else { //leftside
        for (int i = 0; i < NUM_EDGES_NO_IR_LEFT; i++){
            if (CityMap::noSidewalkOnLeft[i][0] == currentNode && CityMap::noSidewalkOnLeft[i][1] == nextNode) return false;
        }
        
        //special handling of peninsulas, as to not detect signals if we are not on the correct edge for them
        if(currentNode == 1 && nextNode == 6 && timeOnEdge > TIME_1_TO_6_MAX_TIME_LEFT) return false;
        else if(currentNode == 16 && nextNode == 19 && timeOnEdge < TIME_16_TO_19_MIN_TIME) return false;
        else if(currentNode == 6 && nextNode == 7 && timeOnEdge < TIME_6_TO_7_MIN_TIME) return false;
        else if(currentNode == 17 && nextNode == 16 && timeOnEdge > TIME_17_TO_16_MAX_TIME) return false;
        else if(currentNode == 12 && nextNode == 8 && (timeOnEdge > TIME_12_TO_8_MAX_TIME || timeOnEdge < TIME_12_TO_8_MIN_TIME)) return false;
        else if(currentNode == 16 && nextNode == 14 && timeOnEdge < TIME_16_TO_14_MIN_TIME) return false;
        else if(currentNode == 8 && nextNode == 10 && timeOnEdge > TIME_8_TO_10_MAX_TIME) return false;
        else if(currentNode == 17 && nextNode == 20 && timeOnEdge > TIME_17_TO_20_MAX_TIME) return false;
        else if(currentNode == 19 && nextNode == 16 && timeOnEdge > TIME_19_TO_16_LEFT_MAX_TIME) return false;
        else if(currentNode == 17 && nextNode == 20 && timeOnEdge < TIME_17_TO_20_MIN_TIME) return false;

        return true;
    }
}
