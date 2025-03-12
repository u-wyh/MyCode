#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main()
{
    int m,n;
    printf("please enter the m and n: ");
    scanf("%d %d",&m,&n);
    char str[m][n];
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            str[i][j]=getchar();
        }
    }
    printf("%d\n",strlen(str[0]));
    printf("%c\n",str[0][m-1]);
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            putchar(str[i][j]);
        }
        printf("\n");
    }
    printf("---------------------------------------------------------------\n");
    return 0;
}
