// k短路问题，可持久化左偏树实现最优解，C++版
// 有n个点编号1~n，有m条边，每条边都是正数边权，组成有向带权图
// 从1号点走到n号点，就认为是一次旅行
// 一次旅行中，边不能重复选，点可以重复经过，如果到达了n号点，那么旅行立刻停止
// 从1号点走到n号点，会有很多通路方案，通路方案的路费为选择边的边权累加和
// 虽然每次旅行都是从1号点到n号点，但是你希望每次旅行的通路方案都是不同的
// 任何两次旅行，只要选择的边稍有不同，就认为是不同的通路方案
// 你的钱数为money，用来支付路费，打印你一共能进行几次旅行
// 测试链接 : https://www.luogu.com.cn/problem/P2483
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 50001;//点的个数
const int MAXM = 200001;//边的个数
const int MAXT = 1000001;//可持久化左偏树的节点个数
const int MAXH = 4200001;
const double INF = 1e18;

int n, m;
double money;

// 关于正反图有一个非常值得注意的地方
// 如果正图中，a到b的边，编号为x
// 那么反图中，b到a的边，编号也是x
// 因为每一条边，正图建立的同时，反图也同步建立
// 所以正反图中这条边分配的编号也是一样的
// 正图
int headg[MAXN];
int tog[MAXM];
int nextg[MAXM];
double weightg[MAXM];
int cntg = 0;

// 反图
int headr[MAXN];
int tor[MAXM];
int nextr[MAXM];
double weightr[MAXM];
int cntr = 0;

// 左偏树代表基于之前的通路方案，选择非树边的可能性
// 左偏树的头就代表最优的选择，假设编号为h的节点是头
// to[h] : 选择最优非树边，这个非树边在正图里指向哪个节点
int to[MAXT];
// cost[h] : 基于之前的通路方案，最优选择会让路费增加多少
double cost[MAXT];
int ls[MAXT];
int rs[MAXT];
int dist[MAXT];
int cntt = 0;

// rt[u] : 在最短路树上，节点u及其所有祖先节点，所拥有的全部非树边，组成的左偏树
int rt[MAXN];

// heap是经典的小根堆，放着很多(key, val)数据，根据val来组织小根堆
//key val是用于存储数据  heap里面是编号  cntd是数据大小 cnth是堆大小
int key[MAXH];
double val[MAXH];
int heap[MAXH];
int cntd, cnth;

// dijkstra算法需要，根据反图跑dijkstra，生成从节点n开始的最短路树
// vis[u] : 节点u到节点n的最短距离，是否已经计算过了
bool vis[MAXN];
// path[u] : 最短路树上，到达节点u的树边，编号是什么，也代表正图上，所对应的边
int path[MAXN];
// dis[u] : 最短路树上，节点n到节点u的最短距离
double dis[MAXN];

void addEdgeG(int u, int v, double w){
    nextg[++cntg] = headg[u];
    tog[cntg] = v;
    weightg[cntg] = w;
    headg[u] = cntg;
}

void addEdgeR(int u, int v, double w){
    nextr[++cntr] = headr[u];
    tor[cntr] = v;
    weightr[cntr] = w;
    headr[u] = cntr;
}

int init(int t, double v){
    to[++cntt] = t;
    cost[cntt] = v;
    ls[cntt] = rs[cntt] = dist[cntt] = 0;
    return cntt;
}

int clone(int i){
    to[++cntt] = to[i];
    cost[cntt] = cost[i];
    ls[cntt] = ls[i];
    rs[cntt] = rs[i];
    dist[cntt] = dist[i];
    return cntt;
}

int merge(int i, int j){
    if(i == 0 || j == 0){
        return i + j;
    }
    if(cost[i] > cost[j]){
        swap(i, j);
    }
    int h = clone(i);
    rs[h] = merge(rs[h], j);
    if(dist[ls[h]] < dist[rs[h]]){
        swap(ls[h], rs[h]);
    }
    dist[h] = dist[rs[h]] + 1;
    return h;
}

// (k, v)组成一个数据，放到堆上，根据v来组织小根堆
void heapAdd(int k, double v){
    key[++cntd] = k;
    val[cntd] = v;
    heap[++cnth] = cntd;
    int cur = cnth, father = cur / 2;
    while(cur > 1 && val[heap[father]] > val[heap[cur]]){
        swap(heap[father], heap[cur]);
        cur = father;
        father = cur / 2;
    }
}

