#include <iostream>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cout.tie(0);
    string str;
    while(cin>>str)
    {
        char maxc=~(0);
        for(auto c:str)
        {
            if(c>maxc) maxc=c;
        }
        bool *maxarr=new bool[str.length()];
        int i=0;
        for(auto c:str)
        {
            if(c==maxc)
                maxarr[i]=true;
            else maxarr[i]=false;
            i++;
        }
        for(int i=0;i<str.length();++i)
        {
            cout<<str[i];
            if(maxarr[i]) cout<<"(max)";
        }
        cout<<endl;
    }
}
