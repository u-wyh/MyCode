// 平衡行为
// 一共有n个节点，编号1~n，有n-1条边形成一棵树
// 返回重心点，返回重心点最大子树的节点数
// 树的重心第一种求解方式
// 以某个节点为根时，最大子树的节点数最少，那么这个节点是重心
// 测试链接 : http://poj.org/problem?id=1655
// 提交以下的code，提交时请把类名改成"Main"，可以直接通过
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 10005;
const int MAXM = 100005;

int head[MAXN];
int Next[MAXM];
int to[MAXM];
int cnt=1;
int sz[MAXN];
//记录以某个节点为边的时候子树所有节点大小
int center=0,best=INT_MAX;
//首先将重心位置 和  最大子树初始化
int n;
//一共有n个节点  n-1条边

void dfs(int u,int f){
    sz[u] = 1;
    // 以当前节点u做根节点，最大的子树有多少节点
    int maxsub = 0;
    //记录最大子树大小
    for (int e = head[u], v; e != 0; e = Next[e]) {
        v = to[e];
        if (v != f) {
            dfs(v, u);
            sz[u] += sz[v];
            maxsub = max(maxsub, sz[v]);
        }
    }
    //到了这里 maxsub求的是他的孩子节点为根的子树大小最大值
    maxsub = max(maxsub, n - sz[u]);
    //n-sz[u]表示的是以当前u为根  他的父亲节点子树逆向最大值（即父亲为根  爷爷为父亲的子节点）
    // 题目要求找到编号最小的重心
    if (maxsub < best || (maxsub == best && u < center)) {
        best = maxsub;
        center = u;
    }
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
    cout<<center;
    return 0;
}
//第一种判断方法：最大子树节点最少
