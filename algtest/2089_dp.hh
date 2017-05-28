#include <iostream>
#include <memory.h>
using namespace std;
//计算不符合要求的数量
//从1开始
int mem[1000010];
//指向已计算的值索引末端
int compnow=0;
int solve(int num)
{
    if(num<=compnow) return mem[num];
    for(int i=compnow+1;i<=num;++i)
    {
        int state=0;
        bool ok=false;
        //define fsm
        //0 2 to 1
        //1 2 to 1/ 6 to 0 and dosome/other to 0
        for(int j=i;j!=0;j/=10)
        {
            int tn=j%10;
            if(tn==4)
            {
                ok=true;
                break;
            }
            switch(state)
            {
            case 0:
                if(tn==2)
                    state=1;
                break;
            case 1:
                if(tn==6)
                {
                    state=0;
                    ok=true;
                    //跳出
                    goto cont;

                }
                else if(tn==2);
                else state=0;
            }
        }
        cont:
        if(ok)
        {
            mem[i]=mem[i-1]+1;
        }
        else mem[i]=mem[i-1];
    }
    compnow=num;
    return mem[num];
}
int main()
{
    memset(mem,0,sizeof(int)*1000010);
    ios::sync_with_stdio(false);
    cout.tie(0);
    int n,m;
    while(cin>>n>>m)
    {
        if(n==m&&n==0) break;
        cout<<m-n+1-(solve(m)-solve(n-1))<<endl;
    }
}
