#ifndef ABh
#define ABh

#include<iostream>
#include<vector>
#include<fstream>
#include<limits>
#include"treeNode.h"
#include"evaluation.h"

#define RedColor "\033[31m"
#define RESET "\033[0m"
extern string order;
extern string outPut;
extern int depthCount,depthLimit;
extern unsigned long long nodeCount;


void AB(treeNode*);

treeNode* maxNode(treeNode*,int,int);
treeNode* minNode(treeNode*,int,int);




void makeMove(string);

void deleteTree(treeNode*);
extern void printOrder(treeNode*);



// treeNode* generateMove(treeNode*);
// treeNode* maxNext(treeNode*);
// treeNode* minNext(treeNode*);

#endif