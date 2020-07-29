#include<iostream>
#include"move.h"

vector<string> move::getEat(){ return eatMove;}
vector<string> move::getReveal(){ return revealMove;}
vector<string> move::getSpread(){ return spreadMove;}
vector<string> move::getAll(){ return allMove;}

void move::addEat(string s){
    eatMove.push_back(s);
}
void move::addReveal(string s){
    revealMove.push_back(s);
}
void move::addSpread(string s){
    spreadMove.push_back(s);
}
void move::addALL(string s){
    allMove.push_back(s);
}
