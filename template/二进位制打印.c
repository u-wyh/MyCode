#include<stdio.h>

void B(int num)
{
    for(int i=31;i>=0;i--)
    {
        if((num&(1<<i))==0)
            printf("0");
        else
            printf("1");
    }
    printf("\n");
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int a;
        scanf("%d",&a);
        B(a);
    }
    return 0;
}
