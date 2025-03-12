#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define eps 1e-3
#define MAX_N 100005

int n;
ll k;
int a[MAX_N], c[MAX_N]; // a 毫升, c 温度
double p[MAX_N], q[MAX_N];

int cmp(const void *a, const void *b) {
    double d1 = *(double *)a;
    double d2 = *(double *)b;
    return d1 < d2 ? -1 : (d1 > d2 ? 1 : 0);
}
//从小到大

int check(double v) {
    ll tot = 0;
    for (int i = 1; i <= n; i++) {
        double x = a[i] * 1.0 * c[i], y = v * a[i];
        p[i] = x - y;
        q[i] = y - x;
        if (q[i] - p[i] < eps) tot--;
    }
    //首先减去自己与自己的可能性  因为这个不需要除以2  如果不提前减去  答案不好算
    qsort(p + 1, n, sizeof(double), cmp);
    qsort(q + 1, n, sizeof(double), cmp);
    int j = 0;
    for (int i = 1; i <= n; i++) {
        while ((q[j + 1] <= p[i]) && j + 1 <= n) j++;
        tot += j;
    }
    return (tot / 2 < k);
    //解释为什么要除以2
    //i是5 -5(必然)  j是2 -2
    //那么就会有ij(5  -2)  和ji(2  -5)  导致多算两倍
    //并且ii(5 -5)  jj(2  -2)也会被加上   但是之前已经减去了
}

int main() {
    scanf("%d%lld", &n, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &a[i], &c[i]);
    }
    double l = 1, r = 1000000000, mid;
    //这里r初始值可以是c[i]的最大值就可以了
    while ((r - l) > eps) {
        mid = (l + r) / 2;
        if (check(mid)) {
            r = mid;
        } else {
            l = mid;
        }
    }
    printf("%.3f\n", l);
    return 0;
}
