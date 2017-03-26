#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#define Road 0
#define Wall 1
#define Guard 2
#define Angle 3
//����Ϊ��ͼԪ�غ궨��
#include <stack>
//using std::stack;
//#define swap(a,b) ({auto t=a;a=b;b=t;})
#define swap(a,b) auto t=a;a=b;b=t
using namespace std;
namespace SearchSpace
{
    //�����ռ�ȫ�ֱ���
    int dmap[202][202]; //Լ�� ��ͼԪ�غ궨��
    int leftSteps[202][202];//ʣ�ಽ��¼��
    bool accMem[202][202];//��¼�Ƿ����ڷ���
    //�˽ṹ�������������ռ�
    struct Pos
    {
        //����ṹ
        int r;
        int c;
        //���� ת��
        inline Pos next(int sign)
        {
            //sign 1 2 3 4
            //�ֱ���� ��������ת��
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
        //���� �Ϸ���
        inline bool isok()
        {
            if(r<0||r>=202||c<0||c>=202)
            {

                //���곬����
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
    //����ר�������ռ�
    int search(int fr,int fc)
    {
        //bfs����
        stack<Pos> one;
        stack<Pos> two;
        stack<Pos> *nowstack=&one;
        stack<Pos> *newstack=&two;
        int nowstep=0;//��ǰ���ڴ���ڵ�Ĳ���
        //������ڵ�
        Pos root;
        root.r=fr;
        root.c=fc;
        //���ڵ���ջ
        nowstack->push(root);
        while(!nowstack->empty())
        {
            //������ջ ��������ӽڵ�

//            stack<Pos> *newstack=new stack<Pos>();
            while(!nowstack->empty())
            {
                //�������и��ڵ�
                //������ڵ��ʣ�ಽ��Ϊ0��ֱ�ӷ��� ����������ӽڵ�
                Pos fatpos=nowstack->top();
                nowstack->pop();//�������ڵ�
                if(dmap[fatpos.r][fatpos.c]==Angle)
                {
                    return nowstep;
                }
                //�������
                int &fat_lstep=leftSteps[fatpos.r][fatpos.c];//���ʣ�ಽ
                fat_lstep--;//����ǰ��
                if(fat_lstep==0)
                {
                    //����ÿ���ӽڵ�
                    for(int i=1;i<=4;++i)
                    {
                        //����ӽڵ� �Ϸ����ж� �Ϸ��� �ж��Ƿ����ڷ����� �Ƿ������������ջ
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
                    //ֱ�ӷ���
                    newstack->push(fatpos);
                }
            }
            nowstep++;//��ǰ����1
//            delete nowstack;
//            nowstack=newstack;
            swap(newstack,nowstack);

        }
        //delete nowstack;
        return -1;//����-1����û�ҵ�
    }
    void mapinit()
    {

        //��ͼ��ʼ�� ȫ��Ϊǽ
        for(int i=0;i<202;++i)
            for(int j=0;j<202;++j)
                dmap[i][j]=Wall;
        //��ʼ������ͼ
        memset(leftSteps,0,202*202*sizeof(int));
        memset(accMem,false,202*202*sizeof(bool));
    }
}
using SearchSpace::dmap;
using SearchSpace::mapinit;
using SearchSpace::leftSteps;//����Ҫ��Բ�ͬ���ͽڵ�����ʣ�ಽ ��˰�������
int main()
{
    //������
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
                    point=Angle; //�������Ѷ�������·
                    lstep=1;
                    break;
                case 'a':
                    fr=i;
                    fc=j;
                    //��Ϊǽ
                    point=Wall;
                    lstep=1;
                    break;
                default:
                    exit(3);
                }
            }
            getchar();//ȥ�س�
            //putchar('\n');
        }
        //����
        int res=SearchSpace::search(fr,fc);
        if(res==-1)
            printf("Poor ANGEL has to stay in the prison all his life.\n");
        else printf("%d\n",res);
    }
    return 0;
}
