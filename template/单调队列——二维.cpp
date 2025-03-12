#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1005;

int n,m,a,b,c,d;
int arr[MAXN][MAXN];
int sum1[MAXN][MAXN];
int sum2[MAXN][MAXN];
int sum[MAXN][MAXN];
int q[MAXN];
int ans1[MAXN][MAXN];
int ans2[MAXN][MAXN];

int main()
{
    cin>>n>>m>>a>>b>>c>>d;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>arr[i][j];
            sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+arr[i][j];
        }
    }
    for(int i=a;i<=n;i++){
        for(int j=b;j<=m;j++){
            sum1[i][j]=sum[i][j]-sum[i][j-b]-sum[i-a][j]+sum[i-a][j-b];
        }
    }
    for(int i=c+1;i<n;i++){
        for(int j=d+1;j<m;j++){
            sum2[i][j]=sum[i][j]-sum[i][j-d]-sum[i-c][j]+sum[i-c][j-d];
        }
    }
//    cout<<endl;
//    for(int i=1;i<=n;i++){
//        for(int j=1;j<=m;j++){
//            cout<<sum[i][j]<<' ';
//        }
//        cout<<endl;
//    }
//    cout<<endl;
//    for(int i=1;i<=n;i++){
//        for(int j=1;j<=m;j++){
//            cout<<sum1[i][j]<<' ';
//        }
//        cout<<endl;
//    }
//    cout<<endl;
//    for(int i=1;i<=n;i++){
//        for(int j=1;j<=m;j++){
//            cout<<sum2[i][j]<<' ';
//        }
//        cout<<endl;
//    }
//    cout<<endl;
    for(int i=c+1;i<n;i++){
        int head=0,tail=0;
        for(int j=d+1;j<m;j++){
            while(head<tail&&q[head]<j-b+d+2){
                head++;
            }
            while(head<tail&&sum2[i][q[tail-1]]>=sum2[i][j]){
                tail--;
            }
            q[tail++]=j;
            if(j>=b-1){
                ans1[i][j+1]=sum2[i][q[head]];
                //cout<<i<<' '<<j+1<<' '<<ans1[i][j+1]<<endl;
            }
        }
    }
    //cout<<endl;
    for(int j=b;j<=m;j++){
        int head=0,tail=0;
        for(int i=c+1;i<n;i++){
            while(head<tail&&q[head]<i-a+c+2){
                head++;
            }
            while(head<tail&&ans1[q[tail-1]][j]>=ans1[i][j]){
                tail--;
            }
            q[tail++]=i;
            if(i>=a-1){
                ans2[i+1][j]=ans1[q[head]][j];
                //cout<<i+1<<' '<<j<<' '<<ans2[i+1][j]<<endl;
            }
        }
    }
    int ans=0;
    for(int i=a;i<=n;i++){
        for(int j=b;j<=m;j++){
            ans=max(ans,sum1[i][j]-ans2[i][j]);
        }
    }
    cout<<ans<<endl;
    return 0;
}
