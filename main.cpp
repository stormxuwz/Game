//
//  main.cpp
//  CS440-HW2
//
//  Created by Wenzhao Xu on 10/27/12.
//  Copyright (c) 2012 Xu Wenzhao. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <time.h>
#include "BattleField.h"
#include "BattleNode.h"
#include "agentplayer.h"


using namespace std;


void print(battlenode *state, battlefield* wargame)
{
    for (int row=1; row<6; row++)
    {
        for(int col=1;col<6;col++)
        {
            cout.width(8);
            cout<<state->fieldposition[row*7+col];
        }
        
        cout<<"   ";
        for(int col=1;col<6;col++)
        {
            cout.width(8);
            cout<<wargame->fieldvalue[row*7+col];
        }
        cout<<endl;
    }
    cout<<state->actionpoint<<endl;
    cout<<state->bluevalue<<"   "<<state->greenvalue<<endl;
}

void output(vector<battlenode *> battleprocess, string filename, battlefield *wargame, player *blue, player * green, int averagemove, double averagetime, int moves)
{
    ofstream outputfile((filename+".result").c_str());
//    outputfile.open(filename,ios::out);
    
    for(int i=0;i<battleprocess.size();i++)
    {
        for (int row=1; row<6; row++)
        {
            for(int col=1;col<6;col++)
            {
                outputfile.width(8);
                outputfile<<battleprocess[i]->fieldposition[row*7+col];
            }
            
            outputfile<<"   ";
            for(int col=1;col<6;col++)
            {
                outputfile.width(8);
                outputfile<<wargame->fieldvalue[row*7+col];
            }
            outputfile<<endl;
        }
        
        outputfile<<endl;
    }
    outputfile<<endl;
    
//    outputfile<<"The Search Depth of Blue vs Green is: "<<blue->depthlimit_minimax<<":"<<green->depthlimit_minimax<<endl;
    
    outputfile<<filename<<endl;             
    outputfile<<"Blue Score: "<<battleprocess.back()->bluevalue<<endl;
    outputfile<<"Green Score: "<<battleprocess.back()->greenvalue<<endl;
    outputfile<<"Total number of moves: "<<moves<<endl;
    
    outputfile<<"Node Examined by Blue: "<<blue->nodeexamined<<endl;
    outputfile<<"Node Examined by Green: "<<green->nodeexamined<<endl;
    
    outputfile<<"Node Examined per move: "<<averagemove<<endl;
    outputfile<<"time per move: "<<averagetime<<"ms"<<endl;
    
    outputfile.close();
}



int main(int argc, const char * argv[])
{
    battlefield *wargame;
    player *green;
    player *blue;
    battlenode *initialstate;
    battlenode *pointstate;
    vector<battlenode *> battleprocess;
    
    int depth1, depth2;
    int turn=1;                 //initial turn, 1 is the blue, -1 is the green
    
    int finalscore_blue;
    int finalscore_green;
    double averagetime=0;
    
    int moves=0;
    int nodesPermove=0;           //
    int nodecurrentmove=0;
    
    depth1=3;                   //the depth limit for the minimax search
    depth2=5;                   //the depth limit for the alpha-beta search
    
    string filename,filename1,filename2,filename3,filename4,filename5;
    
    filename1="/Users/Xuwenzhao/Documents/Developer/C++/CS440-HW2/CS440-HW2/game_boards/Kalamazoo.txt";
    filename2="/Users/Xuwenzhao/Documents/Developer/C++/CS440-HW2/CS440-HW2/game_boards/Peoria.txt";
    filename3="/Users/Xuwenzhao/Documents/Developer/C++/CS440-HW2/CS440-HW2/game_boards/Piqua.txt";
    filename4="/Users/Xuwenzhao/Documents/Developer/C++/CS440-HW2/CS440-HW2/game_boards/Punxsutawney.txt";
    filename5="/Users/Xuwenzhao/Documents/Developer/C++/CS440-HW2/CS440-HW2/game_boards/Wallawalla.txt";
    
    filename=filename5;
    
    wargame=new battlefield(filename);
    
    cout<<wargame->fieldvalue[5];
    
    green=new player(-1,3,6);
    blue=new player(1,3,6);
        
    initialstate=new battlenode(turn);     // 1 means the blue goes first
    
    pointstate=initialstate;
    
    
    // search
//    /*
    for(int i=0;i<100;i++)
    {
        if (turn==1) {
            nodecurrentmove=blue->nodeexamined;
            
            clock_t start_time=clock();                     //start time of a move
            
            blue->Minimax(pointstate,wargame);              //Minimax Search
//            blue->alphabata(pointstate, wargame);         //Alpha-Beta Search
            
            pointstate=pointstate->child[blue->action];     //move to the next state
          
            clock_t end_time=clock();                       //end time of a move
            
            nodecurrentmove=blue->nodeexamined-nodecurrentmove;     //find the nodes examined by this move
            nodesPermove+=nodecurrentmove;                          //added to the total node examined;
            averagetime+=static_cast<double>(end_time-start_time)/CLOCKS_PER_SEC*1000;
            
            battleprocess.push_back(pointstate);
            moves+=1;
            if (pointstate->finalsituation==1) {
                break;
            }
            
            pointstate->depth=0;
            turn=-1;
            
        }
        
        else
        {
            nodecurrentmove=green->nodeexamined;
            
            clock_t start_time=clock();                     //start time of a move

            green->Minimax(pointstate, wargame);
 //         green->alphabata(pointstate, wargame);
            
            pointstate=pointstate->child[green->action];
            
            clock_t end_time=clock();                       //end time of a move
            
            nodecurrentmove=green->nodeexamined-nodecurrentmove;     //find the nodes examined by this move
            nodesPermove+=nodecurrentmove;                          //added to the total node examined;
            averagetime+=static_cast<double>(end_time-start_time)/CLOCKS_PER_SEC*1000;
            
            moves+=1;
            
            battleprocess.push_back(pointstate);
            if (pointstate->finalsituation==1) {
                break;
            }
            pointstate->depth=0;
            turn=1;
        }
        
        
        
    }
    
    averagetime=averagetime/moves;
    nodesPermove=nodesPermove/moves;
    
//    */
     
    //Alpha-Beta Search
   /*
    for(int i=0;i<100;i++)
    {
        if (turn==1) {
            blue->alphabata(pointstate, wargame);
                 
            if (pointstate->finalsituation==1) {
                break;
            }
            
            pointstate=pointstate->child[blue->action];
            battleprocess.push_back(pointstate);

            pointstate->depth=0;

            turn=-1;
            
            print(battleprocess.back(),wargame);
        }
     
        else
        {
            green->alphabata(pointstate, wargame);

            if (pointstate->finalsituation==1) {
                break;
            }
            
            pointstate=pointstate->child[green->action];
            battleprocess.push_back(pointstate);
            
            pointstate->depth=0;
            
            turn=1;
            
             print(battleprocess.back(),wargame);
        }
    }
    
//    */
    
    finalscore_blue=pointstate->bluevalue;
    finalscore_green=pointstate->greenvalue;
    
    if (finalscore_blue>finalscore_green) {
        cout<<"blue wins"<<endl;
    }
    else
        cout<<"green wins"<<endl;
    
    for(int i=0;i<battleprocess.size();i++)
    {
        print(battleprocess[i],wargame);
    }
    cout << "Who win??\n";
    
    output(battleprocess, filename, wargame,blue,green,nodesPermove,averagetime,moves);
    
    delete wargame;
    return 0;
        
}

