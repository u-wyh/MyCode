#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1000005;
const int LIMIT = 20;

int n,m,root;
int log_2[MAXN];
int head[MAXN];
int Next[MAXN];
int to[MAXN];
int cnt=1;
int deep[MAXN],stjump[MAXN][LIMIT];
struct node{
    int u,f,e;
};
stack<node>st;
// 栈里存放三个信息
// u : 当前处理的点
// f : 当前点u的父节点
// e : 处理到几号边了
// 如果e==-1，表示之前没有处理过u的任何边
// 如果e==0，表示u的边都已经处理完了

void build(){
    log_2[0]=-1;
    for(int i=1;i<=n;i++){
        log_2[i]=log_2[i>>1]+1;
    }
}

void dfs(){
    st.push({root,0,-1});
    while (!st.empty()) {
        node cur=st.top();
        st.pop();
        if (cur.e == -1) {
            //说明这是第一次访问  那么直接就要建立好deep  stjump
            deep[cur.u] = deep[cur.f] + 1;
            stjump[cur.u][0] = cur.f;
            for (int p = 1; p <= log_2[n]; p++) {
                stjump[cur.u][p] = stjump[stjump[cur.u][p - 1]][p - 1];
            }
            cur.e = head[cur.u];
        } else {
            //否则到下一条边
            cur.e = Next[cur.e];
        }
        if (cur.e != 0) {
            //说明还有边
            st.push({cur.u, cur.f, cur.e});
            if (to[cur.e] != cur.f) {
                st.push({to[cur.e], cur.u, -1});
                //加入子节点
            }
        }
    }
}

int lca(int a, int b) {
    if (deep[a] < deep[b]) {
        int tmp = a;
        a = b;
        b = tmp;
    }
    //确定大小关系
    for (int p = log_2[n]; p >= 0; p--) {
        if (deep[stjump[a][p]] >= deep[b]) {
            a = stjump[a][p];
        }
    }
    //首先将两者变为同一高度
    if (a == b) {
        return a;
    }
    //如果相同说明就是祖先关系
    for (int p = log_2[n]; p >= 0; p--) {
        if (stjump[a][p] != stjump[b][p]) {
            a = stjump[a][p];
            b = stjump[b][p];
        }
        //判断跳完后是否符合规则
    }
    return stjump[a][0]==0?root:stjump[a][0];
}

int main()
{
    cin>>n>>m>>root;
    build();
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;

        Next[cnt]=head[u];
        to[cnt]=v;
        head[u]=cnt++;

        Next[cnt]=head[v];
        to[cnt]=u;
        head[v]=cnt++;

    }
    //建树
    dfs();
    for(int i=1,u,v;i<=m;i++){
        cin>>u>>v;
        cout<<lca(u,v)<<endl;
    }
    return 0;
}
