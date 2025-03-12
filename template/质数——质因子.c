#include<stdio.h>

int main()
{
    long long n;
    scanf("%lld",&n);
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            printf("%d\n",i);
            while (n % i == 0) {
                n /= i;
            }
        }
    }
    if (n > 1) {
        printf("%d\n",n);
    }
    return 0;
}
