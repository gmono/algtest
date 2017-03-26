#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#define Road 0
#define Wall 1
#define Guard 2
#define Angle 3
//以上为地图元素宏定义
#include <stack>
//using std::stack;
//#define swap(a,b) ({auto t=a;a=b;b=t;})
#define swap(a,b) auto t=a;a=b;b=t
using namespace std;
namespace SearchSpace
{
    //命名空间全局变量
    int dmap[202][202]; //约束 地图元素宏定义
    int leftSteps[202][202];//剩余步记录表
    bool accMem[202][202];//记录是否正在访问
    //此结构体依赖此命名空间
    struct Pos
    {
        //坐标结构
        int r;
        int c;
        //函数 转移
        inline Pos next(int sign)
        {
            //sign 1 2 3 4
            //分别代表 上下左右转移
            Pos ret=*this;
            switch(sign)
            {

            case 1:
                ret.r--;
                break;
            case 2:
                ret.r++;
                break;
            case 3:
                ret.c--;
                break;
            case 4:
                ret.c++;
                break;
            default:
                exit(2);

            }
            return ret;
        }
        //方法 合法性
        inline bool isok()
        {
            if(r<0||r>=202||c<0||c>=202)
            {

                //坐标超界检测
                return false;
            }
            if(dmap[r][c]==Wall)
            {
                return false;

            }
            //printf("%d",dmap[r][c]);
            return true;

        }
    };
    //搜索专用命名空间
    int search(int fr,int fc)
    {
        //bfs过程
        stack<Pos> one;
        stack<Pos> two;
        stack<Pos> *nowstack=&one;
        stack<Pos> *newstack=&two;
        int nowstep=0;//当前正在处理节点的步数
        //构造根节点
        Pos root;
        root.r=fr;
        root.c=fc;
        //根节点入栈
        nowstack->push(root);
        while(!nowstack->empty())
        {
            //构造新栈 放入可用子节点

//            stack<Pos> *newstack=new stack<Pos>();
            while(!nowstack->empty())
            {
                //处理所有父节点
                //如果父节点的剩余步不为0则直接放入 否则放入其子节点
                Pos fatpos=nowstack->top();
                nowstack->pop();//弹出父节点
                if(dmap[fatpos.r][fatpos.c]==Angle)
                {
                    return nowstep;
                }
                //否则继续
                int &fat_lstep=leftSteps[fatpos.r][fatpos.c];//获得剩余步
                fat_lstep--;//减当前步
                if(fat_lstep==0)
                {
                    //处理每个子节点
                    for(int i=1;i<=4;++i)
                    {
                        //获得子节点 合法性判断 合法则 判断是否正在访问中 非访问中则放入新栈
                        Pos child=fatpos.next(i);
                        if(child.isok()&&accMem[child.r][child.c]==false)
                        {
                            newstack->push(child);
                            accMem[child.r][child.c]=true;
                        }
                    }
                }
                else
                {
                    //直接放入
                    newstack->push(fatpos);
                }
            }
            nowstep++;//当前步加1
//            delete nowstack;
//            nowstack=newstack;
            swap(newstack,nowstack);

        }
        //delete nowstack;
        return -1;//返回-1代表没找到
    }
    void mapinit()
    {

        //地图初始化 全设为墙
        for(int i=0;i<202;++i)
            for(int j=0;j<202;++j)
                dmap[i][j]=Wall;
        //初始化记忆图
        memset(leftSteps,0,202*202*sizeof(int));
        memset(accMem,false,202*202*sizeof(bool));
    }
}
using SearchSpace::dmap;
using SearchSpace::mapinit;
using SearchSpace::leftSteps;//由于要针对不同类型节点设置剩余步 因此包含进来
int main()
{
    //调试用
    freopen("t_1242.txt","r+",stdin);
    int rows,cols;
    while(scanf("%d %d\n",&rows,&cols)!=EOF)
    {
        mapinit();
        int fr=0,fc=0;
        for(int i=1;i<=rows;++i)
        {

            for(int j=1;j<=cols;++j)
            {

                char c=getchar();
                int &point=dmap[i][j];
                int &lstep=leftSteps[i][j];
                //putchar(c); //debug
                switch(c)
                {
                case '.':
                    point=Road;
                    lstep=1;

                    break;
                case '#':
                    point=Wall;
                    lstep=1;
                    break;
                case 'x':
                    point=Guard;
                    lstep=2;
                    break;
                case 'r':
                    point=Angle; //反搜索搜多起点最短路
                    lstep=1;
                    break;
                case 'a':
                    fr=i;
                    fc=j;
                    //设为墙
                    point=Wall;
                    lstep=1;
                    break;
                default:
                    exit(3);
                }
            }
            getchar();//去回车
            //putchar('\n');
        }
        //搜索
        int res=SearchSpace::search(fr,fc);
        if(res==-1)
            printf("Poor ANGEL has to stay in the prison all his life.\n");
        else printf("%d\n",res);
    }
    return 0;
}
