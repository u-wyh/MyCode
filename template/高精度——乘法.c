//Âå¹Èp303
#include<stdio.h>
#include<string.h>

char s1[2005],s2[2005];
int a[2005],b[2005],c[2005];

int main()
{
    scanf("%s",s1);
    int la=strlen(s1);
    scanf("%s",s2);
    int lb=strlen(s2);

    for(int i=0;i<la;i++)
    {
        a[la-i]=s1[i]-'0';
    }
    for(int i=0;i<lb;i++)
    {
        b[lb-i]=s2[i]-'0';
    }

    int lc=la+lb;
    for(int i=0;i<=lc;i++)
        c[i]=0;
    for(int i=1;i<=la;i++)
    {
        for(int j=1;j<=lb;j++)
        {
            c[i+j-1]+=a[i]*b[j];
            c[i+j]+=c[i+j-1]/10;
            c[i+j-1]%=10;
        }
    }
    while(c[lc]==0&&lc>1)
        lc--;
    for(int i=lc;i>0;i--)
        printf("%d",c[i]);
    return 0;
}
