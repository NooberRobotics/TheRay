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
    int* path;
    int pathIndex;
    
    QueueArray<Direction> turns;
    
    bool returningToDropoff = false;
    
public:
    
    Direction getTurn(); // only called at intersections
    
    void collisionOccured();
    
    void returnToDropoff(bool turnRightForPickup); //first turn stages must be direction reqiered after pickup
    void searchForPassenger();
    
    
    
    void recalculatePath() {

    
};


#endif /* Navigator_hpp */
