#include<bits/stdc++.h>
using namespace std;
const int MAXN = 70005;
//这里本来50005即可  但是下面访问到了2的16次方
const int LIMIT = 16;

int stmax[MAXN][LIMIT];
int stmin[MAXN][LIMIT];
int arr[MAXN];
int Log2[MAXN];
int n,m;

void build(int n){
    Log2[0]=-1;
    for(int i=1;i<=n;i++){
        Log2[i]=Log2[i>>1]+1;
        stmax[i][0]=arr[i];
        stmin[i][0]=arr[i];
    }
    for(int i=1;i<=Log2[n];i++){
        for(int j=1;j<=n;j++){
            stmax[j][i]=max(stmax[j][i-1],stmax[j+(1<<(i-1))][i-1]);
            stmin[j][i]=min(stmin[j][i-1],stmin[j+(1<<(i-1))][i-1]);
        }
    }
}

int query(int l,int r){
    int p=Log2[r-l+1];
    int maxans=max(stmax[l][p],stmax[r-(1<<p)+1][p]);
    int minans=min(stmin[l][p],stmin[r-(1<<p)+1][p]);
    return maxans-minans;
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        cin>>arr[i];
    build(n);
    while(m--){
        int l,r;
        cin>>l>>r;
        cout<<query(l,r)<<endl;
    }
    return 0;
}
