#ifndef T_1242_HH
#define T_1242_HH
#include <stdio.h>
#include <stack>
#include <stdlib.h>
#include <functional>
//错误原因 太复杂
struct Point
{
    bool isthrough;//是否可以通过
    int stepv;//步权 如果可以通过需要几步 如果isthrough为true且stepv为0则代表目的地 最后把 sum+1就好
    inline bool isok()
    {
        return isthrough&&stepv==0;
    }
    inline bool setok()
    {
        isthrough=true;
        stepv=0;
    }
};
struct Position
{
    Position(){}
    Position(int x,int y,int ns):x(x),y(y),nowstep(ns){}
    int x=0;
    int y=0;
    int nowstep=0;
    bool next(int index,Point**map,int rows,int cols,Position &result)\
    {
        //转移函数
        //index 1->4 左上右下
        switch (index) {
        case 1:
            //上 x-1
            if(x==0||!map[x-1][y].isthrough) return false;
            result=Position(x-1,y,map[x-1][y].stepv+this->nowstep);
            return true;
        case 2:
            //左 y-1
            if(y==0||!map[x][y-1].isthrough) return false;
            result=Position(x,y-1,map[x][y-1].stepv+this->nowstep);
            return true;
        case 3:
            //下 x+1
//            if(x==rows-1||!map[x+1][y].isthrough) return false;
            if(x==rows-1) return false;
            if(!map[x+1][y].isthrough) return false;
            result=Position(x+1,y,map[x+1][y].stepv+this->nowstep);
            return true;
        case 4:
            //右 y+1
//            if(y==cols-1||!map[x][y+1].isthrough) return false;
            if(y==cols-1) return false;
            if(!map[x][y+1].isthrough) return false;
            result=Position(x,y+1,map[x][y+1].stepv+this->nowstep);
            return true;
        default:
            return false;
        }
    }
};
#include <memory.h>
bool bmap[200][200]={true};
int max=-1;
int go(Point **dmap,Position nowpos,int rows,int cols)
{
    //从nowpos出发找到isok为ture
    //使用bfs
    using std::stack;
    stack<Position> tstack;//临时存储栈
    //记忆图
    bool **bmap=new bool*[rows];
    for(int i=0;i<rows;++i)
    {
        bmap[i]=new bool[cols];
        for(int j=0;j<cols;++j) bmap[i][j]=true;
        //为了避免神TM优先级问题 用true代表未访问 或者“可用”
    }

    //开始 入根节点
    tstack.push(nowpos);
    while(!tstack.empty())
    {
        //出栈
        Position pos=tstack.top();
        tstack.pop();
        //遍历子节点 采用入栈时处理策略
        for(int i=1;i<=4;++i)
        {
            //遍历子节点
            Position tpos;
            bool ret=pos.next(i,dmap,rows,cols,tpos);

            if(ret&&bmap[tpos.x][tpos.y])
            {
                //成功获得子节点 直接处理
                if(dmap[tpos.x][tpos.y].isok())
                {
                    //找到 返回步
                    return tpos.nowstep;
                }
                else
                {
                    //没找到 入栈
                    tstack.push(tpos);
                    bmap[tpos.x][tpos.y]=false;//设置为不可用
                }
            }
        }
        //子节点入栈完成
        //继续
    }
    //没找到 return -1;
    return -1;
}
int dfs(Point **map,Position nowpos,int rows,int cols)
{
    //dfs策略
    //非递归dfs
    using std::stack;
    stack<Position> posstack;
    posstack.push(nowpos);
    //入根节点
    //访问图
    bool **bmap=new bool*[rows];
    for(int i=0;i<rows;++i)
    {
        bmap[i]=new bool[cols];
        for(int j=0;j<cols;++j) bmap[i][j]=true;
        //为了避免神TM优先级问题 用true代表未访问 或者“可用”
    }
    bmap[nowpos.x][nowpos.y]=false;//当前位置已访问
    //搜索
    while(!posstack.empty())
    {
        //入栈时处理策略
        Position tpos=posstack.top();
        posstack.pop();
        //加入子节点
    }
}
//虽然不想破怪结构然而这样比较快

auto dfun(Point **map,Position nowpos,int rows,int cols)->void
{
    if(map[nowpos.x][nowpos.y].isok())
        max=max>nowpos.nowstep||max==-1?nowpos.nowstep:max;
    //没找到 尝试搜索下级
    for(int i=1;i<=4;++i)
    {
        Position res;
        bool issub=nowpos.next(i,map,rows,cols,res);
        if(issub&&bmap[res.x][res.y])
        {
            //下级节点可用
            bmap[res.x][res.y]=false;//设置为不可访问
            dfun(map,res,rows,cols);
            bmap[res.x][res.y]=true;//设置
            //继续寻找其他分支
            //理论上来说 可以在函数外放一个int 来保存最短路径 不需要逐级传递 但是这样就破坏了结构
            //不符合原则
        }
    }
}

int fundfs(Point **map,Position nowpos,int rows,int cols)
{
    max=-1;
    using std::function;
    //递归dfs
    memset(bmap,true,sizeof(bool)*200*200);
    bmap[nowpos.x][nowpos.y]=false;//当前位置已访问
    //-1代表没找到
    dfun(map,nowpos,rows,cols);
    return max;
}

int main()
{
    freopen("t_1242.txt","r+",stdin);//测试
    int rows,cols;
    while(scanf("%d %d\n",&rows,&cols)==2)
    {
        //构造数组
        Point **arr=new Point*[rows];
        Position friend_pos;//f的位置
        for(int i=0;i<rows;++i)
        {
            arr[i]=new Point[cols];
            for(int j=0;j<cols;++j)
            {
                char c=getchar();
                Point temp;
                switch (c) {
                case '.':
                    temp.isthrough=true;
                    temp.stepv=1;
                    break;
                case 'x':
                    //guard
                    temp.isthrough=true;
                    temp.stepv=2;
                    break;
                case '#':
                    temp.isthrough=false;
                    temp.stepv=0;
                    break;
                case 'a':
                    temp.setok();//设置为目的地
                    break;
                case 'r':
                    //目前位置装入
                    friend_pos.x=i;
                    friend_pos.y=j;
                    friend_pos.nowstep=0;
                    break;
                default:
                    exit(1);//错误
                    break;
                }
                arr[i][j]=temp;//装入地图
            }
            getchar();//跳过回车
        }
        //地图构造完成 开始处理
//        int stepsum=go(arr,friend_pos,rows,cols);
        int stepsum=fundfs(arr,friend_pos,rows,cols);
        if(stepsum==-1) printf("Poor ANGEL has to stay in the prison all his life.\n");
        else
            printf("%d\n",stepsum+1);//+1因为a不算步骤
    }
}

#endif // T_1242_HH
