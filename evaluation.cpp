#include"evaluation.h"



int chessTypeValue(board *valueBoard){
        int score = 0;
    //cout << "start score=" << score << endl;
    if (valueBoard->playerColor == 0)
    {
        for (int i = 1; i < 15; i++)
        {
            switch (i)
            {
            case 1:
                score += (7 * pieceCount(valueBoard,i));
                break;
            case 2:
                score += (6 * pieceCount(valueBoard,i));
                break;
            case 3:
                score += (5 * pieceCount(valueBoard,i));
                break;
            case 4:
                score += (4 * pieceCount(valueBoard,i));
                break;
            case 5:
                score += (3 * pieceCount(valueBoard,i));
                break;
            case 6:
                score += (2 * pieceCount(valueBoard,i));
                break;
            case 7:
                score += (1 * pieceCount(valueBoard,i));
                break;
            case 8:
                score -= (7 * pieceCount(valueBoard,i));
                break;
            case 9:
                score -= (6 * pieceCount(valueBoard,i));
                break;
            case 10:
                score -= (5 * pieceCount(valueBoard,i));
                break;
            case 11:
                score -= (4 * pieceCount(valueBoard,i));
                break;
            case 12:
                score -= (3 * pieceCount(valueBoard,i));
                break;
            case 13:
                score -= (2 * pieceCount(valueBoard,i));
                break;
            case 14:
                score -= (1 * pieceCount(valueBoard,i));
                break;

            }
        }
    }
    else if (valueBoard->playerColor == 1)
    {
        for (int i = 1; i < 15; i++)
        {
            switch (i)
            {
            case 1:
                score -= (7 * pieceCount(valueBoard,i));
                break;
            case 2:
                score -= (6 * pieceCount(valueBoard,i));
                break;
            case 3:
                score -= (5 * pieceCount(valueBoard,i));
                break;
            case 4:
                score -= (4 * pieceCount(valueBoard,i));
                break;
            case 5:
                score -= (3 * pieceCount(valueBoard,i));
                break;
            case 6:
                score -= (2 * pieceCount(valueBoard,i));
                break;
            case 7:
                score -= (1 * pieceCount(valueBoard,i));
                break;
            case 8:
                score += (7 * pieceCount(valueBoard,i));
                break;
            case 9:
                score += (6 * pieceCount(valueBoard,i));
                break;
            case 10:
                score += (5 * pieceCount(valueBoard,i));
                break;
            case 11:
                score += (4 * pieceCount(valueBoard,i));
                break;
            case 12:
                score += (3 * pieceCount(valueBoard,i));
                break;
            case 13:
                score += (2 * pieceCount(valueBoard,i));
                break;
            case 14:
                score += (1 * pieceCount(valueBoard,i));
                break;
            }
        }
    }
    return score;
}

int pieceCount(board *valueBoard,int i){
    int count = 0;
    U32 p = valueBoard->piece[i];
    while (p)
    {
        p = p ^ LS1B(p);
        count++;
    }
    return count;
}