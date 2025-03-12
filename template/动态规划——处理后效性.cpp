//P2466
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e3+5;

int n,m;
struct node{
    int x,y,v;
}nums[MAXN];
int f[MAXN][MAXN][2];
int sum[MAXN];

bool cmp(node a,node b){
    return a.x<b.x;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>m;
    nums[n+1].x=m,nums[n+1].y=nums[n+1].v=0;
    for(int i=1;i<=n;i++){
        cin>>nums[i].x;
    }
    for(int i=1;i<=n;i++){
        cin>>nums[i].y;
    }
    for(int i=1;i<=n;i++){
        cin>>nums[i].v;
    }
    sort(nums+1,nums+n+2,cmp);
    int st=1;
    for(int i=1;i<=n+1;i++){
        sum[i]=sum[i-1]+nums[i].v;
        if(nums[i].x==m){
            st=i;
        }
    }
    memset(f,-0x3f,sizeof(f));
    f[st][st][0]=f[st][st][1]=0;
    for(int len=1;len<=n+1;len++){
        for(int i=1;i+len<=n+1;i++){
            int j=i+len;
            f[i][j][0]=nums[i].y+max(f[i+1][j][0]-(nums[i+1].x-nums[i].x)*(sum[n+1]-sum[j]+sum[i]),
                                     f[i+1][j][1]-(nums[j].x-nums[i].x)*(sum[n+1]-sum[j]+sum[i]));
            f[i][j][1]=nums[j].y+max(f[i][j-1][1]-(nums[j].x-nums[j-1].x)*(sum[n+1]-sum[j-1]+sum[i-1]),
                                     f[i][j-1][0]-(nums[j].x-nums[i].x)*(sum[n+1]-sum[j-1]+sum[i-1]));
        }
    }

    printf("%.3lf\n",1.0*max(f[1][1+n][0],f[1][1+n][1])/1000.0);
    return 0;
}

