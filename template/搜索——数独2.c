#include<stdio.h>
#include<stdlib.h>

#define size 10

int ans=0;
int a[size*size],n=81;
int b1[size][10],b2[size][10],b3[size][10];

void dfs(int x){
    if(x>n){
        ans++;
        /*
        for(int i=1;i<=n;i++){
            printf("%4d",a[i]);
            if(i%9==0)
                printf("\n");
        }
        printf("------------------------------------------------------------\n");
        */
        return ;
    }
    int row=(x-1)/9+1;
    int col=(x-1)%9+1;
    int block=(row-1)/3*3+(col-1)/3+1;
    for(int i=1;i<=9;i++){
        if(b1[row][i]==0&&b2[col][i]==0&&b3[block][i]==0){
            a[x]=i;
            b1[row][i]=1,b2[col][i]=1,b3[block][i]=1;
            dfs(x+1);
            b1[row][i]=0,b2[col][i]=0,b3[block][i]=0;
        }
    }
}

int main()
{
    dfs(1);
    printf("%d\n",ans);
    return 0;
}

