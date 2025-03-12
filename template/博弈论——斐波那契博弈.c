//斐波那契博弈（即每次只能拿fi中的数字个数的石头）
//泽肯多夫定理任意一个非斐波那契数列中的数字一定可以表示为多个不相邻的斐波那契数字之和
#include<stdio.h>
#include<stdbool.h>
#define Max 201//限制个数的最大值

int main()
{
    int a,b,max,eor;//此处以两个石头堆a,b为例进行编程，可以更多
    scanf("%d %d",&a,&b);
    max=a>b?a:b;
    bool appear[max+1];//定义出现与否的函数
    int sg[max+1];//定义sg函数
    sg[0]=0;
    int fi[12]={1,2,3,5,8,13,21,34,55,89,144,233};//定义我们可以使用到的斐波那契数列
    for(int i=1;i<=max;i++)
    {
        for(int k=0;k<=max;k++)
        {
            appear[k]=false;//初始化appear
        }
        for(int j = 0; fi[j]<=i ; j++) { // 确保 j 不会大于 m
            appear[sg[i-fi[j]]] = true;
        }
        for(int s = 0; s <= max; s++) {
            if(!appear[s]) {
                sg[i] = s;
                break; // 找到 s 后退出循环
            }
        }
    }
    eor=sg[a]^sg[b];
    printf("%d",eor);
    return 0;
}
