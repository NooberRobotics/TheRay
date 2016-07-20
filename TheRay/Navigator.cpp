//
//  Navigator.cpp
//  TheRay
//
//  Created by Morten Kals on 20/07/2016.
//  Copyright © 2016 Noober. All rights reserved.
//

#include "Navigator.hpp"


Direction Navigator::getTurn() {
    return turns.pop();
}

void Navigator::collisionOccured() {
    int temp = lastNode;
    
    lastNode =  currentNode;
    currentNode = temp;
    
    Navigator::recalculatePath();
    
}

void Navigator::returnToDropoff(bool turnRightForPickup){
    
}

void Navigator::searchForPassenger() {
    
}

void Navigator::recalculatePath() {
    if (returningToDropoff) {
        
        
        
    } else {
        
        
        
    }
}