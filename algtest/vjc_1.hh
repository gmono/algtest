#include <iostream>
using namespace std;
int arr[1010];
int sum=0;
void swap(int &a,int &b)
{
    int _t=a;
    a=b;
    b=_t;
    sum++;
}

int main()
{
    int n;
    while(cin>>n)
    {
        sum=0;
        for(int i=0;i<n;++i)
        {
            cin>>arr[i];
        }
        for(int i=0;i<n-1;++i)
        {
            for(int j=n-1;j>i;--j)
            {
                if(arr[j-1]>arr[j]) swap(arr[j-1],arr[j]);
            }
        }
        cout<<sum<<endl;
    }
}
