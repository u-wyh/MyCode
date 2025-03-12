// Prim算法模版（洛谷）
// 动态空间实现
// 测试链接 : https://www.luogu.com.cn/problem/P3366
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法
// 提交以下所有代码，把主类名改成Main，可以直接通过
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5001;
const int MAXM = 200005;

auto compare = [](const pair<int, int>& left, const pair<int, int>& right) {
    return left.second > right.second; // 注意这里是大于，因为我们想要小根堆
};

priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(compare)> heap(compare);
//初始化建立小根堆
vector<vector<pair<int ,int >>>graph;
//无向带权图  所以用到了pair
int n,m;
bool Set[MAXN];
//记录当前节点是否被访问

int main()
{
    cin>>n>>m;
    graph.resize(n+1);
    for(int i=1,u,v,w;i<=m;i++){
        cin>>u>>v>>w;
        graph[u].push_back({v,w});
        graph[v].push_back({u,w});
    }
    //初始化建图
    for(int i=0;i<graph[1].size();i++){
        heap.push(graph[1][i]);
    }
    Set[1]=true;
    //任意选择一个起点  我们选择的是1
    int nodecnt=1;
    int ans=0;
    //nodecnt记录有多少点被记录  ans用于记录最终答案
    while(!heap.empty()){
        int Next=heap.top().first;
        int cost=heap.top().second;
        //next是下一个节点  cost是这条边的权值
        heap.pop();
        if (!Set[Next]) {
            //如果这个节点没有被访问  继续
            nodecnt++;
            Set[Next] = true;
            ans += cost;
            for (int i=0;i<graph[Next].size();i++) {
                heap.push(graph[Next][i]);
            }
            //将他的所有边加入小根堆
        }
    }

    if(nodecnt==n){
        cout<<ans;
    }else{
        cout<<"orz";
    }
    return 0;
}

