#include <iostream>
#include <memory.h>
using namespace std;
#define maxn 1000+5
int values[maxn];
int volumes[maxn];
int N,V;
int result[maxn];
int table[maxn][maxn];
void makeTable()
{
//    memset(table,0,sizeof(int)*maxn*maxn);
    for(int i=0;i<=N;++i)
    {
        for(int j=0;j<=V;++j)
        {
            if(i==0||j==0) {table[i][j]=0;continue;}
            if(volumes[i-1]>j){table[i][j]=table[i-1][j];continue;}
            int t1=values[i-1]+table[i-1][j-volumes[i-1]];
            int t2=table[i-1][j];
            table[i][j]=t1>t2? t1:t2;
        }
    }
}
void solve()
{
    int j=V;
    for(int i=N;i>=1;--i)
    {
        if(table[i][j]==table[i-1][j])
            result[i-1]=0;
        else
        {
            result[i-1]=1;
            j=j-volumes[i-1];
        }
    }
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
        makeTable();
        solve();
        int sum=0;
        for(int j=0;j<N;++j)
        {
            if(result[j]) sum+=values[j];
        }
        cout<<sum<<endl;
    }
    return 0;
}
