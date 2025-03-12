// 棘手的操作，C++版
// 编号1~n个节点，每个节点独立且有自己的权值，实现如下7种操作，操作一共调用m次
// U x y  : x所在的集合和y所在的集合合并
// A1 x v : x节点的权值增加v
// A2 x v : x所在的集合所有节点的权值增加v
// A3 v   : 所有节点的权值增加v
// F1 x   : 打印x节点的权值
// F2 x   : 打印x所在的集合中，权值最大的节点的权值
// F3     : 打印所有节点中，权值最大的节点的权值
// 1 <= n、m <= 3 * 10^5，权值不会超过int类型的范围
// 测试链接 : https://www.luogu.com.cn/problem/P3273
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 300001;
int n, m;
// 左偏树需要
int num[MAXN];
int up[MAXN];
int ls[MAXN];
int rs[MAXN];
int dist[MAXN];
// 并查集的路径信息
int fa[MAXN];
// 集合的大小信息
int siz[MAXN];
// 集合内所有数字应该加多少值
int add[MAXN];
// 准备好一个栈，用迭代方式实现先序遍历，不用递归方式
int sta[MAXN];
// 所有集合头节点的值，进入这个有序表，头节点有序表
multiset<int> heads;
int addAll = 0;

// 编号为h的节点不再是左偏树的头，在头节点有序表里删掉一份h节点的值
void minusHead(int h) {
    if (h != 0) {
        //他的真实值是目前值  加上  加信息的值
        heads.erase(heads.find(num[h] + add[h]));
    }
}

// 编号为h的节点当前是左偏树的头，在头节点有序表里增加一份h节点的值
void addHead(int h) {
    if (h != 0) {
        heads.insert(num[h] + add[h]);
    }
}

void prepare() {
    dist[0] = -1;
    heads.clear();
    for (int i = 1; i <= n; i++) {
        up[i] = ls[i] = rs[i] = dist[i] = 0;
        fa[i] = i;
        siz[i] = 1;
        add[i] = 0;
        addHead(i);//自己一个节点是一个集合  直接加到有序表中
    }
    addAll = 0;
}

int find(int i) {
    fa[i] = fa[i] == i ? i : find(fa[i]);
    return fa[i];
}

int merge(int i, int j) {
    if (i == 0 || j == 0) return i + j;
    if (num[i] < num[j]) {
        swap(i, j);
    }
    rs[i] = merge(rs[i], j);
    up[rs[i]] = i;
    if (dist[ls[i]] < dist[rs[i]]) {
        swap(ls[i], rs[i]);
    }
    dist[i] = dist[rs[i]] + 1;
    fa[ls[i]] = i;
    fa[rs[i]] = i;
    return i;
}

// 节点i是所在左偏树的任意节点，删除节点i，返回整棵树的头节点编号
int remove(int i) {
    int h = find(i);
    fa[ls[i]] = ls[i];
    fa[rs[i]] = rs[i];
    int s = merge(ls[i], rs[i]);
    int f = up[i];
    fa[i] = s;
    up[s] = f;
    if (h != i) {
        fa[s] = h;
        if (ls[f] == i) {
            ls[f] = s;
        } else {
            rs[f] = s;
        }
        for (int d = dist[s]; dist[f] > d + 1; f = up[f], d++) {
            dist[f] = d + 1;
            if (dist[ls[f]] < dist[rs[f]]) {
                swap(ls[f], rs[f]);
            }
        }
    }
    up[i] = ls[i] = rs[i] = dist[i] = 0;
    return fa[s];
}

// 以i为头的左偏树，遭遇了更大的左偏树  一定是小的树加到大的树  启发式合并
// i的标签信息取消，以i为头的整棵树所有节点的值增加v
// 不用递归实现先序遍历，容易爆栈，所以用迭代实现先序遍历
void down(int i, int v) {
    if (i != 0) {
        add[i] = 0;
        int size = 0;
        sta[++size] = i;
        while (size > 0) {
            i = sta[size--];
            num[i] += v;
            if (rs[i] != 0) sta[++size] = rs[i];
            if (ls[i] != 0) sta[++size] = ls[i];
        }
    }
}

// U x y  : x所在的集合和y所在的集合合并
void u(int i, int j) {
    int l = find(i);
    int r = find(j);
    if (l == r) return;
    int lsize = siz[l];
    minusHead(l);
    int rsize = siz[r];
    minusHead(r);
    //比较两个集合的大小  并在有序表中删除两个头结点
    int addTag;//用于记录合并之后的集合整体要加上多少才是真实值
    if (lsize <= rsize) {
        down(l, add[l] - add[r]);
        addTag = add[r];
    } else {
        down(r, add[r] - add[l]);
        addTag = add[l];
    }
    //将较小的树合并到较大的树
    int h = merge(l, r);
    siz[h] = lsize + rsize;
    add[h] = addTag;
    addHead(h);
    //将合并后的头结点加入到有序表中
}

// A1 x v : x节点的权值增加v
void a1(int i, int v) {
    int h = find(i);
    //h为i所在集合头结点  在有序表中删除
    minusHead(h);
    int l = remove(i);
    //l为i所在集合删除i之后的头结点
    if (l != 0) {
        //如果还有元素
        siz[l] = siz[h] - 1;
        add[l] = add[h];
        addHead(l);
    }
    num[i] = num[i] + add[h] + v;//将i节点的信息修正
    fa[i] = i;//自己作为一个集合
    siz[i] = 1;
    add[i] = 0;
    addHead(i);
    u(l, i);//将当前节点加入到原来的集合中
}

void a2(int i, int v) {
    int h = find(i);
    minusHead(h);
    add[h] += v;
    addHead(h);
}

void a3(int v) {
    addAll += v;
}

// F1 x   : 打印x节点的权值
int f1(int i) {
    return num[i] + add[find(i)] + addAll;
    //他的权值等于本身值  加上集合共同加的值  加上所有元素都要加的值
}

// F2 x   : 打印x所在的集合中，权值最大的节点的权值
int f2(int i) {
    int h = find(i);
    return num[h] + add[h] + addAll;
}

int f3() {
    return (*heads.rbegin()) + addAll;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> num[i];
    prepare();
    cin >> m;
    for (int i = 1; i <= m; i++) {
        string op;
        cin >> op;
        if (op == "F3") {
            cout << f3() << "\n";
        } else {
            int x; cin >> x;
            if (op == "U") {
                int y; cin >> y;
                u(x, y);
            } else if (op == "A1") {
                int y; cin >> y;
                a1(x, y);
            } else if (op == "A2") {
                int y; cin >> y;
                a2(x, y);
            } else if (op == "A3") {
                a3(x);
            } else if (op == "F1") {
                cout << f1(x) << "\n";
            } else {
                cout << f2(x) << "\n";
            }
        }
    }
    return 0;
}
