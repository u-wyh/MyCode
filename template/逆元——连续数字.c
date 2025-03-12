#include <stdio.h>
#include <stdlib.h>

#define MAXN 3000001

int inv[MAXN];
int n, p;

// 快速幂函数，计算 base^exp % mod
long long power(long long base, int exp, int mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

// 预计算模逆元
void build(int n, int mod) {
    inv[1] = 1;
    for (int i = 2; i <= n; i++) {
        inv[i] = (mod - (long long)inv[mod % i] * (mod / i) % mod + mod) % mod;
    }
}

int main() {
    scanf("%d %d", &n, &p);
    build(n, p);

    for (int i = 1; i <= n; i++) {
        printf("%d\n", inv[i]);
    }

    return 0;
}
