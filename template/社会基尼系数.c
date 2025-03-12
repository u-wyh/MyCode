#include<stdio.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>

double Gini(int *arr,int n)
{
    int i,j;
    int Deviation = 0 ,Total = n*100;//社会总财富初始时是平均每个人100
    double G;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            Deviation+=abs(arr[i]-arr[j]);
        }
    }
    G=Deviation*1.0/(2*n*Total);
    return G;
}
//计算社会基尼系数的公式


int main()
{
    int n,t;
    printf("please enter the number of people: ");
    scanf("%d",&n);
    printf("please enter the number of rounds: ");
    scanf("%d",&t);
    //完成数据的输入  包括轮数和人数
    int arr[n];
    for(int i=0;i<n;i++){
        arr[i]=100;
    }
    //定义初始时所有人的财富
    srand(time(NULL));//随机数种子
    for(int i=1;i<=t;i++)
    {
        for(int j=0;j<n;j++)
        {
            int other=rand()%n;
            //printf("%5d",other);//可以检查是不是随机生成的
            if(arr[j]!=0)
            {
                if(other==j)
                    other++;
                else
                {
                    arr[j]--;
                    arr[other]++;
                }
            }
        }//内循环一次代表这一个人的财富交换完毕
        for(int i=0;i<n-1;i++){
        int min=i;
        for(int j=i+1;j<n;j++)
        {
            if(arr[j]<arr[min])
                min=j;
        }
        if(min!=i)
        {
            int k=arr[min];
            arr[min]=arr[i];
            arr[i]=k;
        }
    }//将每个人的财富进行排序

    for(int i=0;i<n;i++)
    {
        printf("%4d",arr[i]);
    }
    //输出每个人的财富

    printf("\n");
    printf("\n");

    }//外循环一次代表财富一轮交换完毕


    /*for(int i=0;i<n-1;i++){
        int min=i;
        for(int j=i+1;j<n;j++)
        {
            if(arr[j]<arr[min])
                min=j;
        }
        if(min!=i)
        {
            int k=arr[min];
            arr[min]=arr[i];
            arr[i]=k;
        }
    }//将每个人的财富进行排序

    for(int i=0;i<n;i++)
    {
        printf("%4d",arr[i]);
    }
    //输出每个人的财富
    printf("\n");*/

    printf("%lf\n",Gini(arr,n));
    return 0;
}
