#pragma once
#include "MyTimer_win.h"
#include <intrin.h>
#include <iostream>
constexpr int bufsize = 1080 * 1920 * 3;
//此宏向上取整
#define calwsize(bsize,type) (bsize/sizeof(type)+(bsize%sizeof(type)!=0 ? 1:0))
char *buf = nullptr;
char *buf2 = nullptr;
char *result = nullptr;
template<class T>
long long cal()
{
	MyTimer timer;
	timer.start();
	int i = 0;
	for (i = 0; i<bufsize / sizeof(T); i += sizeof(T))
	{
		*(T *)(result + i) = *(T *)(buf + i) ^ *(T *)(buf2 + i);
	}
	timer.stop();
	printf("%d字节%s循环:", sizeof(T), typeid(T).name());
	std::cout << timer.ticks() << std::endl;
	return timer.ticks();
}
template<class T>
long long s_cal()
{
	MyTimer timer;
	timer.start();
	int i = 0;
	for (i = 0; i<bufsize / sizeof(T); i += sizeof(T))
	{
		*(T *)(result + i) = *(T *)(buf + i) - *(T *)(buf2 + i);
	}
	timer.stop();
	printf("%d字节%s循环:", sizeof(T), typeid(T).name());
	std::cout << timer.ticks() << std::endl;
	return timer.ticks();
}
long long m128cal()
{
	MyTimer timer;
	timer.start();
	int i = 0;
	for (i = 0; i<bufsize / sizeof(__m128i); i += sizeof(__m128i))
	{
		*(__m128i *)(result + i) = _mm_xor_si128(*(__m128i *)(buf + i), *(__m128i *)(buf2 + i));
	}
	timer.stop();
	printf("%d字节%s循环:", sizeof(__m128i), typeid(__m128i).name());
	std::cout << timer.ticks() << std::endl;
	return timer.ticks();
}
long long m256cal()
{
	MyTimer timer;
	timer.start();
	int i = 0;
	for (i = 0; i<bufsize / sizeof(__m256i); i += sizeof(__m256i))
	{
		*(__m256i *)(result + i) = _mm256_xor_si256(*(__m256i *)(buf + i), *(__m256i *)(buf2 + i));
	}
	timer.stop();
	printf("%d字节%s循环:", sizeof(__m256i), typeid(__m256i).name());
	std::cout << timer.ticks() << std::endl;
	return timer.ticks();
}
template<class T>
long long mp_cal()
{
	int tsize = calwsize(bufsize, T);
	MyTimer timer;
	timer.start();
	//int ss = tsize * sizeof(T);
	int i = 0;
#pragma omp parallel for
	for(i=0;i<bufsize/sizeof(T);i+=sizeof(T))
	{
		*(T *)(result + i) = *(T *)(buf + i) ^ *(T *)(buf2 + i);
	}
	timer.stop();
	printf("%d字节%s循环:", sizeof(T), typeid(T).name());
	std::cout << timer.ticks() << std::endl;
	return timer.ticks();
}
long long mp_m128cal()
{
	//int tsize = calwsize(bufsize, __m128i);
	MyTimer timer;
	timer.start();
	int i = 0;
#pragma omp parallel for
	for (i = 0; i<bufsize / sizeof(__m128i); i += sizeof(__m128i))
	{
		*(__m128i *)(result + i) =_mm_xor_si128( *(__m128i *)(buf + i) , *(__m128i *)(buf2 + i));
	}
	timer.stop();
	printf("%d字节%s循环:", sizeof(__m128i), typeid(__m128i).name());
	std::cout << timer.ticks() << std::endl;
	return timer.ticks();
}
long long mp_m256cal()
{
	//int tsize = calwsize(bufsize, __m256i);
	MyTimer timer;
	timer.start();
	int i = 0;
#pragma omp parallel for
	for (i = 0; i<bufsize / sizeof(__m256i); i += sizeof(__m256i))
	{
		*(__m256i *)(result + i) =_mm256_xor_si256(*(__m256i *)(buf + i) , *(__m256i *)(buf2 + i));
	}
	timer.stop();
	printf("%d字节%s循环:", sizeof(__m256i), typeid(__m256i).name());
	std::cout << timer.ticks() << std::endl;
	return timer.ticks();
}
//void m512cal()
//{
//	int tsize = calwsize(bufsize, __m512i);
//	MyTimer timer;
//	timer.start();
//	for (int i = 0; i < tsize; ++i)
//	{
//	}
//	timer.stop();
//	printf("%d字节%s循环:", sizeof(__m256i), typeid(__m256i).name());
//	std::cout << timer.ticks() << std::endl;
//}

void test(long long(*pfun)())
{
	long double time = 0;
	for (int i = 0; i < 10; ++i)
	{
		time += pfun();
	}
	std::cout << "平均用时：" << time / 10<<std::endl;
}
int main()
{
	//缓冲区64字节对齐
	int tsize = calwsize(bufsize,__m512i)*sizeof(__m512i);
	buf = new char[tsize];
	buf2 = new char[tsize];
	result = new char[tsize];
	test(&cal<byte>);
	test(&cal<__int32>);
	test(&cal<__int64>);
	test(&m128cal);
	test(&m256cal);
	std::cout << "OpenMP并行化测试:" << std::endl<<std::endl;
	test(&mp_cal<byte>);
	test(&mp_cal<__int32>);
	test(&mp_cal<__int64>);
	test(&mp_m128cal);
	test(&mp_m256cal);
	std::cout << "减法比较测试:" << std::endl << std::endl;
	test(&s_cal<byte>);
	test(&s_cal<__int32>);
	test(&s_cal<__int64>);
	while (std::cin.get()!='\n');
	return 0;
}
//#pragma loop(hint_parallel[(4)])