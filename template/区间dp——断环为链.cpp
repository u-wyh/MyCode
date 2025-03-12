//P4342
#include<bits/stdc++.h>
using namespace std;

int a[105];
int f[150][150],g[150][150];//f为区间最大值 g为区间最小值
char c[105];
int n,ans=INT_MIN;

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>c[i]>>a[i];
        a[i+n]=a[i],c[i+n]=c[i];
    }
    for(int i=1;i<=2*n;i++){
        for(int j=1;j<=2*n;j++){
            g[i][j]=INT_MAX;
            f[i][j]=INT_MIN;
        }
    }
    //初始化数组
    for(int i=1;i<=2*n;i++){
        f[i][i]=g[i][i]=a[i];
    }
    for(int len=2;len<=n;len++){
        //枚举区间长度
        for(int i=1,j=len;j<=2*n;i++,j++){
            //枚举区间开始点和结束点
            for(int k=i;k<j;k++){
                //枚举断边
                if(c[k+1]=='x'){
                    f[i][j]=max(f[i][j],max(f[i][k]*f[k+1][j],max(g[i][k]*g[k+1][j],max(f[i][k]*g[k+1][j],g[i][k]*f[k+1][j]))));
                    g[i][j]=min(g[i][j],min(f[i][k]*f[k+1][j],min(g[i][k]*g[k+1][j],min(f[i][k]*g[k+1][j],g[i][k]*f[k+1][j]))));
                }
                else if(c[k+1]=='t'){
                    f[i][j]=max(f[i][j],f[i][k]+f[k+1][j]);
                    g[i][j]=min(g[i][j],g[i][k]+g[k+1][j]);
                }
            }
        }
    }
    for(int i=1;i<=n;i++){
        ans=max(ans,f[i][i+n-1]);
    }
    cout<<ans<<endl;
    for(int i=1;i<=n;i++)
        if(f[i][i+n-1]==ans)
            cout<<i<<' ';
    return 0;
}
