// P哥的桶
// 一共有n个桶，排成一排，编号1~n，每个桶可以装下任意个数字
// 高效的实现如下两个操作
// 操作 1 k v : 把数字v放入k号桶中
// 操作 2 l r : 可以从l..r号桶中随意拿数字，返回异或和最大的结果
// 1 <= n、m <= 5 * 10^4
// 0 <= v <= 2^31 - 1
// 测试链接 : https://www.luogu.com.cn/problem/P4839
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有测试用例
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 50001;
const int BIT = 30;

// 线段树的每个范围上维护线性基
int treeBasis[MAXN << 2][BIT + 1];
int basis[BIT + 1];

bool insert(int *basis, int num) {
    for (int i = BIT; i >= 0; i--) {
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
//这就是一个普通的线性基  不是向量线性基

//线段树的基本内容
void add(int jobi, int jobv, int l, int r, int i) {
    insert(treeBasis[i], jobv);
    if (l < r) {
        int mid = (l + r) >> 1;
        if (jobi <= mid) {
            add(jobi, jobv, l, mid, i << 1);
        } else {
            add(jobi, jobv, mid + 1, r, i << 1 | 1);
        }
    }
}

void merge(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        for (int j = BIT; j >= 0; j--) {
            if (treeBasis[i][j] != 0) {
                insert(basis, treeBasis[i][j]);
            }
        }
    } else {
        int mid = (l + r) >> 1;
        if (jobl <= mid) {
            merge(jobl, jobr, l, mid, i << 1);
        }
        if (jobr > mid) {
            merge(jobl, jobr, mid + 1, r, i << 1 | 1);
        }
    }
}

int query(int jobl, int jobr, int m) {
    for(int i=0;i<=BIT;i++){
        basis[i]=0;
    }
    merge(jobl, jobr, 1, m, 1);
    int ans = 0;
    for (int j = BIT; j >= 0; j--) {
        ans = max(ans, ans ^ basis[j]);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int op;
        cin >> op;
        if (op == 1) {
            int jobi, jobv;
            cin >> jobi >> jobv;
            add(jobi, jobv, 1, m, 1);
        } else {
            int jobl, jobr;
            cin >> jobl >> jobr;
            cout << query(jobl, jobr, m) << endl;
        }
    }

    return 0;
}
