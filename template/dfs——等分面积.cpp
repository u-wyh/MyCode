//P4160
#include <iostream>
#include <cmath> // 包含数学库以使用min和max函数
#include <iomanip> // 包含以设置输出精度

using namespace std;

int n;
double x, y;

inline double dfs(double x, double y, int k) {
    if (k == 1) {
        return max(x, y) / min(x, y);
    }
    double ans = 233333333, mx = x * 1.0 / k, my = y * 1.0 / k, t1, t2;
    for (int i = 1; i <= k / 2; i++) {
        t1 = max(dfs(mx * i, y, i), dfs(x - mx * i, y, k - i));
        t2 = max(dfs(x, my * i, i), dfs(x, y - my * i, k - i));
        ans = min(ans, min(t1, t2));
    }
    return ans;
}

int main() {
    cin >> x >> y >> n;
    // 设置输出精度为6位小数
    cout << fixed << setprecision(6) << dfs(x, y, n) << endl;
    return 0;
}
