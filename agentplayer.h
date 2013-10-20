//
//  agentplayer.h
//  CS440-HW2
//
//  Created by Wenzhao Xu on 10/27/12.
//  Copyright (c) 2012 Xu Wenzhao. All rights reserved.
//

#ifndef __CS440_HW2__agentplayer__
#define __CS440_HW2__agentplayer__

#include <iostream>
#include "BattleField.h"
#include "BattleNode.h"

#endif /* defined(__CS440_HW2__agentplayer__) */


class player
{
public:
    int playernum;  //+1 blue, -1 green
    int score;      //the score
    int action;     //the action
    int nodeexamined;
    
    int depthlimit_minimax;      //the depth limit for search in minimax search
    int depthlimit_ab;          //the depth limit for search in alpha-beta search
    
    
    player(int num, int dep1, int dep2);
    int Minimax(battlenode *state, battlefield *field);
    int alphabata(battlenode *state, battlefield *field);
    int evaluation(battlenode* state,battlefield *field);
    
    int max_value(battlefield *field,battlenode *state);
    int min_value(battlefield *field,battlenode *state);
    
};