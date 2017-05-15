#include <iostream>
#include <vector>
#include <string>
#include "MyTimer_win.h"
using namespace std;
typedef unsigned long long basetype;
constexpr basetype MaxDec=10000000000000000000;
template<class Fwd>
struct Reverser {
 const Fwd &fwd;
 Reverser<Fwd>(const Fwd &fwd_): fwd(fwd_) {}
 auto begin() -> decltype(fwd.rbegin()) const { return fwd.rbegin(); }
 auto end() -> decltype(fwd.rend()) const { return fwd.rend(); }
};

template<class Fwd>
Reverser<Fwd> reverse(const Fwd &fwd) { return Reverser<Fwd>(fwd); }
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
            else cf=0;
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
    //32位模拟数乘
    BigNum operator *(const unsigned int num)
    {
        BigNum ret=0;
        int now=0;
        BigNum temp=0;
        for(auto itr=this->data.rbegin();itr!=this->data.rend();++itr,++now)
        {
            basetype t=*itr;
            unsigned int &low=*(unsigned int *)&t;
            unsigned int &high=*((unsigned int *)&t+1);
            temp=0;
            temp+=(basetype)high*num;
            temp<<=32;
            temp+=(basetype)low*num;
            temp<<=now*sizeof(basetype)*8;
            ret+=temp;

        }
        return ret;
    }
    //64位模拟数乘
    BigNum operator *(const basetype num)
    {
        BigNum low=*this**(unsigned int *)&num;
        BigNum high=*this**((unsigned int *)&num+1);
        high<<=sizeof(unsigned int)*8;
        return low+high;
    }
    //BigNum模拟乘法
    BigNum operator *(const BigNum &num)
    {
        BigNum ret=0;
        int now=0;
        for(auto itr=num.data.rbegin();itr!=num.data.rend();++itr,now++)
        {
            ret+=*this**itr;
            ret<<=sizeof(basetype)*8*now;
        }
        return ret;
    }
    //
    void operator *=(const BigNum &num)
    {
        *this=*this*num;
    }

    //64位移位数乘
    void MoveMulOf(const BigNum &num)
    {
        BigNum tnum=*this;
        *this=0;
        //间隔位标识 标识当前以多少位为基础
        int mid=0;
        //记录上一个位的位置
        int old=0;
        for(auto itr=num.data.rbegin();itr!=num.data.rend();++itr,mid+=sizeof(basetype)*8)
        {
            basetype t=*itr;
            //逐级定位
            if(!t) continue;
            for(int i=0;i<sizeof(basetype)*8;++i)
            {
                basetype mask=(basetype)1<<i;
                if(t&mask)
                {
                    int point=mid+i;
                    int lp=point-old;
                    tnum<<=lp;
                    old=point;
                    //叠加
                    *this+=tnum;
                }
            }
        }
    }
    BigNum MoveMul(const BigNum &num)
    {
        BigNum ret=*this;
        ret.MoveMulOf(num);
        return ret;
    }

    //叠加运算
    void operator *=(const basetype num)
    {
        unsigned int t=*((unsigned int *)&num+1);
        if(t)
            *this=*this*num;
        else
            *this=*this*(unsigned int)num;
    }


    template<class T>
    BigNum operator +(const T &num)
    {
        BigNum ret=*this;
        ret+=num;
        return ret;
    }
//
    void operator =(unsigned long long num)
    {
        this->data.clear();
        this->data.push_back(num);
    }

    //位运算
    void operator <<=(const basetype n)
    {
        if(n==0||(data.size()==1&&data[0]==0)) return;
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
        //去0
        for(auto i:reverse(this->data))
        {
            if(i==0) this->data.pop_back();
            else break;
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

template<class T>
class Range
{
public:
    class iterator
    {
    public:
        T s;
        T e;
        T now;
        iterator(T start,T end):s(start),e(end),now(start)
        {

        }
        void toend()
        {
            now=e+1;
        }

        Range<T>::iterator operator++()
        {
            if(this->now==e+1) return *this;
            this->now++;
            return *this;
        }

        bool operator ==(Range<T>::iterator &n)
        {
            if(n.e==e&&n.s==s&&n.now==now) return true;
            return false;
        }
        bool operator !=(Range<T>::iterator &n)
        {
            return !(n==*this);
        }

        T operator *()
        {
            return now;
        }
    };

    T start;
    T send;

    Range(T s,T e):start(s),send(e)
    {

    }

    auto begin()->iterator const{
        return  iterator(this->start,this->send);
    }
    auto end()->iterator const{
        iterator t(start,send);
        t.toend();
        return t;
    }
};
template<class T>
Range<T> range(T start,T end)
{
    Range<T> t(start,end);
    return t;
}

constexpr int testcount=10;
int main()
{
    unsigned long long tn=~((long long)0);
    MyTimer timer;
    BigNum num=0;
    timer.start();
    for(int i=0;i<10000;++i)
    {
        num+=tn;
    }
    timer.stop();
    cout<<"number addition 10000 times is:"<<timer.ticks()<<endl;
    cout<<"number:"<<num.toString(16)<<endl;\


    BigNum num2=0;
    timer.start();
    for(int i=0;i<10000;++i)
    {
        num2+=(BigNum)tn;
    }
    timer.stop();
    cout<<"BigNum addition 10000 times  is:"<<timer.ticks()<<endl;
    cout<<"number:"<<num2.toString(16)<<endl;

    num=tn;
    timer.start();
    for(auto i:range(1,testcount))
    {
        num*=0x10;
    }
    timer.stop();
    cout<<"uint mul time is:"<<timer.ticks()<<endl;
    cout<<"number:"<<num.toString(16)<<endl;


    num=tn;
    timer.start();
    for(auto i:range(1,testcount))
    {
        num*=(basetype)0x10;
    }
    timer.stop();
    cout<<"ulonglong mul time is:"<<timer.ticks()<<endl;
    cout<<"number:"<<num.toString(16)<<endl;

    num=tn;
    timer.start();
    for(auto i:range(1,testcount))
    {
        num*=(BigNum)0x10;
    }
    timer.stop();
    cout<<"BigNum mul time is:"<<timer.ticks()<<endl;
    cout<<"number:"<<num.toString(16)<<endl;

    num=tn;
    timer.start();
    for(auto i:range(1,testcount))
    {
        num=num.MoveMul((BigNum)0x10);
    }
    timer.stop();
    cout<<"BigNum movemul time is:"<<timer.ticks()<<endl;
    cout<<"number:"<<num.toString(16)<<endl;
}
