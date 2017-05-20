#include <iostream>
#include <iomanip>
#include <algorithm>
#include <stack>
#include <cstdio>
#include <vector>
#include <climits>
#include <string.h>
#include <sstream>
using namespace std;

#define WIDTH 9
typedef unsigned int uint;
typedef unsigned long long ulong;
const uint nbase {1000000000};
void trans(const char *n,int len,uint *nres)
{
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
        return;
    }

    static uint sbuf[9]={1,10,100,1000,10000,100000,1000000,10000000,100000000};
    for(int i=len-1;i>=cstart;--i)
    {
//        if(!isstart&&n[i]=='0') continue;
//        else isstart=true;
        if(nowpoint==9)
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
//    return now;

}
int main(void)
{
    ios::sync_with_stdio(false);
    string str;
    static uint a[5600];
    static uint b[5600];
    static uint c[11200];

    while (cin >> str)
    {
        int len_a = (str.length() - 1) / WIDTH + 1;
        trans(str.c_str(),str.length(),a);
        cin>>str;
        int len_b = (str.length() - 1) / WIDTH + 1;
        trans(str.c_str(),str.length(),b);
        int len=len_a+len_b;
        //选择
        uint *base,*num;
        size_t blen,nlen;
        if(len_a<len_b)
        {
            base=a;
            num=b;
            blen=len_a;
            nlen=len_b;
        }
        else
        {
            base=b;
            num=a;
            blen=len_b;
            nlen=len_a;
        }

        memset(c,0,sizeof(uint)*len);
        ulong carry = 0;
        for (int i = 0; i != blen; ++i)
        {
            carry = 0;
            int j;
            for (j = 0; j != nlen; ++j)
            {
                ulong temp = (ulong)base[i] * num[j] + c[i + j] + carry;       //这里要注意，不用long long会溢出
                carry = temp / nbase;
                c[i + j] = temp % nbase;
            }
            if(carry)
            {
                c[i+j]+=carry;
            }
        }
        while(len>1&&!c[len-1]) len--;
        cout << c[--len];
        while (len>0)
            cout << setw(WIDTH) << setfill('0') << c[--len];
        cout << endl;
    }


}
