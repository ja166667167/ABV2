#ifndef moveh
#define moveh

#include<string>
#include<vector>

using namespace std;

class move{

    public:
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