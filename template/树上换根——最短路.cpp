// 聚会后送每个人回家最短用时
// 给定一棵n个点的树，边权代表走过边需要花费的时间
// 给定k个人分别在树上的哪些节点
// 这k个人选择了一个聚会点，所有的人都去往聚会点进行聚会
// 聚会结束后，所有人都会上一辆车，车会把每个人送回家
// 送完最后一个乘客，车不需要回到聚会点
// 如果聚会点在i，请问从聚会地点出发直到送最后一个人回家，最短用时多少
// i = 1 ~ n，打印所有的答案
// 测试链接 : https://www.luogu.com.cn/problem/P6419
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有用例

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;

int n,k;
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int cnt=1;
// people[i]: i内部，有多少乘客要送
int people[MAXN];
// incost[i]: i内部，从i出发送完所有乘客回到i的最少代价
long incost[MAXN];
// inner1[i]: i内部，从i出发送乘客的最长链
long inner1[MAXN];
// inner2[i]: i内部，从i出发送乘客的次长链
long inner2[MAXN];
// 注意 : inner1[i]和inner2[i]所代表的链，一定要来自i的不同儿子
// choose[i]: 送乘客的最长链来自i的哪个儿子
int choose[MAXN];
// outcost[i]: i外部，从i出发送完所有乘客回到i的最少代价
long outcost[MAXN];
// outer[i]: i外部，从i出发送乘客的最长链
long outer[MAXN];

void dfs1(int u, int f) {
    for (int e = head[u], v, w; e != 0; e = Next[e]) {
        v = to[e];
        w = weight[e];
        if (v != f) {
            dfs1(v, u);
            people[u] += people[v];
            if (people[v] > 0) {
                //实际上是一个剪枝操作
                incost[u] += incost[v] + (long) w * 2;
                if (inner1[u] < inner1[v] + w) {
                    choose[u] = v;
                    inner2[u] = inner1[u];
                    inner1[u] = inner1[v] + w;
                } else if (inner2[u] < inner1[v] + w) {
                    inner2[u] = inner1[v] + w;
                }
            }
        }
    }
}

void dfs2(int u, int f) {
    for (int e = head[u], v, w; e != 0; e = Next[e]) {
        v = to[e];
        w = weight[e];
        if (v != f) {
            if (k - people[v] > 0) {
                if (people[v] == 0) {
                    outcost[v] = outcost[u] + incost[u] + (long) w * 2;
                } else {
                    outcost[v] = outcost[u] + incost[u] - incost[v];
                }
                if (v != choose[u]) {
                    outer[v] = max(outer[u], inner1[u]) + w;
                } else {
                    outer[v] = max(outer[u], inner2[u]) + w;
                }
            }
            dfs2(v, u);
        }
    }
}

int main()
{
    cin>>n>>k;
    for(int i=1,u,v,w;i<n;i++){
        cin>>u>>v>>w;

        Next[cnt]=head[u];
        to[cnt]=v;
        weight[cnt]=w;
        head[u]=cnt++;

        Next[cnt]=head[v];
        to[cnt]=u;
        weight[cnt]=w;
        head[v]=cnt++;
    }
    for(int i=1,u;i<=k;i++){
        cin>>u;
        people[u]++;
    }
    dfs1(1,0);
    dfs2(1,0);
    for (int i = 1; i <= n; i++) {
        cout<<(incost[i] + outcost[i] - max(inner1[i], outer[i]))<<endl;
    }
    return 0;
}

