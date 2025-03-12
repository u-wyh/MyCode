#include <stdio.h>

// 计算b的n次方的结果%mod
long long power(long long b, int n, int mod) {
    long long ans = 1;
    while (n > 0) {
        if (n & 1) {
            ans = (ans * b) % mod;
        }
        b = (b * b) % mod;
        n >>= 1;
    }
    return ans;
}

// 第一个计算方法（注意：这里直接进行除法可能不是整数除法）
int compute1(long long a, long long b, int mod) {
    if (b == 0) return -1; // 防止除以0
    return (a / b) % mod; // 注意：这里a/b可能是非整数，结果可能不是预期
}

// 第二个计算方法，使用模逆元
int compute2(long long a, long long b, int mod) {
    if (b == 0) return -1; // 防止除以0
    long long inv = power(b, mod - 2, mod);
    return (int)(((a % mod) * inv) % mod);
}

int main() {
    int mod;
    scanf("%d",&mod);
    long long a,b;
    scanf("%lld %lld",&a,&b);

    printf("%d\n", compute1(a, b, mod)); // 注意：这个方法可能不是整数除法，结果可能不符合预期
    printf("%d\n", compute2(a, b, mod));

    return 0;
}
