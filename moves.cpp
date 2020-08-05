#include<iostream>
#include"moves.h"

using namespace std;

moves::moves(){

}
moves::moves(board *b){

    moveBoard=b;
    
    generateMove();

}

// void moves::printMoves(){
//     cout<<"player color="<<moveBoard->playerColor<<endl;
//    /* for(int i=0;i<16;i++){
//         cout<<moveBoard->piece[i]<<endl;
//     }*/
//     for(int i=0;i<allMove.size();i++){
//         cout<<allMove[i]<<endl;
//     }
// }


void moves::generateMove(){
    generateEat();
    generateReveal();
    generateSpeard();
}
U32 moves::generateCMove(U32 u32src){
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
};
void moves::generateEat(){
    U32 dest;
    //printf("GenerateEat:\n");
    if (!moveBoard->playerColor)
    {
        for (int i = 1; i < 8; i++)
        {
            U32 p = moveBoard->piece[i];
            while (p > 0)
            {
                U32 mask = LS1B(p);
                //printf("i:%d mask:%x\n",i,mask);
                p ^= mask;
                U32 src = U32toInt(mask);
                if (i == 1)
                {
                    dest = pMove[src] & (black ^ moveBoard->piece[14]);
                    //printf("%d\n",i);
                }
                else if (i == 2)
                {
                    dest = pMove[src] & (black ^ moveBoard->piece[8]);
                    // printf("i:%d,mask:%x,src:%d\n",i,mask,src);
                }
                else if (i == 3)
                {
                    dest = pMove[src] & (black ^ moveBoard->piece[8] ^ moveBoard->piece[9]);
                    //printf("i:%d,src:%d\n",i,src);
                }
                else if (i == 4)
                {
                    dest = pMove[src] & (moveBoard->piece[11] | moveBoard->piece[12] | moveBoard->piece[13] | moveBoard->piece[14]);
                    //printf("i:%d,src:%d\n",i,src);
                }
                else if (i == 5)
                {
                    dest = pMove[src] & (moveBoard->piece[12] | moveBoard->piece[13] | moveBoard->piece[14]);
                    //printf("i:%d,src:%d\n",i,src);
                }
                else if (i == 6)
                {

                    dest = generateCMove(mask) & black;
                }
                else if (i == 7)
                {
                    dest = pMove[src] & (moveBoard->piece[8] | moveBoard->piece[14]);
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
    else if (moveBoard->playerColor)
    {
        for (int i = 8; i < 15; i++)
        {
            U32 p = moveBoard->piece[i];
            while (p > 0)
            {
                U32 mask = LS1B(p);
                p ^= mask;
                U32 src = U32toInt(mask);
                if (i == 8)
                    dest = pMove[src] & (red ^ moveBoard->piece[7]);
                else if (i == 9)
                    dest = pMove[src] & (red ^ moveBoard->piece[1]);
                else if (i == 10)
                    dest = pMove[src] & (red ^ moveBoard->piece[1] ^ moveBoard->piece[1]);
                else if (i == 11)
                    dest = pMove[src] & (moveBoard->piece[4] | moveBoard->piece[5] | moveBoard->piece[6] | moveBoard->piece[7]);

                else if (i == 12)
                {
                    dest = pMove[src] & (moveBoard->piece[5] | moveBoard->piece[6] | moveBoard->piece[7]);
                    //printf("p=%llu,src=%llu,dest=%llu\n",p,src,dest);
                }

                else if (i == 13)
                {
                    dest = generateCMove(mask) & red;
                }
                else if (i == 14)
                    dest = pMove[src] & (moveBoard->piece[1] | moveBoard->piece[7]);
                else
                    dest = 0;

                while (dest > 0)
                {
                    //printf("i=%d,red=%x,moveBoard->piece[1]=%x\n", i, red, moveBoard->piece[1]);
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

};
void moves::generateReveal(){
    U32 reveal = moveBoard->piece[15];
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
void moves::generateSpeard(){
    U32 src, dest;
    //printf("GenerateSpeard:\n");
    if(!moveBoard->playerColor){
        for (int i = 1; i <8; i++){
            U32 p = moveBoard->piece[i];
            while (p)
            {
                U32 mask = LS1B(p);
                p ^= mask;
                src = U32toInt(mask);
                dest = pMove[src] & moveBoard->piece[0];
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
    else if(moveBoard->playerColor){
        for (int i = 8; i <15; i++){
            U32 p = moveBoard->piece[i];
            while (p)
            {
                U32 mask = LS1B(p);
                p ^= mask;
                src = U32toInt(mask);
                dest = pMove[src] & moveBoard->piece[0];
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


void moves::refreshRed(){
    int j;
    for (j = 1; j < 8; j++)
    {
        red = red | moveBoard->piece[j];
    }
}
void moves::refreshBlack(){
    int j;
    for (j = 8; j < 15; j++)
    {
        black = black | moveBoard->piece[j];
    }
}
void moves::refreshOccupied(){
    int j;
    //printf("deafult oc:%x\n",occupied);
    for (j = 1; j < 16; j++)
    {
        //printf("piece=%x\n",moveBoard->piece[j]);
        occupied = occupied | moveBoard->piece[j];
        //printf("%x\n",occupied);
    }
    //exit(1);
}

