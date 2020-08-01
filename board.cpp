#include "board.h"


using namespace std;

board::board(){
    readBoardFile();
    initData();
}
board::board(board* b,string s){
    
    
    
    
    
    initData();
}
board::board(U32 p[]){
    for(int i;i<16;i++){
        piece[i]=p[i];
    }
    initData();
}

void board::initData(){
    possibleMoves.setBoard(piece);
    possibleMoves.generateMove();
    setPosBoard();
}

void readBoardFile(){

    fstream file;

}


void board::setPosBoard(){

}


void board::printBoard(){
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

