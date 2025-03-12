#include<stdio.h>
#include<limits.h>

int min(int a,int b)
{
    return a<b?a:b;
}

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int n;
    scanf("%d",&n);
    int nums[n];
    for(int i=0;i<n;i++)
        scanf("%d",&nums[i]);
    int Max=INT_MIN;
    int right=-1;
    for(int i=0;i<n;i++)
    {
        if(nums[i]<Max)
        {
            right=i;
        }
        Max=max(Max,nums[i]);
    }
    int Min=INT_MAX;
    int left=n;
    for(int i=n-1;i>=0;i--)
    {
        if(nums[i]>Min)
        {
            left=i;
        }
        Min=min(Min,nums[i]);
    }
    printf("%d\n",max(0,right-left+1));
    return 0;
}
