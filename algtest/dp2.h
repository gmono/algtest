#ifndef DP2_H
#define DP2_H
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<vector>
using namespace std;
const int MAXN=100000+10;
//const int INF=-1000000-10;
long long dp[MAXN][2];//dp[i][0]表示不选i，dp[i][1]表示选i
int val[MAXN];
vector<int>tree[MAXN];
//三个数中的最大值
int mmax(int x,int y,int z){
    if(x<y) x=y;
    if(x<z) x=z;
    return x;
}
void dfs(int x,int fa){
    //初始化
    dp[x][0]=0;
    dp[x][1]=val[x];
    //查找x的分支
    for(int i=0;i<tree[x].size();i++){
        int son=tree[x][i];
        if(son^fa){//当son还有分支时
            dfs(son,x);//从叶子结点开始找
            //开始讨论选不选x这个结点
            //当不选x这个结点时，最大必然是所有分支中dp[son][0]和dp[son][1]中大于0的最大值的累加
            dp[x][0]=mmax(dp[son][0],dp[son][1],dp[x][0]);//这里把dp[x][0]放入比较避免了儿子是负数的情况

            //当选x这个结点时，最大必然是所有分支中 dp[son][1]>0的最大值+x（保证连通性）
            if(dp[son][1]>0) dp[x][1]+=dp[son][1];
        }
    }
}
int main(){
    int n,a,b;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>val[i];//每个结点的评分
    for(int i=1;i<n;i++){
        cin>>a>>b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }
     dfs(1,-1);
     //最后比较dp[root][0],dp[root][1];
     long long ret=0;
     ret=max(dp[1][1],dp[1][0]);
     cout<<ret<<endl;
    return 0;
}
#endif // DP2_H
