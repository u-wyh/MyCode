#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#define Max 10000

int father[Max];

void build(int n)
{
    for(int i=0;i<=n;i++)
    {
        father[i]=i;
    }
}

int find(int i)
{
    if (i != father[i])
    {
        father[i] = find(father[i]);
    }
    return father[i];
}

bool issameset(int x,int y)
{
    return find(x)==find(y);
}

void un(int x,int y)
{
    father[find(x)] = find(y);
}


int main()
{
    return 0;
}
