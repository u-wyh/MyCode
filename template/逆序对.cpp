//P4280
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;
const int MAXM = 105;

int n, m;
int a[MAXN];
vector<int> lis[2]; // 使用vector来动态管理数组大小，提高灵活性
//lis[0][i]表示前面的数字中大于i的个数
//lis[1][i]表示后面的数字中小于i的个数
long long ans;

int main() {
    scanf("%d%d", &n, &m);
    lis[1].resize(m + 1, 0); // 初始化lis[1]为大小为m+1的数组，所有元素为0

    // 读取输入并统计每个数字出现的次数（忽略-1）
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        if (a[i] != -1) {
            lis[1][a[i]]++;
        }
    }

    // 累加lis[1]数组，方便后续计算前缀和
    for (int i = 1; i <= m; ++i) {
        lis[1][i] += lis[1][i - 1];
        //此时表示的是小于等于i的次数
    }

    // 初始化lis[0]数组
    lis[0].resize(m + 1, 0);

    // 遍历每个位置
    for (int i = 1; i <= n; ++i) {
        int ct=0;
        if (a[i] == -1) {
            int c = 0, d = 0,  mx = INT_MAX; // 使用INT_MAX代替0x7fffffff

            // 找到最优的填充值
            for (int j = ct; j <= m; ++j) {
                int current_sum = lis[0][j + 1] + lis[1][j - 1];
                if (current_sum < mx) {
                    mx = current_sum;
                    ct = j;
                }
            }
            a[i] = ct; // 填充-1位置的最优值
        } else {
            // 如果当前位置不是-1，则更新lis[1]数组（回溯已使用的数字）
            for (int j = a[i]; j <= m; ++j) {
                lis[1][j]--;
            }
        }

        // 更新答案并更新lis[0]数组（记录当前位置之前的LIS长度）
        ans += lis[0][a[i] + 1];
        for (int j = 1; j <= a[i]; ++j) {
            lis[0][j]++;
        }
    }

    printf("%lld\n", ans);
    return 0;
}
