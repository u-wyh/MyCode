// 选课
// 在大学里每个学生，为了达到一定的学分，必须从很多课程里选择一些课程来学习
// 在课程里有些课程必须在某些课程之前学习，如高等数学总是在其它课程之前学习
// 现在有 N 门功课，每门课有个学分，每门课有一门或没有直接先修课
// 若课程 a 是课程 b 的先修课即只有学完了课程 a，才能学习课程 b
// 一个学生要从这些课程里选择 M 门课程学习
// 问他能获得的最大学分是多少
// 测试链接 : https://www.luogu.com.cn/problem/P2014
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法
// 提交以下的code，提交时请把类名改成"Main"，可以直接通过
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 301;

int n,m;
int nums[MAXN];
vector<vector<int>>graph;
int dp[MAXN][MAXN][MAXN];

int f(int i, int j, int k) {
    if (k == 0) {
        //表示没有名额了
        return 0;
    }
    if (j == 0 || k == 1) {
        //没有子树  那么就只能选择头结点了
        //或者只有一个指标 那么只能给头结点  这是为了保证选的点是连成一片的
        return nums[i];
    }
    if (dp[i][j][k] != -1) {
        //如果以前被选过
        return dp[i][j][k];
    }
    int ans = f(i, j - 1, k);//第一种情况  最后一棵子树不选
    // 第j棵子树头节点v
    int v = graph[i][j - 1];
    for (int s = 1; s < k; s++) {
        ans = max(ans, f(i, j - 1, k - s) + f(v, graph[v].size(), s));
    }
    //最后一棵子树可以选择1到k-1  至少留一个给连接点
    //那么就是最后一棵子树的学分加上前面的学分
    dp[i][j][k] = ans;
    return ans;
}
// 当前来到i号节点为头的子树
// 只在i号节点、及其i号节点下方的前j棵子树上挑选节点
// 一共挑选k个节点，并且保证挑选的节点连成一片
// 返回最大的累加和

int main()
{
    cin>>n>>m;
    //注意这道题下标从1开始  但是有虚拟源点0
    m+=1;//建立一个必选的虚拟源点0   所以多加一个选课
    graph.resize(MAXN);
    for(int i=1;i<=n;i++){
        int pre;
        cin>>pre;
        graph[pre].push_back(i);
        cin>>nums[i];
    }
    //建图
    for(int i=0;i<MAXN;i++){
        for(int j=0;j<MAXN;j++){
            for(int k=0;k<MAXN;k++){
                dp[i][j][k]=-1;
            }
        }
    }
    //完成初始化
    cout<<f(0, graph[0].size(), m);

    return 0;
}
