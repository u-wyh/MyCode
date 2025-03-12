#include<stdio.h>
#include<string.h>
#define Max 10000

int main()
{
    char s1[Max];
    scanf("%s",s1);
    int n=strlen(s1);
    int nums[10],ans[n+1];
    for(int i=0;i<=9;i++){
        nums[i]=0;
    }
    for(int i=0;i<n;i++){
        nums[s1[i]-'0']++;
    }
    int mid=0,left=0;
    for(int i=9;i>=1;i--){
        if(nums[i]%2==1&&mid==0){
            mid=i;
        }
        while(nums[i]>1){
            ans[left++]=i;
            nums[i]-=2;
        }
    }
    int len;
    if(left==0){
        if(mid==0){
            printf("0\n");
        }else{
            printf("%d\n",mid);
        }
        return 0;
    }else{
        for(int i=1;i<=nums[0]/2;i++)
            ans[left++]=0;
        if(mid!=0||nums[0]%2==1){
            ans[left]=mid;
            for(int i=0;i<left;i++){
                ans[left*2-i]=ans[i];
            }
            len=left*2;
        }else{
            for(int i=0;i<left;i++){
                ans[left*2-i-1]=ans[i];
            }
            len=left*2-1;
        }
    }
    for(int i=0;i<=len;i++){
        printf("%d",ans[i]);
    }
    return 0;
}
