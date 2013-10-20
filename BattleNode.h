//
//  BattleNode.h
//  CS440-HW2
//
//  Created by Wenzhao Xu on 10/27/12.
//  Copyright (c) 2012 Xu Wenzhao. All rights reserved.
//

#ifndef __CS440_HW2__BattleNode__
#define __CS440_HW2__BattleNode__


#include <iostream>
#include <vector>
#include "BattleField.h"

using namespace std;

class battlenode
{
public:
    
    int depth;
    int previousplayer;
    int player;                     //who will do action based on this node. 
    int actionpoint;
    int finalsituation;             //whether it is the final situation
    int expect_finalvalue;          //The expected value of reaching this node.
    int a,b;
    
    battlenode *parent;             //the pointer to the parent
    vector<battlenode *> nextstep;
    
    battlenode *child[49];          //there are 25 position in the field, so there are 25 children of one node
    
    int fieldposition[49];          //+1,the position is occupied by the blue, -1, the position is occupied by the green
                                    //0 the position is available
    
    int greenvalue,bluevalue;       //the value of green and blue at this node
    
    battlenode(battlefield *field,int i,int depth,int player,battlenode * parent);  //construct function, considering the action result.
                                                                                    //battlefield, action position, action player, last node
    battlenode(int player);         // the initialization for root node.
    
};


#endif /* defined(__CS440_HW2__BattleNode__) */
