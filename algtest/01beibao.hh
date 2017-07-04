#include <iostream>
using namespace std;

//value array
//wight array
//array length
//sum of wight limit
int *Knapsack(int *v,int *w,int len,int C)
{
    int n=len;
    int *m=new int[(n+1)*(C+1)];
    for(int j=0;j<=C;++j)
    {
        m[j]=0;

    }
    for(int i=1;i<=n;++i)
    {
        m[i*(C+1)]=0;
        for(int j=1;j<=C;++j)
        {
            m[i*(C+1)+j]=m[(i-1)*(C+1)+j];
            if(w[i]<=j)
            {
                if(v[i]+m[(i-1)*(C+1)+j-w[i]]>m[(i-1)*(C+1)+j])
                {
                    m[i*(C+1)+j]=m[(i-1)*(C+1)+j-w[i]]+v[i];
                }
            }
        }

    }
    return m;
}
int *build_solution(int *m,int *w,int n,int C)
{
    int j=C;
    int *x=new int[n];
    for(int i=n;i>=1;--i)
    {
        if(m[i*(C+1)+j]==m[(i-1)*(C+1)+j])
        {
            x[i]=0;
        }
        else
        {
            x[i]=1;
            j=j-w[i];
        }
    }
    return x;
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
        Knapsack(values,)
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
