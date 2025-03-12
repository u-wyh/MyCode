//P3149
//这道题要求的是逆序对数量  并且还有修改操作
//首先将数据离散化
//然后我们可以从后往前遍历统计以当前数字为较大数的逆序对数量
//遍历完成后  我们计算逆序对数量前缀和
//即cnt[i]表示两个数字都小于i的逆序对数量  因为我们已经离散化了  所以i可以代表arr
//
//分析：
//1.一个 ≤ak​ 的数与一个 >ak​ 的数组成。对于这个 >ak>ak​ 的数，无论≤ak​ 的数怎么排，
//    它贡献的逆序对个数都是一样的，所以不用管。
//2.两个 >ak​ 的数组成。这种明显个数不变也不用管
//
//所以我们  修改当前值  带来的影响  只会是两个数字都小于它的逆序对数量
//我们统计前缀和是为了如果一个小于当前的数字已经修改了 那么我们只需要更改cnt[cur]-cnt[pre]
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 3e5+5;

int temp[MAXN];
int arr[MAXN];
int n,k;
map<int,int>m;
int tot=1;
int tree[MAXN];
int cnt[MAXN];//cnt[i]统计i作为大数字的逆序对数量
int ans=0;

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

void build(){
    sort(temp+1,temp+n+1);
    m[temp[1]]=tot;
    for(int i=2;i<=n;i++){
        if(temp[i]!=temp[i-1]){
            m[temp[i]]=++tot;
            temp[tot]=temp[i];
        }
    }
    for(int i=1;i<=n;i++){
        arr[i]=m[arr[i]];
        //cout<<arr[i]<<' ';
    }
}

int lowbit(int i) {
	return i & -i;
}

void add(int i, int v) {
    while (i <= tot) {
        tree[i] += v;
        i += lowbit(i);
    }
}

// 1~i范围的累加和
int sum(int i) {
    int ans = 0;
    while (i > 0) {
        ans += tree[i];
        i -= lowbit(i);
    }
    return ans;
}

signed main()
{
    n=read(),k=read();
    for(int i=1;i<=n;i++){
        arr[i]=read();
        temp[i]=arr[i];
    }
    build();
    //完成离散化
    for(int i=n;i>=1;i--){
        add(arr[i],1);
        cnt[arr[i]]+=sum(arr[i]-1);
    }
    for(int i=1;i<=tot;i++){
        ans+=cnt[i];
    }
    cout<<ans<<endl;
    for(int i=1;i<=tot;i++){
        cnt[i]+=cnt[i-1];
    }
    int last=0;
    for(int i=1;i<=k;i++){
        int pos;
        pos=read();
        if(arr[pos]>last){
            ans-=(cnt[arr[pos]]-cnt[last]);
            last=arr[pos];
        }
        cout<<ans<<endl;
    }
    return 0;
}
