#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#define Max 10000

int father[Max],n,m,sets=0,board[Max][Max];

int getindex(int x,int y)
{
    return x*m+y;
}

void build()
{
    for (int a = 0; a < n; a++) {
        for (int b = 0, index1; b < m; b++) {
            if (board[a][b] == 1) {
                index1 = getindex(a, b);
                father[index1] = index1;
                sets++;
            }
        }
    }
    printf("%d\n",sets);
}

int find(int i) {
    if (i != father[i]) {
        father[i] = find(father[i]);
    }
    return father[i];
}

void un(int a,int b,int c,int d)
{
    int fx = find(getindex(a, b));
    int fy = find(getindex(c, d));
    if (fx != fy) {
        father[fx] = fy;
        sets--;
    }
}

int numIslands() {
    build();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (board[i][j] == 1) {
                if (j > 0 && board[i][j - 1] == 1) {
                    un(i, j, i, j - 1);
                }
                if (i > 0 && board[i - 1][j] == 1) {
                    un(i, j, i - 1, j);
                }
            }
        }
    }
    return sets;
}

int main()
{
    scanf("%d %d",&n,&m);
    //getchar();
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            scanf("%d",&board[i][j]);
            //getchar();
        }
        //scanf("\n");
        //getchar();
    }
    printf("%d\n",numIslands());
    return 0;
}
