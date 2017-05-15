#include <iostream>
#include <vector>
#include <string>
#include "MyTimer_win.h"
using namespace std;
typedef unsigned long long basetype;
constexpr basetype MaxDec=10000000000000000000;
/**
 * @brief 打印用大数
 * 内部以10的乘方进制保存数字
 */
class PrintNum
{
public:

    PrintNum(const vector<basetype> &num)
    {
        basetype cf=0;
        for(auto itr=num.begin();itr!=num.end();++itr)
        {
            basetype t=*itr;
            basetype tcf=cf;
            if(t>=MaxDec)
            {
                //怕溢出 先进位再加上
                t-=MaxDec;
                cf=1;
                t+=tcf;
                this->pnum.push_back(t);
            }
            else
            {
                //上面没有执行即 原数小于MaxDEC
                t+=tcf;
                //上面和这里只能同时执行一个
                if(t>=MaxDec)
                {
                    t-=MaxDec;
                    cf=1;
                }
                else
                {
                    cf=0;
                }
                //放入
                this->pnum.push_back(t);
            }

        }
        if(cf)
        {
            this->pnum.push_back(1);
        }
    }

    void print()
    {
        for(auto itr=this->pnum.rbegin();itr!=this->pnum.rend();++itr)
        {
            printf("%llu",*itr);
        }
    }

    operator string()
    {
        string ret;
        char buf[50];
        for(auto itr=this->pnum.rbegin();itr!=this->pnum.rend();++itr)
        {
            sprintf(buf,"%llu",*itr);
            ret+=string(buf);
        }
        return ret;
    }

protected:
    vector<basetype> pnum;
};

//low to high
class BigNum
{
public:


    BigNum(basetype num)
    {
        this->data.push_back(num);
    }
    BigNum(const string &str)
    {

    }
    //calculate
//    BigNum operator +=(const BigNum &num)
//    {
//        auto itr=data.begin();
//        auto nitr=num.data.begin();
//        basetype nowsize=0;
//        basetype cf=0;
//        for(;nitr!=num.data.end();++nitr,++itr)
//        {
//            if(itr==this->data.end())
//            {
//                itr--;
//                this->data.push_back(0);
//                itr++;
//            }
//            basetype maxnum=*itr>*nitr? *itr:*nitr;
//            basetype &res=*itr;
//            res+=*nitr+cf;
//            if(res<maxnum)
//            {
//                cf=1;
//            }

//        }
//        if(cf)
//        {
//            this->data.push_back(cf);
//        }

//    }
    void operator +=(const BigNum &num)
    {
        basetype cf=0;

        for(int i=0;i<num.data.size();++i)
        {
            if(i>=this->data.size()) this->data.push_back(0);
            basetype maxnum=this->data[i]>num.data[i]? this->data[i]:num.data[i];
            this->data[i]+=cf+num.data[i];
            if(this->data[i]<maxnum) cf=1;
        }
        for(int i=num.data.size();cf!=0;++i)
        {
            if(i>=this->data.size())
            {
                this->data.push_back(cf);
                cf=0;
                continue;
            }
            basetype t=this->data[i];
            this->data[i]+=cf;
            cf=this->data[i]<t? 1:0;
        }
    }
    //针对直接加数的快速优化
    void operator +=(const basetype num)
    {
        basetype t=this->data[0];
        this->data[0]+=num;
        int now=1;
        int cf=0;
        if(this->data[0]<t) cf=1;
        while(cf)
        {
            if(now>=this->data.size()) this->data.push_back(0);
            t=this->data[now];
            this->data[now]+=cf;
            if(this->data[now]<t) cf=1;
            else cf=0;
        }
    }

    template<class T>
    BigNum operator +(const T &num)
    {
        BigNum ret=*this;
        ret+=num;
        return ret;
    }

    //位运算
    void operator <<=(const basetype n)
    {
        if(n==0) return;
        constexpr int m=sizeof(basetype)*8;
        int l=n/(m+1);
        int s=n%(m+1);
        int base=this->data.size();
        int i=base+l;
        if(i>=this->data.size()) this->data.resize(i+1);
        while (i>=0)
        {
            basetype t1=base<0? 0:this->data[base]<<s;
            basetype t2=base-1<0? 0:this->data[base-1]>>(m-s);
            this->data[i]=t1|t2;
            i--;
            base--;
        }
    }

    //translation

    string toString(int base)
    {
        string ret;
        for(auto itr=data.rbegin();itr!=data.rend();++itr)
        {
            vector<char> temp;
            for(basetype i=*itr;i>0;i/=base)
            {
                int tnum=i%base;
                char tc=tnum>9? 'A'+tnum-10:'0'+tnum;
                temp.push_back(tc);
            }
            for(auto titr=temp.rbegin();titr!=temp.rend();++titr)
            {
                ret.push_back(*titr);
            }
        }
        return ret;
    }

    operator PrintNum()
    {
        return PrintNum(this->data);
    }

protected:
    vector<basetype> data;
};

int main()
{
    unsigned long long tn=~((long long)0);
    MyTimer timer;
    BigNum num=0;
    timer.start();
    for(int i=0;i<1000;++i)
    {
        num+=tn;
    }
    timer.stop();
    cout<<"Time is:"<<timer.ticks()<<endl;

//    num<<=10;
    cout<<tn<<endl;
    cout<<MaxDec<<endl;
    cout<<num.toString(10)<<endl;
    cout<<((string)(PrintNum)num)<<endl;
    ((PrintNum)num).print();

}
