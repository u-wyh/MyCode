//P3618
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int BASE = 499;
const int MOD = 1000000007;

int n,m;
string s1,s2;
long long p[MAXN];
long long h[MAXN];
long long val;
bool ok[MAXN];
long long dp[MAXN];

void prepare(){
    p[0]=1;
    for(int i=1;i<=MAXN;i++){
        p[i]=p[i-1]*BASE;
    }
}

void build(string str){
    h[0]=str[0]-'a'+1;
    ok[0]=false;
    dp[0]=1;
    for(int i=1;i<n;i++){
        h[i]=h[i-1]*BASE+str[i]-'a'+1;
        ok[i]=false;
        dp[i]=0;
    }
}

long long gethash(int l,int r){
    long long ans=h[r];
    if(l>0){
        ans-=h[l-1]*p[r-l+1];
    }
    return ans;
}

long long query(string str){
    long long ans=str[0]-'a'+1;
    for(int i=1;i<m;i++){
        ans=ans*BASE+str[i]-'a'+1;
    }
    return ans;
}

int main()
{
    int T;
    cin>>T;
    prepare();
    for(int t=1;t<=T;t++){
        long long ans=0;
        cin>>s1>>s2;
        n=s1.length();
        m=s2.length();
        build(s1);
        long long val=query(s2);
        for(int i=m-1;i<n;i++){
            if(gethash(i-m+1,i)==val){
                ok[i]=true;
            }
        }
        dp[0]=1;
        for(int i=1;i<=n;i++){
            dp[i]=dp[i-1];
            if(ok[i-1]){
                dp[i]=(dp[i]+dp[i-m])%MOD;
            }
        }
        cout<<"Case #"<<t<<": "<<dp[n]<<endl;
    }
    return 0;
}
