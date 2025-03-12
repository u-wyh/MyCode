//P8624
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9+7;

long long power(long long a,long long b){
    long long ans=1;
    while(b>0){
        if(b&1){
            ans=((ans*a)%MOD+MOD)%MOD;
        }
        a=((a*a)%MOD+MOD)%MOD;//a每次相当于倍增  只有b的这一位上有1的时候 才会将a乘进ans中
        b>>=1;//b想右移动一位
    }
    return ans;
}

vector<vector<int>> multiply(vector<vector<int>>& a,const vector<vector<int>>& b) {
    int n = a.size();
    int m = b[0].size();
    int k = a[0].size();
    vector<vector<int>> ans(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int c = 0; c < k; c++) {
                ans[i][j] += a[i][c] * b[c][j];
                ans[i][j]=((ans[i][j]%MOD)+MOD)%MOD;
            }
        }
    }
    return ans;
}

// 矩阵快速幂
vector<vector<int>> power(vector<vector<int>>& m, int p) {
    int n = m.size();
    vector<vector<int>> ans(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        ans[i][i] = 1;//单位矩阵 相当于乘法快速幂中的1
    }
    for (; p != 0; p >>= 1) {
        if ((p & 1) != 0) {
            ans = multiply(ans, m);
        }
        m = multiply(m, m);//每次都是倍增
    }
    return ans;
}

signed main()
{
    int n,k;
    cin>>n>>k;
    long long ans=power(4,n);
    vector<vector<int>>base={{1,1,1,1,1,1},{1,1,1,1,1,1},{1,1,1,1,1,1},{1,1,1,1,1,1},{1,1,1,1,1,1},{1,1,1,1,1,1}};
    for(int i=1;i<=k;i++){
        int u,v;
        cin>>u>>v;
        u--,v--;
        base[(u+3)%6][v]=0;
        base[(v+3)%6][u]=0;
        //base[u][(v+3)%6]=0;
        //base[v][(u+3)%6]=0;
    }
    base=power(base,n-1);
    //vector<vector<int>>m={{1,0,0,0,0,0},{0,1,0,0,0,0},{0,0,1,0,0,0},{0,0,0,1,0,0},{0,0,0,0,1,0},{0,0,0,0,0,1}};
    vector<vector<int>>m={{1},{1},{1},{1},{1},{1}};
    m=multiply(base,m);
    long long tmp=0;
    for(int i=0;i<6;i++){
        tmp+=m[i][0];
        tmp%=MOD;
    }
//    for(int i=0;i<6;i++){
//        for(int j=0;j<6;j++){
//            tmp+=base[i][j];
//            tmp%=MOD;
//        }
//    }
    ans=(ans*tmp)%MOD;
    cout<<ans<<endl;
    return 0;
}
