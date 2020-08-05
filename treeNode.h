#ifndef treeH
#define treeH

#include<iostream>
#include<vector>
#include"board.h"
#include"moves.h"



class treeNode{
    public:
        treeNode();//empty
        treeNode(board*); //root
        //treeNode(treeNode*,board*);//next nodes
        virtual ~treeNode(){}

        int selection=0;

        //treeNode *parent;
        //vector<treeNode*> children;

        board *nodeBoard;
        moves *boardMove;

        vector<board*>getNextBoard();
       // void printBoard();
        //void printMoves();
        

};
#endif