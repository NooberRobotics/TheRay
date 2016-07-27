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
#include "Config.hpp"


class Navigator {
    
    int lastNode;
    int currentNode = 0;
    int nextNode = 1;
    bool onBranch = false;
    
    int startNodeIndex;
    
    int nextNodeIndex = 1;
    
    bool returningToDropoff = false;
    
    bool primaryPath = true; // TODO: determine which path we start at
    
    Direction getTurnOnBranch();
    unsigned long timeOfIntersection;
    unsigned long timeOfCollision;
    
    void checkAndHandleCollisionOnTape();
    
public:
    void goOntoBranch();
    void changeStartingPositionToRightTurnFirst();
    
    bool irScanNow = false;
    bool dropOffNow = false;
    bool dropOffTurnRight;
 
    
    Direction getTurn(); // only called at intersections
    
    void collisionOccurred();
    
    bool returnToDropoff(bool turnRightForPickup); //first turn stages must be direction reqiered after pickup
    void passengerDroppedOff();
};


#endif /* Navigator_hpp */
