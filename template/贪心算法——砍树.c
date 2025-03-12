#include <stdio.h>
#include <stdlib.h>

#define MAXN 251

int tree[MAXN][2];
int dp[MAXN][MAXN];
int t, n, m;

void read_input(FILE *fp) {
    fscanf(fp, "%d", &t);
    for (int i = 0; i < t; i++) {
        fscanf(fp, "%d %d", &n, &m);
        for (int j = 1; j <= n; j++) {
            fscanf(fp, "%d", &tree[j][0]);
        }
        for (int j = 1; j <= n; j++) {
            fscanf(fp, "%d", &tree[j][1]);
        }
        // Perform the computation for this test case
        printf("%d\n", compute());
    }
}

int compare(const void *a, const void *b) {
    int *ia = *(int **)a;
    int *ib = *(int **)b;
    return ia[1] - ib[1];
}

int compute() {
    // Sort trees based on growth rate (ascending)
    int *temp[MAXN];
    for (int i = 1; i <= n; i++) {
        temp[i] = tree[i];
    }
    qsort(temp + 1, n, sizeof(int *), compare);

    // Initialize dp array
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            dp[i][j] = 0;
        }
    }

    // Fill dp array
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (j >= 1) {
                dp[i][j] = dp[i - 1][j]; // Not cutting this tree
                if (j >= i) { // Enough days to cut this tree
                    dp[i][j] = dp[i - 1][j - 1] + temp[i][0] + temp[i][1] * (j - 1) > dp[i][j] ?
                               dp[i - 1][j - 1] + temp[i][0] + temp[i][1] * (j - 1) : dp[i][j];
                }
            }
        }
    }

    // Return the result for the last day and last tree
    return dp[n][m];
}

int main() {
    FILE *fp = stdin; // Or fopen("input.txt", "r"); for file input
    read_input(fp);
    fclose(fp); // Only if using file input
    return 0;
}
