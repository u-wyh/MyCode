#include<stdio.h>
#define Max 1000

int n,m;
int nums[Max][Max];

void dfs(int i, int j) {
    if (i < 0 || i == n || j < 0 || j == m || nums[i][j] != 1) {
        return;
    }
    nums[i][j]=2;
    dfs(i-1,j);
    dfs(i,j-1);
    dfs(i+1,j);
    dfs(i,j+1);
}

int main()
{
    scanf("%d %d",&n,&m);
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            scanf("%d",&nums[i][j]);
        }
    }
    for(int i=0;i<m;i++)
    {
        if(nums[0][i]==1)
        {
            dfs(0,i);
        }
        if(nums[n-1][i]==1)
        {
            dfs(n-1,i);
        }
    }
    for(int i=1;i<n-1;i++)
    {
        if(nums[i][0]==1)
        {
            dfs(i,0);
        }
        if(nums[i][m-1]==1)
        {
            dfs(i,m-1);
        }
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            if(nums[i][j]==1)
                nums[i][j]=0;
            else if(nums[i][j]==2)
                nums[i][j]=1;
        }
        //printf("\n");
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            printf("%2d",nums[i][j]);
        }
        printf("\n");
    }
    return 0;
}
