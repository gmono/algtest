#pragma once
//公用测试库
//随机数生成器
#include <random>
//#include "MyTimer_win.h"
#include "MyTimer_linux.h"
#include <time.h>
template<typename ValType>
bool DefaultJfun(ValType v)
{
	return true;
}
template<typename ValType>
bool DefaultPJfun(ValType *p,int count)
{
	return true;
}
//jfun为有效性判断函数 判断生成的随机数是否可用
//bool jfun(valtype v); 返回true代表正确

template<typename ValType>
ValType CreateRandnum(ValType start,ValType end,void *jfun=(void *)&DefaultJfun<ValType>)
{
	typedef bool(*JFunType)(ValType);
	JFunType jfunc = (JFunType)jfun;
	std::random_device rd;
	cr_start:
	unsigned long long rawnum1 = (long long)rd()%(end-start+1);//分母
	unsigned long long rawnum2 = (long long)rd()%(long long)pow(end-start+1,2);//分子
	double ret = (double)rawnum2 / (double)rawnum1  + start;
	ValType val= static_cast<ValType>(ret);

		if (!jfunc(val)) goto cr_start;
		return val;
}
//pjfun为池判断函数 判断一个随机数的集合是否有效 执行一次
//bool pjfun(valtype *pool,int size);//返回true代表有效
//无效继续生成
template<typename ValType>
ValType *CreateRandPool(int size, ValType start, ValType end,void *jfun=(void *)&DefaultJfun<ValType>,void *pjfun=(void*)&DefaultPJfun<ValType>)
{
	typedef bool(*JFunType)(ValType);
	JFunType jfunc = (JFunType)jfun;
	typedef bool(*PJFunType)(ValType *, int);
	PJFunType pjfunc = (PJFunType)pjfun;
	ValType *ret = new ValType[size];
	cp_start:
	for (int i = 0; i < size; ++i)
	{
		ret[i] = CreateRandnum(start, end,jfun);
	}
		if (!pjfunc(ret, size))
		{
			goto cp_start;
		}
	return ret;
}
template<typename T>
void DefaultOut(T *data, int count)
{
}

#include <iostream>
//默认测试100次 每次生成1000个数字的随机数池进行测试 每次传递一个数字
//测试函数范式 void fun(valtype *data,int numcount)
template<typename ValType,typename FunType>
void AutoTest(FunType fun,int start,int end, int usecount = 1,  int testcount = 100, int poolsize = 100,FunType outfun=&DefaultOut<ValType>,void *jfun = (void *)&DefaultJfun<ValType>, void *pjfun = (void*)&DefaultPJfun<ValType>)
{
	MyTimer timer;
	long double nowtime = 0;
	int tcount = poolsize / usecount;
	for (int i = 1; i <= testcount; ++i)
	{
		ValType *pool = CreateRandPool(poolsize, start, end, jfun, pjfun);
		int nowptr = 0;//记录目前使用随机数池的位置
		long double pltime = 0;

		for (int j=1;j<=tcount;j++)
        {
			auto tp = pool + nowptr;
			timer.start();
			fun(tp, usecount); //这里避免计算
			timer.stop();
			//输出临时值
			outfun(tp, usecount);
            long long testtime = timer.ticks();
			pltime = (pltime*(j - 1) + testtime) / j;
			nowptr += usecount;
			
		}

		nowtime = (nowtime*(i - 1) + pltime) / i;
		delete[] pool;
	}
    printf("\nTest %d times of call %d times,use %d value once,average time is: ", testcount, tcount,usecount);
    std::cout<<nowtime<<std::endl;
}
