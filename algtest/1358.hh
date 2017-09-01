#include <iostream>
using namespace std;
#define maxn 1000000+10
char array[maxn];
int nextarr[maxn];
int N;
void makenext()
{
    nextarr[0]=nextarr[1]=0;
    int j=0;
    for(int i=1;i<N;)
    {
        if(array[i]==array[j])
        {
            nextarr[i+1]=j+1;
            j++;
            i++;
        }
        else if(j==0) nextarr[++i]=0;
        else j=nextarr[j];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    int p=1;
    while(cin>>n,n)
    {
        cin>>array;
        N=n;
        makenext();
        cout<<"Test case #"<<p<<endl;
        for(int i=2;i<=N;++i)
        {
            if(i%(i-nextarr[i])==0&&i/(i-nextarr[i])>1)
            {
                cout<<i<<" "<<i/(i-nextarr[i])<<endl;
            }
        }
        cout<<endl;
        p++;
    }
}
