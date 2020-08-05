#ifndef boardh
#define boardh

#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include"U32.h"


class board{
    public:
        board();
        board(board*);
        //board(board*,string);
        board(bool,int[],U32[]);

        virtual ~board(){}

        U32 piece[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0xFFFFFFFF};
        //red=0 black=1
        bool playerColor;
        int numUnrevealPiece[16] = {0,1,2,2,2,2,2,5,1,2,2,2,2,2,5,0};

       

        //void printBoard();


};

#endif