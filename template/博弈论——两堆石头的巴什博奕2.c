#include<stdio.h>
#include<stdbool.h>

int main()
{
    int a,b,m,eor;
    scanf("%d %d %d",&a,&b,&m);
    int temp=a+b;
    a=a>b?a:b;
    b=temp-a;
    int sg[a+1];
    bool appear[m+1];
    sg[0]=0;
    for(int i=1;i<=a;i++){
        for(int j=0;j<=m;j++){
            appear[j]=false;
        }
        for(int j=1;j<=m&&j<=i;j++){
            appear[sg[i-j]]=true;
        }
        for(int s = 0; s <= m; s++) {
            if(!appear[s]) {
                sg[i] = s;
                break; // 找到 s 后退出循环
            }
        }
    }
    eor=sg[a]^sg[b];
    printf("%d\n",eor);
    return 0;
}
