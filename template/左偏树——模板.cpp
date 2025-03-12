// 左偏树模版题1，C++版
// 依次给定n个非负数字，表示有n个小根堆，每个堆只有一个数
// 实现如下两种操作，操作一共调用m次
// 1 x y : 第x个数字所在的堆和第y个数字所在的堆合并
//         如果两个数字已经在一个堆或者某个数字已经删除，不进行合并
// 2 x   : 打印第x个数字所在堆的最小值，并且在堆里删掉这个最小值
//         如果第x个数字已经被删除，也就是找不到所在的堆，打印-1
//         若有多个最小值，优先删除编号小的
// 1 <= n, m <= 10^5
// 测试链接 : https://www.luogu.com.cn/problem/P3377
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100001;
int n, m;
int num[MAXN];
int ls[MAXN];
int rs[MAXN];
int dist[MAXN];
// 并查集需要father数组，方便快速找到树的头
// father[i]不代表i在树上的父亲节点
// father是并查集找代表节点的路径信息
// 需要保证，并查集最上方的代表节点 = 树的头节点
int fa[MAXN];

//预处理
void prepare() {
    dist[0] = -1;
    for(int i = 1; i <= n; i++) {
        ls[i] = rs[i] = dist[i] = 0;
        fa[i] = i;
    }
}

int find(int i) {
    fa[i] = fa[i] == i ? i : find(fa[i]);//扁平化处理
    return fa[i];
}

//将以i 、 j为头的树合并  并返回头结点编号
int merge(int i, int j) {
    if (i == 0 || j == 0) {
        //遇到了空节点 那么就以非空作为头结点
        return i + j;
    }
    if (num[i] > num[j] || (num[i] == num[j] && i > j)) {
        //谁小谁做头 后面是题目规定  一般都是这个规定
        int tmp = i;
        i = j;
        j = tmp;
    }
    rs[i] = merge(rs[i], j);//将右儿子和它做合并
    //检查dist有没有问题 是否需要交换
    if (dist[ls[i]] < dist[rs[i]]) {
        int tmp = ls[i];
        ls[i] = rs[i];
        rs[i] = tmp;
    }
    dist[i] = dist[rs[i]] + 1;
    fa[ls[i]] = fa[rs[i]] = i;
    return i;
}

// 节点i一定是左偏树的头，在左偏树上删掉节点i，返回新树的头节点编号
int pop(int i) {
    fa[ls[i]] = ls[i];
    fa[rs[i]] = rs[i];
    // 并查集有路径压缩，所以i下方的某个节点x，可能有father[x] = i
    // 现在要删掉i了，所以x往上会找不到正确的头节点
    // 为了任何节点往上都能找到正确的头，所以要有下面这句
    fa[i] = merge(ls[i], rs[i]);
    ls[i] = rs[i] = dist[i] = 0;
    return fa[i];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    prepare();
    for (int i = 1; i <= n; i++) {
        cin >> num[i];
    }
    for (int i = 1; i <= m; i++) {
        int op;
        cin >> op;
        if (op == 1) {
            int x, y;
            cin >> x >> y;
            if (num[x] != -1 && num[y] != -1) {
                //表示两个数字都没有被删除
                int l = find(x);
                int r = find(y);
                if (l != r) {
                    //表示两个数字不在一个堆中
                    merge(l, r);
                }
            }
        } else {
            int x;
            cin >> x;
            if (num[x] == -1) {
                //如果数字不存在
                cout << -1 << "\n";
            } else {
                int ans = find(x);
                cout << num[ans] << "\n";
                //弹出最小值
                pop(ans);
                num[ans] = -1;
            }
        }
    }
    return 0;
}
