#include<bits/stdc++.h>
using namespace std;
const int MAXN =105;

int n,m;
int graph[MAXN][MAXN];
//邻接表
int Time=1;
//建立时间戳
int dfn[MAXN];
int low[MAXN];
int fa[MAXN];
//分别是每个节点的参数
int point[MAXN];//割点
int bridge[1000][2];
int cnt=1;

void dfs(int x){
    dfn[x]=Time;
    low[x]=Time++;
    int child=0;
    //dfn数组一经赋值  便不再改变
    //low数组值是什么其实不重要  他只有发生改变或者没有改变这一个有用的信息
    for(int k=1;k<=n;k++){
        if(graph[x][k]){
            //他只可以访问自己能到达的点
            if(!dfn[k]){
                child++;
                fa[k]=x;
                //可以看出它是先访问下一个节点  后来赋值自己  第二种dfs
                dfs(k);
                if(fa[x]==0&&child>=2){
                    point[x]=1;
                }
                if(fa[x]!=0&&low[k]>=dfn[x]){
                    point[x]=1;
                }
                if(low[k]>dfn[x]){
                    bridge[cnt][0]=x;
                    bridge[cnt++][1]=k;
                }
                low[x]=min(low[x],low[k]);
                //因为y没有被访问过  所以先dfs(y)  此时y的low已经被赋值   并且如果发生了修正  那么也已经完成
            }else if(k=fa[x]){
                //那么说明y一定在x之前访问  必然形成一个环
                low[x]=min(low[x],dfn[k]);
            }
            //剩下的那种情况是既已经被访问过  也不在栈中
        }
    }
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        graph[u][v]=1;
    }
    //完成邻接表的初始化
    for(int i=1;i<=n;i++){
        if(!dfn[i]){
            //如果没有被访问到才会进入dfs
            dfs(i);
        }
    }
    for(int i=1;i<=n;i++){
        if(point[i]!=0){
            printf("%3d",i);
        }
    }
    cout<<endl;
    for(int i=1;i<=cnt;i++){
        printf("%d %d\n",bridge[i][0],bridge[i][1]);
    }
    return 0;
}

