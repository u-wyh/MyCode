/*
    丑数是它的质数因子只有2 3 5，并且第一个丑数是1
    那么我们可以知道所有的丑数只能由原来的丑数乘2 3 5得到
*/
#include<stdio.h>
#define max 1000

int min(int a,int b,int c)
{
    int min;
    min=a>b?b:a;
    min=min>c?c:min;
    return min;
}

int main()
{
    int ugly[max];
    ugly[0]=1;
    int two[max],three[max],five[max];
    two[0]=2,three[0]=3,five[0]=5;
    int n,i=0,j=0,k=0,m=0;
    scanf("%d",&n);
    while(m<n)
    {
        printf("%5d",ugly[m]);
        m+=1;
        ugly[m]=min(two[i],three[j],five[k]);
        two[m]=2*ugly[m];
        three[m]=3*ugly[m];
        five[m]=5*ugly[m];
        if(ugly[m]==two[i])
        {
            i++;
        }
        if(ugly[m]==three[j])
        {
            j++;
        }
        if(ugly[m]==five[k])
        {
            k++;
        }
        while(two[i]<=ugly[m])
        {
            i++;
        }
        while(three[j]<=ugly[m])
        {
            j++;
        }
        while(five[k]<=ugly[m])
        {
            k++;
        }
    }
    return 0;
}
