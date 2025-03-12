//P5782
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e6+5;

int n,m;
int dfn[MAXN],low[MAXN];
int st[MAXN],top;
int color,Time;
int col[MAXN];
bool instack[MAXN];

int head[MAXN];
int Next[MAXN];
int to[MAXN];
int cnt=1;

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

void addedge(int u,int v){
    Next[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void tarjan(int x){
    dfn[x]=++Time;
    low[x]=Time;
    st[++top]=x;
    instack[x]=true;
    for(int i=head[x];i;i=Next[i]){
        int v=to[i];
        if(!dfn[v]){
            //表示这个节点没有被访问过
            tarjan(v);
            low[x]=min(low[x],low[v]);
        }
        else if(instack[v]){
            //表示这个属于是回溯了 一定是同一个环上的
            low[x]=min(low[x],dfn[v]);
        }
    }
    if(dfn[x]==low[x]){
        col[x]=++color;
        //将所有节点按照颜色分类  完成缩点
        while(st[top]!=x){
            //属于同一个强联通分量
            col[st[top]]=color;
            instack[st[top]]=false;
            top--;
        }
        instack[x]=false;
        top--;
    }
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=m;i++){
        int a,b,x,y;
        a=read(),x=read(),b=read(),y=read();//a为x  或者  b为y
        //其中 1~n是取0  n+1~2*n是取1
        if(x==1&&y==1){
            //两者必须有至少一个是1
            addedge(a,b+n);//那么a取0  可以得出b一定是1
            addedge(b,a+n);
        }
        else if(x==0&&y==1){
            //a是0  或者  b是1
            addedge(a+n,b+n);//那么a取1  b一定得是1  因为a不符合取0的要求
            addedge(b,a);
        }
        else if(x==1&&y==0){
            addedge(b+n,a+n);
            addedge(a,b);
        }
        else{
            addedge(a+n,b);
            addedge(b+n,a);
        }
    }
    for(int i=1;i<=2*n;i++){
        if(!dfn[i]){
            tarjan(i);
        }
    }
    for(int i=1;i<=n;i++){
        if(col[i]==col[i+n]){
            //不符合要求 直接退出
            cout<<"IMPOSSIBLE"<<endl;
            return 0;
        }
    }
    cout<<"POSSIBLE"<<endl;
    //输出答案求解
    //要使用到拓扑排序   但是实际上拓扑也就是为了防止出现 a->b->a'  即a->a' 这种可能会导致错误情况
    //所以我们选择拓扑序尽量大的  即尽量在后面的  a'一定无法推导出a（如果a'的拓扑序更大的话）
    //因为后面无法指向前面  否则不就是在一个环里面了吗  那这样就是错误的
    //拓扑序尽量大的  其实颜色编号是尽量小的  因为tarjan的时候  先将尾部的那些数字访问到  然后将他们先缩点了
    //所以虽然在有的时候  选择较小的颜色编号是对的  但不是最优的
    for(int i=1;i<=n;i++){
        if(col[i]>col[i+n])
            printf("1 ");
        else
            printf("0 ");
    }
    return 0;
}
