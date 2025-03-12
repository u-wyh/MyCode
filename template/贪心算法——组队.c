#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct
{
    int a,b;
}people;

int max(int a,int b)
{
    return a>b?a:b;
}

int cmp(const void *a,const void *b)
{
    people * pa=(people *)a;
    people * pb=(people *)b;

    return abs(pa->a - pa->b)-abs(pb>a - pb->b);
}

int main()
{
    int n;
    scanf("%d",&n);
    people nums[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d %d",&nums[i].a,&nums[i].b);
    }
    qsort(nums+1,n,sizeof(people),cmp);
    int maxa=nums[1].a;
    int maxb=nums[1].b;
    int ans=0;
    for(int i=2;i<=n;i++)
    {
        if(nums[i].a<=nums[i].b)
        {
            ans=max(ans,maxa+nums[i].a);
        }
        else
        {
            ans=max(ans,maxb+nums[i].b);
        }
        maxa=max(maxa,nums[i].a);
        maxb=max(maxb,nums[i].b);
    }
    printf("%.2lf",(double)1.0*ans/2);
    return 0;
}
