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


Direction* CityMap::getTurns(int lastGoalNode, int lastNode, int currentNode) {
    
}


Direction CityMap::getTurnDirection(int lastNode, int currentNode, int nextNode){
    int arriving = -1;
    int departing = -1;
    
    for (int heading = 0; heading < 4; index++){
        if(this->arrivalMap[currentNode][heading] == lastNode){
            arriving = heading;
        }
        if(this->departureMap[currentNode][heading] == nextNode){
            departing = heading;
        }
    }
    
    int directionNumber = ((departing - arriving) + 4) % 4;
    
    if (directionNumber == 0) return StraightAhead;
    if (directionNumber == 1) return Right;
    if (directionNumber == 2) return TurnAround;
    if (directionNumber == 3) return Left;
}

//Returns a pointer to an array containing the possible nodes to go to.
//Array is the same length as the number of possible nodes
//The controller should use this like this:
//int *PossibleNextNodes;
//
//PossibleNextNodes = getNextNodes(currentNode);
//for(int i = 0;i < PossibleNextNodes.length();i++){
//	NextNode = *(PossibleNextNodes + i);
//
//}
//TO ACCESS THE POINTER USE *P for the 0th index, *(P+X) for the xth index
//
//IMPORTANT NEED TO USE delete p; WHEN DONE WITH THE POINTER TO AVOID MEMORY LEAKS
int* getNextNodes(int currentNode){
    int count = 0;
    for(int i = 0;i < 4;i++){
        if(departureMap[currentNode][i]	!= -1){
            count++;
        }
    }
    int nodes[count];
    int *p = nodes;
    count = 0;
    for(int j = 0;j < 4;j++){
        if(departureMap[currentNode][j] != -1){
            nodes[count] = departureMap[currentNode][j];
            count++;
        }
    }
    return p;
}


//Calculates the fastest path to the drop off zone
//Returns an array for the node numbers of the path
//Index 0 is currentNode, index n-1 is node 11 (drop off zone)

//NEED JORDANS PATH ALGORITHMS AND MAP LOCATIONS
//SEE getNextNodes for proper syntax
int* getDropOffPath(int currentNode, int attempt){
    int path[5];
    int *p = path;
    
    if(attempt == 1){
        path = primaryRoute[currentNode];
    }else if(attempt == 2){
        path = secondaryRoute[currentNode];
    }
    return p;
}
