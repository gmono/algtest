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
        if(j==M) return i-M+1;

    }
    return -1;
}
int main()
{
    int n;
    cin>>n;
    for(int i=0;i<n;++i)
    {
        cin>>N>>M;
        input(ns,N);
        input(ms,M);
        makenext();
        int index=search2();
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
//int text[MAXN];/*文本串*/
//int pattern[MAXN];/*模式串*/
//int next[MAXN];/*next数组*/

///*O(m)的时间求next数组*/
//void getNext(){
//    next[0] = next[1] = 0;
//    for(int i = 1 ; i < m ; i++){
//       int j = next[i];
//       while(j && pattern[i] != pattern[j])
//          j = next[j];
//       next[i+1] = pattern[i] == pattern[j] ? j+1 : 0;
//    }
//}

///*o(n)的时间进行匹配*/
//void find(){
//    int j = 0;/*初始化在模式串的第一个位置*/
//    for(int i = 0 ; i < n ; i++){/*遍历整个文本串*/
//       while(j && pattern[j] != text[i])/*顺着失配边走，直到可以匹配，最坏得到情况是j = 0*/
//         j = next[j];
//       if(pattern[j] == text[i])/*如果匹配成功继续下一个位置*/
//         j++;
//       if(j == m){/*如果找到了直接输出*/
//         printf("%d\n" , i-m+2);/*输出在文本串中第一个匹配的位置，不是下标*/
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

