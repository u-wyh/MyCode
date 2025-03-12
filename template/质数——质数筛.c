#include <stdio.h>
#include <string.h>

// 埃氏筛统计0 ~ n范围内的质数个数
// 时间复杂度O(n * log(logn))
int ehrlich(int n) {
    // 初始时认为0~n所有数都是质数，但0和1不是质数
    int visit[n + 1];
    memset(visit, 0, sizeof(visit)); // 0表示质数，1表示合数

    for (int i = 2; i * i <= n; i++) {
        if (!visit[i]) {
            for (int j = i * i; j <= n; j += i) {
                visit[j] = 1; // 标记为合数
            }
        }
    }

    int cnt = 0;
    for (int i = 2; i <= n; i++) {
        if (!visit[i]) {
            cnt++; // 计数质数
        }
    }

    return cnt;
}

// 欧拉筛统计0 ~ n范围内的质数个数
// 时间复杂度O(n)
int euler(int n) {
    int visit[n + 1];
    memset(visit, 0, sizeof(visit)); // 0表示质数，1表示合数
    int prime[n / 2 + 1];
    int cnt = 0;

    for (int i = 2; i <= n; i++) {
        if (!visit[i]) {
            prime[cnt++] = i;
        }

        for (int j = 0; j < cnt && i * prime[j] <= n; j++) {
            //每一次从最小的质数开始
            visit[i * prime[j]] = 1; // 标记为合数
            if (i % prime[j] == 0) {
                //如果i可以整除prime[j]说明一定含有这个质因子
                //那么如果继续的话  就是将接下来的数字的按照下一个质数排除
                //不是最小质因子排除的
                break; // 每个合数只被其最小的质因数筛去一次
            }
        }
    }

    return cnt;
}

// 改进版埃氏筛，仅计数
int ehrlich2(int n) {
    if (n <= 1) {
        return 0;
    }

    int visit[n + 1];
    memset(visit, 0, sizeof(visit)); // 0表示质数，1表示合数

    // 初始估计的质数数量，只考虑奇数
    int cnt = (n + 1) / 2;

    for (int i = 3; i * i <= n; i += 2) {
        if (!visit[i]) {
            for (int j = i * i; j <= n; j += 2 * i) {
                if (!visit[j]) {
                    visit[j] = 1; // 标记为合数
                    cnt--;
                }
            }
        }
    }
    return cnt;
}

int main() {
    int n ;
    scanf("%d",&n);
    printf("Ehrlich's Sieve: %d\n", ehrlich(n));
    printf("Euler's Sieve: %d\n", euler(n));
    printf("Optimized Ehrlich's Sieve: %d\n", ehrlich2(n));
    return 0;
}
