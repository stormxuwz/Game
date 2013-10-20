//
//  agentplayer.cpp
//  CS440-HW2
//
//  Created by Wenzhao Xu on 10/27/12.
//  Copyright (c) 2012 Xu Wenzhao. All rights reserved.
//

#include <vector>
#include <algorithm>
#include "agentplayer.h"
#include "BattleField.h"

using namespace std;


int player::Minimax(battlenode *state,battlefield *field)
{
    int depth=state->depth;
    int temp_num=0;

    int score_max=-999999;
    int score_min=999999;
    int child_score=0;
    int state_score=0;
    int player=state->player;
    int action_max;
    int action_min;
    
    state->finalsituation=1;                //Preassume this node is the last node.(the end of the game)
    
    if (state->depth==depthlimit_minimax)   //If the depth of this state reach its limit, then return its evaluation function
    {
        state_score=evaluation(state,field);
        state->expect_finalvalue=state_score;
    }
    else
    {
        for(int row=0;row<7;row++)
            for(int col=0;col<7;col++)
            {
                temp_num=row*7+col;
                state->child[temp_num]=NULL;
                
                if (state->fieldposition[temp_num]==0)
                {
                    state->finalsituation=0;                   //The node has its child, so the game is not end
                    state->child[temp_num]=new battlenode(field, temp_num, depth+1, state->player,state);
                    nodeexamined+=1;
                    
                    //minimax algorithm
                    
                    child_score=Minimax(state->child[temp_num], field);     //minimax function to return the minimax value. 
    
                    
                    if (score_max<child_score||score_max==child_score)      //update the best choice
                    {
                        score_max=child_score;
                        action_max=temp_num;
                    }
                    if (score_min>child_score||score_min==child_score)      //update the best choice
                    {
                        score_min=child_score;
                        action_min=temp_num;
                    }
                }
            }
        
        if(state->finalsituation==1)                 //if it has no child node, return its bluevalue;
            return state->bluevalue;
        
        
        if(player==1)                               //current player is blue, return the maximum score and action
        {
            state_score=score_max;
            action=action_max;
            
        }
        else                                        //current player is green, return the minimum score and action
        {
            state_score=score_min;
            action=action_min;
    
        }
    }
    state->expect_finalvalue=state_score;
    return state_score;
}

int player::evaluation(battlenode *state, battlefield *field)
{
    //the evaluation only consider the para method.
    
    //sorting the rest available position based on the value left. 
    int temp_num;
    int count=0;
    int turn=1;
    int scoreA,scoreB,eva_score;
    vector<int> restvalue;
    
    scoreA=state->bluevalue;
    scoreB=state->bluevalue;
    
//    turn=state->player;         //current turn
    
    for (int row=0; row<7; row++)
        for(int col=0;col<7;col++)
        {
            temp_num=row*7+col;
            if (state->fieldposition[temp_num]==0) {
                restvalue.push_back(field->fieldvalue[temp_num]);       //find the available point
                count+=1;
            }
        }
    
    sort(restvalue.begin(),restvalue.end());                            //sort the value
    

    for(int i=count-1;i>-1;i--)
    {
        if (turn==1)
        {
            scoreA=scoreA+restvalue[i];
            turn=-1;
        }
        else
        {
            scoreB=scoreB+restvalue[i];
            turn=1;
    
        }
    }
    
    if(state->player==1)
        eva_score=scoreA;
    else
        eva_score=scoreB;
    
    return eva_score;
}


int player::alphabata(battlenode *state, battlefield *field)
{
    int v;
    
    state->a=-9999;
    state->b=9999;
    
    if (state->player==1)
    {
        v=max_value(field,state);
    }
    
    else
        v=min_value(field,state);
    
    
    return v;
}

int player::max_value(battlefield *field,battlenode *state)
{
    int v=0;
    int temp_num;
    int depth=state->depth;
    int valueofnode;
    int action_max;
    
    state->finalsituation=1;
    
    if (state->depth==depthlimit_ab)
    {
        state->expect_finalvalue=evaluation(state, field);
        return state->expect_finalvalue;
    
    }
    v=-9999;
    
    
    for(int row=0;row<7;row++)
        for(int col=0;col<7;col++)
        {
            temp_num=row*7+col;
            state->child[temp_num]=NULL;
            
            if (state->fieldposition[temp_num]==0)
            {
                state->finalsituation=0;                             //The game is not end
                state->child[temp_num]=new battlenode(field, temp_num, depth+1, state->player,state);
                nodeexamined+=1;
                valueofnode=min_value(field, state->child[temp_num]);
                
                if (valueofnode>v) {            
                    v=valueofnode;              //find the maximum score of child nodes
                    action_max=temp_num;        //record the corresponding action. 
                }
                                
                if (v>state->b || v==state->b) {        //the score of child node is larger than the parent's beta
                    state->expect_finalvalue=v;
                    return v;
                }

                //a=max(a,v);
                if (v>state->a)
                {
                    state->a=v;
                }
                
            }
        }
    
    if(state->finalsituation==1)                 //if it has no child node, return its bluevalue;
    {
        state->expect_finalvalue=state->bluevalue;
        return state->bluevalue;
    }
//  action=1;
    state->expect_finalvalue=v;
    action=action_max;
    return v;
}

int player::min_value(battlefield *field,battlenode *state)
{
    int v=0;
    int temp_num;
    int valueofnode;
    int action_min;
    int depth=state->depth;
    state->finalsituation=1;
    
    if (state->depth==depthlimit_ab)
    {
        state->expect_finalvalue=evaluation(state, field);
        return state->expect_finalvalue;
    }
    v=9999;
    
    
    for(int row=0;row<7;row++)
        for(int col=0;col<7;col++)
        {
            temp_num=row*7+col;
            state->child[temp_num]=NULL;
            
            if (state->fieldposition[temp_num]==0)
            {
                state->finalsituation=0;                             //The game is not end
                state->child[temp_num]=new battlenode(field, temp_num, depth+1, state->player,state);
                nodeexamined+=1;
                valueofnode=max_value(field, state->child[temp_num]);
                
                if (valueofnode<v) {
                    v=valueofnode;
                    action_min=temp_num;
                }
                
                if (v<state->a||v==state->a) {
                    state->expect_finalvalue=v;
                    return v;
                }

                //                b=min(b,v);
                if(v<state->b)
                {
                    state->b=v;
                }
            }
        }
    
    if(state->finalsituation==1)                 //if it has no child node, return its bluevalue;
    {
        state->expect_finalvalue=state->bluevalue;
        return state->bluevalue;
    }
    state->expect_finalvalue=v;
    action=action_min;
    return v;
}

player::player(int num, int depth1, int depth2)
{
    playernum=num;
    depthlimit_minimax=depth1;
    depthlimit_ab=depth2;
    nodeexamined=0;
}