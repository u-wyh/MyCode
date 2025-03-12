#include<stdio.h>
#include<stdlib.h>

int cmp(const void *a,const void *b){
    return (*(int *)a-*(int *)b);
}

int f(int *arr,int limit,int n){
    int ans = 0;
    for (int l = 1, r = 1; l <= n; l++) {
        while (r + 1 <= n&& arr[r + 1] - arr[l] <= limit) {
            r++;
        }
        ans += r - l;
    }
    //»¬¶¯´°¿Ú
    return ans;
}

int main()
{
    int n,k;
    scanf("%d %d",&n,&k);
    int a[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    qsort(a+1,n,sizeof(int),cmp);
    int ans = 0;
    for (int l = 0, r =a[n] -a[1], m, cnt; l <= r;) {
        m = l + ((r - l) >> 1);
        cnt = f(a,m,n);
        if (cnt >= k) {
            ans = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
    printf("%d\n",ans);
    return 0;
}
