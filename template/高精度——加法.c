//Âå¹Èp1601
#include<stdio.h>
#include<string.h>

char s1[505],s2[505];
int a[505],b[505],c[505];

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    scanf("%s",s1);
    int la=strlen(s1);
    //printf("%d\n",la);
    scanf("%s",s2);
    int lb=strlen(s2);
    //printf("%d\n",lb);
    for(int i=0;i<la;i++)
    {
        a[la-i]=s1[i]-'0';
    }
    for(int i=0;i<lb;i++)
    {
        b[lb-i]=s2[i]-'0';
    }
    int lc=max(la,lb)+1;
    for(int i=1;i<=lc;i++)
    {
        c[i]+=a[i]+b[i];
        c[i+1]=c[i]/10;
        c[i]%=10;
    }
    if(c[lc]==0&&lc>0)
        lc--;
    for(int i=lc;i>=1;i--)
        printf("%d",c[i]);
    return 0;
}
