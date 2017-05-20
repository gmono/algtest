#include <iostream>
#include <iomanip>
#include <algorithm>
#include <stack>
#include <cstdio>
#include <vector>
#include <climits>
using namespace std;
namespace walg {
const int base {1000000000};
#define WIDTH 9
typedef unsigned int uint;
void trans(const char *n,vector<uint> &nres)
{
    nres.resize(6300);
    int len=strlen(n);
    int nowpoint=0;
    int nownum=0;
    int nowptr=0;
    //忽略0前缀
    int cstart=0;
    for(int i=0;n[i]=='0';++i) {
        cstart++;
    }
    //这里处理全0
    if(cstart==len)
    {
        nres[0]=0;
        nres.resize(1);
    }

    static uint sbuf[8]={1,10,100,1000,10000,100000,1000000,10000000};
    for(int i=len-1;i>=cstart;--i)
    {
//        if(!isstart&&n[i]=='0') continue;
//        else isstart=true;
        if(nowpoint==8)
        {
            //放入数字
            nres[nowptr++]=nownum;
            nownum=0;
            nowpoint=0;
        }
        //处理
        nownum+=(n[i]-'0')*sbuf[nowpoint];
        nowpoint++;
    }
    //nowptr为当前长度
    if(nownum!=0)
    {
        nres[nowptr++]=nownum;
    }
    nres.resize(nowptr);
//    return now;

}
void mul(string &str1,string &str2)
{
    vector<uint> a, b, c;
    uint x;
    int len_a = (str1.length() - 1) / WIDTH + 1;
    trans(str1.c_str(),a);

    int len_b = (str2.length() - 1) / WIDTH + 1;
    trans(str2.c_str(),b);

    c.resize(len_a + len_b);
    fill(c.begin(), c.end(), 0);
    unsigned long long temp = 0, carry = 0;
    for (int i = 0; i != len_a; ++i)
    {
        carry = 0;
        int j;
        for (j = 0; j != len_b; ++j)
        {
            temp = (unsigned long long)a[i] * b[j] + c[i + j] + carry;       //这里要注意，不用long long会溢出
            carry = temp / base;
            c[i + j] = temp % base;
        }
        while (carry)
        {
            temp = c[i + j] + carry;
            carry = temp / base;
            c[i + j] = temp;
            ++j;
        }
    }
    while (c.size() > 1 && c[c.size() - 1] == 0)
        c.pop_back();

}

}
