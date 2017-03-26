#ifndef T_1234_HH
#define T_1234_HH
#include <iostream>
#include <queue>
using namespace std;
class Time
{
public:
    Time(int h,int m,int s,const string &name):hour(h),min(m),sec(s),pname(name){}

    friend bool operator <(const Time &a,const Time &b);
    int hour=0;
    int min=0;
    int sec=0;
    string pname;
};
class RTime:public Time
{
public:
    RTime(int h,int m,int s,const string &name):Time(h,m,s,name){}
    friend bool operator <(const RTime &a,const RTime &b);

};

bool operator <(const Time &a,const Time &b)
{
    int tarr[3]={a.hour,a.min,a.sec};
    int tarr_d[3]={b.hour,b.min,b.sec};
    for(int i=0;i<3;++i)
    {
        if(tarr[i]<tarr_d[i]) return true;
        else if(tarr[i]>tarr_d[i]) return false;

    }
    return false;//等于
}
bool operator <(const RTime &a,const RTime &b)
{
    int tarr[3]={a.hour,a.min,a.sec};
    int tarr_d[3]={b.hour,b.min,b.sec};
    for(int i=0;i<3;++i)
    {
        if(tarr[i]<tarr_d[i]) return false;
        else if(tarr[i]>tarr_d[i]) return false;

    }
    return true;//等于
}

int main()
{
    int sum;
    cin>>sum;//天数
    for(int i=0;i<sum;++i)
    {
        //处理每天
        int psum;
        cin>>psum;

        std::priority_queue<Time> tque;
        std::priority_queue<RTime> rtque;
        //处理每人
        for(int j=0;j<psum;++j)
        {
            string pep;
            cin>>pep;//输入人名
            int h,m,s;
            cin>>h>>m>>s;
            Time t(h,m,s,pep);
            cin>>h>>m>>s;
            RTime t2(h,m,s,pep);
            //优先队列处理
            tque.push(t);
            rtque.push(t2);
        }
        const Time &open=tque.top();
        const RTime &end=rtque.top();
        cout<<open.pname<<" "<<end.pname<<endl;
    }
}

#endif // T_1234_HH
