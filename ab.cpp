#include"ab.h"

int depthLimit=5;

int depthCount=0;
string order("");
unsigned long long nodeCount=0;


string outPut;

void AB(treeNode* root){
    root = max(root,INT_MIN,INT_MAX);
    cout<<"reslut="<<root->value<<endl;
    makeMove(root->chosenMove);
}

treeNode* max(treeNode *thisNode,int alpha,int beta){
    //cout<<"--------------------------------\n";
    depthCount++;
    nodeCount++;
    //int t;
    thisNode->value =alpha;
    //cout<<"depth= "<<depthCount<<endl;
    if(depthLimit==depthCount){
        
        depthCount--;
        thisNode->value = chessTypeValue(thisNode);
        return thisNode;
    }
    else{

//generate move
        thisNode->refreshBlack();
        thisNode->refreshOccupied();
        thisNode->refreshRed();
        //判斷end game
        //+-dpth 越早贏越好 越晚輸越好
        bool endGame=1;
        for(int i=0;i<16;i++){
            if(thisNode->numUnrevealPiece[i]!=0)
            endGame=false;
        }
        if(endGame){        
            if(thisNode->red==0){
                if(thisNode->playerColor){
                    thisNode->value=(INT_MAX-1)-depthCount;
                }
                else{
                    thisNode->value=(INT_MIN+1)+depthCount;
                }
                return thisNode;
            }
            else if(thisNode->black==0){
                if(thisNode->playerColor){
                    thisNode->value=(INT_MIN+1)+depthCount;
                }
                else{
                    thisNode->value=(INT_MAX-1)-depthCount;
                }
                return thisNode;
            }
        }        
        U32 dest;
//eat and spread
        if (!thisNode->playerColor)
        {
            for (int i = 1; i < 8; i++)
            {
                U32 p = thisNode->piece[i];
                while (p > 0)
                {
                    U32 mask = LS1B(p);
                    p ^= mask;
                    U32 src = U32toInt(mask);
                    if (i == 1)
                    {
                        dest = pMove[src] & ((thisNode->black^    thisNode->piece[14])|  thisNode->piece[0]) ;
                        //printf("%d\n",i);
                    }
                    else if (i == 2)
                    {
                        dest = pMove[src] & (thisNode->black^    thisNode->piece[8]);
                        dest = dest|(pMove[src]&  thisNode->piece[0]);
                        // printf("i:%d,mask:%x,src:%d\n",i,mask,src);
                    }
                    else if (i == 3)
                    {
                        dest = pMove[src] & ((thisNode->black^    thisNode->piece[8] ^    thisNode->piece[9])|  thisNode->piece[0]);
                        //printf("i:%d,src:%d\n",i,src);
                    }
                    else if (i == 4)
                    {
                        dest = pMove[src] & ((   thisNode->piece[11] |    thisNode->piece[12] |    thisNode->piece[13] |    thisNode->piece[14])|  thisNode->piece[0]);
                        //printf("i:%d,src:%d\n",i,src);
                    }
                    else if (i == 5)
                    {
                        dest = pMove[src] & ((   thisNode->piece[12] |    thisNode->piece[13] |    thisNode->piece[14])|  thisNode->piece[0]);
                        //printf("i:%d,src:%d\n",i,src);
                    }
                    else if (i == 6)
                    {

                        dest = thisNode->generateCMove(mask) & thisNode->black;
                        //cout<<hex<<"cannon before= "<<dest<<endl;
                        dest = dest|(pMove[src]& thisNode->piece[0]);
                        //cout<<hex<<"cannon after= "<<dest<<endl;
                        
                    }
                    else if (i == 7)
                    {
                        dest = pMove[src] & (   thisNode->piece[8] |    thisNode->piece[14]);
                        dest = dest|(pMove[src]&  thisNode->piece[0]);
                    }
                    else
                    {
                        dest = 0;
                    }

                    while (dest)
                    {
                        string result("\0");
                        U32 mask2 = LS1B(dest);
                        dest ^= mask2;
                        result.append(U32toString(mask));
                        result.append(1, '-');
                        result.append(U32toString(mask2));
                        //cout<<result<<endl;

//generate board with move
                        if (result.empty())
                        {
                            cout << "unusable move string" << endl;
                            exit(1);
                        }
                        if ( result[2] == '-'){   
                            treeNode *newNode = new treeNode(!thisNode->playerColor,thisNode->piece,thisNode->numUnrevealPiece);
                            int srcP = result[0] - 96 + (result[1] - 49) * 4;
                            int destP = result[3] - 96 + (result[4] - 49) * 4;
                            U32 src = InttoU32(srcP);
                            U32 dest = InttoU32(destP);
                            for (int i = 0; i < 16; i++)
                            {
                                if (( newNode->piece[i] != 0) & (( newNode->piece[i] | src) ==  newNode->piece[i]))
                                {

                                    newNode->piece[i] =  newNode->piece[i] ^ src;
                                    newNode->piece[0] =  newNode->piece[0] | src;
                                    for (int j = 0; j < 16; j++)
                                    {
                                        if (( newNode->piece[j] != 0) & (( newNode->piece[j] | dest) ==  newNode->piece[j]))
                                        {
                                            newNode->piece[j] =  newNode->piece[j] ^ dest;
                                        }
                                    }
                                    newNode->piece[i] =  newNode->piece[i] | dest;
                                }
                            }
//next level                            
                            //depthCount++;
                            
                            newNode=min(newNode,thisNode->value,beta);
                            // cout<<"se value="<<newNode->value<<endl;
                            if(newNode->value>thisNode->value){
                                //aadS(result);
                                thisNode->value=newNode->value;
                                thisNode->chosenMove=result;
                                if(thisNode->child)delete thisNode->child;                              
                                thisNode->child=newNode;
                                
                                
                            }
                            else{
                                delete newNode;
                            }
                            if(thisNode->value>=beta){
                                    depthCount--;
                                    return thisNode;
                            }
                            
                        }
                        else{
                            cout << "child setting ERROR!!!!!!!!!!!!!!!" << endl;
                        }
                    
                    }
                }
            }
        }
        else if (thisNode->playerColor)
        {
            for (int i = 8; i < 15; i++)
            {
                U32 p =    thisNode->piece[i];
                while (p)
                {
                    U32 mask = LS1B(p);
                    p ^= mask;
                    U32 src = U32toInt(mask);
                    if (i == 8){
                        dest = pMove[src] & (thisNode->red ^    thisNode->piece[7]);
                        dest = dest|(pMove[src]&  thisNode->piece[0]);
                    }
                    else if (i == 9){
                        dest = pMove[src] & (thisNode->red ^    thisNode->piece[1]);
                        dest = dest|(pMove[src]&  thisNode->piece[0]);
                    }
                    else if (i == 10)
                        dest = pMove[src] & (thisNode->red ^    thisNode->piece[1] ^    thisNode->piece[1]);
                    
                    else if (i == 11){
                        dest = pMove[src] & (   thisNode->piece[4] |    thisNode->piece[5] |    thisNode->piece[6] |    thisNode->piece[7]);
                        dest = dest|(pMove[src]&  thisNode->piece[0]);
                    }
                    else if (i == 12)
                    {
                        dest = pMove[src] & (   thisNode->piece[5] |    thisNode->piece[6] |    thisNode->piece[7]);
                        dest = dest|(pMove[src]&  thisNode->piece[0]);
                        //printf("p=%llu,src=%llu,dest=%llu\n",p,src,dest);
                    }

                    
                    else if (i == 13)
                    {
                        dest = thisNode->generateCMove(mask) & thisNode->red;
                        dest = dest|(pMove[src]&  thisNode->piece[0]);
                    }
                    else if (i == 14){
                        dest = pMove[src] & (   thisNode->piece[1] |    thisNode->piece[7]);
                        dest = dest|(pMove[src]&  thisNode->piece[0]);
                    }
                    else
                        dest = 0;

                    while (dest)
                    {
                        //printf("i=%d,thisNode->red=%x,   thisNode->piece[1]=%x\n", i, thisNode->red,    thisNode->piece[1]);
                        string result("\0");
                        U32 mask2 = LS1B(dest);
                        dest ^= mask2;
                        result.append(U32toString(mask));
                        result.append(1, '-');
                        result.append(U32toString(mask2));
                        //cout<<result<<endl;
//generate board with move
                        if (result.empty())
                        {
                            cout << "unusable move string" << endl;
                            exit(1);
                        }
                        if ( result[2] == '-'){   
                            treeNode *newNode = new treeNode(!thisNode->playerColor,thisNode->piece,thisNode->numUnrevealPiece);
                            int srcP = result[0] - 96 + (result[1] - 49) * 4;
                            int destP = result[3] - 96 + (result[4] - 49) * 4;
                            U32 src = InttoU32(srcP);
                            U32 dest = InttoU32(destP);
                            for (int i = 0; i < 16; i++)
                            {
                                if (( newNode->piece[i] != 0) & (( newNode->piece[i] | src) ==  newNode->piece[i]))
                                {

                                    newNode->piece[i] =  newNode->piece[i] ^ src;
                                    newNode->piece[0] =  newNode->piece[0] | src;
                                    for (int j = 0; j < 16; j++)
                                    {
                                        if (( newNode->piece[j] != 0) & (( newNode->piece[j] | dest) ==  newNode->piece[j]))
                                        {
                                            newNode->piece[j] =  newNode->piece[j] ^ dest;
                                        }
                                    }
                                    newNode->piece[i] =  newNode->piece[i] | dest;
                                }
                            }
//next level                            
                            
                            //depthCount++;
                            //newNode->printBoard();
                            newNode=min(newNode,thisNode->value,beta);
                            //cout<<"se value= "<<newNode->value<<endl;
                            if(newNode->value>thisNode->value){
                                
                                //aadS(result);
                                thisNode->value=newNode->value;
                                thisNode->chosenMove=result;
                                
                                if(thisNode->child)delete thisNode->child;
                                
                                thisNode->child=newNode;
                                
                            }
                            else{
                                delete newNode;
                            }
                            if(thisNode->value>=beta){
                                    depthCount--;
                                    return thisNode;
                            }
                            
                        }
                        else{
                            cout << "child setting ERROR!!!!!!!!!!!!!!!" << endl;
                        }
                    
                    }
                }
            }
        }
//reveal        
        U32 reveal = thisNode->piece[15];
        U32 mask;
        while (reveal)
        {
            string result("\0");
            mask = LS1B(reveal);
            reveal ^= mask;
            result.append("R(");
            result.append(U32toString(mask));
            result.append(")");
            //cout<<result<<endl;
//generate board with move
            if (result.empty())
            {
                cout << "unusable move string" << endl;
                exit(1);
            }
            else if( result[0]=='R'){
                int revP =     result[2] - 96 + (    result[3] - 49) * 4;
                U32 rev = InttoU32(revP);
                for (int a = 1; a < 15; a++){

                    if (thisNode->numUnrevealPiece[a] != 0)//此棋種還有位翻開的棋
                    {
                        treeNode *newNode = new treeNode(!thisNode->playerColor,thisNode->piece,thisNode->numUnrevealPiece);
                        newNode->piece[15] =  newNode->piece[15] ^ rev;
                        newNode->piece[a] =  newNode->piece[a] | rev;
                        newNode->numUnrevealPiece[a]--;
//next level             

                        //depthCount++;
                        //newNode->printBoard();
                        newNode=min(newNode,thisNode->value,beta);
                        //cout<<"r value= "<<newNode->value<<endl;
                        
                            if(newNode->value>thisNode->value){                             
                                //aadS(result);
                                thisNode->value=newNode->value;
                                thisNode->chosenMove=result;
                                if(thisNode->child)delete thisNode->child;
                                thisNode->child=newNode;
                            }
                            else{
                                delete newNode;
                            }
                        if(thisNode->value>=beta){
                                depthCount--;
                                return thisNode;
                        }
                        
                    }
                
                }
            }
            
            else{
                cout << "child setting ERROR!!!!!!!!!!!!!!!" << endl;
            }
        
        }

    }    
    depthCount--;

    return thisNode;
}

