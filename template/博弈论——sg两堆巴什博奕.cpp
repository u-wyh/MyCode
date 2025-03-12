// 两堆石头的巴什博弈
// 有两堆石头，数量分别为a、b
// 两个人轮流拿，每次可以选择其中一堆石头，拿1~m颗
// 拿到最后一颗石子的人获胜，根据a、b、m返回谁赢
// 来自真实大厂笔试，没有在线测试，对数器验证
#include <iostream>
#include <vector>
#include <cstring>
#include <iomanip>
using namespace std;

const int MAXN = 101;

string dp[MAXN][MAXN][MAXN];

// 动态规划方法彻底尝试
// 为了验证
string win1(int a, int b, int m) {
    if (m >= max(a, b)) {
        return a != b ? "先手" : "后手";
    }
    if (a == b) {
        return "后手";
    }
    if (!dp[a][b][m].empty()) {
        return dp[a][b][m];
    }
    string ans = "后手";
    for (int pick = 1; pick <= min(a, m); pick++) {
        if (win1(a - pick, b, m) == "后手") {
            // 后续过程的赢家是后续过程的后手
            // 那就表示此时的先手，通过这个后续过程，能赢
            ans = "先手";
        }
        if (ans == "先手") {
            // 后续过程的赢家是后续过程的后手
            // 那就表示此时的先手，通过这个后续过程，能赢
            break;
        }
    }
    for (int pick = 1; pick <= min(b, m); pick++) {
        if (win1(a, b - pick, m) == "后手") {
            // 后续过程的赢家是后续过程的后手
            // 那就表示此时的先手，通过这个后续过程，能赢
            ans = "先手";
        }
        if (ans == "先手") {
            break;
        }
    }
    dp[a][b][m] = ans;
    return ans;
}

// sg定理
string win2(int a, int b, int m) {
    int n = max(a, b);
    vector<int> sg(n + 1, 0);
    vector<bool> appear(m + 1, false);
    for (int i = 1; i <= n; i++) {
        fill(appear.begin(), appear.end(), false);
        for (int j = 1; j <= m && i - j >= 0; j++) {
            appear[sg[i - j]] = true;
        }
        for (int s = 0; s <= m; s++) {
            if (!appear[s]) {
                sg[i] = s;
                break;
            }
        }
    }
    return (sg[a] ^ sg[b]) != 0 ? "先手" : "后手";
}

// 时间复杂度O(1)的最优解
// 其实是根据方法2中的sg表观察出来的
string win3(int a, int b, int m) {
    return a % (m + 1) != b % (m + 1) ? "先手" : "后手";
}

int main() {
    cout << "测试开始" << endl;
    int cnt=0;
    for (int a = 0; a < MAXN; a++) {
        for (int b = 0; b < MAXN; b++) {
            for (int m = 1; m < MAXN; m++) {
                cnt++;
                string ans1 = win1(a, b, m);
                string ans2 = win2(a, b, m);
                string ans3 = win3(a, b, m);
                if (ans1 != ans2 || ans1 != ans3) {
                    cout << "出错了！" << endl;
                }
                else{
                    cout<<"第 "<<setw(3)<<cnt<<" 测试通过"<<endl;
                }
            }
        }
    }
    cout << "测试结束" << endl;
    return 0;
}
