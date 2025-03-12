#include<bits/stdc++.h>
using namespace std;

int n,m;
int nums[1005][1005];

void Set(int a,int b,int c,int d,int v){
    nums[a][b]+=v;
    nums[a][d+1]-=v;
    nums[c+1][b]-=v;
    nums[c+1][d+1]+=v;
}

void build(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            nums[i][j]+=nums[i-1][j]+nums[i][j-1]-nums[i-1][j-1];
        }
    }
}

int main()
{
    cin>>n>>m;
    int a,b,c,d;
    while(m--){
        cin>>a>>b>>c>>d;
        Set(a,b,c,d,1);
    }
    build();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            printf("%d ",nums[i][j]);
        }
        printf("\n");
    }
    return 0;
}
