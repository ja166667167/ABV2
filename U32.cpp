#include"U32.h"

int U32toInt(U32 p){
    int i=0;
    if(p==0)
        return 0;
    while(p!=1){
        i++;
        p=p>>1;
    }
    return i;
}
U32 InttoU32(int p){
    U32 u=1;
    if(p==0)
        return 0;
    u=u<<(p-1);
    cout<<hex;
    cout<<u<<endl;
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