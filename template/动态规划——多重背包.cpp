//3423
//https://www.luogu.com.cn/article/dz9q3o65
#include<bits/stdc++.h>
using namespace std;
const int MAXM = 20005;
const int MAXN = 205;

int n,k,minn;
int a[MAXN];
int b[MAXN];
int f[MAXM];
int g[MAXM][MAXN];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

int main()
{
    n=read();
    for(int i=1;i<MAXM;i++){
        f[i]=500;
    }
    f[0]=0;
    for(int i=1;i<=n;i++){
        a[i]=read();
        minn=min(minn,a[i]);
    }
    for(int i=1;i<=n;i++){
        b[i]=read();
    }
    k=read();
    for(int i=minn+1;i<=k;i++){
        for(int j=1;j<=n;j++){
            if(((i-a[j])>=0)&&(f[i-a[j]]+1<f[i])&&(g[i-a[j]][j]+1<=b[j])){
                f[i]=f[i-a[j]]+1;
                for(int jj=1;jj<=n;jj++){
                    g[i][jj]=g[i-a[j]][jj];
                }
                g[i][j]=g[i-a[j]][j]+1;
            }
        }
    }
    cout<<f[k]<<endl;
    for(int i=1;i<=n;i++){
        cout<<g[k][i]<<' ';
    }
    return 0;
}
