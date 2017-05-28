#include <iostream>
using namespace std;


int main()
{

    ios::sync_with_stdio(false);
    cout.tie(0);
    int n,m;
    while(cin>>n>>m)
    {
        if(n==m&&n==0) break;
        int sum=m-n+1;
        if(m)
        for(int i=n;i<=m;++i)
        {
            //define
            //0 6 ->1
            //1 2 ->0 sum--  other ->0
            int state=0;
            for(int j=i;j!=0;j/=10)
            {
                int tnum=j%10;
                if(tnum==4)
                {
                    sum--;
                    break;
                }
                switch(state)
                {
                case 0:
                    if(tnum==6) state=1;
                    break;
                case 1:
                    if(tnum==2)
                    {
                        state=0;
                        sum--;
                        break;
                    }
                    else
                    {
                        state=0;
                    }
                    break;
                }
            }
        }
        cout<<sum<<endl;
    }
}
