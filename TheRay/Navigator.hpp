//
//  Navigator.hpp
//  TheRay
//
//  Created by Morten Kals on 20/07/2016.
//  Copyright © 2016 Noober. All rights reserved.
//

#ifndef Navigator_hpp
#define Navigator_hpp

#include "Direction.hpp"
#include "CityMap.hpp"
#include "QueueArray.h"

class Navigator {
    
    int lastNode;
    int currentNode;
    int nextNode;
    
    int nextNodeIndex; 
    
//    QueueArray<Direction> turns;
    
    bool returningToDropoff = false;
    
    bool primaryPath; // TODO: determine which path we start at
    
public:
    
    Navigator(bool firstIntersectionOnRightSide) {
        
        if (firstIntersectionOnRightSide) {
            
            currentNode = 18;
            nextNode = 19;
            
            primaryPath = false;
            
        } else {
            
            currentNode = 0;
            nextNode = 1;
            
            primaryPath = true;
            
        }
    }
    
    Direction getTurn(); // only called at intersections
    
    void collisionOccurred();
    
    void returnToDropoff(bool turnRightForPickup); //first turn stages must be direction reqiered after pickup
    void searchForPassenger();
};


#endif /* Navigator_hpp */
