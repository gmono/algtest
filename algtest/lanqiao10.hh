#pragma once

//���ű���ʮ��
#include <stdio.h>
#include <vector>
using namespace std;
struct Node
{
	int weight;
	bool iscaled = false; //�Ƿ��Ѿ�����
	long long calval; //����Ľ��
	vector<int> childs;//�ӽڵ�����
};

long long dp(Node *nodes, int nowpoint,int len,int parent)
{
	//��̬�滮״̬������
	//�ڵ�Ȩ���㺯�� д�Ĳ��Ǻ����š������������е�ô� ����ں���ͷ�����ж��Ƿ�����
	//�߼������ţ�����ʵƽ������һ�ε���
	//һ�ζ���������sum��״̬����ȡ����nodes�ĳ���
	//˵�ǲ����ڻ��������ֻ��Ҫ��¼��һ���ڵ� ����ѭ���ͺ��ˡ���
	//��ʵ�ҷ�������ôдȷʵ�ܲ����� ������Ӧ�ðѱ��ڵ��Ƿ������ŵ�����ͷ����ġ���
	//��Ȼ�Ժ�������ͼ�����ô���..
	//�ַ�����ѭ����..
	//long long sign = 1i64 << (sizeof(long long) * 8 - 1);
	//md һ��ʼ����� ȥ�������������Ȩ��֧�ˡ�����������ǡ����Ȩ���С�...
	long long max = 0; //�����һ��������ĸ������ڱ�
	//��ʵ��������ָ�밡 ֻ�Ǿ�����Щ���ÿ�
	Node &nnode = nodes[nowpoint];
	for (int i = 0; i <nnode.childs.size() ; ++i)
	{
		if (nnode.childs[i] == parent) continue;
		//���Դ�ÿһ���ӽڵ㿪ʼ������俪ʼ��������Ȩ
		Node &tnode = nodes[nnode.childs[i]];
		if (tnode.iscaled)
		{
			//����Ī���뵽���ǲ����� ? :���ʽ ��������ʹ��cmovccϵ��ָ��ʵ�� ����������ת ��תЧ�ʺܵ͡���
			//�ð���ǿ��֢�� ����һ��ʼ����ѧ��࣬��Ȼʲôϸ�ڶ�ϲ��Ȩ��һ�¡���
			max = tnode.calval > 0 ? tnode.calval+max : max;
		}
		else
		{
			//�������������������ۼ�Ȩ
			long long tnum=dp(nodes, nnode.childs[i], len,nowpoint);
			max = tnum > 0 ? tnum+max : max;
			//��¼
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
	//������
	Node *nodes = new Node[sum];
	for (int i = 0; i < sum; ++i)
	{
		Node &tnode = nodes[i];
		scanf("%d", &tnode.weight);

	}
	//�����
	for (int i = 0; i < sum-1; ++i)
	{
		//�������ڵ�������1��ʼ���� Ҫ��1
		int a, b;
		scanf("%d %d", &a, &b);
		a--; b--;//��Ϊ0��ʼ�ı��
		nodes[a].childs.push_back(b);
		//��Ӵ�a->b�ı�
		//����� ��Ӵ�b->a�ı�
		nodes[b].childs.push_back(a);
	}
	long long result = search(nodes,sum);
	printf("%lld", result);
	return 0;
}