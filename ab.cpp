#include"AB.h"

int depthLimit=8;

int depthCount=0;
int nodeCount=1;

int AB(treeNode* root){
    return max(root,INT_MIN,INT_MAX);
}
int max(treeNode *thisNode,int alpha,int beta){
    nodeCount++;
    int m =alpha;
    if(depthLimit==depthCount){
        depthCount--;
        return chessTypeValue(thisNode->nodeBoard);
    }
    else{

        vector<board*>nextBoard=thisNode->getNextBoard();

        

        for(int i=0;i<nextBoard.size();i++){
            
            nodeCount++;
            treeNode *nextNode = new treeNode(nextBoard[i]);
            //thisNode->children.push_back(nextNode);
            depthCount++;
            int t = min(nextNode,m,beta);
            delete nextNode;
            delete nextBoard[i];
            if(t>m){
                m=t;
                thisNode->selection=i;
            }
            if(m>=beta){
                depthCount--;
                return m;
            }
        }
    }
    depthCount--;
    return m;
}
int min(treeNode *thisNode,int alpha,int beta){
    nodeCount++;
    int m=beta;
    if(depthLimit==depthCount){
        depthCount--;
        return chessTypeValue(thisNode->nodeBoard);
    }
    else{

        vector<board*>nextBoard=thisNode->getNextBoard();

        for(int i=0;i<nextBoard.size();i++){
            nodeCount++;
            treeNode*nextNode = new treeNode(nextBoard[i]);
            //thisNode->children.push_back(nextNode);
            depthCount++;

            int t=max(nextNode,alpha,m);

            delete nextNode;
            delete nextBoard[i];

            if(t<m){
                m=t;
                thisNode->selection=i;
            }
            if(m<=alpha){
                depthCount--;
                return m;
            }

        }
    }
    depthCount--;
    return m;
}

int getNodeCount(){
    return nodeCount;
}