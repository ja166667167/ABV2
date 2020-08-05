#include"treeNode.h"

treeNode::treeNode(){}

treeNode::treeNode(treeNode* t){
    for(int i=0;i<16;i++){
        piece[i]=t->piece[i];
        numUnrevealPiece[i]=t->numUnrevealPiece[i];
    }
    for(int i=0;i<allMove.size();i++){
        allMove.push_back(t->allMove[i]);
    }

}
treeNode::treeNode(bool c,U32 p[],int n[]){
    for(int i=0;i<16;i++){
        piece[i]=p[i];
        numUnrevealPiece[i]=n[i];
    }
    playerColor=c;
    
}
// treeNode::treeNode(treeNode *t,board*b){
//     parent=t;
//     nodeBoard=b;
//     boardMove = new moves(b);
// }

vector<treeNode*> treeNode::setChildren(){

    
    

    if (  allMove.empty())
    {
        cout << "Moves are empty when probing" << endl;
        exit(1);
    }
    
    for(int i=0;i< allMove.size();i++){
        if ( allMove[i][2] == '-'){   
            treeNode *newNode = new treeNode(playerColor,piece,numUnrevealPiece);
            int srcP = allMove[i][0] - 96 + (allMove[i][1] - 49) * 4;
            int destP = allMove[i][3] - 96 + (allMove[i][4] - 49) * 4;
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
            newNode->generateMove();
            children.push_back( newNode);
        }
        else if( allMove[i][0]=='R'){
            int revP =     allMove[i][2] - 96 + (    allMove[i][3] - 49) * 4;
            U32 rev = InttoU32(revP);
            for (int a = 1; a < 15; a++){

                if (numUnrevealPiece[a] != 0)//此棋種還有位翻開的棋
                {
                    treeNode *newNode = new treeNode(playerColor,piece,numUnrevealPiece);
                    newNode->piece[15] =  newNode->piece[15] ^ rev;
                    newNode->piece[a] =  newNode->piece[a] | rev;
                    newNode->numUnrevealPiece[a]--;
                    newNode->generateMove();
                    children.push_back( newNode);

                }
            
            }
        }
        
        else{
            cout << "child setting ERROR!!!!!!!!!!!!!!!" << endl;
        }
    }

    return children;
}

void treeNode::generateMove(){
    refreshRed();
    refreshBlack();
    refreshOccupied();
    generateEat();
    generateSpeard();
    generateReveal();

}

