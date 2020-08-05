#include"treeNode.h"

treeNode::treeNode(){}

treeNode::treeNode(board *b){
    nodeBoard=b;
    boardMove = new moves(b);
}

// treeNode::treeNode(treeNode *t,board*b){
//     parent=t;
//     nodeBoard=b;
//     boardMove = new moves(b);
// }

vector<board*> treeNode::getNextBoard(){
    
    vector<board*>possibleBoards;

    if ( boardMove->allMove.empty())
    {
        cout << "Moves are empty when probing" << endl;
        exit(1);
    }
    
    for(int i=0;i<boardMove->allMove.size();i++){
        if (boardMove->allMove[i][2] == '-'){   
            
            board* newBoard = new board(nodeBoard);
            int srcP =    boardMove->allMove[i][0] - 96 + (   boardMove->allMove[i][1] - 49) * 4;
            int destP =    boardMove->allMove[i][3] - 96 + (   boardMove->allMove[i][4] - 49) * 4;
            U32 src = InttoU32(srcP);
            U32 dest = InttoU32(destP);
            for (int i = 0; i < 16; i++)
            {
                if ((newBoard->piece[i] != 0) & ((newBoard->piece[i] | src) == newBoard->piece[i]))
                {

                    newBoard->piece[i] = newBoard->piece[i] ^ src;
                    newBoard->piece[0] = newBoard->piece[0] | src;
                    for (int j = 0; j < 16; j++)
                    {
                        if ((newBoard->piece[j] != 0) & ((newBoard->piece[j] | dest) == newBoard->piece[j]))
                        {
                            newBoard->piece[j] = newBoard->piece[j] ^ dest;
                        }
                    }
                    newBoard->piece[i] = newBoard->piece[i] | dest;
                }
            }

            possibleBoards.push_back(newBoard);
        }
        else if(boardMove->allMove[i][0]=='R'){
            int revP =    boardMove->allMove[i][2] - 96 + (   boardMove->allMove[i][3] - 49) * 4;
            U32 rev = InttoU32(revP);
            for (int a = 1; a < 15; a++){

                if (nodeBoard->numUnrevealPiece[a] != 0)//此棋種還有位翻開的棋
                {
                    board* newBoard= new board(nodeBoard);
                    newBoard->piece[15] = newBoard->piece[15] ^ rev;
                    newBoard->piece[a] = newBoard->piece[a] | rev;
                    newBoard->numUnrevealPiece[a]--;
                    possibleBoards.push_back(newBoard);

                }
            
            }
        }
        
        else{
            cout << "simulate ERROR!!!!!!!!!!!!!!!" << endl;
        }
    }
    return possibleBoards;
}

// void treeNode::printMoves(){
//     boardMove->printMoves();
// }
// void treeNode::printBoard(){
//     nodeBoard->printBoard();
// }