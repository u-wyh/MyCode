// 电动车游城市
// 小明的电动车电量充满时可行驶距离为 cnt，每行驶 1 单位距离消耗 1 单位电量，且花费 1 单位时间
// 小明想选择电动车作为代步工具。地图上共有 N 个景点，景点编号为 0 ~ N-1
// 他将地图信息以 [城市 A 编号,城市 B 编号,两城市间距离] 格式整理在在二维数组 paths，
// 表示城市 A、B 间存在双向通路。
// 初始状态，电动车电量为 0。每个城市都设有充电桩，
// charge[i] 表示第 i 个城市每充 1 单位电量需要花费的单位时间。
// 请返回小明最少需要花费多少单位时间从起点城市 start 抵达终点城市 end
// 测试链接 : https://leetcode.cn/problems/DFPeFJ/
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 105;
const int MAXM = 205;
const int MAXCNT = 105;

struct Range {
    int cur,power,cost;
};
// 比较函数，用于小根堆，当 l 值相等时，可以通过添加额外的比较来保持稳定性
bool compare(const Range& a, const Range& b) {
    return a.cost > b.cost; // 注意这里是大于号，因为我们要使用 greater<> 来获得小根堆
}
priority_queue<Range, vector<Range>, decltype(&compare)> heap(compare);
//建立小根堆
// cur : 当前点
// power : 来到当前点的电量
// cost : 花费时间
int n,m;
int edge[MAXM][3];
vector<vector<pair<int ,int >>>graph;
//建立图  无向图
int st,en,cnt;
int charge[MAXN];
int dis[MAXN][MAXCNT];
bool visited[MAXN][MAXCNT];
//判断当前位置  当前状态是否被访问过

int main()
{
    cin>>n>>m>>st>>en>>cnt;
    //输入城市数目  道路数目  开始以及结束位置  油箱最大容积
    graph.resize(n);
    for(int i=1;i<=m;i++){
        cin>>edge[i][0]>>edge[i][1]>>edge[i][2];
        graph[edge[i][0]].push_back({edge[i][1],edge[i][2]});
        graph[edge[i][1]].push_back({edge[i][0],edge[i][2]});
    }
    //建立无向图
    for(int i=0;i<n;i++){
        cin>>charge[i];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= cnt; j++) {
            dis[i][j] = INT_MAX;
        }
    }
    //初始化dis数组

    dis[st][0] = 0;
    heap.push({ st, 0, 0 });
    //将起始点压入堆中
    while (!heap.empty()) {
        Range record = heap.top();
        heap.pop();
        int cur = record.cur;
        int power = record.power;
        int cost = record.cost;
        if (visited[cur][power]) {
            continue;
        }
        visited[cur][power] = true;
        if (cur == en) {
            // 常见剪枝
            // 发现终点直接返回
            // 不用等都结束
            cout<<cost;
            return 0;
        }
        if (power < cnt) {
            // 充一格电
            // cur, power+1
            if (!visited[cur][power + 1] && cost + charge[cur] < dis[cur][power + 1]) {
                dis[cur][power + 1] = cost + charge[cur];
                heap.push({ cur, power + 1, cost + charge[cur] });
            }
        }
        for (int i=0;i<graph[cur].size();i++) {
        // 不充电去别的城市
            int nextCity = graph[cur][i].first;
            int restPower = power - graph[cur][i].second;
            int nextCost = cost + graph[cur][i].second;
            if (restPower >= 0 && !visited[nextCity][restPower] && nextCost < dis[nextCity][restPower]) {
                //如果电量足以支撑到达下一个城市  并且下一个城市的这个状态没有被访问过   并且用电量少于当前  才可以
                dis[nextCity][restPower] = nextCost;
                heap.push({ nextCity, restPower, nextCost });
            }
        }
    }
    cout<<-1;
    return 0;
}
