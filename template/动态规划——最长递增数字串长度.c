#include<stdio.h>
#include<string.h>
#define maxest 100

static int a[maxest][maxest];

int f1(int i,int j,int m,int n)
{
    int next = 0;
    if (i > 0 && a[i][j] < a[i - 1][j]) {
        next = max(next, f1( i - 1, j,m,n));
    }
    if (i + 1 < m && a[i][j] < a[i + 1][j]) {
        next = max(next, f1( i + 1, j,m,n));
    }
    if (j > 0 && a[i][j] < a[i][j - 1]) {
        next = max(next, f1( i, j - 1,m,n));
    }
		if (j + 1 < n && a[i][j] < a[i][j + 1]) {
        next = max(next, f1( i, j + 1,m,n));
    }
    return next + 1;
}
int max(int a,int b)
{
    return a>b?a:b;
}
int main()
{
    int m,n;
    printf("please enter the n and m: ");
    scanf("%d %d",&n,&m);
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            scanf("%d",&a[i][j]);
        }
    }
    int ans=0;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            ans=max(ans,f1(i,j,m,n));
        }
    }
    printf("%5d\n",ans);
    return 0;
}
