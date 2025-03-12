//P4054
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 305;
const int MAXC = 105;

int arr[MAXN][MAXN];
int tree[MAXN][MAXN][MAXC];
int n,m,k;

int lowbit(int i){
    return i&-i;
}

void add(int x,int y,int color,int v){
    for(int i=x;i<=n;i+=lowbit(i)){
        for(int j=y;j<=m;j+=lowbit(j)){
            tree[i][j][color]+=v;
        }
    }
}
//在(x,y)上给color加上v

int sum(int x,int y,int color){
    int ans=0;
    for(int i=x;i;i-=lowbit(i)){
        for(int j=y;j;j-=lowbit(j)){
            ans+=tree[i][j][color];
        }
    }
    return ans;
}
//查询从(1,1)到(x,y)上  颜色color出现了多少次

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>arr[i][j];
            add(i,j,arr[i][j],1);
        }
    }
    cin>>k;
    for(int i=1;i<=k;i++){
        int op;
        cin>>op;
        if(op==2){
            int x1,x2,y1,y2,c;
            cin>>x1>>x2>>y1>>y2>>c;
            int ans=sum(x2,y2,c)+sum(x1-1,y1-1,c)-sum(x2,y1-1,c)-sum(x1-1,y2,c);
            cout<<ans<<endl;
        }
        else{
            int x,y,c;
            cin>>x>>y>>c;
            add(x,y,arr[x][y],-1);
            arr[x][y]=c;
            add(x,y,arr[x][y],1);
        }
    }
    return 0;
}
