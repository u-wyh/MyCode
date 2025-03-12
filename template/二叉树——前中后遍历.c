#include<stdio.h>

void build(int l1,int r1,int l2,int r2,int *a,int *b){
    for(int i=l2;i<=r2;i++){
        if(b[i]==a[l1]){
            build(l1+1,l1+i-l2,l2,i-1,a,b);
            build(l1+i-l2+1,r1,i+1,r2,a,b);
            printf("%d ",a[l1]);
            return ;
        }
    }
}

int main()
{
    int n;
    scanf("%d",&n);
    int a[n+1],b[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=n;i++){
        scanf("%d",&b[i]);
    }
    build(1,n,1,n,a,b);
    return 0;
}