// 小根堆上，堆顶的数据(k, v)弹出，并返回数据所在的下标ans
// 根据返回值ans，key[ans]得到k，val[ans]得到v
int heapPop(){
    int ans = heap[1];
    heap[1] = heap[cnth--];
    int cur = 1, l = cur * 2, r = l + 1, best;
    while(l <= cnth){
        best = r <= cnth && val[heap[r]] < val[heap[l]] ? r : l;
        best = val[heap[best]] < val[heap[cur]] ? best : cur;
        if(best == cur) {
            break;
        }
        swap(heap[best], heap[cur]);
        cur = best;
        l = cur * 2;
        r = l + 1;
    }
    return ans;
}

bool heapEmpty(){
    return cnth == 0;
}

// 根据反图跑dijkstra算法
// 得到从节点n出发的最短路树、每个节点到节点n的最短距离信息
// 最短路树如果有多个，找到任何一个即可
void dijkstra(){
    fill(dis, dis + MAXN, INF);
    dis[n] = 0;
    cntd = cnth = 0;
    heapAdd(n, 0.0);//相当于heap.push({n,0})
    while(!heapEmpty()){
        int top = heapPop();
        int u = key[top];
        double w = val[top];
        if(!vis[u]){
            vis[u] = true;
            for(int e = headr[u], v; e != 0; e = nextr[e]){
                v = tor[e];
                if(dis[v] > w + weightr[e]){
                    dis[v] = w + weightr[e];
                    path[v] = e;//不断更新 直到无法变化的就是正确答案
                    heapAdd(v, dis[v]);
                }
            }
        }
    }
}

// 在最短路树上的每个节点，生成自己的左偏树
// 节点u的左偏树 = 节点u自己的非树边左偏树 + 节点u在最短路树上的父亲的左偏树
// 课上重点解释了这么做的意义
//因为每次新建该节点的左偏树时候  后续节点要已经建好
//所以建立左偏树的顺序很重要 所以我们可以根据到n的距离排序建树
void mergeRoad(){
    cntd = cnth = 0;//清空手写堆
    for(int i = 1; i <= n; i++){
        heapAdd(i, dis[i]);
    }
    dist[0] = -1;
    while(!heapEmpty()){
        int top = heapPop();
        int u = key[top];
        for(int e = headg[u], v; e != 0; e = nextg[e]){
            // path[u]既是边在反图中的编号，也是边在正图中的编号
            // 因为正反图同步建立，边的正图编号 == 边的反图编号
            v = tog[e];
            if(e != path[u]){
                rt[u] = merge(rt[u], init(v, weightg[e] + dis[v] - dis[u]));
                //新建信息包括 to 和 影响
            }
        }
        if(path[u] != 0){
            rt[u] = merge(rt[u], rt[tog[path[u]]]);//和自己的祖先合并
        }
    }
}

// 从路费第1小的方案开始，逐渐找到第2小、第3小...
// 看看money能够覆盖几次旅行，返回旅行的次数
int expand(){
    int ans = 0;
    money -= dis[1];
    if(money >= 0){
        //说明至少可以满足第一次的花费  那么继续
        ans++;
        cntd = cnth = 0;//开始往堆里放数据
        if(rt[1] != 0){
            // 开始阶段
            // 1号节点左偏树的堆顶，代表增加代价最小的非树边，放入决策堆
			// 目前路通方案的路费，同步放入
            heapAdd(rt[1], dis[1] + cost[rt[1]]);
        }
        while(!heapEmpty()){
            int top = heapPop();
            int h = key[top];
            double w = val[top];
            money -= w;
            if(money < 0){
                break;
            }
            ans++;
            // 当前选择的非树边，被左偏树上的左儿子替换
            if(ls[h] != 0){
                heapAdd(ls[h], w - cost[h] + cost[ls[h]]);
            }
            // 当前选择的非树边，被左偏树上的右儿子替换
            if(rs[h] != 0){
                heapAdd(rs[h], w - cost[h] + cost[rs[h]]);
            }
            // 当前选择的非树边，指向节点to[h]，那么从to[h]的左偏树里，新增一个最优的非树边
            if(to[h] != 0 && rt[to[h]] != 0){
                heapAdd(rt[to[h]], w + cost[rt[to[h]]]);
            }
        }
    }
    return ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m >> money;
    int u, v;
    double w;
    for(int i = 1; i <= m; i++){
        cin >> u >> v >> w;
        // 题目说了，一旦到达节点n，旅行立刻停止
        // 所以从节点n出发的边，一律忽略
        if(u != n){
            addEdgeG(u, v, w);//建正图
            addEdgeR(v, u, w);//建反图
        }
    }
    dijkstra();//反图上跑dj算法
    mergeRoad();
    int ans = expand();
    cout << ans << endl;
    return 0;
}
