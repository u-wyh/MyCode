// Bellman-Ford算法应用（不是模版）
// k站中转内最便宜的航班
// 有 n 个城市通过一些航班连接。给你一个数组 flights
// 其中 flights[i] = [fromi, toi, pricei]
// 表示该航班都从城市 fromi 开始，以价格 pricei 抵达 toi。
// 现在给定所有的城市和航班，以及出发城市 src 和目的地 dst，你的任务是找到出一条最多经过 k 站中转的路线
// 使得从 src 到 dst 的 价格最便宜 ，并返回该价格。 如果不存在这样的路线，则输出 -1。
// 测试链接 : https://leetcode.cn/problems/cheapest-flights-within-k-stops/
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 101;
const int MAXM = 10001;

int n,m,k,st,en;
//一共有n个站点  有m条路线相连   最多可以中转k个
//从st到en
int cur[MAXN],Next[MAXN];
//Next是一个辅助数组  作用下面说
int edge[MAXM][3];
//在Bellman算法中  我们不需要建立邻接矩阵 邻接表等等
//我们是根据路线的条数进行区分的

int main()
{
    cin>>n>>m>>k>>st>>en;
    for(int i=1;i<=n;i++){
        cur[i]=INT_MAX;
    }
    cur[st]=0;
    //cur数组记录的是每个点到st的距离  初始化为正无穷
    for(int i=1;i<=m;i++){
        cin>>edge[i][0]>>edge[i][1]>>edge[i][2];
    }
    for(int i=0;i<=k;i++){
        for(int j=1;j<=n;j++){
            Next[j]=cur[j];
        }
        //我们要建立Next数组  因为存在一种可能性  就是在一轮优化中  同时实现了两个点  这样不利于我们统计k
        for(int j=1;j<=m;j++){
            if (cur[edge[j][0]] != INT_MAX) {
                //如果不是正无穷  说明可以到达edge[j][0]  那么可以继续尝试优化下一个edge[j][1]
                Next[edge[j][1]] = min(Next[edge[j][1]], cur[edge[j][0]] + edge[j][2]);
                //这一轮到达edge[j][1] 的距离是原来的值  和  到达edge[j][0]的值加上从edge[j][0]到edge[j][1]
            }
        }
        //如果修改值的话，从cur数组中拿数字
        for(int j=1;j<=n;j++){
            cur[j]=Next[j];
        }
        //将cur更新为Next数组
    }
    if(cur[en]==INT_MAX){
        cur[en]=-1;
    }
    cout<<cur[en];
    return 0;
}

