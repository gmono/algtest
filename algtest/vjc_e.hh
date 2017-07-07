#include <stdio.h>
#include <vector>
#define maxn 50000+10
int ns[maxn];
struct Node
{
    int s;
    int e;
    int min;
    int max;
    Node *left;
    Node *right;
};
Node *makeTree(int N)
{
    using std::vector;
    vector<Node *> one;
    vector<Node *> two;
    vector<Node *> *now=one;
    vector<Node *> *childs=two;
    for(int i=0;i<N;i+=2)
    {
        Node *tnode=new Node();
        tnode->s=i;
        tnode->e=i+1;
        tnode->min=ns[i];
        tnode->max=ns[i+1];
        tnode->left=nullptr;
        tnode->right=nullptr;
        childs->push_back(tnode);
    }
    if(N%2!=0)
    {
        Node *n=new Node();
        n->s=N-1;
        n->e=n->s;
        n->max=ns[n-1];
        n->min=n->max;
        n->right=nullptr;
        n->left=nullptr;
        childs->push_back(n);
    }
    while(!childs->empty())
    {
        now->clear();
        for(int i=0;i<childs->size();i+=2)
        {
            Node *n1=childs[i];
            Node *n2=childs[i+1];
            Node *n=new Node();
            n->s=n1->s;
            n->e=n2->e;
            n->min=std::min(n1->min,n2->min);
            n->max=std::max(n1->max,n2->max);
            n->left=n1;
            n->right=n2;
            now->push_back(n);
        }
        if(childs->size()%2==0)
        {
            Node *pn=childs[childs->size()-1];
            Node *n=new Node();
            *n=*pn;
            n->left=n->right=pn;
            now->push_back(n);
        }
        std::swap(now,childs);
    }
    Node *head=now[0];
    return head;

}
int queryHeight(Node *head,int s,int e)
{
    s--;e--;\
    if(s-e<=1)
    {
        return
    }
    int mid=(s+e)/2;
    int m1=queryHeight(head->left,s,mid);
    int m2=queryHeight(head->right,mid+1,e);
    return m1>m2? m1:m2;
}


int main()
{
    int N,Q;
    while(scanf("%d %d",&N,&Q))
    {
        for(int i=0;i<N;++i)
        {
            scanf("%d",ns[i]);
        }
        Node *head=makeTree(N);
        for(int i=0;i<Q;++i)
        {
            int s,e;
            scanf("%d %d",&s,&e);
            int h=queryHeight(head,s,e);
            cout<<h<<endl;
        }
    }
}
