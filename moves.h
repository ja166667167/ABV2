#ifndef movesh
#define movesh

#include<string>
#include<vector>
#include"U32.h"
#include"board.h"

using namespace std;

class moves{

    public:
        moves();
        moves(board*);
        virtual ~moves(){}

        void generateMove();
        //void printMoves();

        board *moveBoard;
        U32 red=0,black=0,occupied=0;


        //vector<string> eatMove;
        //vector<string> spreadMove;
        //vector<string> revealMove;
        vector<string> allMove;
 
        U32 generateCMove(U32);
        void generateEat();
        void generateReveal();
        void generateSpeard();

        void refreshRed();
        void refreshBlack();
        void refreshOccupied();
       
};

#endif