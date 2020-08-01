#ifndef boardh
#define boardh

#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include"U32.h"
#include"moves.h"


class board{
    public:
        board();
        board(board*,string);
        board(U32[]);

        virtual ~board(){}

        U32 piece[16]={0};
        

        moves possibleMoves;
        vector<board*> possibleBoards;

        void readBoardFile();
        void initData(); //using piece[], init red black occupied moves nextBoards
        
        void setPosBoard();
        
        void printBoard();


};

#endif