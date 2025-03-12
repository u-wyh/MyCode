// 教父
// 一共有n个节点，编号1~n，有n-1条边形成一棵树
// 返回所有重心点
// 树的重心第二种求解方式
// 以某个节点为根时，每颗子树的节点数不超过总节点数的一半，那么这个节点是重心
// 测试链接 : http://poj.org/problem?id=3107
// 提交以下的code，提交时请把类名改成"Main"，可以直接通过
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
const int MAXM = 1000005;

int head[MAXN];
int Next[MAXM];
int to[MAXM];
int cnt=1;
int sz[MAXN];
//记录以某个节点为边的时候子树所有节点大小
int maxsize[MAXN];
//记录以某个节点为根节点的时候最大子树大小
int n;
//一共有n个节点  n-1条边

void dfs(int u,int f){
    sz[u] = 1;
    // 以当前节点u做根节点，最大的子树有多少节点
    maxsize[u] = 0;
    //记录最大子树大小
    for (int e = head[u], v; e != 0; e = Next[e]) {
        v = to[e];
        if (v != f) {
            dfs(v, u);
            sz[u] += sz[v];
            maxsize[u]=max(maxsize[u],sz[v]);
        }
    }
    maxsize[u] = max(maxsize[u], n - sz[u]);
}

int main()
{
    cin>>n;
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
    dfs(1,0);
    for(int i=1;i<=n;i++){
        if(maxsize[i]<=n/2){
            cout<<i<<' ';
        }
        //最多不会超过两个
    }
    return 0;
}
//第二种方式：所有子树节点不超过总数的一半
