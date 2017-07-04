#include <iostream>
#include <unordered_map>
using namespace std;
#define tmap unordered_map
int farr[60];
int f(int index,int A,int B)
{
    if(index==1||index==2) return 1;
   if(farr[index]!=-1) return farr[index];
   farr[index]=(A*f(index-1,A,B)+B*f(index-2,A,B))%7;
   return farr[index];
}
void init()
{
    std::fill(farr,farr+60,-1);
}
#define getsign(a,b) ((a<<16)+b)
int main()
{
    int A,B,n;
    for(;;)
    {
        cin>>A>>B>>n;
        if(A==0&&B==0&&n==0) break;
        init();
        int pn=-1;
        tmap<int,int> cmap;
        cmap.insert(pair<int,int>(getsign(1,1),2));
        for(int i=3;i<=n;++i)
        {
            int sign=getsign(f(i-1,A,B),f(i,A,B));
            auto ptr=cmap.find(sign);
            if(ptr!=cmap.end())
            {
                int start=ptr->second-1;
                int end=i-2;
                pn=start+(n-start)%(end-start+1);
                break;
            }
            else
            {
                cmap.insert(pair<int,int>(sign,i));
            }
        }
        if(pn==-1) pn=n;
        int result=f(pn,A,B);
        cout<<result<<endl;
    }
}
