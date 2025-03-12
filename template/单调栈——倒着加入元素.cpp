//p5858
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5e3+5;

int n,m,s;
long long dp[MAXN][MAXN];
int arr[MAXN];
int q[MAXN],head,tail;

signed main()
{
    cin>>n>>m>>s;
    for(int i=0;i<=n;i++){
        for(int j=0;j<=m;j++){
            dp[i][j]=-1e15;
        }
    }
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    dp[0][0]=0;
    for(int i=1;i<=n;i++){
        head=1,tail=2;
        q[head]=m;
//        if(dp[i][m-1]>dp[i][m])
//            head--,tail--;
//        q[++head]=m-1;
		for(int j=m;j;j--){
			while(head<tail&&q[head]-j>=s)
                head++;
            while(head<tail&&dp[i-1][q[tail-1]]<dp[i-1][j-1]){
                tail--;
            }
            q[tail++]=j-1;
            dp[i][j]=arr[i]*j+dp[i-1][q[head]];
		}
	}
	long long ans=-1e15;
	for(int i=0;i<=m;i++){
        ans=max(ans,dp[n][i]);
	}
	cout<<ans<<endl;
    return 0;
}
