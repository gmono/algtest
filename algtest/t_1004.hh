#ifndef T_1004_HH
#define T_1004_HH
#include <iostream>
#include <map>
#include <string>
#include <list>
using namespace std;
int main()
{
    int sum;
    list<string> lst;
    while(cin>>sum)
    {
        if(sum==0) break;
        map<string,int> counter;
        for(int i=0;i<sum;++i)
        {
            string str;
            cin>>str;
            auto ptr=counter.find(str);
            if(ptr==counter.end())
                counter.insert(pair<string,int>(str,1));
            else
            {
                ptr->second=ptr->second+1;
            }
        }
        auto now=counter.begin();//iterator
        for(auto i=counter.begin();i!=counter.end();++i)
        {
            if(i->second>now->second) now=i;
        }
        string turestr=now->first;
        lst.push_back(turestr);
    }
    for(auto i=lst.begin();i!=lst.end();++i)
    {
        cout<<*i<<endl;
    }
}

#endif
