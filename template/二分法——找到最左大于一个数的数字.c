#include<stdio.h>
#include<stdlib.h>

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int nums[n];
    for(int i=0;i<n;i++){
        scanf("%d",&nums[i]);
    }
    int ans=-1,l=0,r=n-1;
    int mid=(l+r)/2;
    while(l<=r){
        if(nums[mid]>=m){
            ans=mid;
            r=mid-1;
        } else {
            l=mid+1;
        }
        mid=(l+r)/2;
    }
    printf("%d\n",ans);
    return 0;
}
