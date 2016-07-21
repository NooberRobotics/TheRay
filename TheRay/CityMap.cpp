//
//  Map.cpp
//  TheRay
//
//  Created by Erik MacLennan on 2016-07-19.
//  Copyright © 2016 Noober. All rights reserved.
//

#include "CityMap.hpp"

//Takes the lastNode, currentNode and nextNode as input parameters
//Returns the angle to turn. -180 <= angle <= 180
//
//Takes advantage of your turning Function. Theoretically Only Turn -90,0, or 90
//CAN HANDLE 180 THO
//SHOULD BE ABLE TO CALL THE TURNING ALGORITM FROM THIS.


int CityMap::getNextNodeToGoal(int currentNodeIndex, bool primaryPath) {
    if (primaryPath) {
        return CityMap::primaryDropOffPath[currentNodeIndex][0];
    } else {
        return CityMap::secondaryDropOffPath[currentNodeIndex][0];
    }
}


int CityMap::getNextNodeIndex(int currentNodeIndex) {
    int index = currentNodeIndex + 1;
    return index < 39 ? index : index - 39;
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
        if (CityMap::arrivalMap[currentNode][heading] == lastNode){
            arriving = heading;
        }
        if (CityMap::departureMap[currentNode][heading] == nextNode){
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