#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

bool f(int limit,int *nums,int n,int m)
{
    int sum=0;
    for(int i=1;i<=n;i++){
        if(nums[i]>=limit){
            m--;
        }else{
            sum+=nums[i];
        }
        if(sum>=m*limit)
            return true;
    }
    return false;
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int nums[n+1],r=0,l=0,mid,ans=-1;
    for(int i=1;i<=n;i++){
        scanf("%d",&nums[i]);
        r+=nums[i];
    }
    while(l<=r){
        mid=l+((r-l)>>1);
        if(f(mid,nums,n,m)){
            ans=mid;
            l=m+1;
        }else{
            r=m-1;
        }
    }
    printf("%d\n",ans);
    return 0;
}
