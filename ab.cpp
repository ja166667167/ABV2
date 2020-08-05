#include"AB.h"

int depthLimit=3;

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
        return chessTypeValue(thisNode);
    }
    else{

        try{
            thisNode->setChildren();
        }
        catch(std::bad_alloc &ba){
            cout<<nodeCount<<" d="<<depthCount<<" BA in MAX setChildren\n";
            for(int i=0;i<thisNode->children.size();i++){
                thisNode->children[i]->printBoard();
                thisNode->children[i]->printMoves();
            }
            exit(1);
        }
        
        int n =thisNode->children.size();

        for(int i=0;i<n;i++){
            
            nodeCount++;

            depthCount++;

            int t = min(thisNode->children[0],m,beta);
            //delete thisNode->children[0];
            thisNode->children.erase(thisNode->children.begin());
            thisNode->children.shrink_to_fit();            
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
        return chessTypeValue(thisNode);
    }
    else{

        try{
            thisNode->setChildren();
        }
        catch(std::bad_alloc &ba){
            cout<<nodeCount<<" d="<<depthCount<<" BA in MAX setChildren\n";
            for(int i=0;i<thisNode->children.size();i++){
                thisNode->children[i]->printBoard();
                thisNode->children[i]->printMoves();
            }
            exit(1);
        }
        int n =thisNode->children.size();
        for(int i=0;i<n;i++){
            nodeCount++;
            
            //thisNode->children.push_back(nextNode);
            depthCount++;

            int t=max(thisNode->children[0],alpha,m);

            //delete thisNode->children[0];
            thisNode->children.erase(thisNode->children.begin());
            thisNode->children.shrink_to_fit();


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