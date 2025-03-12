//https://codeforces.com/problemset/problem/432/D
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int z[MAXN];
int cnt[MAXN];//长度为i的个数
char a[MAXN];
int n;

void zArray(char* s, int n) {
    z[0] = n;
    cnt[n]++;
    for (int i = 1, c = 1, r = 1, len; i < n; i++) {
        len = r > i ? min(r - i, z[i - c]) : 0;
        while (i + len < n && s[i + len] == s[len]) {
            len++;
        }
        if (i + len > r) {
            r = i + len;
            c = i;
        }
        z[i] = len;
        cnt[len]++;
    }
}

int main()
{
    scanf("%s",a);
    n=strlen(a);
    zArray(a,n);
    int ans=0;
    for(int i=n-1;i>=1;i--){
        cnt[i]+=cnt[i+1];
    }
    for(int i=1;i<n;i++){
        if(z[i]==n-i){
            ans++;
        }
    }
    ans++;
    cout<<ans<<endl;
    for(int i=n-1;i>0;i--){
        if(z[i]==n-i){
            cout<<z[i]<<' '<<cnt[z[i]]<<endl;
        }
    }
    cout<<n<<' '<<1;
    return 0;
}
