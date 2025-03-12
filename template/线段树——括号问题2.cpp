//P8765
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e6+5;
const int MAXM = 2e5+5;

int n,m;
//char str[MAXN];
int pre[MAXN];
struct node{
	int l, r;
	int mmax, mmin;         // [l, r]中前缀和的最大值为mmax，最小值为mmin
	int rev, add;           // rev -- 是否需要翻转; add -- 待增加的值
} tree[MAXN << 2];

int read(void)
{
	int ret = 0;
	bool flag = false;
	char ch = getchar();
	while (ch < '0' || ch > '9')
	{
		if (ch == '-')    flag = true;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9' && ch != EOF)
	{
		ret = ret * 10 + ch - '0';
		ch = getchar();
	}
	if (flag)    ret = -ret;
	return ret;
}

void up(int i){
    tree[i].mmax=max(tree[i<<1].mmax,tree[i<<1|1].mmax);
    tree[i].mmin=min(tree[i<<1].mmin,tree[i<<1|1].mmin);
}

void build(int l,int r,int i){
    if(l==r){
        tree[i].mmin=pre[l];
        tree[i].mmax=pre[l];
    }
    else{
        int mid = (l + r) >> 1;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);
        up(i);
    }
    tree[i].l=l;
    tree[i].r=r;
    tree[i].rev=0;
    tree[i].add=0;
}

void addlazy(int i,int v){
    tree[i].add+=v;
    tree[i].mmax+=v;
    tree[i].mmin+=v;
}

void updatelazy(int i){
    int tmp1 = tree[i].mmax, tmp2 = tree[i].mmin;
	tree[i].mmax = -tmp2;
	tree[i].mmin = -tmp1;
	tree[i].rev ^= 1;
	tree[i].add *= -1;
}

void down(int i){
    if(tree[i].rev){
        updatelazy(i<<1);
        updatelazy(i<<1|1);
        tree[i].rev=0;
    }
    if(tree[i].add){
        addlazy(i<<1,tree[i].add);
        addlazy(i<<1|1,tree[i].add);
        tree[i].add=0;
    }
}

// 范围修改
// jobl ~ jobr范围上每个数字增加jobv
void add(int jobl, int jobr, long jobv, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        addlazy(i, jobv);
    } else {
        int mid = (l + r) >> 1;
        down(i);
        if (jobl <= mid) {
            add(jobl, jobr, jobv, l, mid, i << 1);
        }
        if (jobr > mid) {
            add(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
        }
        up(i);//汇总修改数据
    }
}

void reverse(int jobl,int jobr,int l,int r,int i){
    if (jobl <= l && r <= jobr) {
        updatelazy(i);
    } else {
        int mid = (l + r) >> 1;
        down(i);
        //表示之前这个节点有修改信息  那么向下传递
        //虽然这道题是翻转操作 可能有人认为两次反转实际上就没有作用了  所以没必要down
        //这种想法是错误的 因为上一次可能是1~10  这一次是1~5 范围不一样
        //如果不翻转 那么实际上是有一部分少了一次反转
        if (jobl <= mid) {
            reverse(jobl, jobr,l, mid, i << 1);
        }
        if (jobr > mid) {
            reverse(jobl, jobr,mid + 1, r, i << 1 | 1);
        }
        up(i);
    }
}

int query(int jobl, int jobr, int l, int r, int i) {
    if(jobl==0&&jobr==0){
        return 0;
    }
    if (jobl <= l && r <= jobr) {
        return tree[i].mmin;
    }
    int mid = (l + r) >> 1;
    down(i);
    int ans=INT_MAX;
    if (jobl <= mid) {
        ans=min(ans,query(jobl, jobr, l, mid, i << 1));
    }
    if (jobr > mid) {
        ans=min(ans,query(jobl, jobr, mid + 1, r, i << 1 | 1));
    }
    return ans;
}
//求出区间上最小值

void update(int jobl,int jobr,int l,int r,int i){
    int val=query(jobl-1,jobl-1,1,n,1);
    reverse(1,jobl-1,1,n,1);
	add(jobl, n, -2 * val,1,n,1);

    val=query(jobr,jobr,1,n,1);
    reverse(jobl,jobr,1,n,1);
	add(jobr + 1, n, -2 * val,1,n,1);
}
//相当于反转两次
//reverse(L,R)=reverse(1,L−1)+reverse(1,R)

signed main()
{
	cin>>n>>m;
    for(int i=1;i<=n;i++){
        char x;
        cin>>x;
        pre[i] = x == '(' ? 1 : -1;
		pre[i] += pre[i - 1];
        //求出前缀和
        //cout<<pre[i]<<' ';
    }
    //cout<<endl;
    build(1,n,1);
    for(int i=1;i<=m;i++){
        int op;
        op=read();
        if(op==1){
            int l,r;
            l=read();
            r=read();
            update(l,r,1,n,1);
        }
        else{
            int b;
            b=read();
			int key = query(b - 1, b - 1,1,n,1);
			//求出该位置的答案
			int l = b, r = n;
			while (l <= r){
                //二分法
                //只要中间的最小值不比原来小就可以
				int m = (l + r) >> 1;
				int mmin = query(l, m,1,n,1);
				if (mmin < key || (mmin >= key && query(m, n,1,n,1) > key))
					r = m - 1;
				else
					l = m + 1;
                //如果区间 [L,M] 内的最小值（记为 mmin）小于 presum[L - 1]，则将 R 设置为 M−1。
                //如果区间 [L,M] 内的最小值 mmin大于或等于 presum[L - 1]，
                //    并且区间 [M,R]内的最小值也大于 presum[L - 1]，那么同样将 R 设置为 M−1。
                //如果上述两个条件都不满足，则将 L 设置为 M+1。
			}
			if (r >= b && query(r,r,1,n,1) == key)
                printf("%lld\n",r);
			else
                printf("0\n");
        }
    }
    return 0;
}
