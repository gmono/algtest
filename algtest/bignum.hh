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
    BigNum operator +=(const BigNum &num)
    {
        auto itr=data.begin();
        auto nitr=num.data.begin();
        basetype nowsize=0;
        basetype cf=0;
        for(;nitr!=num.data.end();++nitr,++itr)
        {
            if(itr==this->data.end())
            {
                itr--;
                this->data.push_back(0);
                itr++;
            }
            basetype maxnum=*itr>*nitr? *itr:*nitr;
            basetype &res=*itr;
            res+=*nitr+cf;
            if(res<maxnum)
            {
                cf=1;
            }

        }
    }

    BigNum operator +(const BigNum &num)
    {
        BigNum ret=*this;
        ret+=num;
        return ret;
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
    for(int i=0;i<100;++i)
    {
        num+=tn;
    }
    cout<<num.toString(16);
}
