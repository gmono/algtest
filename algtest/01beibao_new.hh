#include <iostream>
#include <memory.h>
using namespace std;
#define maxn 1000+5
int N,V;
int volumes[maxn];
int values[maxn];
int dp[maxn];
int solve()
{
    memset(dp,0,sizeof(int)*maxn);
    for(int i=0;i<N;++i)
    {
        for(int j=V;j>=volumes[i];--j)
        {
            dp[j]=max(dp[j-volumes[i]]+values[i],dp[j]);
        }
    }
    int ret=dp[V];
    return ret;

}

int main()
{
    int T;
    cin>>T;
    for(int i=0;i<T;++i)
    {
        //V:volume N:the number of bones
        cin>>N>>V;
        for(int j=0;j<N;++j)
        {
            cin>>values[j];
        }
        for(int j=0;j<N;++j)
        {
            cin>>volumes[j];
        }
        cout<<solve()<<endl;
    }
    return 0;
}
