
#include <iostream>
#include "MyTimer_win.h"
MyTimer timer;
#define start timer.start()
#define ok(tip) {timer.stop();cout<<tip<<"the time is:"<<timer.ticks()<<endl;}
#include <string>
using namespace std;
void create(string &str,int maxn)
{
    str.clear();
    int len=rand()%maxn+1;
    for(int i=0;i<len;++i)
    {
        str.push_back('0'+rand()%10);
    }
}
#include <string.h>
#include "1402.hh"
#include "1402_new.hh"
#include "1402_c.hh"
#include "1402_w.hh"
void cmp(vector<uint> &res,uint *buf,int len)
{
    //比较1402和1402c 的结果
    if(len!=res.size())
    {
        cout<<"error length"<<endl;
    }
    for(int i=0;i<len;++i)
    {
        if(buf[i]!=res[i])
        {
            printf("error beteen test:%u true:%u at %d\n",buf[i],res[i],i);
            break;
        }
        if(i==len-1)
        {
            printf("test is ok\n");
        }
    }
    getchar();
}

int main()
{
    srand(time(0));
    constexpr int testcount=10;
    constexpr int maxn=50000;
    char *num1=new char[maxn+1000];
    char *num2=new char[maxn+1000];
    char *result=new char[maxn*2+1000];
    string n1,n2;
    for(int i=0;i<testcount;++i)
    {
        create(n1,maxn);
        create(n2,maxn);
        strcpy(num1,n1.c_str());
        strcpy(num2,n2.c_str());
        //为了公平
        start;
        vector<uint> nc;
        vector<uint> nc2;
        oldalg::trans(n1,nc);
        oldalg::trans(n2,nc2);
        vector<uint> res=oldalg::mul(nc,nc2);
//        print(res);
//        putchar('\n');
        ok("oldalg's ");
//        getchar();

        start;
        calg::len1=calg::trans(num1,calg::num1);
        calg::len2=calg::trans(num2,calg::num2);
        calg::mul();
        ok("calg's ");

//        cmp(nc,calg::num1,calg::len1);
//        cmp(nc2,calg::num2,calg::len2);
//        cmp(res,calg::result,calg::reslen);

        start;
        walg::mul(n1,n2);
        ok("w's ");

//        start;
//        int len1=newalg::trans(num1);
//        int len2=newalg::trans(num2);
//        memset(result,0,len1+len2);
//        int rlen=newalg::mul(result,num1,len1,num2,len2);
////        newalg::directPrint(result,rlen);
//        //newalg::backTrans(result,rlen);
//        //printf("%s",result);
//        putchar('\n');
//        ok("newalg's ");

        putchar('\n');
//        getchar();
    }
}
