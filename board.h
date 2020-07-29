#ifndef boardh
#define boardh

#include<iostream>
#include<string>
#include"U32.h"
#include"moves.h"


class board{
    public:
        board();
        board(board*,string);
        board(U32[]);

        virtual ~board(){}

        U32 piece[16];
        U32 red,black,occupied;
        moves possibleMoves= new move(b);
        vector<board*> possibleBoards;

};

#endif