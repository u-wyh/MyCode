#include <bits/stdc++.h>
using namespace std;

int maps[151][151];//邻接矩阵，简单易懂
struct Edge {
    int x,y;
} E[5001];//这是存答案的，用邻接表存，应该不用解释
int dfn[151],low[151],n,m,id,cnt,f[151];
/*
这些数组的含义：
dfn:{下标：点编号     内存的值：深度优先搜索时第几个遍历}
low:{下标：点编号     内存的值：这个点能通过它的子孙到达的dfn值最小的点的dfn}
f:{下标：点标号       内存的值：它遍历的上一个点}
变量的含义：n:结点个数        m:边个数       id:用于dfn标记      cnt:用于邻接表存图
*/
bool cmp(Edge a,Edge b) {
    if(a.x==b.x)return a.y<b.y;
    return a.x<b.x;
}//因题目要求，边要排序

void addEdge(int x,int y) {
    E[++cnt].x=x;
    E[cnt].y=y;
}//addedge函数，存入邻接表

void tarjan(int x) {
    int c=0,y;
    dfn[x]=low[x]=++id;
    for(int i=1; i<=n; i++) {
        if(!maps[x][i])continue;//首先要有边
        y=i;//处理对象
        if(dfn[y]&&y!=f[x])
            low[x]=min(low[x],dfn[y]);//如果是它爸爸，割边就没有用了，好好理解
        if(!dfn[y]) {//如果找到祖先还有什么用呢
            f[y]=x;//不是祖先就认爸爸
            tarjan(y);//dfs过程
            low[x]=min(low[x],low[y]);//回溯时带着爸爸更新low
            if(low[y]>dfn[x])
                addEdge(x,y);//是割边，就加入吧
        }
    }
}//tarjan部分，证明在下面
int main() {
    int x,y;
    cin>>n>>m;
    for(register int i=1; i<=m; i++) {
        cin>>x>>y;
        maps[x][y]=maps[y][x]=1;//存边
    }
    for(register int i=1; i<=n; i++) {
        if(!dfn[i])
            tarjan(i);//tarjan
    }
    sort(E+1,E+cnt+1,cmp);//sort大法好
    for(register int i=1; i<=cnt; i++) {
        cout<<min(E[i].x,E[i].y)<<' '<<max(E[i].x,E[i].y)<<endl;//输出
    }
    return 0;//程序结束了，证明开始了
}
