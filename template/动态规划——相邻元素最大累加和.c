#include<stdio.h>
#define Max 100

int main()
{
    int arr[Max];
    int i=0;
    while(scanf("%d",&arr[i++])==1);
    int n=i-1;
    //n是数组有效长度
    printf("%5d\n",n);
    int max=0,sum=0;
    for(i=0;i<n;i++)
    {
        sum+=arr[i];
        if(sum<0)
            sum=0;
        if(sum>max)
            max=sum;
    }
    printf("%d\n",max);
    return 0;
}
