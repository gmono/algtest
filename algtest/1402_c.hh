#include <iostream>
#include <stdio.h>
#include <string.h>
namespace calg {

typedef unsigned int uint;
typedef unsigned long long ulong;
constexpr uint maxnum=1000000000;
uint num1[6300];

uint num2[6300];
int len1;
int len2;
uint result[12600];
int reslen;

void mul()
{
    uint *base;
    int baselen;
    uint *mnum;
    int mlen;
    if(len1<len2)
    {
        base=num1;
        baselen=len1;
        mnum=num2;
        mlen=len2;
    }
    else
    {
        base=num2;
        baselen=len2;
        mnum=num1;
        mlen=len1;
    }
    //执行 以base为基 模拟手算乘 mnum
    memset(result,0,sizeof(uint)*(len1+len2));
    for(int i=0;i<baselen;++i)
    {
        uint key=base[i];
        //以key进行数乘法
        uint cf=0;
        for(int j=0;j<mlen;++j)
        {
            ulong tnum=(ulong)mnum[j]*key+cf;
            cf=tnum/maxnum;
            result[j+i]+=tnum%maxnum;
            //使用if hdu 733ms
            //使用下面的数学计算 hdu 680ms
            //这个1402c的测试速度明明比用c++ vector的快3倍左右
            //hdu竟然差不多速度
            //本人有句妈卖批不知。。。
//            if(result[j+i]>maxnum) {
//                cf++;
//                result[j+i]-=maxnum;
//            }
            cf+=result[j+i]/maxnum;
            result[j+i]-=maxnum*(result[j+i]/maxnum);
        }
        if(cf)
        {
            //i+mlen 最高为baselen + mlen-1
            result[i+mlen]=cf;
        }
    }
    reslen=len1+len2;
    if(result[reslen-1]==0)
    {
        reslen--;
    }
}
/**
 * @brief trans 转换为数字序列
 * @param n 字符串
 * @param nres 数字序列变量
 * @return 数字序列长度
 */
int trans(char *n,uint *nres)
{
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
        return 1;
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
    return nowptr;
//    return now;

}
void print()
{
    int end=reslen-1;
    while(result[end]==0&&end>=0) end--;
    if(end==-1)
    {
        printf("0\n");
        return;
    }
    printf("%u",result[end]);
    for(int i=end-1;i>=0;--i)
    {
        printf("%09u",result[i]);
    }
    printf("\n");
}

}
using namespace calg;
using namespace std;
int main()
{
    ios::sync_with_stdio(false);
    static char buf1[51000];
    static char buf2[51000];
    while(cin>>buf1>>buf2)
    {
        len1=trans(buf1,num1);
        len2=trans(buf2,num2);
        mul();
        print();
    }
}


