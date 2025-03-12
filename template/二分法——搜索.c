#include<stdio.h>

int main()
{
    int arr[100],m,i=0,ans=-1;
    printf("please enter the number that you want to find: ");
    scanf("%d",&m);
    printf("please enter the array: ");
    while(scanf("%d",&arr[i++])==1);
    int high,mid,low;
    high=i-1;
    low=0;
    while(high>=low)
    {
        mid=(low+high)/2;
        if(arr[mid]>m)
            high=mid-1;
        else if(arr[mid]<m)
            low=mid+1;
        else
            break;
    }
    if(low>high)
    {
        printf("No\n");
    }
    else
        printf("the %d number is that you want\n",mid+1);

    high=i;
    low=0;
    while(high>=low)
    {
        mid=(low+high)/2;
        if(arr[mid]>=m)
        {
            high=mid-1;
            ans=mid;
        }
        else
            low=mid+1;
    }
    printf("the min number that bigger than m is %d",arr[ans]);
    return 0;
}
