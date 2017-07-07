#include <iostream>
#include <time.h>
using namespace std;
int solve1(int a,int b)
{
        for(int i=2;;i++)
        {
            if( (i%b)==0)continue;
            if(a%(b*i)!=0)
            {
                return b*i;
            }
        }

}
int gcd(int m,int n){
    int r;
    while(r=m%n){
        m=n;
        n=r;
    }
    return n;
}
int solve2(int a,int b)
{
    a/=b;
            for(int i=2;;i++){
                if(gcd(i,a)==1){
                    return i*b;;
                }
            }
}

int main()
{
    srand(time(0));
    int sum=0;
    for(int i=0;i<10000;++i)
    {
        int a,b;
        b=rand()%32767;
        a=(rand()%32767)*b;
        int n1=solve1(a,b),n2=solve2(a,b);
        if(n1!=n2)
        {
            sum++;
            cout<<"error:"<<n1<<" "<<n2<<endl;
        }
    }
    cout<<"error sum:"<<sum;
}
