#include<stdio.h>

int main()
{
    int t;
    scanf("%d",&t);
    for(int i=1;i<=t;i++){
        int n;
        scanf("%d",&n);
        int nums[n+1],eor=0,sum=0;
        for(int i=1;i<=n;i++){
            scanf("%d",&nums[i]);
            eor^=nums[i];
            sum+=nums[i];
        }
        if(sum==n&&sum%2==0){
            printf("John\n");
        }else if(sum==n&&sum%2==1){
            printf("Brother\n");
        }else{
            if(eor==0){
                printf("Brother\n");
            }else{
                printf("John\n");
            }
        }
    }
    return 0;
}
