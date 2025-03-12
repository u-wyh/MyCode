#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 100001

int nums[MAXN];
int dp[MAXN];
int ends[MAXN];
int ans[MAXN];
int n, k;

void lis() {
    k = dp_fill();
    for (int i = 0; i < k; i++) {
        ans[i] = INT_MAX;
    }

    for (int i = 0; i < n; i++) {
        if (dp[i] == k) {
            ans[0] = nums[i];
        } else {
            if (ans[k - dp[i] - 1] < nums[i]) {
                ans[k - dp[i]] = nums[i];
            }
        }
    }
}

int dp_fill() {
    int len = 0;
    for (int i = n - 1; i >= 0; i--) {
        int find = binary_search(len, nums[i]);
        if (find == -1) {
            ends[len++] = nums[i];
            dp[i] = len;
        } else {
            ends[find] = nums[i];
            dp[i] = find + 1;
        }
    }
    return len;
}

int binary_search(int len, int num) {
    int l = 0, r = len - 1, m, ans = -1;
    while (l <= r) {
        m = (l + r) / 2;
        if (ends[m] <= num) {
            ans = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
    return ans;
}

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 0; i < n; i++) {
            scanf("%d", &nums[i]);
        }

        lis();

        for (int i = 0; i < k - 1; i++) {
            printf("%d ", ans[i]);
        }
        printf("%d\n", ans[k - 1]);
    }

    return 0;
}
