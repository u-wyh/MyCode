// 最长理想子序列
// 给定一个长度为n，只由小写字母组成的字符串s，给定一个非负整数k
// 字符串s可以生成很多子序列，下面给出理想子序列的定义
// 子序列中任意相邻的两个字符，在字母表中位次的差值绝对值<=k
// 返回最长理想子序列
// 1 <= n <= 10^5
// 0 <= k <= 25
// s只由小写字母组成
// 测试链接 : https://leetcode.cn/problems/longest-ideal-subsequence/
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// 线段树节点数量，对于26个字母足够大
const int MAXN = (26 + 1) * 4;

int maxTree[MAXN];
int n = 26;

// 更新父节点值
void up(int i) {
    maxTree[i] = max(maxTree[i << 1], maxTree[i << 1 | 1]);
}

// 单点更新
void update(int jobi, int jobv, int l, int r, int i) {
    if (l == r && jobi == l) {
        maxTree[i] = jobv;
    } else {
        int m = (l + r) >> 1;
        if (jobi <= m) {
            update(jobi, jobv, l, m, i << 1);
        } else {
            update(jobi, jobv, m + 1, r, i << 1 | 1);
        }
        up(i);
    }
}

// 查询区间最大值
int queryMax(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        return maxTree[i];
    }
    int m = (l + r) >> 1;
    int ans = INT_MIN;
    if (jobl <= m) {
        ans = max(ans, queryMax(jobl, jobr, l, m, i << 1));
    }
    if (jobr > m) {
        ans = max(ans, queryMax(jobl, jobr, m + 1, r, i << 1 | 1));
    }
    return ans;
}

int longestIdealString(string s, int k) {
    fill(maxTree,maxTree+MAXN, 0);
    int ans = 0;
    for (char cha : s) {
        int v = cha - 'a' + 1;
        int p = queryMax(max(v - k, 1), min(v + k, n), 1, n, 1) + 1;
        ans = max(ans, p);
        update(v, p, 1, n, 1);
    }
    return ans;
}

int main() {
    string s;
    int k;
    cout << "Enter the string: ";
    cin >> s;
    cout << "Enter the value of k: ";
    cin >> k;

    int result = longestIdealString(s, k);
    cout << "The length of the longest ideal string is: " << result << endl;

    return 0;
}
