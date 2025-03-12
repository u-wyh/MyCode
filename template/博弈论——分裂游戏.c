#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 21
#define MAXV 101

int sg[MAXN];
int nums[MAXN];
int appear[MAXV];

void build() {
    for (int i = 1; i < MAXN; i++) {
        memset(appear, 0, sizeof(appear));
        for (int j = i - 1; j >= 0; j--) {
            for (int k = j; k >= 0; k--) {
                appear[sg[j] ^ sg[k]] = 1;
            }
        }
        for (int s = 0; s < MAXV; s++) {
            if (!appear[s]) {
                sg[i] = s;
                break;
            }
        }
    }
}

int main() {
    int t, n;
    build();

    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &nums[n - 1 - i]);
        }

        char result[100];
        int eor = 0;
        for (int i = 0; i < n; i++) {
            if (nums[i] % 2 == 1) {
                eor ^= sg[i];
            }
        }

        if (eor == 0) {
            sprintf(result, "-1 -1 -1\n0");
        } else {
            int cnt = 0, a = -1, b = -1, c = -1;
            for (int i = n - 1; i >= 1; i--) {
                if (nums[i] > 0) {
                    for (int j = i - 1; j >= 0; j--) {
                        for (int k = j; k >= 0; k--) {
                            int pos = eor ^ sg[i] ^ sg[j] ^ sg[k];
                            if (pos == 0) {
                                cnt++;
                                if (a == -1) {
                                    a = i;
                                    b = j;
                                    c = k;
                                }
                            }
                        }
                    }
                }
            }
            sprintf(result, "%d %d %d\n%d\n", n - 1 - a, n - 1 - b, n - 1 - c, cnt);
        }

        printf("%s", result);
    }

    return 0;
}
