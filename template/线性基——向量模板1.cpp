// 装备购买
// 一共有n个物品，每个物品都有m个属性值
// 下面定义什么是不必要的物品：如果已经选择了k个物品，此时又有一件当前物品
// 如果给已经选择的物品分配一组相乘的系数，并把属性值相加，就能得到当前物品
// 那么就说当前物品是不必要的，比如下面的例子
// a = { 4, 6, 2 }, b = { 2, 8, 4 }, c = { 6, 19, 9 }
// a * 0.5 + b * 2 = c，那么c物品是不必要的
// 每个物品都有价格，现在希望尽量多的购买物品，但不能出现不必要的物品
// 返回最多能买几件物品和最少的花费
// 1 <= n、m <= 500
// 0 <= 属性值 <= 1000
// 测试链接 : https://www.luogu.com.cn/problem/P3265
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有测试用例
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip> // for std::setprecision

using namespace std;

const int MAXN = 502;
const int MAXM = 502;
const double sml = 1e-5;

double mat[MAXN][MAXM + 1]; // +1 for the price column
int basis[MAXN];
int n, m;
int cnt, cost;

//向量线性基模版
bool insert(int i) {
    for (int j = 1; j <= m; j++) {
        if (fabs(mat[i][j]) >= sml) {
            if (basis[j] == 0) {
                basis[j] = i;
                return true;
            }
            double rate = mat[i][j] / mat[basis[j]][j];
            for (int k = j; k <= m; k++) {
                mat[i][k] -= rate * mat[basis[j]][k];
            }
        }
    }
    return false;
}

void compute() {
    cnt = cost = 0;
    // Sorting based on the price in ascending order
    vector<pair<double, int>> prices; // pair of price and index
    for (int i = 1; i <= n; i++) {
        prices.emplace_back(mat[i][m + 1], i);
    }
    sort(prices.begin(), prices.end());
    //根据价格排序

    for (const auto& p : prices) {
        int i = p.second;
        if (insert(i)) {
            cnt++;
            cost += static_cast<int>(mat[i][m + 1]);
        }
    }
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> mat[i][j];
        }
    }
    for (int i = 1; i <= n; i++) {
        cin >> mat[i][m + 1]; // price
    }
    compute();
    cout << cnt << " " << cost << endl;
    return 0;
}