U32 treeNode::generateCMove(U32 u32src){
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
void treeNode::generateEat(){
    U32 dest;
    //printf("GenerateEat:\n");
    if (!playerColor)
    {
        for (int i = 1; i < 8; i++)
        {
            U32 p =  piece[i];
            while (p > 0)
            {
                U32 mask = LS1B(p);
                //printf("i:%d mask:%x\n",i,mask);
                p ^= mask;
                U32 src = U32toInt(mask);
                if (i == 1)
                {
                    dest = pMove[src] & (black ^  piece[14]);
                    //printf("%d\n",i);
                }
                else if (i == 2)
                {
                    dest = pMove[src] & (black ^  piece[8]);
                    // printf("i:%d,mask:%x,src:%d\n",i,mask,src);
                }
                else if (i == 3)
                {
                    dest = pMove[src] & (black ^  piece[8] ^  piece[9]);
                    //printf("i:%d,src:%d\n",i,src);
                }
                else if (i == 4)
                {
                    dest = pMove[src] & ( piece[11] |  piece[12] |  piece[13] |  piece[14]);
                    //printf("i:%d,src:%d\n",i,src);
                }
                else if (i == 5)
                {
                    dest = pMove[src] & ( piece[12] |  piece[13] |  piece[14]);
                    //printf("i:%d,src:%d\n",i,src);
                }
                else if (i == 6)
                {

                    dest = generateCMove(mask) & black;
                }
                else if (i == 7)
                {
                    dest = pMove[src] & ( piece[8] |  piece[14]);
                }
                else
                {
                    dest = 0;
                }
                //printf("%x\n",dest);
                while (dest > 0)
                {
                    string result("\0");
                    U32 mask2 = LS1B(dest);
                    dest ^= mask2;
                    result.append(U32toString(mask));
                    result.append(1, '-');
                    result.append(U32toString(mask2));
                    //eatMove.push_back(result);
                    allMove.push_back(result);

                }
            }
        }
    }
    else if ( playerColor)
    {
        for (int i = 8; i < 15; i++)
        {
            U32 p =  piece[i];
            while (p > 0)
            {
                U32 mask = LS1B(p);
                p ^= mask;
                U32 src = U32toInt(mask);
                if (i == 8)
                    dest = pMove[src] & (red ^  piece[7]);
                else if (i == 9)
                    dest = pMove[src] & (red ^  piece[1]);
                else if (i == 10)
                    dest = pMove[src] & (red ^  piece[1] ^  piece[1]);
                else if (i == 11)
                    dest = pMove[src] & ( piece[4] |  piece[5] |  piece[6] |  piece[7]);

                else if (i == 12)
                {
                    dest = pMove[src] & ( piece[5] |  piece[6] |  piece[7]);
                    //printf("p=%llu,src=%llu,dest=%llu\n",p,src,dest);
                }

                else if (i == 13)
                {
                    dest = generateCMove(mask) & red;
                }
                else if (i == 14)
                    dest = pMove[src] & ( piece[1] |  piece[7]);
                else
                    dest = 0;

                while (dest > 0)
                {
                    //printf("i=%d,red=%x, piece[1]=%x\n", i, red,  piece[1]);
                    string result("\0");
                    U32 mask2 = LS1B(dest);
                    dest ^= mask2;
                    result.append(U32toString(mask));
                    result.append(1, '-');
                    result.append(U32toString(mask2));
                    //eatMove.push_back(result);
                    allMove.push_back(result);

                }
            }
        }
    }

}

void treeNode::generateReveal(){
    U32 reveal =  piece[15];
    U32 mask;
    //printf("GenerateReveal:\n");
    while (reveal > 0)
    {
        string result("\0");
        mask = LS1B(reveal);
        reveal ^= mask;
        result.append("R(");
        result.append(U32toString(mask));
        result.append(")");
        //revealMove.push_back(result);
        allMove.push_back(result);
        //cout << result << endl;
    }
}

void treeNode::generateSpeard(){
    U32 src, dest;
    //printf("GenerateSpeard:\n");
    if(! playerColor){
        for (int i = 1; i <8; i++){
            U32 p =  piece[i];
            while (p)
            {
                U32 mask = LS1B(p);
                p ^= mask;
                src = U32toInt(mask);
                dest = pMove[src] &  piece[0];
                while (dest)
                {
                    //printf("i=%d ",i);///////////////////
                    string result("\0");
                    U32 mask2 = LS1B(dest);
                    dest ^= mask2;
                    result.append(U32toString(mask));
                    result.append(1, '-');
                    result.append(U32toString(mask2));
                    //spreadMove.push_back(result);
                    allMove.push_back(result);
                    //cout << result << endl;
                }
                //printf("\n");//////////////////////////
            }
        }
    }
    else if( playerColor){
        for (int i = 8; i <15; i++){
            U32 p =  piece[i];
            while (p)
            {
                U32 mask = LS1B(p);
                p ^= mask;
                src = U32toInt(mask);
                dest = pMove[src] &  piece[0];
                while (dest)
                {
                    //printf("i=%d ",i);///////////////////
                    string result("\0");
                    U32 mask2 = LS1B(dest);
                    dest ^= mask2;
                    result.append(U32toString(mask));
                    result.append(1, '-');
                    result.append(U32toString(mask2));
                    //spreadMove.push_back(result);
                    allMove.push_back(result);
                    //cout << result << endl;
                }
                //printf("\n");//////////////////////////
            }
        }
    }
}


void treeNode::refreshRed(){
    int j;
    for (j = 1; j < 8; j++)
    {
        red = red | piece[j];
    }
}
void treeNode::refreshBlack(){
    int j;
    for (j = 8; j < 15; j++)
    {
        black = black | piece[j];
    }
}
void treeNode::refreshOccupied(){
    int j;
    //printf("deafult oc:%x\n",occupied);
    for (j = 1; j < 16; j++)
    {
        //printf("piece=%x\n",  piece[j]);
        occupied = occupied | piece[j];
        //printf("%x\n",occupied);
    }
    //exit(1);
}

void treeNode::printBoard()
{
    int a, b, p, c;
    U32 s;
    for (a = 7; a >= 0; a--)
    {
        for (b = 1; b < 5; b++)
        {
            p = 4 * a + b;
            //printf("p = %d\n",p);
            s = InttoU32(p);
            //printf("s = %x\n",s);
            for (c = 0; c < 16; c++)
            {
                if (((piece[c] | s) == piece[c]) & (piece[c] != 0))
                {
                    switch (c)
                    {
                    case 0:
                        printf("- ");
                        break;
                    case 1:
                        printf("K ");
                        break;
                    case 2:
                        printf("G ");
                        break;
                    case 3:
                        printf("M ");
                        break;
                    case 4:
                        printf("R ");
                        break;
                    case 5:
                        printf("N ");
                        break;
                    case 6:
                        printf("C ");
                        break;
                    case 7:
                        printf("P ");
                        break;
                    case 8:
                        printf("k ");
                        break;
                    case 9:
                        printf("g ");
                        break;
                    case 10:
                        printf("m ");
                        break;
                    case 11:
                        printf("r ");
                        break;
                    case 12:
                        printf("n ");
                        break;
                    case 13:
                        printf("c ");
                        break;
                    case 14:
                        printf("p ");
                        break;
                    case 15:
                        printf("X ");
                        break;
                    default:
                        printf("?");
                    }
                    //printf("s=%x c=%d piece=%x\n", s, c,piece[c]);
                }
            }
        }
        printf("\n");
    }
}
void treeNode::printMoves(){
    cout<<"player color="<<playerColor<<endl;
   /* for(int i=0;i<16;i++){
        cout<<piece[i]<<endl;
    }*/
    for(int i=0;i<allMove.size();i++){
        cout<<allMove[i]<<endl;
    }
}
