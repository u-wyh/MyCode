//两堆石头的巴什博奕
#include<stdio.h>
#include<stdbool.h>

int main()
{
    int a,b,m,max,eor;
    scanf("%d %d %d",&a,&b,&m);//输入两堆石头各自的数量以及一次最多拿多少
    max=a>b?a:b;
    bool appear[m+1];
    int sg[max+1];
    sg[0]=0;//定义sg函数，并赋初值
    for(int i=0;i<=max;i++)
    {
        for(int k=0;k<=m;k++)
        {
            appear[k]=false;//完成appear函数的初始化
        }
        for(int j = 1; j <= i && j <= m; j++) { // 确保 j 不会大于 m
            appear[sg[i-j]] = true;
        }
        for(int s = 0; s <= m; s++) {
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
