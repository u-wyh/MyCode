//P1123
#include<bits/stdc++.h>
using namespace std;

int t,n,m;
int d[8][8],nums[8][8];
int ans=0,now=0;
int walk[8][2]={{1,0},{-1,0},{0,1},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1}};

void dfs(int x,int y){
    if(y==m+1){
        dfs(x+1,1);
        return ;
    }
    if(x==n+1){
        ans=max(ans,now);
        return ;
    }
    dfs(x,y+1);
    if(d[x][y]==0){
        now+=nums[x][y];
        for(int k=0;k<8;k++){
            int ux=x+walk[k][0],uy=y+walk[k][1];
            d[ux][uy]++;
        }
        dfs(x,y+1);
        now-=nums[x][y];
        for(int k=0;k<8;k++){
            int ux=x+walk[k][0],uy=y+walk[k][1];
            d[ux][uy]--;
        }
    }
}

int main()
{
    cin>>t;
    while(t--){
        memset(d,0,sizeof(d));
        memset(nums,0,sizeof(nums));
        ans=0;
        cin>>n>>m;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                cin>>nums[i][j];
            }
        }
        now=0;
        ans=0;
        dfs(1,1);
        cout<<ans<<endl;
    }
    return 0;
}
