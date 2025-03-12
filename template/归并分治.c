#include<stdio.h>

static int arr[100];
static int help[100];
static int n;

int smallSum(int l, int r) {
    if (l == r) {
        return 0;
    }
    int m = (l + r) / 2;
    return smallSum(l, m) + smallSum(m + 1, r) + merge(l, m, r);
}

int merge(int l, int m, int r) {
    // 统计部分
    int ans = 0;
    for (int j = m + 1, i = l, sum = 0; j <= r; j++) {
        while (i <= m && arr[i] <= arr[j]) {
            sum += arr[i++];
        }
        ans += sum;
    }
    // 正常merge
    int i = l;
    int a = l;
    int b = m + 1;
    while (a <= m && b <= r) {
        help[i++] = arr[a] <= arr[b] ? arr[a++] : arr[b++];
    }
    while (a <= m) {
        help[i++] = arr[a++];
    }
    while (b <= r) {
        help[i++] = arr[b++];
    }
    for (i = l; i <= r; i++) {
        arr[i] = help[i];
    }
    return ans;
}
int main()
{
    for(int i=0;i<20;i++)
    {
        scanf("%d",&arr[i]);
    }
    printf("%d\n",smallSum(0,19));
    for(int i=0;i<20;i++)
    {
        printf("%4d",arr[i]);
    }
    return 0;
}
