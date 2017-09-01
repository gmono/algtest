#include <iostream>
using namespace std;
int ns[1000000+10];
int N;
int ms[10000+10];
int M;
int nextarr[10000+10];

void input(int *ss,int n)
{
    for(int i=0;i<n;++i)
    {
        cin>>ss[i];
    }
}

void makenext()
{
    int i=1,j=0;
    nextarr[0]=0;
    while(i<M)
    {
        if(ms[i]==ms[j])
        {
            nextarr[i]=j+1;
            i++;
            j++;
        }
        else if(j==0)
        {
            nextarr[i]=0;
            i++;
        }
        else
        {
            j=nextarr[j-1];
        }
    }
}
void makenext2()
{
    int j=0;
    nextarr[0]=0;
    for(int i=1;i<M;++i)
    {
        while(j&&ms[j]!=ms[i]) j=nextarr[j-1];
        if(ms[i]==ms[j])
        {
            nextarr[i]=j+1;
            j++;
        }
        else nextarr[i]=0;
    }
}

int search()
{
    int s=0,i=0;
    //s->str i->format
    int j=0;
    for(int i=0;i<N;)
    {
        if(ns[i]==ms[j])
        {
            i++;
            j++;
        }
        else if(j==0)
        {
            i++;
        }
        else
        {
            j=nextarr[j-1];
        }

        if(j==M) return i-M+1;
    }
    return -1;
}
int search2()
{
    //s->str i->format
    int j=0;
    for(int i=0;i<N;i++)
    {
        while(j&&ns[i]!=ms[j]) j=nextarr[j-1];
        if(ns[i]==ms[j])
            j++;
        //���ڴ�ʱi��û�е��� ���ָ�����һ��ƥ���ϵ��ַ�
        //����iΪ0��ʼ���±� ��Ҫת��Ϊ1��ʼ���±�����+1
        //i+1-M�õ�1��ʼ���±�ָ��ƥ�俪ʼλ��ǰһ���ַ�����Ϊiָ��ƥ�俪ʼλ�ã�
        //��+1�õ�ƥ�俪ʼλ��ָ��
        if(j==M) return i-M+2;

    }
    return -1;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin>>n;
    for(int i=0;i<n;++i)
    {
        cin>>N>>M;
        input(ns,N);
        input(ms,M);
        makenext2();
        int index=search();
        cout<<index<<endl;
    }
}


//#include<algorithm>
//#include<iostream>
//#include<cstdio>
//#include<cstring>
//using namespace std;

//#define MAXN 1000010

//int t , n , m;
//int text[MAXN];/*�ı���*/
//int pattern[MAXN];/*ģʽ��*/
//int next[MAXN];/*next����*/

///*O(m)��ʱ����next����*/
//void getNext(){
//    next[0] = next[1] = 0;
//    for(int i = 1 ; i < m ; i++){
//       int j = next[i];
//       while(j && pattern[i] != pattern[j])
//          j = next[j];
//       next[i+1] = pattern[i] == pattern[j] ? j+1 : 0;
//    }
//}

///*o(n)��ʱ�����ƥ��*/
//void find(){
//    int j = 0;/*��ʼ����ģʽ���ĵ�һ��λ��*/
//    for(int i = 0 ; i < n ; i++){/*���������ı���*/
//       while(j && pattern[j] != text[i])/*˳��ʧ����ߣ�ֱ������ƥ�䣬��õ������j = 0*/
//         j = next[j];
//       if(pattern[j] == text[i])/*���ƥ��ɹ�������һ��λ��*/
//         j++;
//       if(j == m){/*����ҵ���ֱ�����*/
//         printf("%d\n" , i-m+2);/*������ı����е�һ��ƥ���λ�ã������±�*/
//         return;
//       }
//    }
//    printf("-1\n");
//}

//int main(){
//   scanf("%d" , &t);
//   while(t--){
//      scanf("%d%d" , &n , &m);
//      for(int i = 0 ; i < n ; i++)
//         scanf("%d" , &text[i]);
//      for(int i = 0 ; i < m ; i++)
//         scanf("%d" , &pattern[i]);
//      getNext();
//      find();
//   }
//   return 0;
//}

