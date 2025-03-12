// 增加限制的最长公共子序列问题
// 给定两个字符串s1和s2，s1长度为n，s2长度为m
// 返回s1和s2的最长公共子序列长度
// 注意：
// 两个字符串都只由小写字母组成
// 1 <= n <= 10^6
// 1 <= m <= 10^3
// 状态设计优化的经典题，对数器验证
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <cstring>
#include <iomanip>

using namespace std;

// 为了测试
void randomString(char* ans, int n) {
    srand(time(0));
    for (int i = 0; i < n; i++) {
        ans[i] = 'a' + rand() % 26;
    }
    ans[n] = '\0'; // 确保字符串以null结尾
}

// 经典动态规划的版本
int lcs1(const string& str1, const string& str2) {
    int n = str1.size();
    int m = str2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    return dp[n][m];
}

// 利用限制条件做优化的版本
const int MAXN = 1000005;
const int MAXM = 1005;
const int NA = INT_MAX;

char s1[MAXN];
char s2[MAXM];
int n, m;
int Right[26];
int Next[MAXN][26];
int dp[MAXM][MAXM];

void build() {
    fill_n(Right, 26, NA);
    for (int i = n ; i >= 0; i--) { // 注意这里从n-1开始，且包括-1（用于初始化）
        for (int j = 0; j < 26; j++) {
            Next[i][j] =  Right[j]; // -1表示无效位置
        }
        if (i > 0) {
            Right[s1[i-1] - 'a'] = i;
        }
    }
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= m; j++) {
            dp[i][j] = -1;
        }
    }
}

// 长度为i的s2前缀串，想和s1字符串形成长度为j的公共子序列
// 返回s1中最后一个字符的位置（从0开始），如果做不到，返回NA
int f(int i, int j) {
    if (i < j) return NA;
    if (j == 0) return 0; // 返回-1表示空序列
    if (dp[i][j] != -1) return dp[i][j];
    int cha = s2[i - 1] - 'a';
    int ans = f(i - 1, j); // 不选当前字符
    int pre = f(i - 1, j - 1) ; // 选当前字符，但注意i-1不能越界
    if (pre != NA) { // 检查是否有效
        ans =min(Next[pre][cha] , ans);
    }
    dp[i][j] = ans; // 记录结果，-1表示无法形成长度为j的子序列
    return ans;
}

int lcs2(const string& str1, const string& str2) {
    strncpy(s1, str1.c_str(), MAXN);
    strncpy(s2, str2.c_str(), MAXM);
    n = strlen(s1);
    m = strlen(s2);
    build();
    int ans = 0;
    for (int j = m; j >= 1; j--) {
        int len = f(m, j);
        if (len != NA) {
            ans = j;
            break;
        }
    }
    return ans;
}

// 为了测试
int main() {
    srand(time(0));
    int n = 100;
    int m = 100;
    int testTime = 1000; // 减少测试次数以加快测试速度
    cout << "功能测试开始" << endl;
    for (int i = 0; i < testTime; i++) {
        int size1 = rand() % n + 1;
        int size2 = rand() % m + 1;
        char* str1 = new char[size1 + 1];
        char* str2 = new char[size2 + 1];
        randomString(str1, size1);
        randomString(str2, size2);
        int ans1 = lcs1(string(str1), string(str2));
        int ans2 = lcs2(string(str1), string(str2));
        if (ans1 != ans2) {
            cout << "出错了!" << endl;
            //break; // 发现问题后停止测试
        }
        else{
            cout<<"第"<<setw(6)<<i+1<<"组测试正确"<<endl;
        }
        delete[] str1;
        delete[] str2;
    }
    cout << "功能测试结束" << endl << endl;

    cout << "性能测试开始" << endl;
    n = 1000000;
    m = 100;
    cout << "n = " << n << endl;
    cout << "m = " << m << endl;
    char* str1 = new char[n + 1];
    char* str2 = new char[m + 1];
    //cout<<666<<endl;
    randomString(str1, n);
    randomString(str2, m);
    //cout<<777<<endl;

    clock_t start1 = clock();
    //cout<<555<<endl;
    int k1=lcs1(string(str1), string(str2));
    //cout<<444<<endl;
    clock_t end1 = clock();
    double elapsed1 = double(end1 - start1) / CLOCKS_PER_SEC;
    cout << "lcs1方法运行时间 : " << elapsed1<< " 秒" << endl;

    clock_t start2 = clock();
    int result = lcs2(string(str1), string(str2));
    clock_t end2 = clock();
    double elapsed2 = double(end2 - start2) / CLOCKS_PER_SEC;
    cout << "lcs2方法运行时间 : " << elapsed2<< " 秒" << endl;
    cout << "性能测试结束" << endl;

    delete[] str1;
    delete[] str2;
    return 0;
}
