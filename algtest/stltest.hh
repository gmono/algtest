#include <iostream>
#include <queue>
#include <deque>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <list>
#include <vector>
#include <sstream>
#include <string>
#include <iomanip>
#include <climits>

//智能提示
using std::__cxx11::basic_ostringstream;
using std::__cxx11::basic_istringstream;
using namespace std;
int *create_pool(int min,int max,int size)
{
    int *ret=new int[size];
    for(int i=0;i<size;++i)
    {
        ret[i]=rand()%(max+1);
        if(ret[i]<min) ret[i]+=min;
    }
    return ret;
}

int main()
{
    ios::sync_with_stdio(false);
    cout.tie(0);
    basic_ostringstream<char> out;

    string line;
    getline(cin,line);
    basic_istringstream<char> in(line);

    int count=100;
    int *arr=create_pool(0,count,count);

    cout<<"raw："<<endl;
    for(int i=0;i<count;++i)
    {
        cout<<arr[i]<<' ';
    }
    cout<<"stringstream:"<<endl;
    for(int i=0;i<count;++i)
    {
        out<<setfill('.')<<setw(8)<<setbase(16)<<arr[i];
    }
    cout<<out.str()<<endl;
    cout<<"priority_queue:"<<endl;
    //priority queue
    //优先队列默认使用less比较器 比较中大的优先 从大到小排列
    priority_queue<int,vector<int>,greater<int>> q;
    //set以及map 默认使用less比较器 遍历时为从小到大 如果是greater比较器则相反
    set<int> p;
    unordered_set<int> us;
    for(int i=0;i<count;++i)
    {
        q.push(arr[i]);
        p.insert(arr[i]);
        us.insert(arr[i]);
    }
    while(!q.empty())
    {
        cout<<setfill('|')<<setw(4)<<q.top();
        q.pop();
    }
    cout<<"set(map):"<<endl;
    for(auto i=p.begin();i!=p.end();++i)
    {
        cout<<*i<<" ";
    }
    cout<<"unordered_set(map):"<<endl;
    for(auto i=us.begin();i!=us.end();++i)
    {
        cout<<*i<<" ";
    }
    cout<<"sort:"<<endl;
    //sort函数同set（map）
    sort(arr,arr+count,greater<int>());
    for(int i=0;i<count;++i)
    {
        cout<<arr[i]<<' ';
    }
    struct mycomp
    {
        bool operator()(const int a,const int b)
        {
            static bool t=false;
            t=!t;
            return t? a>b:a<=b;
        }
    };
    sort(arr,arr+count,mycomp());
    cout<<endl<<"mycomp,sort:"<<endl;
    for(int i=0;i<count;++i)
    {
        cout<<arr[i]<<' ';
    }

}
