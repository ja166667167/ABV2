#ifndef treeH
#define treeH

#include<iostream>
#include<vector>
#include"U32.h"
extern int deleteCount;

class treeNode{
    public:
        treeNode();//empty
        //treeNode(treeNode*); //root
        //treeNode(treeNode*,board*);//next nodes
        treeNode(bool,U32[],int[]);
        virtual ~treeNode();

        //int selection=0;

        //treeNode *parent;
        //vector<treeNode*> children;

        //board *nodeBoard;
        U32 piece[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0xFFFFFFFF};
        U32 red =0, black=0,occupied=0;
        //red =0, black=1 
        bool playerColor;
        int numUnrevealPiece[16] = {0,1,2,2,2,2,2,5,1,2,2,2,2,2,5,0};
        //move boardMove;
        float value=0;
        string chosenMove="not choose yet";
        treeNode* child=NULL;
        //treeNode* parent;
        void printBoard();

        U32 generateCMove(U32);
        void refreshRed();
        void refreshBlack();
        void refreshOccupied();
        //void printMoves();
        

};
#endif