treeNode* min(treeNode *thisNode,int alpha,int beta){
    depthCount++;
    //cout<<"--------------------------------\n";
    nodeCount++;
    //int t;
    thisNode->value =beta;

    if(depthLimit==depthCount){
        thisNode->playerColor=!thisNode->playerColor;
        depthCount--;
        thisNode->value=chessTypeValue(thisNode);
        return thisNode;
    }
    else{

//generate move
        thisNode->refreshBlack();
        thisNode->refreshOccupied();
        thisNode->refreshRed();
        //判斷end game
        bool endGame=1;
        for(int i=0;i<16;i++){
            if(thisNode->numUnrevealPiece[i]!=0)
            endGame=false;
        }
        if(endGame){
            if(thisNode->red==0){
                if(thisNode->playerColor){
                    thisNode->value=(INT_MIN+1)+depthCount;
                }
                else{
                    thisNode->value=(INT_MAX-1)-depthCount;
                }
                return thisNode;
            }
            else if(thisNode->black==0){
                if(thisNode->playerColor){
                    thisNode->value=(INT_MAX-1)-depthCount;
                }
                else{
                    thisNode->value=(INT_MIN+1)+depthCount;
                }
                return thisNode;
            }
        }        
        U32 dest;
//eat and spread
        if (!thisNode->playerColor)
        {
            for (int i = 1; i < 8; i++)
            {
                U32 p = thisNode->piece[i];
                while (p > 0)
                {
                    U32 mask = LS1B(p);
                    p ^= mask;
                    U32 src = U32toInt(mask);
                    if (i == 1)
                    {
                        dest = pMove[src] & ((thisNode->black^ thisNode->piece[14])|  thisNode->piece[0]) ;
                        //printf("%d\n",i);
                    }
                    else if (i == 2)
                    {
                        dest = pMove[src] & (thisNode->black^    thisNode->piece[8]);
                        dest = dest|(pMove[src]&  thisNode->piece[0]);
                        // printf("i:%d,mask:%x,src:%d\n",i,mask,src);
                    }
                    else if (i == 3)
                    {
                        dest = pMove[src] & ((thisNode->black^    thisNode->piece[8] ^    thisNode->piece[9])|  thisNode->piece[0]);
                        //printf("i:%d,src:%d\n",i,src);
                    }
                    else if (i == 4)
                    {
                        dest = pMove[src] & ((   thisNode->piece[11] |    thisNode->piece[12] |    thisNode->piece[13] |    thisNode->piece[14])|  thisNode->piece[0]);
                        //printf("i:%d,src:%d\n",i,src);
                    }
                    else if (i == 5)
                    {
                        dest = pMove[src] & ((   thisNode->piece[12] |    thisNode->piece[13] |    thisNode->piece[14])|  thisNode->piece[0]);
                        //printf("i:%d,src:%d\n",i,src);
                    }
                    else if (i == 6)
                    {

                        dest = thisNode->generateCMove(mask) & thisNode->black;
                        dest = dest|(pMove[src]&  thisNode->piece[0]);
                    }
                    else if (i == 7)
                    {
                        dest = pMove[src] & (   thisNode->piece[8] |    thisNode->piece[14]);
                        dest = dest|(pMove[src]&  thisNode->piece[0]);
                    }
                    else
                    {
                        dest = 0;
                    }

                    while (dest)
                    {
                        string result("\0");
                        U32 mask2 = LS1B(dest);
                        dest ^= mask2;
                        result.append(U32toString(mask));
                        result.append(1, '-');
                        result.append(U32toString(mask2));
                        //cout<<RedColor<<result<<RESET<<"\n";

//generate board with move
                        if (result.empty())
                        {
                            cout << "unusable move string" << endl;
                            exit(1);
                        }
                        if ( result[2] == '-'){   
                            treeNode *newNode = new treeNode(!thisNode->playerColor,thisNode->piece,thisNode->numUnrevealPiece);
                            int srcP = result[0] - 96 + (result[1] - 49) * 4;
                            int destP = result[3] - 96 + (result[4] - 49) * 4;
                            U32 src = InttoU32(srcP);
                            U32 dest = InttoU32(destP);
                            for (int i = 0; i < 16; i++)
                            {
                                if (( newNode->piece[i] != 0) & (( newNode->piece[i] | src) ==  newNode->piece[i]))
                                {

                                    newNode->piece[i] =  newNode->piece[i] ^ src;
                                    newNode->piece[0] =  newNode->piece[0] | src;
                                    for (int j = 0; j < 16; j++)
                                    {
                                        if (( newNode->piece[j] != 0) & (( newNode->piece[j] | dest) ==  newNode->piece[j]))
                                        {
                                            newNode->piece[j] =  newNode->piece[j] ^ dest;
                                        }
                                    }
                                    newNode->piece[i] =  newNode->piece[i] | dest;
                                }
                            }
//next level                            
                            //depthCount++;
                            //newNode->printBoard();
                            newNode=max(newNode,alpha,thisNode->value);
                            //cout<<RedColor<<"se value= "<<newNode->value<<RESET<<endl; 

                            if(newNode->value<thisNode->value){
                                //aadS(result);
                                thisNode->value=newNode->value;
                                thisNode->chosenMove=result;
                                 if(thisNode->child)delete thisNode->child;
                                thisNode->child=newNode;
                            }
                            else{
                                delete newNode;
                            }
                            if(thisNode->value<=alpha){
                                depthCount--;
                                return thisNode;
                            }
                            
                        }
                        else{
                            cout << "child setting ERROR!!!!!!!!!!!!!!!" << endl;
                        }
                    
                    }
                }
            }
        }
        else if (thisNode->playerColor)
        {
            for (int i = 8; i < 15; i++)
            {
                U32 p =    thisNode->piece[i];
                while (p > 0)
                {
                    U32 mask = LS1B(p);
                    p ^= mask;
                    U32 src = U32toInt(mask);
                    if (i == 8){
                        dest = pMove[src] & (thisNode->red ^    thisNode->piece[7]);
                        dest = dest|(pMove[src]&  thisNode->piece[0]);
                    }
                    else if (i == 9){
                        dest = pMove[src] & (thisNode->red ^    thisNode->piece[1]);
                        dest = dest|(pMove[src]&  thisNode->piece[0]);
                    }
                    else if (i == 10)
                        dest = pMove[src] & (thisNode->red ^    thisNode->piece[1] ^    thisNode->piece[1]);
                    
                    else if (i == 11){
                        dest = pMove[src] & (   thisNode->piece[4] |    thisNode->piece[5] |    thisNode->piece[6] |    thisNode->piece[7]);
                        dest = dest|(pMove[src]&  thisNode->piece[0]);
                    }
                    else if (i == 12)
                    {
                        dest = pMove[src] & (   thisNode->piece[5] |    thisNode->piece[6] |    thisNode->piece[7]);
                        dest = dest|(pMove[src]&  thisNode->piece[0]);
                        //printf("p=%llu,src=%llu,dest=%llu\n",p,src,dest);
                    }

                    
                    else if (i == 13)
                    {
                        dest = thisNode->generateCMove(mask) & thisNode->red;
                        dest = dest|(pMove[src]&  thisNode->piece[0]);
                    }
                    else if (i == 14){
                        dest = pMove[src] & (   thisNode->piece[1] |    thisNode->piece[7]);
                        dest = dest|(pMove[src]&  thisNode->piece[0]);
                    }
                    else
                        dest = 0;

                    while (dest > 0)
                    {
                        //printf("i=%d,thisNode->red=%x,   thisNode->piece[1]=%x\n", i, thisNode->red,    thisNode->piece[1]);
                        string result("\0");
                        U32 mask2 = LS1B(dest);
                        dest ^= mask2;
                        result.append(U32toString(mask));
                        result.append(1, '-');
                        result.append(U32toString(mask2));
                        //eatMove.push_back(result);
                        //cout<<RedColor<<result<<RESET<<"\n";
//generate board with move
                        if (result.empty())
                        {
                            cout << "unusable move string" << endl;
                            exit(1);
                        }
                        if ( result[2] == '-'){
                            //cout<<result<<"\n";   
                            treeNode *newNode = new treeNode(!thisNode->playerColor,thisNode->piece,thisNode->numUnrevealPiece);
                            int srcP = result[0] - 96 + (result[1] - 49) * 4;
                            int destP = result[3] - 96 + (result[4] - 49) * 4;
                            U32 src = InttoU32(srcP);
                            U32 dest = InttoU32(destP);
                            for (int i = 0; i < 16; i++)
                            {
                                if (( newNode->piece[i] != 0) & (( newNode->piece[i] | src) ==  newNode->piece[i]))
                                {

                                    newNode->piece[i] =  newNode->piece[i] ^ src;
                                    newNode->piece[0] =  newNode->piece[0] | src;
                                    for (int j = 0; j < 16; j++)
                                    {
                                        if (( newNode->piece[j] != 0) & (( newNode->piece[j] | dest) ==  newNode->piece[j]))
                                        {
                                            newNode->piece[j] =  newNode->piece[j] ^ dest;
                                        }
                                    }
                                    newNode->piece[i] =  newNode->piece[i] | dest;
                                }
                            }
//next level                            
                            //depthCount++;
                            //newNode->printBoard();
                            newNode=max(newNode,alpha,thisNode->value);
                            //cout<<RedColor<<"se value= "<<newNode->value<<RESET<<endl; 
                            //cout<<"v= "<<newNode->value<<endl;
                            if(newNode->value<thisNode->value){
                                //aadS(result);
                                thisNode->value=newNode->value;
                                thisNode->chosenMove=result;
                                 if(thisNode->child)delete thisNode->child;
                                thisNode->child=newNode;
                            }
                            else{
                                delete newNode;
                            }
                            if(thisNode->value<=alpha){
                                depthCount--;
                                return thisNode;
                            }
                            
                        }
                        else{
                            cout << "child setting ERROR!!!!!!!!!!!!!!!" << endl;
                        }
                    
                    }
                }
            }
        }
//reveal        
        U32 reveal = thisNode->piece[15];
        U32 mask;
        while (reveal > 0)
        {
            string result("\0");
            mask = LS1B(reveal);
            reveal ^= mask;
            result.append("R(");
            result.append(U32toString(mask));
            result.append(")");
            //cout<<RedColor<<result<<RESET<<"\n";
//generate board with move
            if (result.empty())
            {
                cout << "unusable move string" << endl;
                exit(1);
            }
            else if( result[0]=='R'){
                int revP =     result[2] - 96 + (    result[3] - 49) * 4;
                U32 rev = InttoU32(revP);
                for (int a = 1; a < 15; a++){

                    if (thisNode->numUnrevealPiece[a] != 0)//此棋種還有位翻開的棋
                    {
                        treeNode *newNode = new treeNode(!thisNode->playerColor,thisNode->piece,thisNode->numUnrevealPiece);
                        newNode->piece[15] =  newNode->piece[15] ^ rev;
                        newNode->piece[a] =  newNode->piece[a] | rev;
                        newNode->numUnrevealPiece[a]--;
//next level   


                        //depthCount++;
                            //newNode->printBoard();
                            newNode=max(newNode,alpha,thisNode->value);
                            //cout<<RedColor<<"r value= "<<newNode->value<<RESET<<endl;                        
                        
                        if(newNode->value<thisNode->value){
                                //aadS(result);
                                thisNode->value=newNode->value;
                                thisNode->chosenMove=result;
                                if(thisNode->child)delete thisNode->child;
                                thisNode->child=newNode;
                            }
                            else{
                                delete newNode;
                            }
                        if(thisNode->value<=alpha){
                            depthCount--;
                            return thisNode;
                        }
                        
                    }
                
                }
            }
            else{
                cout << "child setting ERROR!!!!!!!!!!!!!!!" << endl;
            }
        
        }

    }    
    depthCount--;
    return thisNode;
}

unsigned long long getNodeCount(){
    return nodeCount;
}
int getDepthLim(){
    return depthLimit;
}





void makeMove(string s){
    ofstream move("move.txt");
    if(move.is_open()){
        if(s[2]=='-'){
            move<<"0\n";
            move<<s[0]<<s[1]<<"\n";
            move<<s[3]<<s[4];
        }
        else if(s[0]=='R'){
            move<<"1\n";
            move<<s[2]<<s[3]<<"\n";
            move<<"0";
        }
        else{
            cout<<"OutPut string error\n";
            exit(1);
        }
    }
}

void aadS(string s){
    
    if(order.size()>(depthCount-1)*5){
        order.replace(order.begin()+5*depthCount,order.begin()+5*(depthCount+1),s);
    }
    else{
        order+=s;
    }
} 

// treeNode* generateMove(treeNode *thisNode){}
// treeNode* nextNode(treeNode* thisNode){}
