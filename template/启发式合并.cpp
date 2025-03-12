//P3201
#include<cstdio>
#define rep(i, a, b) for (register int i=(a); i<=(b); ++i)
#define per(i, a, b) for (register int i=(a); i>=(b); --i)
using namespace std;
void swap(int &x, int &y){x^=y^=x^=y;}
const int N=1000005;
int head[N], nxt[N], col[N], now[N], cnt[N], st[N], ans;

inline int read()
{
    int x=0,f=1;char ch=getchar();
    for (;ch<'0'||ch>'9';ch=getchar()) if (ch=='-') f=-1;
    for (;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+ch-'0';
    return x*f;
}

void merge(int x, int y)
{
    cnt[y]+=cnt[x]; cnt[x]=0;
    for (int i=head[x]; i; i=nxt[i])
    {
        if (col[i+1]==y) ans--;
        if (col[i-1]==y) ans--;
    }
    for (int i=head[x]; i; i=nxt[i]) col[i]=y;
    nxt[st[x]]=head[y]; head[y]=head[x];
    head[x]=st[x]=cnt[x]=0;
}

int main()
{
    int n=read(), m=read();
    rep(i, 1, n)
    {
        col[i]=read(); now[col[i]]=col[i];
        if (col[i]^col[i-1]) ans++;
        if (!head[col[i]]) st[col[i]]=i;
        cnt[col[i]]++; nxt[i]=head[col[i]]; head[col[i]]=i;
    }
    rep(i, 1, m)
    {
        int opt=read();
        if (opt==2) printf("%d\n", ans);
        else
        {
            int x=read(), y=read();
            if (x==y) continue;
            if (cnt[now[x]]>cnt[now[y]]) swap(now[x], now[y]);
            x=now[x]; y=now[y];
            if (cnt[x]) merge(x, y);
        }
    }
    return 0;
}

