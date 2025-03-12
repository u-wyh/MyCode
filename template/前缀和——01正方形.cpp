#include<bits/stdc++.h>
using namespace std;
const int MAXN=130;

int n,m;
int sum[MAXN][MAXN];

int fun(int X1,int Y1,int X2,int Y2){
    return (X1<=X2&&Y1<=Y2)?sum[X2][Y2]+sum[X1-1][Y1-1]-sum[X2][Y1-1]-sum[X1-1][Y2]:0;
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>sum[i][j];
            sum[i][j]+=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];
        }
    }
    if(sum[n][m]==0){
        cout<<0;
        return 0;
    }
    int ans=1;
    for(int a=1;a<=n;a++){
        for(int b=1;b<=m;b++){
            for(int c=a+ans,d=b+ans,k=ans+1;c<=n&&d<=m;c++,d++,k++){
                //有剪枝行为   即如果长度比当前最优解小  说明没有用 可以舍弃
                if((fun(a,b,c,d)-fun(a+1,b+1,c-1,d-1))==(4*k-4))
                    ans=k;
            }
        }
    }
    cout<<ans*ans;
    return 0;
}


