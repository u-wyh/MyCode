//通过位运算实现加减乘除
#include<stdio.h>

int add(int a,int b)
{
    int ans=a;
    while(b!=0)
    {
        ans=a^b;
        b=(a&b)<<1;
        a=ans;
    }
    return ans;
}
/*
原理解释：
    ^异或是一种不进位运算，那么如果我们想求a+b的值，相当于我们可以求a^b+进位信息
    所以我们的重点是求进位信息
    &按位与运算是同为一则为一，否则为0
    所以可以求得第一次进位信息
    然后继续进行操作，直到进位信息为0
*/
int minus(int a,int b)
{
    return add(a,add(~b,1));
}
//减法相当于a+(-b)
int multiply(int a,int b)
{
    int flag=1;
    if(b<0)
    {
        b=fabs(b);
        flag=-1;
    }
    int ans=0;
    while(b!=0)
    {
        if((b&1)!=0)
        {
            ans=add(ans,a);
        }
        a<<=1;
        b>>=1;
    }
    return ans*flag;
}
/*
原理解释：
    二进位制的乘法相当于一个数的每一位上的数字与另外一个数相乘
    b&1是为了确认b的最低位是不是0，如果是0，那么乘法后的结果是0，没有想加的必要
    采用加法的形式
    a向左一位，b向右一位    即保证乘法不会有因为位数的问题损失
*/
int divide(int a,int b)
{
    int ans=0;
    for(int i=30;i>=0;i=minus(i,1))
    {
        if((a>>i)>=b)
        {
            ans|=(1<<i);
            a=minus(a,b<<i);
        }
    }
    return ans;
}
int main()
{
    int a,b;
    scanf("%d %d",&a,&b);
    printf("%d\n",add(a,b));
    printf("%d\n",minus(a,b));
    printf("%d\n",multiply(a,b));
    printf("%d\n",divide(a,b));
    return 0;
}
//这个函数只能处理两个数字都是正数的情况
