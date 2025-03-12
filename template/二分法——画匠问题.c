#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

int f(int *nums,int limit,int n){
    int parts=1;
    int sum=0;
    for(int i=1;i<=n;i++){
        if(nums[i]>limit)
            return INT_MAX;
        if(sum+nums[i]>limit){
            parts++;
            sum=nums[i];
        } else {
            sum+=nums[i];
        }
    }
    return parts;
}

int main()
{
    int n,k;
    scanf("%d %d",&n,&k);
    int a[n+1],sum=0;
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        sum+=a[i];
    }
    int l=0,r=sum,mid,ans;
    while(l<=r){
        mid=l+((r-l)>>1);
        if(f(a,mid,n)<=k){
            ans=mid;
            r=mid-1;
        }else{
            l=mid+1;
        }
    }
    printf("%d\n",ans);
    return 0;
}
