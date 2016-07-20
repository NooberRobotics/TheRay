//
//  Navigator.hpp
//  TheRay
//
//  Created by Morten Kals on 20/07/2016.
//  Copyright © 2016 Noober. All rights reserved.
//

#ifndef Navigator_hpp
#define Navigator_hpp

#include <stdio.h>
#include "Controller.hpp"

class Navigator {
    
    int lastNode;
    int currentNode;
    int* path;
    int pathIndex;
    
    Direction* turns
    
    bool returningToDropoff = false;

public:
    
    Direction getTurn(); // only called at intersections
    Direction getTurnAfterPickup(bool rightTurnToPickup);
    
    void collisionOccured();
    
    void returnToDropoff();
    void searchForPassenger();
    
};


#endif /* Navigator_hpp */
