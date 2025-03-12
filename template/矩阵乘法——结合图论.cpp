//P5789
#include<bits/stdc++.h>
using namespace std;
const int MOD = 2017;

vector<vector<int>> multiply(vector<vector<int>>& a,const vector<vector<int>>& b) {
    int n = a.size();
    int m = b[0].size();
    int k = a[0].size();
    vector<vector<int>> ans(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int c = 0; c < k; c++) {
                ans[i][j] += a[i][c] * b[c][j];
                ans[i][j]%=MOD;
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

int main()
{
    int n,m,t;
    cin>>n>>m;
    vector<vector<int>>base(n+1,vector<int>(n+1));
    for(int i=0;i<=n;i++){
        base[i][0]=1;
        base[i][i]=1;
    }
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        base[u][v]=1,base[v][u]=1;
    }
    cin>>t;
    vector<vector<int>> base_pow=power(base,t);
    int ans=0;
    for(int i=0;i<=n;i++){
        ans+=base_pow[1][i];
        ans%=MOD;
    }
    cout<<ans<<endl;
    return 0;
}
