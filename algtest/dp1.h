#ifndef DP1_H
#define DP1_H
#include<iostream>
#include<cstring>
using namespace std;
const long long MOD=1e9+7;
struct Mat{
    int m[7][7];//这里的i，j表示的是i面朝上的骰子接j面朝上的骰子后，原方法要乘的数
}ans,base,X;
int limit[7][7];
void init(){
    memset(base.m,0,sizeof(base.m));
    memset(ans.m,0,sizeof(ans.m));
    memset(X.m,0,sizeof(X.m));
    //初始化ans=>单位矩阵
    for(int i=1;i<=6;i++)
        for(int j=1;j<=6;j++){
            ans.m[i][j]=(i==j);
        }
    //初始化base
    for(int i=1;i<=6;i++)
        for(int j=1;j<=6;j++){
            base.m[i][j]=(!limit[i][j])*4;
        }
    /*
    //debug
    cout<<"base:" <<endl;
    for(int i=1;i<=6;i++)
        for(int j=1;j<=6;j++){
            cout<<base.m[i][j]<<" ";
        }
    cout<<endl;
    */

    //初始化X
    for(int i=1;i<=6;i++) X.m[i][1]=4; //初值为第一个骰子i面朝上接
    /*
    //debug
    cout<<"X:" <<endl;
    for(int i=1;i<=6;i++)
        for(int j=1;j<=6;j++){
            cout<<X.m[i][j]<<" ";
        }
    cout<<endl;
    */
}
//定义矩阵乘法
Mat mul(Mat A,Mat B){
    Mat tmp;
    memset(tmp.m,0,sizeof(tmp.m));
    for(int i=1;i<=6;i++)
        for(int j=1;j<=6;j++)
            for(int k=1;k<=6;k++){
                tmp.m[i][j]+=A.m[i][k]*B.m[k][j];
            //	tmp.m[i][j]=(tmp.m[i][j]+MOD)%MOD;//防止负数出现
            }
    /*
    //debug
    cout<<"tmp:" <<endl;
    for(int i=1;i<=6;i++)
        for(int j=1;j<=6;j++){
            cout<<tmp.m[i][j]<<" ";
        }
    cout<<endl;
    */
    return tmp;
}
//快速幂
Mat quick_mat(int n){
    while(n){
        if(n&1){
            ans=mul(ans,base);
        }
        base=mul(base,base);
        n>>=1;
    }
    return ans;
}
int main(){
    int n,mm;
    int a,b;
    cin>>n>>mm;
    for(int i=0;i<mm;i++){
        cin>>a>>b;
        limit[a][(b+3)%6]=1;
        limit[b][(a+3)%6]=1;
    }
    /*
    //debug
    cout<<"limit:" <<endl;
    for(int i=1;i<=6;i++)
        for(int j=1;j<=6;j++){
            cout<<limit[i][j]<<" ";
        }
    cout<<endl;*/

    init();

    Mat ret;
    int sum=0;
    ret=quick_mat(n-1);
    ret=mul(ret,X);
    for(int i=1;i<=6;i++) sum+=ret.m[i][1];
    cout<<sum%MOD<<endl;
    return 0;
}
#endif // DP1_H
