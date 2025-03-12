#include <iostream>
#include <vector>

using namespace std;

// 矩阵相乘
// a的列数一定要等于b的行数
vector<vector<int>> multiply(const vector<vector<int>>& a, const vector<vector<int>>& b) {
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
// 要求矩阵m是正方形矩阵
vector<vector<int>> power(const vector<vector<int>>& m, int p) {
    int n = m.size();
    vector<vector<int>> ans(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        ans[i][i] = 1;
    }
    vector<vector<int>> temp = m;
    for (; p != 0; p >>= 1) {
        if ((p & 1) != 0) {
            ans = multiply(ans, temp);
        }
        temp = multiply(temp, temp);
    }
    return ans;
}

// 打印二维矩阵
void print(const vector<vector<int>>& m) {
    for (const auto& row : m) {
        for (int val : row) {
            if (val < 10) {
                cout << val << "   ";
            } else if (val < 100) {
                cout << val << "  ";
            } else {
                cout << val << " ";
            }
        }
        cout << endl;
    }
}

// 矩阵乘法的展示
void f1() {
    vector<vector<int>> a = { { 1, 3 }, { 4, 2 } };
    vector<vector<int>> b = { { 2, 3 }, { 3, 2 } };
    vector<vector<int>> ans1 = multiply(a, b);
    print(ans1);
    cout << "======" << endl;
    vector<vector<int>> c = { { 2, 4 }, { 3, 2 } };
    vector<vector<int>> d = { { 2, 3, 2 }, { 3, 2, 3 } };
    vector<vector<int>> ans2 = multiply(c, d);
    print(ans2);
    cout << "======" << endl;
    vector<vector<int>> e = { { 2, 4 }, { 1, 2 }, { 3, 1 } };
    vector<vector<int>> f = { { 2, 3 }, { 4, 1 } };
    vector<vector<int>> ans3 = multiply(e, f);
    print(ans3);
    cout << "======" << endl;
    vector<vector<int>> g = { { 3, 1, 2 } };
    vector<vector<int>> h = { { 1, 2, 1 }, { 3, 2, 1 }, { 4, 2, -2 } };
    vector<vector<int>> ans4 = multiply(g, h);
    print(ans4);
}

// 矩阵快速幂用法的展示
void f2() {
    vector<vector<int>> a = { { 1, 2 }, { 3, 4 } };
    vector<vector<int>> b = multiply(a, multiply(a, multiply(a, multiply(a, a))));
    print(b);
    cout << "======" << endl;
    vector<vector<int>> ans = power(a, 5);
    print(ans);
}

// 用矩阵乘法解决斐波那契第n项的问题
void f3() {
    vector<vector<int>> start = { { 1, 0 } };
    vector<vector<int>> m = {
        { 1, 1 },
        { 1, 0 }
    };
    vector<vector<int>> a = multiply(start, m);
    print(a);
    cout << "======" << endl;
    vector<vector<int>> b = multiply(a, m);
    print(b);
    cout << "======" << endl;
    vector<vector<int>> c = multiply(b, m);
    print(c);
    cout << "======" << endl;
    vector<vector<int>> d = multiply(c, m);
    print(d);
}

// 用矩阵快速幂解决斐波那契第n项的问题
void f4() {
    vector<vector<int>> start = { { 1, 0 } };
    vector<vector<int>> m = {
        { 1, 1 },
        { 1, 0 }
    };
    vector<vector<int>> a = multiply(start, power(m, 1));
    print(a);
    cout << "======" << endl;
    vector<vector<int>> b = multiply(start, power(m, 2));
    print(b);
    cout << "======" << endl;
    vector<vector<int>> c = multiply(start, power(m, 3));
    print(c);
    cout << "======" << endl;
    vector<vector<int>> d = multiply(start, power(m, 4));
    print(d);
}

int main() {
    cout << "f1() : " << endl;
    cout << "矩阵乘法展示开始" << endl;
    f1();
    cout << "矩阵乘法展示结束" << endl << endl;

    cout << "f2() : " << endl;
    cout << "矩阵快速幂展示开始" << endl;
    f2();
    cout << "矩阵快速幂展示结束" << endl << endl;

    cout << "f3() : " << endl;
    cout << "求斐波那契数列第n项" << endl;
    cout << "用矩阵乘法解决" << endl;
    cout << "展示开始" << endl;
    f3();
    cout << "展示结束" << endl << endl;

    cout << "f4() : " << endl;
    cout << "求斐波那契数列第n项" << endl;
    cout << "用矩阵快速幂解决" << endl;
    cout << "展示开始" << endl;
    f4();
    cout << "展示结束" << endl << endl;

    return 0;
}
