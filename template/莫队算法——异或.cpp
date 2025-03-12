//P4462
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m,k;
int arr[MAXN];
struct node{
    int l,r,id;
}nums[MAXN];
long long  ans[MAXN];
int pos[MAXN];
int tot[200010];
long long  sum;


inline int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}return f*x;}

bool cmp(node a,node b){
    return (pos[a.l]==pos[b.l])?a.r<b.r:(pos[a.l]&1)?a.r<b.r:a.r>b.r;
}

void Add(int n){
    //将一个数字加入  并计算贡献
    sum+=tot[arr[n]^k];
    tot[arr[n]]++;
}

void Sub(int n){
    //减去一个数字   并处理影响
    tot[arr[n]]--;
    sum-=tot[arr[n]^k];
}

int main()
{
    cin>>n>>m>>k;
    int siz=pow(n,2.0/3.0);
    for(int i=1;i<=n;i++){
        arr[i]=read();
        arr[i]^=arr[i-1];
        pos[i]=i/siz;
    }
    for(int i=1;i<=m;i++){
        nums[i].l=read();
        nums[i].r=read();
        nums[i].id=i;
    }
    sort(nums+1,nums+m+1,cmp);
    tot[0]=1;
    int l=0,r=0;
    for(int i=1;i<=m;i++){
        while(nums[i].l-1<l) Add(--l);
        while(nums[i].r>r) Add(++r);
        while(nums[i].l-1>l) Sub(l++);
        while(nums[i].r<r) Sub(r--);
        //匹配区间  得到答案
        ans[nums[i].id]=sum;
    }
    for(int i=1;i<=m;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}
