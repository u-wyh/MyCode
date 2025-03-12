#include<stdio.h>

int main()
{
    long long a,b,p,A,B;
    scanf("%lld %lld %lld",&a,&b,&p);
    A=a;
    B=b;
    long long ans=1;
    while (b > 0) {
        if ((b & 1) == 1) {
            ans = (ans * a) % p;
        }
        a = (a * a) % p;
        b >>= 1;
    }
    printf("%lld^%lld mod %lld =%lld\n",A,B,p,ans);
    return 0;
}
