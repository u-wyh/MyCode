//P3538
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;
const int BASE = 499;

long long h[MAXN];
long long p[MAXN];
int n,m;
string s;
int visit[MAXN];
int prime[MAXN];
int nxt[MAXN];
int ok[MAXN];

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

void build(const string& str) {
    p[0] = 1;
    for (int j = 1; j < MAXN; ++j) {
        p[j] = p[j - 1] * BASE;
    }
    h[0] = str[0] - 'a' + 1;
    for (int j = 1; j < str.length(); ++j) {
        h[j] = h[j - 1] * BASE + str[j] - 'a' + 1;
    }
}

inline long long getHash(int l, int r) {
    long long ans = h[r];
    if (l > 0) {
        ans -= h[l - 1] * p[r - l +1];
    }
    return ans;
}

void euler(int n) {
    int cnt=0;
    for (int i = 2; i <= n; i++) {
        if (!visit[i]) {
            prime[cnt++] = i;
            nxt[i] = i;
        }

        for (int j = 0; j < cnt && (long long)i * prime[j] <= n; j++) {
            //每一次从最小的质数开始
            visit[i * prime[j]] = 1; // 标记为合数
            nxt[i*prime[j]]=prime[j];
            if (i % prime[j] == 0) {
                break; // 每个合数只被其最小的质因数筛去一次
            }
        }
    }
}

int main()
{
    n=read();
    cin>>s;
    build(s);
    euler(n);
    m=read();
    for(int i=1;i<=m;i++){
        int l,r;
        l=read(),r=read();
        l--,r--;
        int len=(r-l+1);
        if(getHash(l+1,r)==getHash(l,r-1)){
            cout<<1<<endl;
            continue;
        }
        int tt=0;
        while(len!=1){
            ok[++tt]=nxt[len];
            len=len/nxt[len];
        }
        len = r-l+1;
        for(int j = 1;j <= tt;j++){
            int t = len/ok[j];
            if(getHash(l+t,r)==getHash(l,r-t)){
                len = t;
            }
        }
        cout<<len<<endl;
    }
    return 0;
}
