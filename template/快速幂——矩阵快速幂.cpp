// 求斐波那契数列第n项
// 测试链接 : https://leetcode.cn/problems/fibonacci-number/
// 这个测试的数据量太小，并且不牵扯取模的事情
// 所以矩阵快速幂看不出优势
#include <iostream>
#include <vector>

using namespace std;

// 时间复杂度O(n)，普通解法
int fib1(int n) {
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    int lastLast = 0, last = 1;
    for (int i = 2, cur; i <= n; i++) {
        cur = lastLast + last;
        lastLast = last;
        last = cur;
    }
    return last;
}

// 矩阵相乘
// a的列数一定要等于b的行数
vector<vector<int>> multiply(vector<vector<int>>& a, const vector<vector<int>>& b) {
    int n = a.size();
    int m = b[0].size();
    int k = a[0].size();
    vector<vector<int>> ans(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int c = 0; c < k; c++) {
                ans[i][j] += a[i][c] * b[c][j];
            }
        }
    }
    return ans;
}

// 矩阵快速幂
vector<vector<int>> power(vector<vector<int>>& m, int p) {
    int n = m.size();
    vector<vector<int>> ans(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        ans[i][i] = 1;//单位矩阵 相当于乘法快速幂中的1
    }
    for (; p != 0; p >>= 1) {
        if ((p & 1) != 0) {
            ans = multiply(ans, m);
        }
        m = multiply(m, m);//每次都是倍增
    }
    return ans;
}

// 时间复杂度O(logn)，矩阵快速幂的解法
int fib2(int n) {
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }

    // 定义初始矩阵和转移矩阵
    vector<vector<int>> start = { {1, 0} };
    vector<vector<int>> base = {
        {1, 1},
        {1, 0}
    };

    // 计算矩阵快速幂
    vector<vector<int>> ans = multiply(start, power(base, n - 1));
    return ans[0][0];
}

int main() {
    int n;
    cout << "Enter the value of n: ";
    cin >> n;

    cout << "Fibonacci number (O(n)): " << fib1(n) << endl;
    cout << "Fibonacci number (O(logn)): " << fib2(n) << endl;

    return 0;
}
