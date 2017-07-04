#include <iostream>
#include <map>
using namespace std;

int main()
{
    int n;
    while((cin>>n,n))
    {
        map<string,int> bmap;
        for(int i=0;i<n;++i)
        {
            string color;
            cin>>color;
            auto ptr=bmap.find(color);
            if(ptr==bmap.end()) bmap.insert(pair<string,int>(color,1));
            else
            {
                ptr->second++;
            }
        }
        string maxname;
        int maxsum=0;
        for(auto itr=bmap.begin();itr!=bmap.end();++itr)
        {
            if(itr->second>maxsum)
            {
                maxsum=itr->second;
                maxname=itr->first;
            }
        }
        cout<<maxname<<endl;
    }
}
