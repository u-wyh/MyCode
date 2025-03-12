// 最好的部署
// 一共有n台机器，编号1 ~ n，所有机器排成一排
// 你只能一台一台的部署机器，你可以决定部署的顺序，最终所有机器都要部署
// 给定三个数组no[]、one[]、both[]
// no[i] : 如果i号机器部署时，相邻没有机器部署，此时能获得的收益
// one[i] : 如果i号机器部署时，相邻有一台机器部署，此时能获得的收益
// both[i] : 如果i号机器部署时，相邻有两台机器部署，此时能获得的收益
// 第1号机器、第n号机器当然不会有两台相邻的机器
// 返回部署的最大收益
// 1 <= n <= 10^5
// 0 <= no[i]、one[i]、both[i]
// 来自真实大厂笔试，对数器验证
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1001;
int no[MAXN];
int one[MAXN];
int both[MAXN];
int n;
int dp[1001][1001];
int dp1[1001][2];

// 部署l...r范围上的机器
// 并且l-1和r+1的机器一定都没有部署
// 返回部署的最大收益
int f(int l, int r) {
    //cout<<111<<endl;
    if (l == r) {
        return no[l];
    }
    if (dp[l][r] != -1) {
        return dp[l][r];
    }
    int ans = f(l + 1, r) + one[l];
    ans = max(ans, f(l, r - 1) + one[r]);
    for (int i = l + 1; i < r; i++) {
        ans = max(ans, f(l, i - 1) + f(i + 1, r) + both[i]);
    }
    dp[l][r] = ans;
    return ans;
}

// 区间dp的尝试
// 时间复杂度O(n^3)
// 正确但是并不推荐
int best1() {
    //cout<<222<<endl;
    for (int l = 1; l <= n; l++) {
        for (int r = l; r <= n; r++) {
            dp[l][r] = -1;
        }
    }
    //cout<<999<<endl;
    return f(1, n);
}

// 线性dp的尝试
// 时间复杂度O(n)
// 推荐
int best2() {
    dp1[n][0] = no[n];
    dp1[n][1] = one[n];
    for (int i = n - 1; i >= 1; i--) {
        dp1[i][0] = max(no[i] + dp1[i + 1][1], one[i] + dp1[i + 1][0]);
        dp1[i][1] = max(one[i] + dp1[i + 1][1], both[i] + dp1[i + 1][0]);
    }
    return dp1[1][0];
}

// 为了测试
void random(int size, int v) {
    n = size;
    srand(time(0));
    for (int i = 1; i <= n; i++) {
        no[i] = rand() % v;
        one[i] = rand() % v;
        both[i] = rand() % v;
    }
}

// 为了测试
int main() {
    int maxn = 100;
    int maxv = 100;
    int testTime = 10000;
    cout << "测试开始" << endl;
    for (int i = 0; i < testTime; i++) {
        int size = rand() % maxn + 1;
        random(size, maxv);
        //cout<<555<<endl;
        int ans1 = best1();
        //cout<<666<<endl;
        int ans2 = best2();
        //cout<<777<<endl;
        //cout<<' '<<ans1<<' '<<ans2<<endl;
        if (ans1 != ans2) {
            cout << "出错了!" << endl;
        }
        else{
            cout<<"第"<<setw(6)<<i<<"组测试正确"<<endl;
        }
    }
    cout << "测试结束" << endl;
    return 0;
}
