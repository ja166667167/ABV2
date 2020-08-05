#include<iostream>
#include"AB.h"


using namespace std;

board* readFile(){

    board *newBoard = new board();
    


    ifstream file("board.txt");

    if (!file.is_open())
    {
        cout << "file error" << endl;
        exit(1);
    }

    int intSrc, intDest, intRev;
    U32 U32Src, U32Dest, U32Rev;
    string line;
    int lineCount = 0;
    bool firstColor = NULL, meFirst = true;
    //start reading
    while (1)
    {

        getline(file, line);
        if (++lineCount < 14)
            continue;
        if (line == "* Comment 0 0")
            break;

        stringstream ss(line);
        string s;
        //first part
        ss >> s;
        ss >> s;
        ss >> s;
        //red =0 black =1
        if (lineCount == 14)
        {
            if (s[3] >= 97 && s[3] <= 122)
                firstColor = true;
            else if (s[3] >= 65 && s[3] <= 90)
                firstColor = false;
            else
            {
                cout << "geting firstColor error" << endl;
                exit(1);
            }
        }

        //Eat or move
        if (s[2] == '-')
        {
            intSrc = s[0] - 96 + (s[1] - 49) * 4;
            intDest = s[3] - 96 + (s[4] - 49) * 4;
            U32Src = InttoU32(intSrc);
            U32Dest = InttoU32(intDest);
            for (int i = 0; i < 16; i++)
            {
                if ((newBoard->piece[i] != 0) & ((newBoard->piece[i] | U32Src) == newBoard->piece[i]))
                {
                    
                    newBoard->piece[i] = newBoard->piece[i] ^ U32Src;
                    
                    newBoard->piece[0] = newBoard->piece[0] | U32Src;
                   
                    for (int j = 0; j < 16; j++)
                    {
                        if ((newBoard->piece[j] != 0) & ((newBoard->piece[j] | U32Dest) == newBoard->piece[j]))
                        {
                            //printf("j=%d\n", j);
                            newBoard->piece[j] = newBoard->piece[j] ^ U32Dest;
                        }
                    }
                    newBoard->piece[i] = newBoard->piece[i] | U32Dest;
                }
            }
        }
        //Reveal
        else
        {
            intRev = s[0] - 96 + (s[1] - 49) * 4;
            U32Rev = InttoU32(intRev);
            newBoard->piece[15] = newBoard->piece[15] ^ U32Rev;

            int i = 0;
            switch (s[3])
            {
            case 'K':
                i = 1;
                break;
            case 'G':
                i = 2;
                break;
            case 'M':
                i = 3;
                break;
            case 'R':
                i = 4;
                break;
            case 'N':
                i = 5;
                break;
            case 'C':
                i = 6;
                break;
            case 'P':
                i = 7;
                break;
            case 'k':
                i = 8;
                break;
            case 'g':
                i = 9;
                break;
            case 'm':
                i = 10;
                break;
            case 'r':
                i = 11;
                break;
            case 'n':
                i = 12;
                break;
            case 'c':
                i = 13;
                break;
            case 'p':
                i = 14;
                break;
            }

            newBoard->piece[i] = newBoard->piece[i] | U32Rev;
            newBoard->numUnrevealPiece[i]--;
            //printf("i=%d,intRev=%d,rev=%x,newBoard->piece=%x\n",i,intRev,rev,newBoard->piece[i]);
        }
        //second part
        if (ss >> s)
        {
            if (s[2] == '-')
            { //Eat
                intSrc = s[0] - 96 + (s[1] - 49) * 4;
                intDest = s[3] - 96 + (s[4] - 49) * 4;
                U32Src = InttoU32(intSrc);
                U32Dest = InttoU32(intDest);
                for (int i = 0; i < 16; i++)
                {
                    if ((newBoard->piece[i] != 0) & ((newBoard->piece[i] | U32Src) == newBoard->piece[i]))
                    {
                        //printf("i=%d\n",i);
                        newBoard->piece[i] = newBoard->piece[i] ^ U32Src;
                        //printf("newBoard->piece=%d\n", newBoard->piece[i]);
                        newBoard->piece[0] = newBoard->piece[0] | U32Src;
                        //printf("[0]=%d\n", newBoard->piece[0]);
                        for (int j = 0; j < 16; j++)
                        {
                            if ((newBoard->piece[j] != 0) & ((newBoard->piece[j] | U32Dest) == newBoard->piece[j]))
                            {
                                //printf("j=%d\n", j);
                                newBoard->piece[j] = newBoard->piece[j] ^ U32Dest;
                            }
                        }
                        newBoard->piece[i] = newBoard->piece[i] | U32Dest;
                    }
                }
            }
            else
            { //Reveal
                intRev = s[0] - 96 + (s[1] - 49) * 4;
                U32Rev = InttoU32(intRev);
                newBoard->piece[15] = newBoard->piece[15] ^ U32Rev;

                int i = 0;
                switch (s[3])
                {
                case 'K':
                    i = 1;
                    break;
                case 'G':
                    i = 2;
                    break;
                case 'M':
                    i = 3;
                    break;
                case 'R':
                    i = 4;
                    break;
                case 'N':
                    i = 5;
                    break;
                case 'C':
                    i = 6;
                    break;
                case 'P':
                    i = 7;
                    break;
                case 'k':
                    i = 8;
                    break;
                case 'g':
                    i = 9;
                    break;
                case 'm':
                    i = 10;
                    break;
                case 'r':
                    i = 11;
                    break;
                case 'n':
                    i = 12;
                    break;
                case 'c':
                    i = 13;
                    break;
                case 'p':
                    i = 14;
                    break;
                }
                newBoard->piece[i] = newBoard->piece[i] | U32Rev;
                //newBoard->numUreveal->piece[i]--;
                //printf("i=%d,intRev=%d,rev=%x,newBoard->piece=%x\n",i,intRev,rev,newBoard->piece[i]);
            }
        }
        //如果沒有後段 代表不是我先手
        else
            meFirst = false;
    }

    newBoard->playerColor = firstColor && meFirst;

    file.close();
    return newBoard;
}

board *newBoard=readFile();


int main(){

    int ans=0;
    treeNode *root = new treeNode(newBoard);
    try{
    ans=AB(root);
    }
    catch(std::bad_alloc &ba){
        cout<<"bad Allocation caught:"<<ba.what()<<"\n";
    }
    cout<<getNodeCount()<<"\n";
    cout<<ans<<"\n";
    return 0;
}