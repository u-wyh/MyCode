// 相邻字符不同的最长路径
// 给你一棵 树（即一个连通、无向、无环图），根节点是节点 0
// 这棵树由编号从 0 到 n - 1 的 n 个节点组成
// 用下标从 0 开始、长度为 n 的数组 parent 来表示这棵树
// 其中 parent[i] 是节点 i 的父节点
// 由于节点 0 是根节点，所以 parent[0] == -1
// 另给你一个字符串 s ，长度也是 n ，其中 s[i] 表示分配给节点 i 的字符
// 请你找出路径上任意一对相邻节点都没有分配到相同字符的 最长路径
// 并返回该路径的长度
// 测试链接 : https://leetcode.cn/problems/longest-path-with-different-adjacent-characters/
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100005;

struct Info {
    int maxPathFromHead; // 一定要从头节点出发的情况下，相邻字符不等的最长路径长度
    int maxPath; // 整棵树上，相邻字符不等的最长路径长度

    Info(int a, int b) {
        maxPathFromHead = a;
        maxPath = b;
    }
};
int parent[MAXN];
char s[MAXN];
int n;
vector<vector<int>>graph;

Info f(int u) {
    if (graph[u].empty()) {
        // u节点是叶
        return Info(1, 1);//如果没有子节点的话  那么 最长 和 为首最长 均为1
    }
    int max1 = 0; // 下方最长链
    int max2 = 0; // 下方次长链
    int maxPath = 1;
    for (int i=0;i<graph[u].size();i++) {
        int v=graph[u][i];//下一个子节点
        Info nextInfo = f(v);//完成递归
        maxPath = max(maxPath, nextInfo.maxPath);
        if (s[u] != s[v]) {
            if (nextInfo.maxPathFromHead > max1) {
                max2 = max1;
                max1 = nextInfo.maxPathFromHead;
            } else if (nextInfo.maxPathFromHead > max2) {
                max2 = nextInfo.maxPathFromHead;
            }
        }
    }
    int maxPathFromHead = max1 + 1;
    maxPath = max(maxPath, max1 + max2 + 1);
    return Info(maxPathFromHead, maxPath);//返回当前值
}

int main()
{
    cin>>n;
    graph.resize(n+1);
    for(int i=1;i<=n;i++){
        cin>>parent[i];
    }
    for(int i=1;i<=n;i++){
        cin>>s[i];
    }
    for (int i = 1; i < n; i++) {
        if(parent[i]==-1)
            continue;
        graph[parent[i]].push_back(i);
    }
    //建图
    cout<<f(0).maxPath;
    //输出整棵树的最大值
    return 0;
}
