#include<stdio.h>
#include<stdlib.h>

#define MAX 10000+5

int n,a[MAX],stack[MAX];

int cmp(const void *a,const void *b){
    return (*(int *)b - *(int *)a);
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    qsort(a+1,n,sizeof(int),cmp);
    for(int i=1;i<=n;i++){
        stack[i]=a[i];
    }
    int ans=0,size=n;
    while(size>=2){
        ans+=stack[size]+stack[size-1];
        int k=stack[size]+stack[size-1];
        size--;
        int i=size-1;
        while(k>=stack[i]&&i>=1){
            stack[i+1]=stack[i];
            i--;
        }
        stack[i+1]=k;
    }
    printf("%d\n",ans);
    return 0;
}
