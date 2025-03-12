//P1545
#include<bits/stdc++.h>
using namespace std;
const int MAXL = 1e6+5;
const int MAXN = 1e3+5;

int n,len;
int a,b;
int flag[MAXL];
int dp[MAXN];
struct node{
    int l,r,val;
}tree[MAXN<<2];

void up(int i){
    tree[i].val=min(tree[i<<1].val,tree[i<<1|1].val);
}

void build(int l, int r, int i) {
    tree[i].l=l;
    tree[i].r=r;
    tree[i].val=1e9;
    if (l == r) {
        return ;
    } else {
        int mid = (l + r) >> 1;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);
        up(i);
    }
}

void update(int pos, int v, int i) {
    if (tree[i].l == tree[i].r) {
        tree[i].val=v;
        return ;
    } else {
        int mid = (tree[i].l + tree[i].r) >> 1;
        if (pos <= mid) {
            update(pos,v, i << 1);
        }
        if (pos > mid) {
            update(pos,v, i << 1 | 1);
        }
        up(i);
    }
}

int query(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        return tree[i].val;
    }
    int mid = (l + r) >> 1;
    int ans = 1e9;
    if (jobl <= mid) {
        ans = query(jobl, jobr, l, mid, i << 1);
    }
    if (jobr > mid) {
        ans =min(ans, query(jobl, jobr, mid + 1, r, i << 1 | 1));
    }
    return ans;
}

int main()
{
    cin>>n>>len>>a>>b;
    for(int i=1;i<=n;i++){
        int x,y;
        cin>>x>>y;
        flag[x+1]++;
        flag[y-1]--;
    }
    for(int i=1;i<=len;i++){
        if(flag[i]>0){
            flag[i]=1;
        }
    }
    build(0,len,1);
    update(0,0,1);
    for(int i = a * 2; i <= len; i += 2) {
        cout<<66<<endl;
		if(flag[i])
            continue;
		int ql = max(0, i - 2 * b), qr = i - 2 * a;
		dp[i] = query(ql, qr, 0 , n , 1) + 1;
		update(i, dp[i], 1);
	}
	if(dp[len]>=1e9){
        dp[len]=-1;
	}
	cout<<dp[len]<<endl;
    return 0;
}

/*
暴力算法
struct node{
    int l,r;
}nums[MAXN];

int main()
{
    cin>>n>>len>>a>>b;
    int k=0;
    for(int i=1;i<=n;i++){
        cin>>nums[i].l>>nums[i].r;
        for(int j=nums[i].l+1;j<=nums[i].r-1;j++){
            ok[j]=true;
        }
        k=max(nums[i].r,k);
    }
    for(int i=1;i<=len;i++){
        cout<<ok[i]<<' ';
    }
    cout<<endl;
    for(int i=1;i<=len;i++){
        dp[i]=1e9;
    }
    for(int i = a*2; i <= len; i += 2) {
		if(ok[i]) continue; //该位置若不能作为子线段的端点就跳过
		for(int j = a; j <= b; j ++) {
			int k = i - j*2;
			if(k < 0) continue;
			dp[i] = min(dp[i], dp[k]+1);
		}
	}
	for(int i=1;i<=len;i++){
        cout<<dp[i]<<' ';
    }
    cout<<endl;
	cout<<dp[len]<<endl;
    return 0;
}
*/
