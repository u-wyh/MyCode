//Âå¹Èp1480
#include<stdio.h>
#include<string.h>

char s1[5005];
long long la,lc,x=0,a[5005],c[5005],b;

int main()
{
    scanf("%s",s1);
    int la=strlen(s1);
    scanf("%lld",&b);

    for(int i=1;i<=la;i++)
    {
        a[i]=s1[i-1]-'0';
    }

    for(int i=1;i<=la;i++)
    {
        c[i]=(x*10+a[i])/b;
        x=(x*10+a[i])%b;
    }
    lc=1;

    while(c[lc]==0&&lc<la)
        lc++;

    for(int i=lc;i<=la;i++)
        printf("%d",c[i]);
    return 0;
}

