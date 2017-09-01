#include <iostream>
using namespace std;
int ns[1000000+10];
int N;
int ms[10000+10];
int M;
int nextarr[10000+10];

void input(int *ss,int n)
{
    for(int i=0;i<n;++i)
    {
        cin>>ss[i];
    }
}

void makenext()
{
    nextarr[0]=nextarr[1]=0;
    int j=0;
    for(int i=1;i<M;++i)
    {
        while(j&&ms[i]!=ms[j]) j=nextarr[j];
        if(ms[i]==ms[j])
        {
            nextarr[i+1]=j+1;
            j++;
        }
        else nextarr[i+1]=0;
    }
}
int search()
{
    int j=0;
    for(int i=0;i<N;++i)
    {
        while(j&&ns[i]!=ms[j]) j=nextarr[j];
        if(ns[i]==ms[j]) j++;
        if(j>=M) return i-M+2;
    }
    return -1;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin>>n;
    for(int i=0;i<n;++i)
    {
        cin>>N>>M;
        input(ns,N);
        input(ms,M);
        makenext();
        int index=search();
        cout<<index<<endl;
    }
}

