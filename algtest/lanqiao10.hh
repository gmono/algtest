#pragma once

//蓝桥杯第十题
#include <stdio.h>
#include <vector>
using namespace std;
struct Node
{
	int weight;
	bool iscaled = false; //是否已经计算
	long long calval; //计算的结果
	vector<int> childs;//子节点数组
};

long long dp(Node *nodes, int nowpoint,int len,int parent)
{
	//动态规划状态处理函数
	//节点权计算函数 写的不是很优雅。。不过可能有点好处 如果在函数头这里判断是否计算过
	//逻辑上优雅，但其实平均多了一次调用
	//一次动作可以有sum种状态，这取决于nodes的长度
	//说是不存在环嘛。。所以只需要记录上一个节点 不自循环就好了。。
	//其实我发现我这么写确实很不优雅 。。就应该把本节点是否计算过放到函数头这里的。。
	//不然以后处理无向图都不好处理..
	//分分钟死循环啊..
	//long long sign = 1i64 << (sizeof(long long) * 8 - 1);
	//md 一开始想错了 去计算子树里最大权分支了。。求出来的是“最大权序列”...
	long long max = 0; //构造出一个超级大的负数当哨兵
	//其实还可以用指针啊 只是觉得有些不好看
	Node &nnode = nodes[nowpoint];
	for (int i = 0; i <nnode.childs.size() ; ++i)
	{
		if (nnode.childs[i] == parent) continue;
		//尝试从每一个子节点开始计算从其开始的最大可能权
		Node &tnode = nodes[nnode.childs[i]];
		if (tnode.iscaled)
		{
			//这里莫名想到了是不是用 ? :表达式 编译器会使用cmovcc系列指令实现 而不是用跳转 跳转效率很低。。
			//好吧我强迫症了 还是一开始不能学汇编，不然什么细节都喜欢权衡一下。。
			max = tnode.calval > 0 ? tnode.calval+max : max;
		}
		else
		{
			//计算其子树的最大可能累加权
			long long tnum=dp(nodes, nnode.childs[i], len,nowpoint);
			max = tnum > 0 ? tnum+max : max;
			//记录
			tnode.calval = tnum;
			tnode.iscaled = true;
		}
	}
	return nnode.weight + max;
	//return max==sign? nnode.weight:max+nnode.weight;
}
long long search(Node *nodes,int len)
{
	long long max = 0;
	for (int i = 0; i < len; ++i)
	{
		Node &tnode = nodes[i];
		
		long long tnum = tnode.iscaled? tnode.calval:dp(nodes, i,len,-1);
		max = tnum > max ? tnum : max;

	}
	return max;
}
int main()
{
	int sum = 0;
	scanf("%d", &sum);
	//构造树
	Node *nodes = new Node[sum];
	for (int i = 0; i < sum; ++i)
	{
		Node &tnode = nodes[i];
		scanf("%d", &tnode.weight);

	}
	//输入边
	for (int i = 0; i < sum-1; ++i)
	{
		//这里树节点索引从1开始所以 要减1
		int a, b;
		scanf("%d %d", &a, &b);
		a--; b--;//变为0开始的编号
		nodes[a].childs.push_back(b);
		//添加从a->b的边
		//无向边 添加从b->a的边
		nodes[b].childs.push_back(a);
	}
	long long result = search(nodes,sum);
	printf("%lld", result);
	return 0;
}