#pragma once
//���ò��Կ�
//�����������
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
//jfunΪ��Ч���жϺ��� �ж����ɵ�������Ƿ����
//bool jfun(valtype v); ����true������ȷ

template<typename ValType>
ValType CreateRandnum(ValType start,ValType end,void *jfun=(void *)&DefaultJfun<ValType>)
{
	typedef bool(*JFunType)(ValType);
	JFunType jfunc = (JFunType)jfun;
	std::random_device rd;
	cr_start:
	unsigned long long rawnum1 = (long long)rd()%(end-start+1);//��ĸ
	unsigned long long rawnum2 = (long long)rd()%(long long)pow(end-start+1,2);//����
	double ret = (double)rawnum2 / (double)rawnum1  + start;
	ValType val= static_cast<ValType>(ret);

		if (!jfunc(val)) goto cr_start;
		return val;
}
//pjfunΪ���жϺ��� �ж�һ��������ļ����Ƿ���Ч ִ��һ��
//bool pjfun(valtype *pool,int size);//����true������Ч
//��Ч��������
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
//Ĭ�ϲ���100�� ÿ������1000�����ֵ�������ؽ��в��� ÿ�δ���һ������
//���Ժ�����ʽ void fun(valtype *data,int numcount)
template<typename ValType,typename FunType>
void AutoTest(FunType fun,int start,int end, int usecount = 1,  int testcount = 100, int poolsize = 100,FunType outfun=&DefaultOut<ValType>,void *jfun = (void *)&DefaultJfun<ValType>, void *pjfun = (void*)&DefaultPJfun<ValType>)
{
	MyTimer timer;
	long double nowtime = 0;
	int tcount = poolsize / usecount;
	for (int i = 1; i <= testcount; ++i)
	{
		ValType *pool = CreateRandPool(poolsize, start, end, jfun, pjfun);
		int nowptr = 0;//��¼Ŀǰʹ��������ص�λ��
		long double pltime = 0;

		for (int j=1;j<=tcount;j++)
        {
			auto tp = pool + nowptr;
			timer.start();
			fun(tp, usecount); //����������
			timer.stop();
			//�����ʱֵ
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
