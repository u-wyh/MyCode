#include<stdio.h>

int recursion(int *arr,int left,int right)
{
    if(left==right)
        return arr[left];
    int mid=(left+right)/2;
    int a=recursion(arr,left,mid);
    int b=recursion(arr,mid+1,right);
    return a>b?a:b;
}
int main()
{
    int arr[100],i=0;
    while(scanf("%d",&arr[i])==1)
    {
        i++;
    }
    printf("%d",recursion(arr,0,i));
    return 0;
}
