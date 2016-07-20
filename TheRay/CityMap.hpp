//
//  Map.hpp
//  TheRay
//
//  Created by Erik MacLennan on 2016-07-19.
//  Copyright © 2016 Noober. All rights reserved.
//

#ifndef CityMap_hpp
#define CityMap_hpp

#include "Robot.hpp"
#include "Controller.hpp"



class CityMap {
    
    enum Heading {
        North = 0,
        East = 1,
        South = 2,
        West = 3
    };
    
public:
    CityMap() {
        
    }
    
    //returns array of directions to follow.
    Direction* getTurns(int lastGoalNode, int lastNode, int currentNode);
    
    //Direction directions[10] = {StraightAhead};
    
    Direction getTurnDirection(int lastNode, int currentNode, int nextNode);
    
    int* travelPathToGoal(int currentNode, bool alternatePath = false); // returns array containing nodes in order
    int* travelPathSearch(int currentNode);
    
    
    int arrivalMap[21][4] = {
        {1,-1,-1,-1},
        {2,-1,0,6},
        {-1,-1,1,7},
        {5,-1,-1,-1},
        {-1,-1,-1,5},
        {6,4,3,-1},
        {7,1,5,8},
        {-1,2,6,11},
        {12,6,10,-1},
        {10,-1,-1,-1},
        {-1,8,9,12},
        {-1,7,-1,17},
        {8,-1,10,16},
        {14,-1,-1,-1},
        {16,-1,13,15},
        {-1,14,-1,-1},
        {17,12,14,19},
        {-1,11,16,20},
        {19,-1,-1,-1},
        {20,16,18,-1},
        {-1,17,19,-1},
    };
    
    int departureMap[21][4] = {
        {-1,-1,1,-1},
        {0,6,2,-1},
        {1,7,-1,-1},
        {-1,-1,5,-1},
        {-1,5,-1,-1},
        {3,-1,6,4},
        {5,8,7,1},
        {6,11,-1,2},
        {10,-1,12,6},
        {-1,-1,10,-1},
        {9,12,-1,8},
        {-1,17,-1,7},
        {10,16,8,-1},
        {-1,-1,14,-1},
        {13,15,16,-1},
        {-1,-1,-1,14},
        {14,19,17,12},
        {16,20,-1,11},
        {-1,-1,19,-1},
        {18,-1,20,16},
        {19,-1,-1,17},
    };

};

#endif
