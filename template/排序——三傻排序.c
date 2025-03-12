#include<stdio.h>
#include<stdlib.h>
void select(int *arr)
{
    int i,temp,j,n,min;
    n=17;
    for(i=0;i<n;i++)
    {
        min=i;
        for(j=i;j<n;j++)
            if(arr[j]<arr[min])
                min=j;
        if(min!=i)
        {
            int k=arr[min];
            arr[min]=arr[i];
            arr[i]=k;
        }
    }
    for(i=0;i<n;i++)
        printf("%4d",arr[i]);
    printf("\n");
}
void bubble(int *arr)
{
    int i,j,n,temp;
    n=17;
    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-1;j++)
        {
            if(arr[j]>arr[j+1])
            {
                temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }
    for(i=0;i<n;i++)
        printf("%4d",arr[i]);
    printf("\n");
}
void insert(int *arr)
{
    int i,j,temp,n=17;
    for(i=1;i<n;i++)
    {
        for(j=i-1;arr[j]>arr[j+1]&&j>=0;j--)
        {
            temp=arr[j];
            arr[j]=arr[j+1];
            arr[j+1]=temp;
        }
    }
    for(i=0;i<n;i++)
        printf("%4d",arr[i]);
    printf("\n");
}
int main()
{
    int arr[17];
    for(int i=0;i<17;i++)
    {
        scanf("%d",&arr[i]);
    }
    printf("冒泡排序结果为： ");
    bubble(arr);
    printf("选择排序结果为： ");
    select(arr);
    printf("插入排序结果为： ");
    insert(arr);
    return 0;
}
