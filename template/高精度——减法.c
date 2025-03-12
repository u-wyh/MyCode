//Âå¹Èp2142
#include<stdio.h>
#include<string.h>
#include<stdbool.h>

char s1[10090],s2[10090],s3[10090];
int a[10090],b[10090],c[10090];
int flag=0;

int max(int a,int b)
{
    return a>b?a:b;
}

int compare(char *s1,char *s2)
{
    int n1,n2;
    n1=strlen(s1);
    n2=strlen(s2);
    if(n1!=n2)
        return n1>n2;
    for(int i=0;i<n1;i++)
    {
        if(s1[i]!=s2[i])
            return s1[i]>s2[i];
    }
    return true;
}

int main()
{
    scanf("%s",s1);
    scanf("%s",s2);
    if(!compare(s1,s2))
    {
        flag=1;
        strcpy(s3,s1);
        strcpy(s1,s2);
        strcpy(s2,s3);
    }
    int la=strlen(s1);
    int lb=strlen(s2);

    for(int i=0;i<la;i++)
    {
        a[la-i]=s1[i]-'0';
    }
    for(int i=0;i<lb;i++)
    {
        b[lb-i]=s2[i]-'0';
    }

    int lc=max(la,lb);

    for(int i=1;i<=lc;i++)
    {
        if(a[i]<b[i])
        {
            a[i+1]--;
            a[i]+=10;
        }
        c[i]=a[i]-b[i];
    }
    while(c[lc]==0&& lc>1)
        lc--;
    if(flag==1)
        printf("-");
    for(int i=lc;i>0;i--)
        printf("%d",c[i]);
    return 0;
}
