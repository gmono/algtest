

#include <iostream>
#include <vector>
#include <math.h>
using namespace std;
namespace oldalg {
typedef unsigned int uint;
typedef unsigned long long ulong;
#define MaxDec 100000000
#define MaxByte 8
void trans(const string &s,vector<uint> &n)
{
    int nowstep=0;
    uint buf=0;
    for(auto itr=s.rbegin();itr!=s.rend();++itr)
    {
        if(nowstep==MaxByte)
        {
            //放入
            n.push_back(buf);
            buf=0;
            //
            nowstep=0;
        }
        uint t=(*itr-'0')*pow(10,nowstep);
        buf+=t;
        nowstep++;
    }
    if(nowstep)
    {
        n.push_back(buf);
    }

}
void add(vector<uint> &result,const vector<uint> &n,int base)
{
    if(result.size()<base) result.resize(base);
    size_t maxlen=result.size()-base>n.size()? result.size()-base:n.size();
    int cf=0;

    for(int i=0;i<maxlen;i++)
    {
        int p=i+base;
        if(p>=result.size()) result.push_back(0);
        uint anum;
        if(i>=n.size()) anum=0;
        else anum=n[i];
        result[p]+=anum+cf;
        cf=result[p]>=MaxDec? 1:0;
        result[p]=result[p]>=MaxDec? result[p]-MaxDec:result[p];
    }
    if(cf)
    {
        result.push_back(1);
    }
}
//标准数乘法
void nmul(vector<uint> &res,uint n)
{
    uint cf=0;
    for(int i=0;i<res.size();++i)
    {
        ulong temp=res[i];
        temp*=n;
        temp+=cf;
        cf=temp/MaxDec;
        res[i]=temp%MaxDec;
    }
    if(cf)
    {
        res.push_back(cf);
    }
}
////优化数乘法
//vector<uint> &smul(const vector<uint> &bn,uint n)
//{
//    static vector<uint> pool[10];
//    static vector<uint> obn;
//    bool isequal=true;
//    if(bn.size()!=obn.size()) isequal=false;
//    else for(int i=0;i<bn.size();++i)
//    {
//        if(bn[i]!=obn[i])
//        {
//            isequal=false;
//            break;
//        }
//    }
//    if(!isequal)
//    {
//        //重新生成pool
//        pool[0].clear();
//        pool[0].push_back(0);
//        for(int i=1;i<10;++i)
//        {
//            vector<uint> tv=bn;
//            nmul(tv,i);
//            pool[i]=tv;
//        }
//    }
//    //
//    return pool[n];
//}

vector<uint> mul(const vector<uint> &n1,const vector<uint> &n2)
{
    vector<uint> ret;
    const vector<uint> &base=n1.size()<n2.size()? n1:n2;
    const vector<uint> &num=n1.size()<n2.size()? n2:n1;
    for(int i=0;i<base.size();++i)
    {
        uint t=base[i];
        vector<uint> tres=num;
        nmul(tres,t);
        add(ret,tres,i);
    }
    //clear
    for(auto itr=ret.rbegin();itr!=ret.rend();++itr)
    {
        if(!*itr) ret.pop_back();
        else break;
    }
    return ret;
}


void print(const vector<uint> &n)
{
    if(n.size()==0)
    {
        printf("0");
        return;
    }
    char strbuf[]="00000000";
    bool isone=true;
    for(auto itr=n.rbegin();itr!=n.rend();itr++)
    {
        uint tn=*itr;
        if(isone)
        {
            isone=false;
            printf("%u",tn);
        }
        else
        {
            for(int i=0;i<8;++i)
            {
                strbuf[7-i]=tn%10+'0';
                tn/=10;
            }
            printf("%s",strbuf);
        }

    }
}

}
using namespace oldalg;
//int main()
//{
//    string n1,n2;
//    while(cin>>n1>>n2)
//    {
//        vector<uint> nc;
//        vector<uint> nc2;
//        trans(n1,nc);
//        trans(n2,nc2);
//        vector<uint> res=mul(nc,nc2);
//        print(res);
//        putchar('\n');
//    }
//    return 0;
//}
