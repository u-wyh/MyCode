#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>
#define Max 100

static int dp[Max][Max];

int max(int a,int b)
{
    return a>b?a:b;
}

int min(int a,int b)
{
    return a<b?a:b;
}

int f1(int *nums,int l,int r)
{
    if(l==r)
        return nums[l];
    if(l+1==r)
        return max(nums[l],nums[r]);
    int p1=nums[l]+min(f1(nums,l+1,r-1),f1(nums,l+2,r));
    int p2=nums[r]+min(f1(nums,l+1,r-1),f1(nums,l,r-2));
    //这里之所以会出现min是因为下一步不该先手走了，后手会选取最大值，所以先手只有min
    return max(p1,p2);
}

bool predict(int *nums,int sum,int n)
{
    int a=f1(nums,0,n-1);
    return (2*a)>=sum;
}

//记忆化搜索

int f2(int *nums,int l,int r)
{
    if (dp[l][r] != -1) {
        return dp[l][r];
    }
    int ans;
    if (l == r) {
        ans = nums[l];
    } else if (l == r - 1) {
        ans = max(nums[l], nums[r]);
    } else {
        int p1 = nums[l] + min(f2(nums, l + 2, r), f2(nums, l + 1, r - 1));
        int p2 = nums[r] + min(f2(nums, l + 1, r - 1), f2(nums, l, r - 2));
        ans = max(p1, p2);
    }
    dp[l][r] = ans;
    return ans;
}

bool predict2(int *nums,int sum,int n)
{
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            dp[i][j] = -1;
        }
    }
    int first = f2(nums, 0, n - 1);
    return 2 * first >= sum;
}
int main()
{
    int nums[Max];
    //int i=0;
    int t;
    printf("please enter the t: ");
    scanf("%d",&t);
    //while(scanf("%d",&nums[i])==1)
        //sum+=nums[i++];
    //int n=i;
    //n是数组实际有效长度
    srand(time(NULL));
    for(int i=0;i<t;i++)
    {
        int n=rand()%30+1;
        int sum=0;
        for(int j=0;j<n;j++)
        {
            nums[j]=rand()%100+1;
            sum+=nums[j];
        }

        if(predict(nums,sum,n))
            printf("first\n");
        else
            printf("second\n");
        if(predict2(nums,sum,n))
            printf("first\n");
        else
            printf("second\n");

        printf("------------------------------------------------------------------\n");

    }
    return 0;
}
