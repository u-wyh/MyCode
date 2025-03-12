// Prim算法优化（洛谷）
// 静态空间实现
// 时间复杂度O(n + m) + O((m+n) * log n)
// 测试链接 : https://www.luogu.com.cn/problem/P3366
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法
// 提交以下所有代码，把主类名改成Main，可以直接通过
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5001;
const int MAXM = 400001;

int n, m;
int u, w;

// 链式前向星建图
int head[MAXN];
int Next[MAXM];
int to[MAXM];
int weight[MAXM];
int cnt=1;

// 改写的堆结构
//heap[i][0]表示第i个位置的节点编号
//heap[i][1]表示第i个位置的节点代价
int heap[MAXN][2];
// where[v] = -1，表示v这个节点，从来没有进入过堆
// where[v] = -2，表示v这个节点，已经弹出过了
// where[v] = i(>=0)，表示v这个节点，在堆上的i位置
int where[MAXN];
// 堆的大小
int heapSize;
// 找到的节点个数
int nodeCnt;

void addEdge(int u, int v, int w) {
    Next[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}

bool isEmpty() {
    return heapSize == 0;
}

// 堆上，i位置的信息 和 j位置的信息 交换！
void swap(int i, int j) {
    int a = heap[i][0];
    int b = heap[j][0];
    where[a] = j;
    where[b] = i;
    swap(heap[i],heap[j]);
}

//建立堆
void heapify(int i) {
    int l = i * 2 + 1;
    while (l < heapSize) {
        int best = l + 1 < heapSize && heap[l + 1][1] < heap[l][1] ? l + 1 : l;
        best = heap[best][1] < heap[i][1] ? best : i;
        if (best == i) {
            break;
        }
        swap(best, i);
        i = best;
        l = i * 2 + 1;
    }
}

void pop() {
    u = heap[0][0];
    w = heap[0][1];
    swap(0, --heapSize);
    heapify(0);
    where[u] = -2;
    nodeCnt++;
}

void heapInsert(int i) {
    while (heap[i][1] < heap[(i - 1) / 2][1]) {
        swap(i, (i - 1) / 2);
        i = (i - 1) / 2;
    }
}

// 当前处理的是编号为ei的边！
void addOrUpdateOrIgnore(int ei) {
    int v = to[ei];
    int w = weight[ei];
    // 去往v点，权重w
    if (where[v] == -1) {
        // v这个点，从来没有进入过堆！
        heap[heapSize][0] = v;
        heap[heapSize][1] = w;
        where[v] = heapSize++;
        heapInsert(where[v]);
    } else if (where[v] >= 0) {
        // v这个点的记录，在堆上的位置是where[v]
        heap[where[v]][1] = min(heap[where[v]][1], w);
        heapInsert(where[v]);
    }
}

int prim() {
    // 1节点出发
    nodeCnt = 1;
    where[1] = -2;//将节点1直接视为已经弹出过了
    for (int ei = head[1]; ei > 0; ei = Next[ei]) {
        //首先将1节点的所有连边加入堆中
        addOrUpdateOrIgnore(ei);
    }
    int ans = 0;
    while (!isEmpty()) {
        pop();
        ans += w;
        for (int ei = head[u]; ei > 0; ei = Next[ei]) {
            addOrUpdateOrIgnore(ei);
        }
    }
    return ans;
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        where[i]=-1;
    }
    for (int i = 0, u, v, w; i < m; i++) {
        cin>>u>>v>>w;
        addEdge(u, v, w);
        addEdge(v, u, w);
    }
    int ans = prim();
    if(nodeCnt == n)
        cout<< ans ;
    else
        cout<<"orz"<<endl;
    return 0;
}
