//
//  BattleField.h
//  CS440-HW2
//
//  Created by Wenzhao Xu on 10/27/12.
//  Copyright (c) 2012 Xu Wenzhao. All rights reserved.
//

#ifndef __CS440_HW2__BattleField__
#define __CS440_HW2__BattleField__

#include <string>

using namespace std;


class battlefield
{
public:
    int fieldvalue[49];       //Add a wall to the battlefield 7*7=49
    battlefield(string filename);
    
};


#endif /* defined(__CS440_HW2__BattleField__) */
