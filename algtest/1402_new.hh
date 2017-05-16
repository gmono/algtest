
#include <stdio.h>
#include <memory.h>
/**
 * @brief trans 转换字符串为十进制数列
 * @param str 字符串
 * @return 数列长度
 */
int trans(char *str)
{
#define SWAP(a,b) {auto _t=a;a=b;b=_t;}
    int len;
    int i;
    for(i=0;str[i]=='0';++i);
    if(str[i]==0)
    {
        str[0]=0;
        return 1;
    }
    //搜到了第一个不为0的字符 处理
    int j;
    for(j=0;str[i+j]!=0;++j)
    {
        str[j]=str[i+j]-'0';
    }
    len=j;
    //以上转换加复制
    //下面反转
    //反转为从低到高位存储
    for(int k=0;k<len/2;++k)
    {
        SWAP(str[k],str[len-1-k]);
    }
    //这里是全都是0的情况
    return len;
}
/**
 * @brief backTrans 回转为一个可直接输出的字符串
 * @param list 十进制序列
 * @param len 序列长度
 */
void backTrans(char *list,int len)
{
//    if(!list[len-1]) len--;
    for(int i=0;i<len/2;++i)
    {
        list[i]+='0';
        list[len-1-i]+='0';

        SWAP(list[i],list[len-1-i]);
    }
    list[len]=0;
}
void directPrint(char *list,int len)
{
//    if(!list[len-1]) len--;
    for(int i=len-1;i>=0;--i)
    {
        putchar(list[i]+'0');
    }
}

void add(char *result,const char *num,int numlen)
{
    int cf=0;
    for(int i=0;i<numlen;++i)
    {
        result[i]+=cf+num[i];
        if(result[i]>=10) {
            cf=1;
            result[i]-=10;
        }
        else cf=0;
    }
    if(cf)
    {
        result[numlen]+=1;
    }

}
/**
 * @brief nmul 自乘
 * @param num OPS and OPD
 * @param len num长度
 * @param n 要乘的数
 * @result 新序列的长度
 */
int nmul(char *num,int len,char n)
{
    if(!n)
    {
        num[0]=0;
        return 1;
    }
    char cf=0;
    for(int i=0;i<len;++i)
    {
        //边界假设 10*10+10=110<255
        num[i]=num[i]*n+cf;
        cf=num[i]/10;
        num[i]=num[i]%10;

    }
    if(cf)
    {
        num[len]=cf;
        return len+1;
    }
    return len;
}
/**
 * @brief smul 优化数乘法
 * @param num 要乘的数
 * @param len 数的长度
 * @param n 因子
 * @param nlen 新序列长度（out）
 * @param isusep 是否使用优化模式（池模式)
 * @return 新序列指针 (不可释放)
 */
const char *smul(char *num,int len,char n,int &nlen,bool isusep)
{
    if(!isusep)
    {
        //不使用池 直接返回
        static char temp[51000];
        if(n==0)
        {
            temp[0]=0;
            nlen=1;
        }
        else
        {
            memcpy(temp,num,len);
            nlen=nmul(temp,len,n);
        }
        return temp;
    }
    static char pool[10][51000]={0};
    static int plens[10]={0};
    static char recn[51000];
    static char reclen=0;
    bool isrecreate=false;
    if(len!=reclen) isrecreate=true;
    else for(int i=0;i<len;++i)
    {
        if(num[i]!=recn[i])
        {
            isrecreate=true;
            break;
        }
    }
    if(isrecreate)
    {
        //重新生成池
        for(int i=1;i<10;++i)
        {
            memcpy(pool[i],num,len);
            plens[i]=nmul(pool[i],len,i);
        }
        //记录
        memcpy(recn,num,len);
        reclen=len;
    }
    //返回池记录
    nlen=plens[n];
    return pool[n];
}
/**
 * @brief mul 乘法
 * @param result 保存结果的序列 要求全部为0
 * @param num1 因子1
 * @param len1 因子1长度
 * @param num2 因子2
 * @param len2 因子2长度
 * @result 返回序列长度
 */
int mul(char *result,char *num1,int len1,char *num2,int len2)
{

    char *base,*num;
    int baselen,nlen;
    if(len1<len2)
    {
        baselen=len1;
        nlen=len2;
        base=num1;
        num=num2;
    }
    else
    {
        baselen=len2;
        nlen=len1;
        base=num2;
        num=num1;
    }
    //为了加速 这里特殊处理base为0的情况
    if(baselen==1&&base[0]==0)
    {
        result[0]=0;
        return 1;
    }
    //如果不大于等于10 就不用池
    bool isusep=baselen>=10;
    //计算
    for(int i=0;i<baselen;++i)
    {
        char b=base[i];
        //以b为因子进行数乘结果向高位移i个十进制位后叠加
        int mlen;
        const char *buf=smul(num,nlen,b,mlen,true);
        add(result+i,buf,mlen);
    }
    if(result[len1+len2-1]==0) return len1+len2-1;
    return len1+len2;
}

int main()
{
    static char num1[51000];
    static char num2[51000];
    static char result[101000];
    while(scanf("%s %s",num1,num2)!=EOF)
    {
        int len1=trans(num1);
        int len2=trans(num2);
        memset(result,0,len1+len2);
        int rlen=mul(result,num1,len1,num2,len2);
        directPrint(result,rlen);
        putchar('\n');
    }
}

