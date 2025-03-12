#include<stdio.h>
#include<limits.h>

int min(int a,int b)
{
    return a<b?a:b;
}

int main()
{
    int n;
    scanf("%d",&n);
    int nums[n+1];
    int k=INT_MAX,max=0;
    int profit[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i]);
        k=min(k,nums[i]);
        profit[i]=nums[i]-k;
        if(profit[i]>max)
            max=profit[i];
    }
    printf("%d\n",max);
    return 0;
}
