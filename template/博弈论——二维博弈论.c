//二维博弈论
#include<stdio.h>
#include<stdbool.h>

int main()
{
    int a,b;
    scanf("%d %d",&a,&b);//输入两堆石子的个数
    int sg[a+1][b+1];//定义sg函数
    sg[1][1]=0;
    bool appear[a+1][b+1];

    for(int i=0;i<=a;i++){
        for(int m=1;m<=a;m++){
            for(int n=1;n<=b;n++){
                appear[m][n]=false;//完成appear的初始化
            }
        }
        for(int s = 0; s <= (a+b); s++) {
            if(!appear[s]) {
                sg[i] = s;
                break; // 找到 s 后退出循环
            }
        }
    }
    return 0;
}
