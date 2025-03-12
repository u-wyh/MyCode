#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#define MAX_TESTS 10

// 快速幂函数，计算 (base^exp) % mod
int64_t qpow(int64_t base, int64_t exp, int64_t mod) {
    int64_t result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

// Miller-Rabin素数测试
bool miller_rabin(int64_t n, int s) {
    if (n < 3 || n % 2 == 0) return n == 2;

    int64_t u = n - 1, t = 0;
    while (u % 2 == 0) {
        u /= 2;
        t++;
    }

    int64_t primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    for (int i = 0; i < s && primes[i] < n; i++) {
        int64_t a = primes[i];
        if (n % a == 0) return false;

        int64_t x = qpow(a, u, n);
        if (x == 1 || x == n - 1) continue;

        for (int j = 1; j < t; j++) {
            x = (x * x) % n;
            if (x == n - 1) break;
        }

        if (x != n - 1) return false;
    }

    return true;
}

int main() {
    int t;
    scanf("%d", &t);

    char buffer[100]; // 假设数字不会太长，足以用字符串读取
    while (t--) {
        scanf("%s", buffer);
        int64_t n = strtoll(buffer, NULL, 10);

        if (miller_rabin(n, MAX_TESTS)) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }

    return 0;
}
