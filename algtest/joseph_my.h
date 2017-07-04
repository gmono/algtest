#include <iostream>
#include <algorithm>
using namespace std;
int mintable[15]={0};
int joseph(int k)
{
    if(mintable[k]) return mintable[k];
    for(int m=1;;m++)
    {
        //尝试每一个m
        int n=2*k; //初始状态的N有2*k个 每出局一个N减少1 相当于第n-1个出局
        //表示出局一个 由于k->n-1的任何一个出局都一样 因此可以这样
        bool isok=true;
        int t=0;
        for(int i=1;i<=k;++i)
        {
//            t=(t+m-1)%n;
            t=(t+m)%n+1;
//            if(t<k)
            if(t<=k)
            {
                isok=false;
                break;
            }
            n--;
        }
        if(isok)
        {
            mintable[k]=m;
            return m;
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cout.tie(0);
    int k;
    while(cin>>k)
    {
        if(k==0) break;
        cout<<joseph(k)<<endl;
    }
}
