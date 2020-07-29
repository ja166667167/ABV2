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