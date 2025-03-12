#include<bits\stdc++.h>
using namespace std;

#define MAXN 101
#define MAXM 101

struct coord{
    int x,y;
};

int n,m;
queue<coord>Q;
int ans[MAXN][MAXM],nums[MAXN][MAXM];
int walk[4][2]={{0,1},{0,-1},{1,0},{-1,0}};

int main()
{
    scanf("%d %d",&n,&m);
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            ans[i][j]=-1;
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            scanf("%d",&nums[i][j]);
            if(nums[i][j]==1){
                ans[i][j]=0;
                Q.push({i,j});
            }
        }
    }
    while(!Q.empty()){
        coord u=Q.front();
        int ux=u.x,uy=u.y;
        Q.pop();
        for(int k=0;k<4;k++){
            int x=ux+walk[k][0],y=uy+walk[k][1];
            int d=ans[ux][uy];
            if(x<0||x>=n||y<0||y>=m||ans[x][y]!=-1)
                continue;
            ans[x][y]=d+1;
            Q.push({x,y});
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            printf("%3d",ans[i][j]);
        }
        printf("\n");
    }
    return 0;
}
