#include <stdio.h>

// Function to find the number of trailing zeros in binary representation of a number
// using similar logic as in the Java code
int lowZero(int status) {
    int ans = 0;
    while (status > 0) {
        if ((status & 1) == 0) break;
        status >>= 1;
        ans++;
    }
    return ans;
}

int main() {
    int t, n, a, b, sg;

    // Read the number of test cases
    scanf("%d", &t);

    while (t--) {
        // Read the number of pairs
        scanf("%d", &n);

        sg = 0;

        // Iterate over each pair (considering only odd indices)
        for (int j = 1; j <= n; j += 2) {
            scanf("%d %d", &a, &b);

            // Perform the XOR operation with the lowZero result of bitwise OR of (a-1) and (b-1)
            sg ^= lowZero((a - 1) | (b - 1));
        }

        // Print the result
        if (sg != 0) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }

    return 0;
}
