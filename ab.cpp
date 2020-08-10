#include"ab.h"

int depthLimit=5;

int depthCount=0;

unsigned long long nodeCount=1;

U32 red=0,black=0,occupied=0;
string outPut;

void AB(treeNode* root){
    treeNode* newNode = max(root,INT_MIN,INT_MAX);
    cout<<"value="<<newNode->value<<endl;
    makeMove(outPut);
}

treeNode* max(treeNode *thisNode,int alpha,int beta){
    //cout<<"--------------------------------\n";
    nodeCount++;
    //int t;
    thisNode->value =alpha;

    if(depthLimit==depthCount){
        depthCount--;
        thisNode->value = chessTypeValue(thisNode);
        return thisNode;
    }
    else{

//generate move
        refreshBlack(thisNode);
        refreshOccupied(thisNode);
        refreshRed(thisNode);
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
                        dest = pMove[src] & ((black ^    thisNode->piece[14])|  thisNode->piece[0]) ;
                        //printf("%d\n",i);
                    }
                    else if (i == 2)
                    {
                        dest = pMove[src] & (black ^    thisNode->piece[8]);
                        dest = dest|(pMove[src]&  thisNode->piece[0]);
                        // printf("i:%d,mask:%x,src:%d\n",i,mask,src);
                    }
                    else if (i == 3)
                    {
                        dest = pMove[src] & ((black ^    thisNode->piece[8] ^    thisNode->piece[9])|  thisNode->piece[0]);
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

                        dest = generateCMove(mask) & black;
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
                        //cout<<result<<endl;

//generate board with move
                        if (result.empty())
                        {
                            cout << "unusable move string" << endl;
                            exit(1);
                        }
                        if ( result[2] == '-'){   
                            treeNode *newNode = new treeNode(thisNode->playerColor,thisNode->piece,thisNode->numUnrevealPiece);
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
                            depthCount++;
                            newNode=min(newNode,thisNode->value,beta);
                            
                            if(newNode->value>thisNode->value){
                                thisNode->value=newNode->value;
                                if(depthCount==1)
                                    outPut=result;
                                
                            }
                            if(thisNode->value>=beta){
                                    depthCount--;
                                    return thisNode;
                            }
                            delete newNode;
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
                        dest = pMove[src] & (red ^    thisNode->piece[7]);
                        dest = dest|(pMove[src]&  thisNode->piece[0]);
                    }
                    else if (i == 9){
                        dest = pMove[src] & (red ^    thisNode->piece[1]);
                        dest = dest|(pMove[src]&  thisNode->piece[0]);
                    }
                    else if (i == 10)
                        dest = pMove[src] & (red ^    thisNode->piece[1] ^    thisNode->piece[1]);
                    
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
                        dest = generateCMove(mask) & red;
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
                        //printf("i=%d,red=%x,   thisNode->piece[1]=%x\n", i, red,    thisNode->piece[1]);
                        string result("\0");
                        U32 mask2 = LS1B(dest);
                        dest ^= mask2;
                        result.append(U32toString(mask));
                        result.append(1, '-');
                        result.append(U32toString(mask2));
                        //eatMove.push_back(result);
                        //cout<<result<<endl;
//generate board with move
                        if (result.empty())
                        {
                            cout << "unusable move string" << endl;
                            exit(1);
                        }
                        if ( result[2] == '-'){   
                            treeNode *newNode = new treeNode(thisNode->playerColor,thisNode->piece,thisNode->numUnrevealPiece);
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
                            depthCount++;
                            newNode=min(newNode,thisNode->value,beta);
                            
                            if(newNode->value>thisNode->value){
                                thisNode->value=newNode->value;
                                if(depthCount==1)
                                    outPut=result;
                            }
                            if(thisNode->value>=beta){
                                    depthCount--;
                                    return thisNode;
                            }
                            delete newNode;
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
                        treeNode *newNode = new treeNode(thisNode->playerColor,thisNode->piece,thisNode->numUnrevealPiece);
                        newNode->piece[15] =  newNode->piece[15] ^ rev;
                        newNode->piece[a] =  newNode->piece[a] | rev;
                        newNode->numUnrevealPiece[a]--;
//next level                        
                        depthCount++;
                        newNode=min(newNode,thisNode->value,beta);
                        
                        if(newNode->value>thisNode->value){
                            thisNode->value=newNode->value;
                            if(depthCount==1)
                                    outPut=result;
                        }
                        if(thisNode->value>=beta){
                                depthCount--;
                                return thisNode;
                        }
                        delete newNode;
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
    //cout<<"--------------------------------\n";
    nodeCount++;
    //int t;
    thisNode->value =beta;

    if(depthLimit==depthCount){
        depthCount--;
        thisNode->value=chessTypeValue(thisNode);
    }
    else{

//generate move
        refreshBlack(thisNode);
        refreshOccupied(thisNode);
        refreshRed(thisNode);
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
                        dest = pMove[src] & ((black ^ thisNode->piece[14])|  thisNode->piece[0]) ;
                        //printf("%d\n",i);
                    }
                    else if (i == 2)
                    {
                        dest = pMove[src] & (black ^    thisNode->piece[8]);
                        dest = dest|(pMove[src]&  thisNode->piece[0]);
                        // printf("i:%d,mask:%x,src:%d\n",i,mask,src);
                    }
                    else if (i == 3)
                    {
                        dest = pMove[src] & ((black ^    thisNode->piece[8] ^    thisNode->piece[9])|  thisNode->piece[0]);
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

                        dest = generateCMove(mask) & black;
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
                        //cout<<result<<"\n";

//generate board with move
                        if (result.empty())
                        {
                            cout << "unusable move string" << endl;
                            exit(1);
                        }
                        if ( result[2] == '-'){   
                            treeNode *newNode = new treeNode(thisNode->playerColor,thisNode->piece,thisNode->numUnrevealPiece);
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
                            depthCount++;
                            newNode=max(newNode,alpha,thisNode->value);
                            
                            if(newNode->value<thisNode->value){
                                    thisNode->value=newNode->value;
                                    if(depthCount==1)
                                    outPut=result;
                            }
                            if(thisNode->value<=alpha){
                                depthCount--;
                                return thisNode;
                            }
                            delete newNode;
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
                        dest = pMove[src] & (red ^    thisNode->piece[7]);
                        dest = dest|(pMove[src]&  thisNode->piece[0]);
                    }
                    else if (i == 9){
                        dest = pMove[src] & (red ^    thisNode->piece[1]);
                        dest = dest|(pMove[src]&  thisNode->piece[0]);
                    }
                    else if (i == 10)
                        dest = pMove[src] & (red ^    thisNode->piece[1] ^    thisNode->piece[1]);
                    
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
                        dest = generateCMove(mask) & red;
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
                        //printf("i=%d,red=%x,   thisNode->piece[1]=%x\n", i, red,    thisNode->piece[1]);
                        string result("\0");
                        U32 mask2 = LS1B(dest);
                        dest ^= mask2;
                        result.append(U32toString(mask));
                        result.append(1, '-');
                        result.append(U32toString(mask2));
                        //eatMove.push_back(result);
                        //cout<<result<<"\n";
//generate board with move
                        if (result.empty())
                        {
                            cout << "unusable move string" << endl;
                            exit(1);
                        }
                        if ( result[2] == '-'){   
                            treeNode *newNode = new treeNode(thisNode->playerColor,thisNode->piece,thisNode->numUnrevealPiece);
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
                            depthCount++;
                            newNode=max(newNode,alpha,thisNode->value);
                            
                            if(newNode->value<thisNode->value){
                                    thisNode->value=newNode->value;
                                    if(depthCount==1)
                                    outPut=result;
                            }
                            if(thisNode->value<=alpha){
                                depthCount--;
                                return thisNode;
                            }
                            delete newNode;
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
                        treeNode *newNode = new treeNode(thisNode->playerColor,thisNode->piece,thisNode->numUnrevealPiece);
                        newNode->piece[15] =  newNode->piece[15] ^ rev;
                        newNode->piece[a] =  newNode->piece[a] | rev;
                        newNode->numUnrevealPiece[a]--;
//next level                        
                        depthCount++;
                        newNode=max(newNode,alpha,thisNode->value);
                        
                        if(newNode->value<thisNode->value){
                                thisNode->value=newNode->value;
                                if(depthCount==1)
                                    outPut=result;
                        }
                        if(thisNode->value<=alpha){
                            depthCount--;
                            return thisNode;
                        }
                        delete newNode;
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

U32 generateCMove(U32 u32src){
    int intSrc = U32toInt(u32src);
    int r = intSrc / 4, c = intSrc % 4;
    U32 dest = 0, dest1 = 0;
    U32 x = ((row[r] & occupied) ^ (1 << intSrc)) >> (4 * r);
    U32 y = ((column[c] & occupied) ^ (1 << intSrc)) >> c;
    if (x)
    {
        if (c == 0)
        {
            U32 mask = LS1B(x);
            dest = dest | LS1B(x ^= mask);
        }
        if (c == 1)
        {
            dest = dest | (((x & 12) == 12) ? 8 : 0);
        }
        if (c == 2)
        {
            dest = dest | (((x & 3) == 3) ? 1 : 0);
        }
        if (c == 3)
        {
            U32 mask1 = MS1B(x);
            dest = dest | MS1B(x ^= mask1);
        }
    }
    dest = dest << (4 * r);

    if (y)
    {
        if (r == 0)
        {
            U32 y1 = y & 0x11111110;
            U32 mask = LS1B(y1);
            dest1 = dest1 | LS1B(y1 ^= mask);
        }
        if (r == 1)
        {
            U32 y1 = y & 0x11111100;
            U32 mask = LS1B(y1);
            dest1 = dest1 | LS1B(y1 ^= mask);
        }
        if (r == 2)
        {
            U32 y1 = y & 0x11111000;
            U32 mask = LS1B(y1);
            dest1 = dest1 | LS1B(y1 ^= mask);
            U32 y2 = y & 0x00000011;
            U32 mask1 = MS1B(y2);
            dest1 = dest1 | MS1B(y2 ^= mask1);
        }
        if (r == 3)
        {
            U32 y1 = y & 0x11110000;
            U32 mask = LS1B(y1);
            dest1 = dest1 | LS1B(y1 ^= mask);
            U32 y2 = y & 0x00000111;
            U32 mask1 = MS1B(y2);
            dest1 = dest1 | MS1B(y2 ^= mask1);
        }
        if (r == 4)
        {
            U32 y1 = y & 0x11100000;
            U32 mask = LS1B(y1);
            dest1 = dest1 | LS1B(y1 ^= mask);
            U32 y2 = y & 0x00001111;
            U32 mask1 = MS1B(y2);
            dest1 = dest1 | MS1B(y2 ^= mask1);
        }
        if (r == 5)
        {
            U32 y1 = y & 0x11000000;
            U32 mask = LS1B(y1);
            dest1 = dest1 | LS1B(y1 ^= mask);
            U32 y2 = y & 0x00011111;
            U32 mask1 = MS1B(y2);
            dest1 = dest1 | MS1B(y2 ^= mask1);
        }
        if (r == 6)
        {
            U32 y2 = y & 0x00111111;
            U32 mask1 = MS1B(y2);

            dest1 = dest1 | MS1B(y2 ^= mask1);
        }
        if (r == 7)
        {
            U32 y2 = y & 0x01111111;
            U32 mask1 = MS1B(y2);
            dest1 = dest1 | MS1B(y2 ^= mask1);
        }
    }
    dest1 = dest1 << c;

    return (dest | dest1);
}

void refreshRed(treeNode*thisNode){
    int j;
    for (j = 1; j < 8; j++)
    {
        red = red |   thisNode->piece[j];
    }
}
void refreshBlack(treeNode*thisNode){
    int j;
    for (j = 8; j < 15; j++)
    {
        black = black |   thisNode->piece[j];
    }
}
void refreshOccupied(treeNode*thisNode){
    int j;
    //printf("deafult oc:%x\n",occupied);
    for (j = 1; j < 16; j++)
    {
        //printf("piece=%x\n",    thisNode->piece[j]);
        occupied = occupied |   thisNode->piece[j];
        //printf("%x\n",occupied);
    }
    //exit(1);
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
            cout<<outPut<<"\n";
            cout<<"outPut string error\n";
            exit(1);
        }
    }
}

// treeNode* generateMove(treeNode *thisNode){}
// treeNode* nextNode(treeNode* thisNode){}
