// 从树中删除边的最小分数
// 存在一棵无向连通树，树中有编号从0到n-1的n个节点，以及n-1条边
// 给你一个下标从0开始的整数数组nums长度为n，其中nums[i]表示第i个节点的值
// 另给你一个二维整数数组edges长度为n-1
// 其中 edges[i] = [ai, bi] 表示树中存在一条位于节点 ai 和 bi 之间的边
// 删除树中两条不同的边以形成三个连通组件，对于一种删除边方案，定义如下步骤以计算其分数：
// 分别获取三个组件每个组件中所有节点值的异或值
// 最大 异或值和 最小 异或值的 差值 就是这种删除边方案的分数
// 返回可能的最小分数
// 测试链接 : https://leetcode.cn/problems/minimum-score-after-removals-on-a-tree/
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1001;

// 下标为原始节点编号
int dfn[MAXN];
// 下标为dfn序号
int eor[MAXN];
// 下标为dfn序号
int sz[MAXN];
int dfnCnt=0;
int edges[MAXN][2];
vector<vector<int>>graph;
int nums[MAXN];
int n;

void f(int u) {
    int i = ++dfnCnt;
    dfn[u] = i;
    eor[i] = nums[u];
    sz[i] = 1;
    for (int j=0;j<graph[u].size();j++) {
        int v=graph[u][j];
        if (dfn[v] == 0) {
            //表示这个点是以前没有访问过的  不需要准备一个父节点
            f(v);
            eor[i] ^= eor[dfn[v]];
            sz[i] += sz[dfn[v]];
        }
    }
}
//生成dfn  sz  deep 数组

int main()
{
    cin>>n;

    for(int i=1;i<=n;i++){
        cin>>nums[i];
    }
    graph.resize(n+1);
    for(int i=1;i<n;i++){
        cin>>edges[i][0]>>edges[i][1];
        graph[edges[i][0]].push_back(edges[i][1]);
        graph[edges[i][1]].push_back(edges[i][0]);
    }
    //建立双向图
    //注意我们这里使用的都是从下标1开始  没有下标0

    f(1);//我们第一个点直接强制定义为1
    int ans = INT_MAX;
    for (int i = 1, a, b, pre, pos, sum1, sum2, sum3; i < n-1; i++) {
        a = max(dfn[edges[i][0]], dfn[edges[i][1]]);//第一条边的端点dfn最大值
        for (int j = i + 1; j < n; j++) {
            //枚举每两条边
            b = max(dfn[edges[j][0]], dfn[edges[j][1]]);//第二条边的端点dfn最大值
            if (a < b) {
                pre = a;
                pos = b;
            } else {
                pre = b;
                pos = a;
            }
            //将较小的那个设置为pre
            sum1 = eor[pos];
            // xor[1] : 整棵树的异或和
            // 因为头节点是0，一定拥有最小的dfn序号1
            // f函数调用的时候，也是从0节点开始的
            if (pos < pre + sz[pre]) {
                //如果这两个点是包含关系
                sum2 = eor[pre] ^ eor[pos];
                sum3 = eor[1] ^ eor[pre];
            } else {
                sum2 = eor[pre];
                sum3 = eor[1] ^ sum1 ^ sum2;
            }
            ans = min(ans, max(max(sum1, sum2), sum3) - min(min(sum1, sum2), sum3));
        }
    }
    cout<<ans;
    return 0;
}
