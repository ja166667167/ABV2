#ifndef ABh
#define ABh

#include<iostream>
#include<vector>
#include<fstream>
#include"treeNode.h"
#include"evaluation.h"


void AB(treeNode*);

int max(treeNode*,int,int);
int min(treeNode*,int,int);

string getOutPut();
unsigned long long getNodeCount();
int getDepthLim();
U32 generateCMove(U32);

void makeMove(string);

void refreshRed(treeNode*);
void refreshBlack(treeNode*);
void refreshOccupied(treeNode*);

#endif