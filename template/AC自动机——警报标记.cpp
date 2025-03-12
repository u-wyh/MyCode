// 数数(利用AC自动机检查命中)
// 我们称一个正整数x为幸运数字的条件为
// x的十进制中不包含数字串集合s中任意一个元素作为子串
// 例如s = { 22, 333, 0233 }
// 233是幸运数字，2333、20233、3223不是幸运数字
// 给定n和s，计算不大于n的幸运数字的个数
// 答案对1000000007取模
// 测试链接 : https://www.luogu.com.cn/problem/P3311
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法
// 提交以下的code，提交时请把类名改成"Main"，可以直接通过
#include<bits/stdc++.h>
using namespace std;
const int MOD = 1000000007;
// 目标字符串的数量
const int MAXN = 1301;
// 所有目标字符串的总字符数量
const int MAXS = 2001;

// 读入的数字
string num;

// 读入数字的长度
int n,m;

// AC自动机
int tree[MAXS][10];
int fail[MAXS];
int cnt = 0;

// 具体题目相关，本题为命中任何目标串就直接报警
// 所以每个节点记录是否触发警报
bool alert[MAXS];
int Queue[MAXS];

// 动态规划表
int dp[MAXN][MAXS][2][2];

void clear() {
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= cnt; j++) {
            dp[i][j][0][0] = -1;
            dp[i][j][0][1] = -1;
            dp[i][j][1][0] = -1;
            dp[i][j][1][1] = -1;
        }
    }
}

// AC自动机加入目标字符串
void insert(string word) {
    int u = 0;
    for (char s:word) {
        int c = s - '0';
        if (tree[u][c] == 0) {
            tree[u][c] = ++cnt;
        }
        u = tree[u][c];
    }
    alert[u] = true;
}

// 加入所有目标字符串之后
// 设置fail指针 以及 设置直接跳转支路
// 做了AC自动机固定的优化
// 做了命中标记前移防止绕圈的优化
void setFail() {
    int l = 0;
    int r = 0;
    for (int i = 0; i <= 9; i++) {
        if (tree[0][i] > 0) {
            Queue[r++] = tree[0][i];
        }
    }
    while (l < r) {
        int u = Queue[l++];
        for (int i = 0; i <= 9; i++) {
            if (tree[u][i] == 0) {
                tree[u][i] = tree[fail[u]][i];
            } else {
                fail[tree[u][i]] = tree[fail[u]][i];
                Queue[r++] = tree[u][i];
            }
        }
        // 命中标记前移
        alert[u] |= alert[fail[u]];
    }
}

// 逻辑分支都详细列出来的版本
// i来到的位置
// j : AC自动机里来到的节点编号
// free : 是不是可以随意选择了
// free = 0，不能随意选择数字，要考虑当前数字的大小
// free = 1，能随意选择数字
// has : 之前有没有选择过数字
// has = 0，之前没选择过数字
// has = 1，之前选择过数字
// 返回i....幸运数字的个数
int f1(int i, int j, int free, int has) {
    if (alert[j]) {
        return 0;
    }
    if (i == n) {
        return has;
    }
    if (dp[i][j][free][has] != -1) {
        return dp[i][j][free][has];
    }
    int ans = 0;
    int cur = num[i] - '0';
    if (has == 0) {
        if (free == 0) {
            // 分支1 : 之前没有选择过数字 且 之前的决策等于num的前缀
            // 能来到这里说明i一定是0位置, 那么cur必然不是0
            // 当前选择不要数字
            ans = (ans + f1(i + 1, 0, 1, 0)) % MOD;
            // 当前选择的数字比cur小
            for (int pick = 1; pick < cur; pick++) {
                ans = (ans + f1(i + 1, tree[j][pick], 1, 1)) % MOD;
            }
            // 当前选择的数字为cur
            ans = (ans + f1(i + 1, tree[j][cur], 0, 1)) % MOD;
        } else {
            // 分支2 : 之前没有选择过数字 且 之前的决策小于num的前缀
            // 当前选择不要数字
            ans = (ans + f1(i + 1, 0, 1, 0)) % MOD;
            // 当前可以选择1~9
            for (int pick = 1; pick <= 9; pick++) {
                ans = (ans + f1(i + 1, tree[j][pick], 1, 1)) % MOD;
            }
        }
    } else {
        if (free == 0) {
            // 分支3 : 之前已经选择过数字 且 之前的决策等于num的前缀
            // 当前选择的数字比cur小
            for (int pick = 0; pick < cur; pick++) {
                ans = (ans + f1(i + 1, tree[j][pick], 1, 1)) % MOD;
            }
            // 当前选择的数字为cur
            ans = (ans + f1(i + 1, tree[j][cur], 0, 1)) % MOD;
        } else {
            // 分支4 : 之前已经选择过数字 且 之前的决策小于num的前缀
            // 当前可以选择0~9
            for (int pick = 0; pick <= 9; pick++) {
                ans = (ans + f1(i + 1, tree[j][pick], 1, 1)) % MOD;
            }
        }
    }
    dp[i][j][free][has] = ans;
    return ans;
}

int main()
{
    //string num;
    cin>>num;
    n=num.length();
    //cout<<n<<endl;
    cin>>m;
    for(int i=1;i<=m;i++){
        string s;
        cin>>s;
        insert(s);
    }
    setFail();
    // 清空动态规划表
    clear();
    // 执行记忆化搜索
    cout<<f1(0,0,0,0);
    return 0;
}
