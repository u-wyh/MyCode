#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#define Max 100001

static int arr[Max];
static int help[Max];
static int cnts[10];

void radixsort(int bit,int t)
{
    for(int offset=1;bit>0;offset*=10,bit--)
    {
        for(int i=0;i<10;i++)
        {
            cnts[i]=0;
        }
        for(int i=0;i<t;i++)
        {
            cnts[(arr[i]/offset)%10]++;
        }
        for(int i=1;i<10;i++)
        {
            cnts[i]=cnts[i]+cnts[i-1];
        }
        for(int i=t-1;i>=0;i--)
        {
            help[--cnts[(arr[i]/offset)%10]]=arr[i];
        }
        for(int i=0;i<t;i++)
        {
            arr[i]=help[i];
        }
    }
}

int main()
{
    int t,bit=0;
    scanf("%d",&t);
    srand(time(NULL));//种下随机数种子
    int max=0,k=1;//初始化max  k值
    for(int i=0;i<t;i++)
    {
        arr[i]=rand()%100;
        if(max<arr[i])
            max=arr[i];//得到数组的最大值
        printf("%5d",arr[i]);
    }
    printf("\n");

    while(max>=k)
    {
        k*=10;
        bit++;
    }
    printf("%d\n",bit);
    radixsort(bit,t);
    for(int i=0;i<t;i++)
        printf("%5d",arr[i]);
    return 0;
}
