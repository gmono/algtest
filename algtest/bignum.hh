#include <iostream>
#include <vector>
#include <string>

using namespace std;

//low to high
class BigNum
{
public:
    typedef unsigned long long basetype;

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
        basetype t=n%sizeof(basetype);
        basetype s=n/sizeof(basetype);
        for(int i=data.size()-1,base=data.size()-1-s;base>=0;)
        {

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

protected:
    vector<basetype> data;
};

int main()
{
    unsigned long long tn=~((long long)0);
    BigNum num=0;
    for(int i=0;i<10000000;++i)
    {
        num+=tn;
    }
    cout<<num.toString(16);
}
