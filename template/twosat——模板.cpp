//https://acm.hdu.edu.cn/showproblem.php?pid=3062
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
const int MAXN = 2005;//最多有1000对夫妻 拆开就是2000人
const int MAXM = 4000040;

int dfn[MAXN],low[MAXN];
int st[MAXN],top;
int color,Time;
int col[MAXN];
bool instack[MAXN];
int n,m;

int head[MAXN];
int Next[MAXM];
int to[MAXM];
int cnt=1;

void init(){
    cnt=1;
    color=0;
    Time=0;
    top=0;
    memset(dfn,0,sizeof(dfn));
    memset(low,0,sizeof(low));
    memset(head,0,sizeof(head));
    memset(col,0,sizeof(col));
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
    cin.tie(nullptr)->sync_with_stdio(false);
    while(cin>>n>>m){
        init();
        for(int i=1;i<=m;i++){
            int a1,a2,c1,c2;
            cin>>a1>>a2>>c1>>c2;
            // 对于第 i 对夫妇，我们用 2i+1 表示丈夫，2i 表示妻子。
            addedge(2*a1+c1,2*a2+1-c2);
            addedge(2*a2+c2,2*a1+1-c1);
        }
        for(int i=0;i<2*n;i++){
            if(!dfn[i]){
                tarjan(i);
            }
        }
        bool flag=true;
        for(int i=0;i<2*n;i+=2){
            if(col[i]==col[i+1]){
                //如果夫妻是一个颜色 一定不对
                flag=false;
                cout<<"NO"<<endl;
                break;
            }
        }
        if(flag)
            cout<<"YES"<<endl;
    }
    return 0;
}
