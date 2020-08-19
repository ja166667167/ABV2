#include"U32.h"

string U32toString(U32 p){
    string outPut;
    if(p==0x0){
        cout<<"U32toString p=0";
        exit(1);
    }
    for(int i=0;i<4;i++){
       if((column[i]|p)==column[i]){
            switch(i){
                case 0:
                    outPut+='a';
                    break;
                case 1:
                    outPut+='b';
                    break;
                case 2:
                    outPut+='c';
                    break;
                case 3:
                    outPut+='d';
                    break;
                }
            } 
    }
    for (int j = 0; j < 8;j++){
            if((row[j]|p)==row[j]){
                switch(j){
                    case 0:
                        outPut+='1';break;
                    case 1:
                        outPut+='2';break;
                    case 2:
                        outPut+='3';break;
                    case 3:
                        outPut+='4';break;
                    case 4:
                        outPut+='5';break;
                    case 5:
                        outPut+='6';break;
                    case 6:
                        outPut+='7';break;
                    case 7:
                        outPut+='8';break;
                }
            }
        }
    return outPut;
}
// 0~32: 0=空值 第一格為1
int U32toInt(U32 p){
    int i=0;
    while(p){
        p=p>>1;
        i++;
    }
    return i;
}

U32 InttoU32(int p){
    U32 u=1;
    if(p==0)
        return 0;
    u=u<<(p-1);
    //cout<<hex;
    //cout<<u<<endl;
    return u;
}
U32 LS1B(U32 x){
    return x & (-x);
}
U32 MS1B(U32 x){
    x |= (x >> 1);
    x |= (x >> 2);
    x |= (x >> 4);
    x |= (x >> 8);
    x |= (x >> 16);
    //x |= (x >> 32);
    return (x >> 1) + 1;
}