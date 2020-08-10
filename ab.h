#ifndef ABh
#define ABh

#include<iostream>
#include<vector>
#include<fstream>
#include"treeNode.h"
#include"evaluation.h"

extern string outPut;
extern int depthCount,depthLimit;
extern unsigned long long nodeCount;
extern U32 red,black,occupied;

void AB(treeNode*);

treeNode* max(treeNode*,int,int);
treeNode* min(treeNode*,int,int);


unsigned long long getNodeCount();
int getDepthLim();
U32 generateCMove(U32);

void makeMove(string);

void refreshRed(treeNode*);
void refreshBlack(treeNode*);
void refreshOccupied(treeNode*);

// treeNode* generateMove(treeNode*);
// treeNode* maxNext(treeNode*);
// treeNode* minNext(treeNode*);

#endif