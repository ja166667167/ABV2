#ifndef movesh
#define movesh

#include<string>
#include<vector>
#include"board.h"

using namespace std;

class move{

    public:
        moves();
        moves(board*);
        virtual ~moves(){}
        void generateMove(board*);
        vector<string> getEat();
        vector<string> getReveal();
        vector<string> getSpread();
        vector<string> getAll();

        void addEat(string);
        void addReveal(string);
        void addSpread(string);
        void addALL(string);
    private:
        vector<string> eatMove;
        vector<string> spreadMove;
        vector<string> revealMove;
        vector<string> allMove;

};

#endif