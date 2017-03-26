#ifndef T_1242_HH
#define T_1242_HH
//这里采用那种结构上稀烂但是却很有效率也很简单的编程形式
//总体来说 面向过程
#include <stdio.h>
#include <stack>
//地图
int map[202][202];//地图 其中值 4:路 1:墙 2:守卫 3:目的
int memory[202][202];//记忆图 数字表示剩余步数
int r,c;//当前所处行列
int steps;//搜索到的最少步 无解为-1
struct Pos
{
    int r;
    int c;
};
using std::stack;
stack<Pos> *posstack;//bfs stack 栈里存储的都是可访问的点
void search()
{
    //bfs策略
    posstack=new stack<Pos>();//创建
    steps=-1;//设置为-1 如果找到就把当前步赋值给它 否则就直接返回
    posstack->push(Pos{r,c});
    int nowstep=0;
    //加入跟节点
    while(!posstack->empty())
    {
        //当前栈全部取出 替换成其子节点 如果当前节点的memory不为0 则直接加入本身
        stack<Pos> *newstack=new stack<Pos>();//创建新栈创建子节点
        while(!posstack->empty())
        {
            //处理每个节点的子节点
            Pos &nowp=posstack->top();
            int &mem=memory[nowp.r][nowp.c];
            mem--;
            if(mem!=0)
            {
                //直接加入本节点
                newstack->push(nowp);

            }
            else
            {
                //加入其子节点
                //上下左右
                Pos child=nowp;
                child.r--;
                if(map[child.r][child.c]==4||map[child.r][child.c]==2)
                {
                    //可访问点
                    if(memory[child.r][child.c]>0)
                        newstack->push(child);
                }
                else if(map[child.r][child.c]==3)
                {
                    //目的地
                    steps=nowstep+1;
                    goto ok;
                }

                child=nowp;
                child.r++;
                if(map[child.r][child.c]==4||map[child.r][child.c]==2)
                {
                    //可访问点
                    if(memory[child.r][child.c]>0)
                        newstack->push(child);
                }
                else if(map[child.r][child.c]==3)
                {
                    //目的地
                    steps=nowstep+1;
                    goto ok;
                }

                child=nowp;
                child.c--;
                if(map[child.r][child.c]==4||map[child.r][child.c]==2)
                {
                    //可访问点
                    if(memory[child.r][child.c]>0)
                        newstack->push(child);
                }
                else if(map[child.r][child.c]==3)
                {
                    //目的地
                    steps=nowstep+1;
                    goto ok;
                }

                child=nowp;
                child.c++;
                if(map[child.r][child.c]==4||map[child.r][child.c]==2)
                {
                    //可访问点
                    if(memory[child.r][child.c]>0)
                        newstack->push(child);
                }
                else if(map[child.r][child.c]==3)
                {
                    //目的地
                    steps=nowstep+1;
                    goto ok;
                }

            }
            posstack->pop();
            //
        }
        //newstack 替换
        delete posstack;
        posstack=newstack;//替换为新节点栈
        nowstep++;
    }
    ok:;
    //返回结果
}

int main()
{
    freopen("t_1242.txt","r+",stdin);
    int rows,cols;
    while(scanf("%d %d",&rows,&cols)==2)
    {
        getchar();
        //读取数字成功则继续
        for(int i=1;i<=rows;++i)
        {
            for(int j=1;j<=cols;++j)
            {
                //读取填充地图
                char ch=getchar();
                switch(ch)
                {
                case '.':
                    map[i][j]=4;
                    memory[i][j]=1;
                    break;
                case '#':
                    map[i][j]=1;//墙
                    //不设置记忆
                    break;
                case 'x':
                    map[i][j]=2;
                    memory[i][j]=2;
                    break;
                case 'a':
                    map[i][j]=3;//目的地
                    //同样无需设置步数
                    break;
                case 'r':
                    //friend point
                    //记录当前位置
                    r=i;
                    c=j;
                    memory[i][j]=1;
                    break;
                default:
                    printf("error!");
                    return 1;
                }
            }
            getchar();//跳过回车
        }
        //加围墙
        for(int i=0;i<=cols+1;++i)
        {
            //上围墙
            map[0][i]=1;//墙
        }
        for(int i=0;i<=cols+1;++i)
        {
            //下围墙
            map[rows+1][i]=1;//墙
        }
        for(int i=0;i<=rows+1;++i)
        {
            //左围墙
            map[i][0]=1;//墙
        }
        for(int i=0;i<=rows+1;++i)
        {
            //右围墙
            map[i][cols+1]=1;//墙
        }
        search();
        if(steps!=-1)
        {
            printf("%d\n",steps+1);//
        }
        else
        {
            printf("Poor ANGEL has to stay in the prison all his life.\n");
        }
    }
}

#endif // T_1242_HH
