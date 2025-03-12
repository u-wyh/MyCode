// 寻找最近和次近
// 给定一个长度为n的数组arr，下标1 ~ n范围，数组无重复值
// 关于近的定义，距离的定义如下:
// 对i位置的数字x来说，只关注右侧的数字，和x的差值绝对值越小就越近
// 距离为差值绝对值，如果距离一样，数值越小的越近
// 数值 : 3 5 7 1
// 下标 : 1 2 3 4
// 对1位置的数字3来说，第一近是4位置的1，距离为2；第二近是2位置的5，距离为2
// 每个位置的数字都求第一近的位置及其距离、第二近的位置及其距离
// 分别用to1、dist1、to2、dist2数组表示，0表示不存在
// 有序表的实现 + 数组手搓双向链表的实现
// 对数器验证
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <climits>
#include <cstdlib>
#include <ctime>
#include <unordered_set>
#include <iomanip>

using namespace std;

const int MAXN = 10001;

int arr[MAXN];
int n;
int to1[MAXN];
int dist1[MAXN];
int to2[MAXN];
int dist2[MAXN];

pair<int, int> Rank[MAXN];
int pre[MAXN];
int nex[MAXN];

void update(int i, int j, int dist) {
    if (j == 0) return;
    if (to1[i] == 0 || dist < dist1[i] || (dist == dist1[i] && arr[j] < arr[to1[i]])) {
        to2[i] = to1[i];
        dist2[i] = dist1[i];
        to1[i] = j;
        dist1[i] = dist;
    } else if (to2[i] == 0 || dist < dist2[i] || (dist == dist2[i] && arr[j] < arr[to2[i]])) {
        to2[i] = j;
        dist2[i] = dist;
    }
}

void near1() {
    set<pair<int, int>, greater<pair<int, int>>> set;
    for (int i = n; i >= 1; --i) {
        to1[i] = to2[i] = 0;
        dist1[i] = dist2[i] = INT_MAX;
        auto cur = make_pair(arr[i], i);
        auto it = set.lower_bound(cur);
        if (it != set.begin()) {
            --it;
            update(i, it->second, abs(arr[i] - it->first));
        }
        auto it2 = set.upper_bound(cur);
        if (it2 != set.end()) {
            update(i, it2->second, abs(arr[i] - it2->first));
        }
        set.insert(cur);
    }
}

void near2() {
    for (int i = 1; i <= n; ++i) {
        Rank[i] = make_pair(arr[i], i);
    }
    sort(Rank + 1, Rank + n + 1);
    for (int i = 1; i <= n; ++i) {
        pre[Rank[i].second] = (i > 1) ? Rank[i - 1].second : 0;
        nex[Rank[i].second] = (i < n) ? Rank[i + 1].second : 0;
    }
    for (int i = 1; i <= n; ++i) {
        update(i, pre[i], abs(arr[i] - arr[pre[i]]));
        if (pre[pre[i]] != 0) {
            update(i, pre[pre[i]], abs(arr[i] - arr[pre[pre[i]]]));
        }
        update(i, nex[i], abs(arr[i] - arr[nex[i]]));
        if (nex[nex[i]] != 0) {
            update(i, nex[nex[i]], abs(arr[i] - arr[nex[nex[i]]]));
        }
    }
}

void randomFill(int v) {
    unordered_set<int> set;
    while (set.size() < n) {
        int cur = rand() % (2 * v) - v + 1;
        set.insert(cur);
    }
    auto it = set.begin();
    for (int i = 1; i <= n; ++i) {
        arr[i] = *it++;
    }
}

bool check() {
    near1();
    vector<int> a(MAXN), b(MAXN), c(MAXN), d(MAXN);
    for (int i = 1; i <= n; ++i) {
        a[i] = to1[i];
        b[i] = dist1[i];
        c[i] = to2[i];
        d[i] = dist2[i];
    }
    near2();
    for (int i = 1; i <= n; ++i) {
        if (a[i] != to1[i] || b[i] != dist1[i]) {
            return false;
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (c[i] != to2[i] || d[i] != dist2[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    srand(time(0));
    n = 100;
    int v = 500;
    int testTime = 100;
    cout << "测试开始" << endl;
    for (int i = 1; i <= testTime; ++i) {
        randomFill(v);
        if (!check()) {
            cout << "出错了!" << endl;
        } else {
            cout << "第" << setw(3) << i << "组测试正确" << endl;
        }
        // system("pause"); // 注释掉这行以加快测试速度
    }
    cout << "测试结束" << endl;
    return 0;
}
