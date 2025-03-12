#include<stdio.h>
#include<stdbool.h>

int max(int a,int b){
    return a>b?a:b;
}

bool f(int *nums,int energy,int n,int max){
    for(int i=1;i<=n;i++){
        if(energy>=nums[i]){
            energy+=(energy-nums[i]);
        } else {
            energy-=(nums[i]-energy);
        }
        if(energy>=max){
            return true;
        }
        if(energy<=0){
            return false;
        }
    }
    return true;
}

int main()
{
    int n;
    scanf("%d",&n);
    int a[n+1],l=0,r,mid,ans,Max;
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        Max=max(a[i],r);
    }
    r=Max;
    while(l<=r){
        mid=l+((r-l)>>1);
        if(f(a,mid,n,Max)){
            r=mid-1;
            ans=mid;
        } else {
            l=mid+1;
        }
    }
    printf("%d\n",ans);
    return 0;
}
