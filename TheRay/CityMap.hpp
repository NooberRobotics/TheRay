//
//  Map.hpp
//  TheRay
//
//  Copyright © 2016 Noober Robotics. All rights reserved.
//

#ifndef CityMap_hpp
#define CityMap_hpp

#include "Direction.hpp"
#include <Arduino.h>


namespace CityMap {
    
    enum Heading {
        North = 1,
        East = 2,
        South = 3,
        West = 4
    };
    
    int getNextNodeToSearch(int currentNodeIndex, bool primaryPath);
    int getNextNodeIndex(int currentNodeIndex);
    
    int getNextNodeToGoal(int startNodeIndex, int nextNodeIndex, bool primaryPath);
    int updateNodeIndex(int nextNode, bool primaryPath);
    bool irValid(bool rightSide, int currentNode, int nextNode);
    
    Direction getTurnDirection(int lastNode, int currentNode, int nextNode);

    int getLeftmostTurnNode(int lastNode, int currentNode);
    
    int* travelPathToGoal(int currentNode, bool alternatePath = false); // returns array containing nodes in order
    int* travelPathSearch(int currentNode);
    
    const int arrivalMap[21][4] = {
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
    
    const int departureMap[21][4] = {
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
    
    
    const int primaryDropOffPath[21][5] = {
        {1,2,7,11,-1},      // 0
        {2,7,11,-1,-1},
        {7,11,-1,-1,-1},
        {5,6,7,11,-1},
        {5,6,7,11,-1},
        {6,7,11,-1,-1},     // 5
        {7,11,-1,-1,-1},
        {11,-1,-1,-1,-1},
        {6,7,11,-1,-1},
        {10,8,6,7,11},
        {8,6,7,11,-1},      // 10
        {-1,-1,-1,-1,-1},   //Already There
        {16,17,11,-1,-1},
        {14,16,17,11,-1},
        {16,17,11,-1,-1},
        {14,16,17,11,-1},   // 15
        {17,11,-1,-1,-1},
        {11,-1,-1,-1,-1},
        {19,20,17,11,-1},
        {20,17,11,-1,-1},
        {17,11,-1,-1,-1},
    };
    
    //-1 if at drop off zone
    const int secondaryDropOffPath[21][7] = {
        {1,6,8,12,16,17,11},    // 0
        {6,8,12,16,17,11,-1},
        {1,6,8,12,16,17,11},
        {5,6,8,12,16,17,11},
        {5,6,8,12,16,17,11},
        {6,8,12,16,17,11,-1},   // 5
        {8,12,16,17,11,-1,-1},
        {6,8,12,16,17,11,-1},
        {12,16,17,11,-1,-1,-1},
        {10,12,16,17,11,-1,-1},
        {12,16,17,11,-1,-1,-1}, // 10
        {-1,-1,-1,-1,-1,-1,-1}, //Already There
        {8,6,7,11,-1,-1,-1},
        {14,16,12,8,6,7,11},
        {16,12,8,6,7,11,-1},
        {14,16,12,8,6,7,11},    // 15
        {12,8,6,7,11,-1,-1},
        {16,12,8,6,7,11,-1},
        {19,16,12,8,6,7,11},
        {16,12,8,6,7,11,-1},
        {19,16,12,8,6,7,11},
    };
    
#define TRAVERSAL_MAP_SIZE 37
    
    const int primaryTraversalPath[TRAVERSAL_MAP_SIZE] = {
        0,1,6,5,4,5,3,5,6,8,10,9,10,12,16,17,11,7,2,1,6,8,12,16,14,15,14,13,14,16,19,20,17,11,7,6,1
    };

    const int secondaryTraversalPath[TRAVERSAL_MAP_SIZE] = {
         18,19,16,14,15,14,13,14,16,12,8,6,7,11,17,20,19,16,12,10,9,10,8,6,5,4,5,3,5,6,1,2,7,11,17,16,19
    };
    
    const int collisionNodes[7] = { 0, 3, 4, 9, 13, 15, 18 };
    const int scanNodes[2] = {5,14};

    const int irSearchNodes[] = {1,5,10,14,19};
    
#define NUM_EDGES_NO_IR_LEFT 12
#define NUM_EDGES_NO_IR_RIGHT 12
    
    const int noSidewalkOnRight[NUM_EDGES_NO_IR_RIGHT][2] = {
        {0,1},
        {1,2},
        {2,7},
        {7,11},
        {11,17},
        {17,20},
        {20,19},
        {19,18},
        {10,12},
        {12,8},
        {8,10},
        {9,10}
    };
    
    const int noSidewalkOnLeft[NUM_EDGES_NO_IR_LEFT][2] = {
        {1,0},
        {2,1},
        {7,2},
        {11,7},
        {17,11},
        {20,17},
        {19,20},
        {18,19},
        {12,10},
        {8,12},
        {10,8},
        {9,10}
    };
    
};

#endif
