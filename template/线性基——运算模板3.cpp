// 元素
// 给定n个魔法矿石，每个矿石有状态和魔力，都是整数
// 若干矿石组成的组合能否有效，根据状态异或的结果来决定
// 如果一个矿石组合内部会产生异或和为0的子集，那么这个组合无效
// 返回有效的矿石组合中，最大的魔力和是多少
// 1 <= n <= 1000
// 1 <= 状态 <= 10^18
// 1 <= 魔力 <= 10^4
// 测试链接 : https://www.luogu.com.cn/problem/P4570
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有测试用例
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 1001;
const int BIT = 61; // 由于long long是64位，但最高位是符号位，所以这里用61位

typedef long long ll;

struct Node {
    ll num, power;
};

Node arr[MAXN];
ll basis[BIT];
int n;

// 比较函数，用于按power降序排序
bool cmp(Node a, Node b) {
    return a.power > b.power;
}

// 线性基里插入num，如果线性基增加了返回true，否则返回false
bool insert(ll num) {
    for (int i = BIT - 1; i >= 0; i--) {
        if (num >> i & 1) {
            if (basis[i] == 0) {
                basis[i] = num;
                return true;
            }
            num ^= basis[i];
        }
    }
    return false;
}

// 计算得到最大线性基的最少花费（实际上是最大魔力和）
ll compute() {
    ll ans = 0;
    sort(arr + 1, arr + n + 1, cmp);
    for (int i = 1; i <= n; i++) {
        if (insert(arr[i].num)) {
            //因为已经把顺序提前排好了  按照从大到小排列
            //所以只要插入成功  就直接加上  这样一定是最优的
            ans += arr[i].power;
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false); // 关闭同步，加速输入输出
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i].num >> arr[i].power;
    }
    cout << compute() << endl;
    return 0;
}
