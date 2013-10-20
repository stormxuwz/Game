//
//  BattleNode.cpp
//  CS440-HW2
//
//  Created by Wenzhao Xu on 10/27/12.
//  Copyright (c) 2012 Xu Wenzhao. All rights reserved.
//

#include "BattleNode.h"

int allyaround(int position, battlefield *field, int player, int *fieldposition)       //check whether there is friendly fire near, return 1 true, 0 none
{
    
    if(fieldposition[position+7]==player)
        return 1;

    if(fieldposition[position-7]==player)
        return 1;
    
    if(fieldposition[position+1]==player)
        return 1;
    
    if(fieldposition[position-1]==player)
        return 1;
    
    return 0;
}

battlenode::battlenode(int p)       //initialize for the root node
{
    player=p;
    depth=0;
    previousplayer=0;
    for (int i=0;i<49;i++)
    {
        fieldposition[i]=-99;
    }
    
    for(int row=1;row<6;row++)
        for(int col=1;col<6;col++)
            fieldposition[row*7+col]=0;
    
    bluevalue=0;
    parent=this;
    greenvalue=0;
    a=-9999;
    b=9999;
}


battlenode::battlenode(battlefield *field, int position, int n, int actionplayer,battlenode *parent1) //initialize for the next node
{
    depth=n;
    greenvalue=0;
    bluevalue=0;
    a=parent1->a;
    b=parent1->b;
    
    parent=parent1;
    
    //inherent last battle situation
    
    for (int i=0; i<49; i++) {
        fieldposition[i]=parent1->fieldposition[i];
    }
    
    int temp;
    int temp_num;
    int ally=0;
    
    actionpoint=position;
    
    ally=allyaround(position, field, actionplayer,fieldposition);           //find whether there is alliance near the position
    
    if(ally==0)           // no allyaround here, use Commando Para Drop
        fieldposition[position]=actionplayer;
 
    else                  //ally here, use M1 Death Blitz, make all the surrending point as the aliance
    {
        
        fieldposition[position]=actionplayer;

        temp=position+1;
        if(fieldposition[temp]>-99 && fieldposition[temp]==-actionplayer)
            fieldposition[temp]=actionplayer;
        
        temp=position-1;
        if(fieldposition[temp]>-99 && fieldposition[temp]==-actionplayer)   
            fieldposition[temp]=actionplayer;
        
        temp=position+7;
        if(fieldposition[temp]>-99 && fieldposition[temp]==-actionplayer)
            fieldposition[temp]=actionplayer;
        
        temp=position-7;
        if(fieldposition[temp]>-99 && fieldposition[temp]==-actionplayer)
            fieldposition[temp]=actionplayer;
        
    }
    
    //calculate the value of green and blue
    
    for (int row=0; row<7; row++)
        for(int col=0;col<7;col++)
        {
            temp_num=row*7+col;
            if(fieldposition[temp_num]==1)
            {
                temp=field->fieldvalue[temp_num]*fieldposition[temp_num];
                bluevalue=bluevalue+temp;
            }
            
            if(fieldposition[temp_num]==-1)
            {
                temp=field->fieldvalue[temp_num]*(-1)*fieldposition[temp_num];
                greenvalue=greenvalue+temp;
            }
        }
    player=-actionplayer;     //change turn
    previousplayer=actionplayer;

}




