#pragma once
#include "common.h"
//堆会造成0号元素浪费 心理障碍(精确内存管理)需要克服
//堆结构测试
#define Left(i) 2*i
#define Right(i) 2*i+1
#define Parent(i) i/2
#define swap(a,b) {auto _t=a;a=b;b=_t;}
void Max_Heap(int *arr, int len, int root)
{
	//维护一个最大堆
	int maxindex = root;
	int left = Left(root);
	int right = Right(root);
	if (left <= len&&arr[left] > arr[maxindex])
		maxindex = left;
	if (right <= len&&arr[right] > arr[maxindex])
		maxindex = right;
	if (maxindex != root)
	{
		swap(arr[root], arr[maxindex]);
		Max_Heap(arr, len, maxindex);
	}
}
void BuildMaxHeap(int *arr, int len)
{
	for (int i = len / 2; i >= 1; --i)
	{
		Max_Heap(arr, len, i);
	}
}
void HeapSort(int *arr, int len)
{
	for (int i = len; i >= 2; --i)
	{
		swap(arr[1], arr[i]);
		len--;
		Max_Heap(arr, len,1);
	}
}
void test(int *p, int count)
{
	BuildMaxHeap(p, count);
	HeapSort(p, count);
}
void out(int *p, int count)
{
	for (int i = 1; i < count; ++i)
	{
		printf("%d ", p[i]);
	}
	getchar();
	putchar('\n');
}
void testinsert(int *p, int count)
{
	//插入排序测试
	for (int i = 2; i < count; ++i)
	{
		for (int j = i - 1; j >= 1; --j)
		{
			if (p[i] < p[j])
			{
				//找到比p[i]小的p[j] 插到p[j+1]
				int t = p[i];
				for (int a = i; a >= j+2; --a)
				{
					p[a] = p[a - 1];
				}
				p[j + 1] = t;
			}
		}
	}
}
int alquick(int *tp, int p, int r)
{
	int x = tp[r];
	int i = p - 1;
	for (int j = p; j < r; ++j)
	{
		if (tp[j] <= x)
		{
			i++;
			swap(tp[i], tp[j]);
		}
	}
	swap(tp[i + 1], tp[r]);
	return i + 1;
}
void testquick(int *tp, int p,int r)
{
	if (p < r)
	{
		int q = alquick(tp, p, r);
		testquick(tp, p, q - 1);
		testquick(tp, q + 1, r);
	}
}
void quick(int *p, int count)
{
	int tcount = count - 1;
	int *tp = p + 1;
	testquick(tp, 0,tcount-1);
}
int main()
{
	AutoTest<int>(&quick, 0, 1000000, 10001, 10, 100000);
	AutoTest<int>(&test, 0, 1000000, 10001, 10, 100000);
	AutoTest<int>(&testinsert, 0, 1000000,10001,10,100000);
	return 0;
}
#include <stdio.h>
//int main(int argc, char **argv)
//{
//	int sum;
//	while (scanf("%d", &sum) != EOF)
//	{
//		int *arr = new int[sum+1];
//		for (int i = 1; i <= sum; ++i)
//		{
//			scanf("%d", arr + i);
//		}
//		BuildMaxHeap(arr, sum);
//		HeapSort(arr, sum);
//		printf("排序后结果：");
//		for (int i = 1; i <= sum; ++i)
//		{
//			printf("%d ", arr[i]);
//		}
//		putchar('\n');
//	}
//}