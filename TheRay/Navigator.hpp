//
//  Navigator.hpp
//  TheRay
//
//  Copyright © 2016 Noober Robotics. All rights reserved.
//

#ifndef Navigator_hpp
#define Navigator_hpp

#include "Direction.hpp"
#include "CityMap.hpp"
#include "Config.hpp"
#include "Robot.hpp"

class Navigator {
    
    int lastNode;
    int currentNode = 0;
    int nextNode = 1;
    
    int startNodeIndex;
    
    int nextNodeIndex = 1;
    
    bool returningToDropoff = false;
    
    bool primaryPath = true;
    
    unsigned long timeOfIntersection;
    unsigned long timeOfCollision;
    
    void checkAndHandleCollisionOnTape();
    
    bool collisionInBranchesHandled();

    
public:
    
    void changeStartingPositionToRightTurnFirst();
    
    bool dropOffNow = false;
    bool dropOffTurnRight;
    
    Direction getTurn(); // only called at intersections
    
    bool collisionOccurred();
    
    bool returnToDropoff(bool turnRightForPickup); //first turn stages must be direction required after pickup
    void passengerDroppedOff();
    bool shouldPerformPickup(bool rightSide);
};


#endif /* Navigator_hpp */
