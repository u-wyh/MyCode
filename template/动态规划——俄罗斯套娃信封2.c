#include<stdio.h>
#define Max 100

static int w[Max],h[Max];

void select(int n)
{
    int i,j,min;
    for(i=0;i<n;i++)
    {
        min=i;
        for(j=i;j<n;j++)
            if(w[j]<w[min])
                min=j;
        if(min!=i)
        {
            int k1=w[min];
            int k2=h[min];
            w[min]=w[i];
            h[min]=h[i];
            w[i]=k1;
            h[i]=k2;
        }
    }
    for(i=0;i<n;i++)
        printf("%4d",w[i]);
    printf("\n");
    for(i=0;i<n;i++)
        printf("%4d",h[i]);
    printf("\n");
    printf("-------------------------------------------------------------------\n");
    for(i=0;i<n-1;i++)
    {
        for(j=i+1;j<n;j++)
        {
            if(w[i]==w[j])
            {
                if(h[i]<h[j])
                {
                    int k=h[i];
                    h[i]=h[j];
                    h[j]=k;
                }
            }
        }
    }
    for(i=0;i<n;i++)
        printf("%4d",w[i]);
    printf("\n");
    for(i=0;i<n;i++)
        printf("%4d",h[i]);
    printf("\n");
}

int bs1(int* ends, int len, int num) {
    int l = 0, r = len - 1, m, ans = -1;
    while (l <= r) {
        m = (l + r) / 2;
        if (ends[m] >= num) {
            ans = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
    return ans;
}
int lengthOfLIS2(int n) {
    int ends [n];
    // len表示ends数组目前的有效区长度
    // ends[0...len-1]是有效区，有效区内的数字一定严格升序
    int len = 0;
    for (int i = 0, find; i < n; i++) {
        find = bs1(ends, len, h[i]);
        if (find == -1) {
            ends[len++] = h[i];
        } else {
            ends[find] = h[i];
        }
    }
    return len;
}

int main()
{
    int i=0;
    while(scanf("%d %d",&w[i],&h[i++])==2);
    int n=i-1;
    printf("%d\n",n);
    select(n);
    printf("%5d\n",lengthOfLIS2(n));
    return 0;
}
