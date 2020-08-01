#include<iostream>
#include"moves.h"

using namespace std;

moves::moves(){

}
moves::moves(U32 p[]){
    for(int i;i<16;i++){
        piece[i]=p[i];
    }
    refreshBlack();
    refreshRed();
    refreshOccupied();
    
    generateMove();

}


vector<string> moves::getEat(){ return eatMove;}
vector<string> moves::getReveal(){ return revealMove;}
vector<string> moves::getSpread(){ return spreadMove;}
vector<string> moves::getAll(){ return allMove;}

void moves::addEat(string s){
    eatMove.push_back(s);
}
void moves::addReveal(string s){
    revealMove.push_back(s);
}
void moves::addSpread(string s){
    spreadMove.push_back(s);
}
void moves::addALL(string s){
    allMove.push_back(s);
}

void moves::setBoard(U32 p[]){
    
}

void moves::generateMove(){
    generateEat();
    generateReveal();
    generateSpeard();
}
void moves::generateCMove(U32 u32src){};
void moves::generateEat(){};
void moves::generateReveal(){};
void moves::generateSpeard(){};

void moves::refreshRed(){
    int j;
    for (j = 1; j < 8; j++)
    {
        red = red | piece[j];
    }
}
void moves::refreshBlack(){
    int j;
    for (j = 8; j < 15; j++)
    {
        black = black | piece[j];
    }
}
void moves::refreshOccupied(){
    int j;
    //printf("deafult oc:%x\n",occupied);
    for (j = 1; j < 16; j++)
    {
        //printf("piece=%x\n",piece[j]);
        occupied = occupied | piece[j];
        //printf("%x\n",occupied);
    }
    //exit(1);
}

