#include<stdio.h>
#define Max 1000

int father[Max],sets;

void build(int n)
{
    for(int i=0;i<n;i++)
    {
        father[i]=i;
    }
    sets=n;
}

int find(int i)
{
    if (i != father[i])
    {
        father[i] = find(father[i]);
    }
    return father[i];
}

void un(int x, int y) {
    int fx = find(x);
    int fy = find(y);
    if (fx != fy) {
        father[fx] = fy;
        sets--;
    }
}

int main()
{
    int n;
    scanf("%d",&n);
    int nums[n];
    for(int i=0;i<n;i++)
    {
        scanf("%d",&nums[i]);
    }
    build(n/2);
    for (int i = 0; i < n; i += 2) {
        un(nums[i] / 2, nums[i + 1] / 2);
    }
    printf("%d\n",n / 2 - sets);
    return 0;
}
