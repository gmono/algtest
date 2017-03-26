#ifndef T_1022_HH
#define T_1022_HH
#include <iostream>
#include <queue>
#include <string>
#include <stack>
#include <queue>
#include <list>
using namespace std;

int main(int argc, char *argv[])
{
    freopen("test.txt","r+",stdin);

    list<string> srcs;
    list<string> dess;
    int sum;
    while(cin>>sum)
    {
        string src;
        string des;
        getchar();
        for(int i=0;i<sum;++i)
        {
            src.push_back(getchar());
        }
        getchar();
        for(int i=0;i<sum;++i)
        {
            des.push_back(getchar());
        }
        srcs.push_back(src);
        dess.push_back(des);
    }
    for(auto ti=srcs.begin(),tdi=dess.begin();ti!=srcs.end();++ti,++tdi)
    {
        string src=*ti;
        string des=*tdi;
        stack<char> teststack;//栈
        queue<string> operalist;
        auto di=des.begin();
        auto i=src.begin();
        for(;i!=src.end()||!teststack.empty();)
        {
            //栈操作
            char tc=*i;
            char dc=*di;
            if(!teststack.empty()&&teststack.top()==dc)
            {
                teststack.pop();
                di++;
                //操作记录
                operalist.push("out");
                //找到字符出栈一个
            }
            else if(i==src.end())
            {
                //不等于 且没有更多字符可以放入则失败 跳出
                break;
            }
            else
            {
                teststack.push(tc);
                operalist.push("in");
                i++;
            }

        }
        //完成
        if(di!=des.end())
        {
            cout<<"No."<<endl;
            cout<<"FINISH"<<endl;
        }
        else
        {
            cout<<"Yes."<<endl;
            while(!operalist.empty())
            {
                //
                cout<<operalist.front()<<endl;
                operalist.pop();;
            }
            cout<<"FINISH"<<endl;

        }
    }

    getchar();
    return 0;
}

#endif // T_1022_HH
