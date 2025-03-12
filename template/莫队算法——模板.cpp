#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5e4+5;

int n,m;
int arr[MAXN];
int pos[MAXN];
int ans;
struct node{
    int l,r,a,b,id;
}nums[MAXN];
int cnt[MAXN];

inline int read(){
    int x=0;int ch=getchar(),f=1;
    while (!isdigit(ch)&&(ch!='-')&&(ch!=EOF)) ch=getchar();
    if (ch=='-'){f=-1;ch=getchar();}
    while (isdigit(ch)){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
    return x*f;
}

inline int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

//奇偶性排序优化
inline bool cmp(node a,node b) {
	return (pos[a.l] ^ pos[b.l]) ? pos[a.l] < pos[b.l] : ((pos[a.l] & 1) ? a.r < b.r : a.r > b.r);
}

inline bool cmpid(node a,node b){
    return a.id<b.id;
}

inline void Add(int n){
    ans-=cnt[arr[n]]*cnt[arr[n]];
    cnt[arr[n]]++;
    ans+=cnt[arr[n]]*cnt[arr[n]];
}

inline void Sub(int n){
    ans-=(cnt[arr[n]]*cnt[arr[n]]);
    cnt[arr[n]]--;
    ans+=(cnt[arr[n]]*cnt[arr[n]]);
}

signed main()
{
    n=read();
    m=read();
    int siz=sqrt(n);
    for(int i=1;i<=n;i++){
        arr[i]=read();
        pos[i]=i/siz;
    }
    for(int i=1;i<=m;i++){
        nums[i].l=read();
        nums[i].r=read();
        nums[i].id=i;
    }
    sort(nums+1,nums+m+1,cmp);
    int l=1,r=0;
    for(int i=1;i<=m;i++){
        while(nums[i].l<l) Add(--l);
        while(nums[i].r>r) Add(++r);
        while(nums[i].l>l) Sub(l++);
        while(nums[i].r<r) Sub(r--);
        //匹配区间  得到答案
        if(nums[i].l==nums[i].r)
		{
            nums[i].a=0;
			nums[i].b=1;
            continue;
        }
        nums[i].a=ans-(nums[i].r-nums[i].l+1);
        nums[i].b=(nums[i].r-nums[i].l+1)*(nums[i].r-nums[i].l);
        int g=gcd(nums[i].a,nums[i].b);
        nums[i].a/=g;
		nums[i].b/=g;
    }

    sort(nums+1,nums+m+1,cmpid);
    for(int i=1;i<=m;i++){
        printf("%d/%d\n",nums[i].a,nums[i].b);
    }
    return 0;
}
