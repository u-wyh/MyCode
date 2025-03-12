//P6035
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e6+5;
const int MOD = 1e9+7;

int n;
int arr[MAXN];
// 线段树
int sum[MAXN << 2];
int ans=1;

// 初始化线段树，单点范围的初始累加和为1，认为所有数字都可用
void build(int l, int r, int i) {
    if (l == r) {
        sum[i] = 1;
    } else {
        int mid = (l + r) >> 1;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);
        sum[i] = sum[i << 1] + sum[i << 1 | 1];
    }
}

// 单点jobi上，增加jobv，因为是单点更新，所以不需要建立懒更新机制
void add(int jobi, int jobv, int l, int r, int i) {
    if (l == r) {
        sum[i] += jobv;
    } else {
        int mid = (l + r) >> 1;
        if (jobi <= mid) {
            add(jobi, jobv, l, mid, i << 1);
        } else {
            add(jobi, jobv, mid + 1, r, i << 1 | 1);
        }
        sum[i] = sum[i << 1] + sum[i << 1 | 1];
    }
}

// 查询jobl~jobr范围的累加和
int Sum(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        return sum[i];
    }
    int mid = (l + r) >> 1;
    int ans = 0;
    if (jobl <= mid) {
        ans += Sum(jobl, jobr, l, mid, i << 1);
    }
    if (jobr > mid) {
        ans += Sum(jobl, jobr, mid + 1, r, i << 1 | 1);
    }
    return ans;
}

// 线段树上找到第k名的是什么，找到后删掉词频，返回的过程修改累加和
// 注意这个排名是在子树中的排名
int getAndDelete(int k, int l, int r, int i) {
    int ans;
    if (l == r) {
        //找到目标 删除词频
        sum[i]--;
        ans = l;
    } else {
        int mid = (l + r) >> 1;
        if (sum[i << 1] >= k) {
            ans = getAndDelete(k, l, mid, i << 1);
        } else {
            ans = getAndDelete(k - sum[i << 1], mid + 1, r, i << 1 | 1);
            //要减去左侧排名的影响
        }
        sum[i] = sum[i << 1] + sum[i << 1 | 1];
        //返回的过程修改累加和
    }
    return ans;
}

void compute() {
    build(1, n, 1);
    //将线段树重新复原
    for (int i = 1; i <= n; i++) {
        arr[i] = getAndDelete((int) arr[i] + 1, 1, n, 1);
        //此时这个arr数组用来存放排列
    }
}

signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
        if(arr[i]>n-i){
            cout<<0<<endl;
            return 0;
        }
        if(arr[i]==-1){
            arr[i]=0;
            ans=(ans*(n-i+1))%MOD;
        }
    }
    cout<<ans<<endl;
    compute();
    for (int i = 1; i <= n; i++) {
        cout<<arr[i] <<" ";
    }
    return 0;
}
