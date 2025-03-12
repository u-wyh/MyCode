// 外星千足虫
// 一共有n种虫子，编号1~n，虫子腿为奇数认为是外星虫，偶数认为是地球虫
// 一共有m条虫子腿的测量记录，记录编号1~m
// 比如其中一条测量记录为，011 1，表示1号虫没参与，2号、3号虫参与了，总腿数为奇数
// 测量记录保证不会有自相矛盾的情况，但是可能有冗余的测量结果
// 也许拥有从第1号到第k号测量记录就够了，k+1~m号测量记录有或者没有都不影响测量结果
// 打印这个k，并且打印每种虫子到底是外星虫还是地球虫
// 如果使用所有的测量结果，依然无法确定每种虫子的属性，打印"Cannot Determine"
// 1 <= n <= 1000
// 1 <= m <= 2000
// 测试链接 : https://www.luogu.com.cn/problem/P2447
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有测试用例
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <climits>

using namespace std;

const int BIT = 64;
const int MAXN = 2002;
const int MAXM = (MAXN / BIT) + 1;

long long mat[MAXN][MAXM];
int n, m, s;
int need;

// 高斯消元解决异或方程组
void gauss(int n) {
    need = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= n; ++j) {
            if (mat[j - 1][(i - 1) / BIT] & (1LL << ((i - 1) % BIT))) {
                swap(mat[i - 1], mat[j - 1]);
                need = max(need, j);
                break;
            }
        }
        // 一旦没有唯一解，可以结束了
        if (!(mat[i - 1][(i - 1) / BIT] & (1LL << ((i - 1) % BIT)))) {
            return;
        }
        for (int j = 1; j <= n; ++j) {
            if (i != j && (mat[j - 1][(i - 1) / BIT] & (1LL << ((i - 1) % BIT)))) {
                for (int k = 0; k < MAXM; ++k) {
                    mat[j - 1][k] ^= mat[i - 1][k];
                }
            }
        }
    }
}

// 设置row行，col列的状态为v
void set(int row, int col, int v) {
    if (v == 0) {
        mat[row - 1][col / BIT] &= ~(1LL << (col % BIT));
    } else {
        mat[row - 1][col / BIT] |= 1LL << (col % BIT);
    }
}

// 获取row行，col列的状态
int get(int row, int col) {
    return (mat[row - 1][col / BIT] >> (col % BIT)) & 1;
}

// 交换两行
void swap(long long* a, long long* b) {
    long long tmp[MAXM];
    for (int i = 0; i < MAXM; ++i) {
        tmp[i] = a[i];
        a[i] = b[i];
        b[i] = tmp[i];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    s = max(n, m);
    for (int i = 1; i <= m; ++i) {
        string line;
        cin >> line;
        for (int j = 1; j <= n; ++j) {
            set(i, j, line[j - 1] - '0');
        }
        int val;
        cin >> val;
        set(i, s + 1, val);
    }

    gauss(s);
    bool sign = true;
    for (int i = 1; i <= n; ++i) {
        if (!get(i, i)) {
            sign = false;
            break;
        }
    }

    if (!sign) {
        cout << "Cannot Determine" << endl;
    } else {
        cout << need << endl;
        for (int i = 1; i <= n; ++i) {
            if (get(i, s + 1)) {
                cout << "?y7M#" << endl;
            } else {
                cout << "Earth" << endl;
            }
        }
    }

    return 0;
}
