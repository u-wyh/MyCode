#include<stdio.h>
#include<limits.h>
#define Max 10000

static int cuts[Max];
static int help[Max];
static int dp[Max][Max];

void merge(int l,int m,int r)
{
    int a=l;
    int b=m+1;
    int i=l;
    while(a<=m&&b<=r)
        help[i++]=cuts[a]<=cuts[b]?cuts[a++]:cuts[b++];
    while(a<=m)
        help[i++]=cuts[a++];
    while(b<=r)
        help[i++]=cuts[b++];
    for(i=l;i<=r;i++)
        cuts[i]=help[i];
}
void mergesort(int l,int r)
{
    if(l>=r)
        return ;
    int m=(l+r)/2;
    mergesort(l,m);
    mergesort(m+1,r);
    merge(l,m,r);
}

int min(int a,int b)
{
    return a<b?a:b;
}

int f(int* arr, int l, int r) {
    if (l > r) {
			return 0;
    }
    if (l == r) {
			return arr[r + 1] - arr[l - 1];
    }
    if (dp[l][r] != -1) {
        return dp[l][r];
    }
    int ans = INT_MAX;
    for (int k = l; k <= r; k++) {
        ans = min(ans, f(arr, l, k - 1) + f(arr, k + 1, r));
    }
    ans += arr[r + 1] - arr[l - 1];
    dp[l][r] = ans;
    return ans;
}

int minCost1(int h, int* cuts,int n) {
    int arr [n + 2];
    arr[0] = 0;
    for (int i = 1; i <= n; ++i)
    {
        arr[i] = cuts[i - 1];
    }
    arr[n + 1] = h;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dp[i][j] = -1;
        }
    }
    return f(arr, 1, n);
}

int main()
{
    int h;
    scanf("%d",&h);
    int i=0;
    while(scanf("%d",&cuts[i++])==1);
    int  n=i-1;
    mergesort(0,n-1);
    printf("%d\n",minCost1(h,cuts,n));
    return 0;
}
