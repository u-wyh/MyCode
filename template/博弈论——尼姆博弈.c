#include<stdio.h>
#include<stdbool.h>

int main()
{
    int m,k=0;
    scanf("%d",&m);//此处的m是数组总长度
    int arr[m],max=0;
    for(int i=0;i<m;i++)
    {
        scanf("%d",&arr[i]);//输入各个堆的石头数目
        if(arr[i]>=max)
            max=arr[i];//求出数组中的最大值，为sg函数做准备
    }
    int sg[max+1];//定义sg函数
    sg[0]=0;
    bool appear[max+1];
    for(int i=1;i<=max;i++)
    {
        for(int k=0;k<=max;k++)
        {
            appear[k]=false;//初始化appear
        }
        for(int j = 1; j <= i && j <= max; j++) { // 确保 j 不会大于 m
            appear[sg[i-j]] = true;
        }
        for(int s = 0; s <= max; s++) {
            if(!appear[s]) {
                sg[i] = s;
                break; // 找到 s 后退出循环
            }
        }
    }
    for(int i = 0; i < m; i++) { // 迭代到 n，因为 sg 数组现在有 n+1 个元素
        printf("%5d %5d\n",arr[i], sg[arr[i]]);
        k=k^sg[arr[i]];
    }
    printf("%d",k);
    return 0;
}
