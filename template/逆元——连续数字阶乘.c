#include <stdio.h>

#define MOD 1000000007
#define LIMIT 1000

// 阶乘表
long long fac[LIMIT + 1];
// 阶乘的逆元表
long long inv[LIMIT + 1];

// 快速幂计算 a^b % MOD
long long power(long long a, int b) {
    long long ans = 1;
    a = a % MOD;
    while (b > 0) {
        if (b & 1) {
            ans = (ans * a) % MOD;
        }
        a = (a * a) % MOD;
        b >>= 1;
    }
    return ans;
}

// 构建阶乘表和逆元表
void build() {
    fac[0] = 1;
    for (int i = 1; i <= LIMIT; i++) {
        fac[i] = (fac[i - 1] * i) % MOD;
    }
    inv[LIMIT] = power(fac[LIMIT], MOD - 2);
    for (int i = LIMIT - 1; i >= 0; i--) {
        inv[i] = (inv[i + 1] * (i + 1)) % MOD;
    }
}


int c1(int n, int m) {
    // 特殊情况处理
    if (m > n) return 0;
    if (m == 0 || m == n) return 1;
    // 使用逆元计算组合数
    long long ans = ((inv[m] * inv[n-m]) % MOD) * power(inv[n], MOD - 2) % MOD;
    return (int)ans;
}


// 计算组合数 C(n, m) % MOD，使用阶乘表和逆元表
int c2(int n, int m) {
    long long ans = fac[n];
    ans = (ans * inv[m]) % MOD;
    ans = (ans * inv[n - m]) % MOD;
    return (int)ans;
}


int main() {
    printf("测试开始\n");
    build();

    int n = 500;
    for (int m = 0; m <= n; m++) {
        int ans2 = c2(n, m);
        int ans3 = c1(n, m);
        // 注意：没有c1函数进行比较，因为C语言处理不了大数直接除法
        printf("C(%d, %d) %% %d = %d  %d\n", n, m, MOD, ans2,ans3);
    }

    printf("测试结束\n");
    //这个测试是Cn m  m从0到500  n==500

    int a ;
    int b ;
    scanf("%d %d",&a,&b);
    printf("计算 C ( %d , %d ) %% %d\n", a, b, MOD);
    printf("方法答案 : %d\n", c2(a, b));
    printf("方法答案 : %d\n", c1(a, b));
    return 0;
}
