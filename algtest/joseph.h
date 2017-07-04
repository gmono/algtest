#include <iostream>
using namespace std;
int mintable[15]={0};
int joseph(int k)
{
    if(mintable[k]) return mintable[k];
    int a=1;
    for(;;)
    {
        for(int b=1;b<=k;++b)
        {
            int m=a*k+b;
            int t=0,n=2*k;
            int i;
            for(i=1;i<=k;++i)
            {
                t=(t+m-1)%n;
                if(t<k) break;
                n--;
            }
            if(i>k)
            {
                mintable[k]=m;
                return m;
            }
        }
        a+=2;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cout.tie(0);
    int k;
    while(cin>>k)
    {
        if(!k) break;
        cout<<joseph(k)<<endl;
    }
    return 0;
}
