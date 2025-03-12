#include<stdio.h>

int main()
{
    int arr[100],i=0;
    printf("please enter the array: ");
    while(scanf("%d",&arr[i++])==1);
    int high,mid,low;
    high=i-1;
    low=0;
    printf("the result is : ");
    if(i==1)
        printf("%d",arr[0]);
    else
    {
        if(arr[0]>arr[1])
            printf("%d\n",arr[0]);
        else if(arr[high]>arr[high-1])
            printf("%d\n",arr[high]);
        else
        {
            while(low<=high)
            {
                mid=(low+high)/2;
                if(arr[mid]<arr[mid-1])
                    high=mid-1;
                else if(arr[mid+1]>arr[mid])
                    low=mid+1;
                else
                {
                    printf("%d\n",arr[mid]);
                    break;
                }
            }
        }
    }
    return 0;
}
