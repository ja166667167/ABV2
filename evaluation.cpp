#include"evaluation.h"



float chessTypeValue(treeNode *valueNode){
        float score = 0;
    //cout << "start score=" << score << endl;
    if (valueNode->playerColor == 0)
    {
        for (int i = 1; i < 15; i++)
        {
            switch (i)
            {
            case 1:
                score += (7 * pieceCount(valueNode,i));
                break;
            case 2:
                score += (6 * pieceCount(valueNode,i));
                break;
            case 3:
                score += (5 * pieceCount(valueNode,i));
                break;
            case 4:
                score += (4 * pieceCount(valueNode,i));
                break;
            case 5:
                score += (3 * pieceCount(valueNode,i));
                break;
            case 6:
                score += (2 * pieceCount(valueNode,i));
                break;
            case 7:
                score += (1 * pieceCount(valueNode,i));
                break;
            case 8:
                score -= (7 * pieceCount(valueNode,i));
                break;
            case 9:
                score -= (6 * pieceCount(valueNode,i));
                break;
            case 10:
                score -= (5 * pieceCount(valueNode,i));
                break;
            case 11:
                score -= (4 * pieceCount(valueNode,i));
                break;
            case 12:
                score -= (3 * pieceCount(valueNode,i));
                break;
            case 13:
                score -= (2 * pieceCount(valueNode,i));
                break;
            case 14:
                score -= (1 * pieceCount(valueNode,i));
                break;

            }
        }
    }
    else if (valueNode->playerColor == 1)
    {
        for (int i = 1; i < 15; i++)
        {
            switch (i)
            {
            case 1:
                score -= (7 * pieceCount(valueNode,i));
                break;
            case 2:
                score -= (6 * pieceCount(valueNode,i));
                break;
            case 3:
                score -= (5 * pieceCount(valueNode,i));
                break;
            case 4:
                score -= (4 * pieceCount(valueNode,i));
                break;
            case 5:
                score -= (3 * pieceCount(valueNode,i));
                break;
            case 6:
                score -= (2 * pieceCount(valueNode,i));
                break;
            case 7:
                score -= (1 * pieceCount(valueNode,i));
                break;
            case 8:
                score += (7 * pieceCount(valueNode,i));
                break;
            case 9:
                score += (6 * pieceCount(valueNode,i));
                break;
            case 10:
                score += (5 * pieceCount(valueNode,i));
                break;
            case 11:
                score += (4 * pieceCount(valueNode,i));
                break;
            case 12:
                score += (3 * pieceCount(valueNode,i));
                break;
            case 13:
                score += (2 * pieceCount(valueNode,i));
                break;
            case 14:
                score += (1 * pieceCount(valueNode,i));
                break;
            }
        }
    }
    //cout<<"score="<<score<<endl;
    return score;
}

int pieceCount(treeNode*valueNode,int i){
    int count = 0;
    U32 p = valueNode->piece[i];
    while (p)
    {
        p = p ^ LS1B(p);
        count++;
    }
    return count;
}