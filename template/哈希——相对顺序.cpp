//P8085
#include <bits/stdc++.h>
using namespace std;
const int INF = 2147483647;
const int MAXN = 1e6 + 3;
const int BASE = 13131;

int L1[MAXN], R1[MAXN];
int L2[MAXN], R2[MAXN];
int A[MAXN], B[MAXN], n, m;
long long H[MAXN], P[MAXN];
map<string, int> M;

int main() {
    string t;

    // Read first set of strings
    while (cin >> t && t != "$") {
        R1[M[t]] = ++n;//表示这个词语右边最早再次出现的位置
        L1[n] = M[t];//表示这个词语左边最早再次出现的位置
        M[t] = n;
    }

    M.clear();

    // Read second set of strings
    while (cin >> t && t != "$") {
        R2[M[t]] = ++m;
        L2[m] = M[t];
        M[t] = m;
    }

    // Set default values for R1 and R2 if they are not defined
    for (int i = 1; i <= n; ++i) if (!R1[i]) R1[i] = INF;
    for (int i = 1; i <= m; ++i) if (!R2[i]) R2[i] = INF;//如果右边没有出现过

    // Calculate prefix distances for both sets
    for (int i = 1; i <= n; ++i) A[i] = (L1[i] ? i - L1[i] : -1);
    for (int i = 1; i <= m; ++i) B[i] = (L2[i] ? i - L2[i] : -1);//该位置的单词距离自己左边出现最早位置的距离

    long long h0 = 0, h = 0;
    P[0] = 1;
    for (int i = 1; i <= m; ++i) P[i] = P[i - 1] * BASE;

    // Calculate initial hash values for B and A
    for (int i = 1; i <= m; ++i) h0 = h0 * BASE + B[i];//h0是我们所要求的
    for (int i = 1; i <= m; ++i) h = h * BASE + A[i];

    // Check if the initial hashes match
    if (h == h0) {
        cout << 1 << endl;
        return 0;
    }

    // Slide the window over A and check for matches
    for (int i = m + 1; i <= n; ++i) {
        // Update hash values for the new window in A
        h = h * BASE + A[i] - A[i - m] * P[m];//还没有完全修正前的哈希值

        // Adjust hash if necessary due to overlapping in R1
        if (R1[i - m] <= i) {//即引发的变化在如今查询的范围中
            int overlapIndex = R1[i - m];
            h -= A[overlapIndex] * P[i - overlapIndex];//减去错误的哈希值
            A[overlapIndex] = -1;  // Mark as invalid for further use
            h += A[overlapIndex] * P[i - overlapIndex];  // 加上修正后的哈希值
        } else if (R1[i - m] <= n) {
            A[R1[i - m]] = -1;  // Just mark as invalid if it falls within bounds
        }

        // Check if the current hash matches h0
        if (h == h0) {
            cout << i - m + 1 << endl;
            return 0;
        }
    }

    // No match found
    return 0;
}
