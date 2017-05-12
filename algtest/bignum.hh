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

    }
protected:
    vector<basetype> data;
};

int main()
{

}
