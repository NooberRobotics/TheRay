//
//  Controller.cpp
//  TheRay
//
//  Copyright © 2016 Noober. All rights reserved.
//

#include "Controller.hpp"


Direction Controller::getNextTurn(int lastNode, int currentNode, int nextNode){
    
//    
//    int arriving = -1;
//    int leaving = -1;
//    
//    for (int index = 0;index < 4;index++){
//        if(arrivalMap[currentNode][index] == lastNode){
//            arriving = (index + 1);
//        }
//        if(departureMap[currentNode][index] == nextNode){
//            leaving = (index + 1);
//        }
//    }
//    
//    
//    int turnAngle = (leaving - arriving)*90;
    
    int turnAngle = 0;
    
    if (turnAngle >= 135 || turnAngle <= -135){
        return TurnAround;
    }else if(turnAngle < -45){
        return Left;
    }else if(turnAngle > 45){
        return Right;
    }
    
    return StraightAhead;
}

void Controller::execution() {
    
    switch(robot.cruise(nextTurnDirection)){
            
        case Collided:
            robot.evade();
            nextTurnDirection = StraightAhead;
            break;
        case IRRight:
            robot.pickUpPassenger(true);
            nextTurnDirection = StraightAhead;
            break;
        case IRLeft:
            robot.pickUpPassenger(false);
            nextTurnDirection = StraightAhead;
            break;
        case Intersection:
            
            int num = analogRead(QRD_MIDRIGHT) % 3;
            
            if (num == 0) {
                nextTurnDirection = Left;
            } else if (num == 1) {
                nextTurnDirection = Right;
            } else {
                nextTurnDirection = StraightAhead;
            }
            
            break;
        case PickupSuccessful:
            nextTurnDirection = Left;
            break;
        case PickupFailed:
            nextTurnDirection = Right;
            break;
        case DroppedOff:
            break;
    }
    
    execution();
}



//Returns a pointer to an array containing the possible nodes to go to.
//Array is the same length as the number of possible nodes
//void getNextNodes(int currentNode){
////    
////    int count = 0;
////    for(int i = 0;i < 4;i++){
////        if(departureMap[currentNode][i]	!= -1){
////            count++;
////        }
////    }
////    
////    array<int,5> nodes;
////    
////    count = 0;
////    
////    for(int j = 0;j < 4;j++){
////        if(departureMap[currentNode][j] != -1){
////            nodes[count] = departureMap[currentNode][j];
////            count++;
////        }
////    }
////    
////    return nodes;
//}


//Calculates the fastest path to the drop off zone
//Returns an array for the node numbers of the path
//Index 0 is currentNode, index n-1 is node 11 (drop off zone)


//int* getDropOffPath(int currentNode, int attempt){
//    
//    
//    
//    
//}
//
