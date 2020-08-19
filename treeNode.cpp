#include"treeNode.h"

int deleteCount=0;
//int newCount=0;

treeNode::treeNode(){
    //cout<<"newNode\n";
    //newCount++;
}

// treeNode::treeNode(treeNode* t){
//     for(int i=0;i<16;i++){
//         piece[i]=t->piece[i];
//         numUnrevealPiece[i]=t->numUnrevealPiece[i];
//     }
// }
treeNode::treeNode(bool c,U32 p[],int n[]){
    for(int i=0;i<16;i++){
        piece[i]=p[i];
        numUnrevealPiece[i]=n[i];
    }
    playerColor=c;
    //newCount++;
    //cout<<"newNode"<<"\n";
}
treeNode::~treeNode(){
    //cout<<"delete Node\n";
    deleteCount++;
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
        occupied = occupied|piece[j];
        
    }
    
}

U32 treeNode::generateCMove(U32 u32src){
    int intSrc = U32toInt(u32src);
    int r = intSrc / 4, c = intSrc % 4;
    //cout<<"r="<<r<<"c="<<c<<endl;
    U32 dest = 0, dest1 = 0;
    //cout<<hex<<occupied<<endl;
    U32 x = ((row[r] & occupied) ^ u32src) >> (4 * r);//row和occupied的交集 退到第一列
    U32 y = ((column[c] & occupied) ^ u32src) >> c;//col和occupied交集 退到第一列
    //cout<<hex<<"x= "<<x<<" y= "<<y<<endl;
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
    //cout<<hex<<"dest="<<dest<<" dest1="<<dest1<<endl;
    
    return (dest | dest1);
}
