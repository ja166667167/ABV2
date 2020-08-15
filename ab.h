#ifndef ABh
#define ABh

#include<iostream>
#include<vector>
#include<fstream>
#include"treeNode.h"
#include"evaluation.h"

#define RedColor "\033[31m"
#define RESET "\033[0m"
extern string order;
extern string outPut;
extern int depthCount,depthLimit;
extern unsigned long long nodeCount;


void AB(treeNode*);

treeNode* max(treeNode*,int,int);
treeNode* min(treeNode*,int,int);


unsigned long long getNodeCount();
int getDepthLim();


void makeMove(string);
void addS(string);


// treeNode* generateMove(treeNode*);
// treeNode* maxNext(treeNode*);
// treeNode* minNext(treeNode*);

#endif