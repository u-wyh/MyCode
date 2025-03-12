#include<stdio.h>
#include<stdlib.h>

int cmp(const void *a,const void *b){
    return (*(int *)a-*(int *)b);
}

int f(int *nums,int speed,int n){
    int ans=0;
    for(int i=1;i<=n;i++){
        ans+=(nums[i]+speed-1)/speed;
    }
    return ans;
}

int main()
{
    int n,t;
    scanf("%d %d",&n,&t);
    int a[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    qsort(a+1,n,sizeof(int),cmp);
    int l=1,r=a[n];
    int ans=0,mid=0;
    while(l<=r){
        mid=l+((r-l)>>1);
        if(f(a,mid,n)<=t){
            ans=mid;
            r=mid-1;
        } else {
            l=mid+1;
        }
    }
    printf("%d\n",ans);
    return 0;
}
