#ifndef movesh
#define movesh

#include<string>
#include<vector>
#include"U32.h"

using namespace std;

class moves{

    public:
        moves();
        moves(U32[]);
        virtual ~moves(){}

        void generateMove();
        void setBoard(U32[]);
        
        vector<string> getEat();
        vector<string> getReveal();
        vector<string> getSpread();
        vector<string> getAll();
        


    private:

        U32 piece[16]={0};
        U32 red=0,black=0,occupied=0;

        vector<string> eatMove;
        vector<string> spreadMove;
        vector<string> revealMove;
        vector<string> allMove;
        
        void addEat(string);
        void addReveal(string);
        void addSpread(string);
        void addALL(string);

        void generateCMove(U32);
        void generateEat();
        void generateReveal();
        void generateSpeard();

        void refreshRed();
        void refreshBlack();
        void refreshOccupied();
       
};

#endif