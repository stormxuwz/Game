//
//  BattleField.cpp
//  CS440-HW2
//
//  Created by Wenzhao Xu on 10/27/12.
//  Copyright (c) 2012 Xu Wenzhao. All rights reserved.
//

#include "BattleField.h"
#include <fstream>


battlefield::battlefield(string filename)
{
    ifstream inputfile;
    inputfile.open(filename,ios::in);
    int index;
//    int value=-1;
    
    
    for (int i=0;i<7;i++)
        for(int j=0;j<7;j++)
        {
            index=i*7+j;
            fieldvalue[index]=-999;
        }
    
    for (int i=1; i<6; i++) {
        for(int j=1;j<6;j++)
        {
            inputfile>>fieldvalue[i*7+j];
        }
    }
    
}