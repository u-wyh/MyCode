#include<stdio.h>

void insert(int *arr,int n)
{
    int i,j,temp;
    for(i=2;i<=n;i++)
    {
        for(j=i-1;arr[j]>arr[j+1]&&j>=1;j--)
        {
            temp=arr[j];
            arr[j]=arr[j+1];
            arr[j+1]=temp;
        }
    }
}
int main()
{
    int n;
    scanf("%d",&n);
    int nums[2*n+1][2];
    int arr[2*n+1];
    for(int i=1;i<=2*n;i++)
    {
        for(int j=0;j<2;j++)
        {
            scanf("%d",&nums[i][j]);
        }
    }
    int sum=0;
    for(int i=1;i<=2*n;i++)
    {
        sum+=nums[i][0];
        arr[i]=nums[i][1]-nums[i][0];
    }
    insert(arr,2*n);
    for(int i=1;i<=n;i++)
        sum+=arr[i];
    printf("%d\n",sum);
    return 0;
}
