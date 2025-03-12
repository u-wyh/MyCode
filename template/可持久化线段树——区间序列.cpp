// 第一次出现位置的序列，java版
// 给定一个长度为n的数组arr，下标1~n，一共有m条查询，每条查询格式如下
// l r : arr[l..r]范围上，每个数第一次出现的位置，把这些位置组成一个序列
//       假设该范围有s种不同的数，那么序列长度为s
//       打印该序列第s/2个位置(向上取整)，对应arr的什么位置
// 题目有强制在线的要求，上一次打印的答案为lastAns，初始时lastAns = 0
// 每次给定的l和r，按照如下方式得到真实的l和r，查询完成后更新lastAns
// a = (给定l + lastAns) % n + 1
// b = (给定r + lastAns) % n + 1
// 真实l = min(a, b)
// 真实r = max(a, b)
// 1 <= n、m <= 2 * 10^5    0 <= arr[i] <= 2 * 10^5
// 测试链接 : https://acm.hdu.edu.cn/showproblem.php?pid=5919
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有测试用例
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 200002;
const int MAXT = MAXN * 37;

int cases, n, m;
//每次读入的原始数组
int arr[MAXN];

// pos[v] : v这个数字上次出现的位置
int pos[MAXN];

// 可持久化线段树需要
int root[MAXN];
int ls[MAXT];
int rs[MAXT];

// 数组范围上只记录每种数第一次出现的位置，这样的位置有多少个
//也可以叫做tree数组
int firstSize[MAXT];

int cnt;

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

int build(int l, int r) {
    int rt = ++cnt;
    if (l < r) {
        int mid = (l + r) / 2;
        ls[rt] = build(l, mid);
        rs[rt] = build(mid + 1, r);
    }
    firstSize[rt] = 0;
    return rt;
}

// 数组范围l~r，信息在i号节点
// 如果jobv = -1，意味着jobi位置减少一个计数
// 如果jobv = +1，意味着jobi位置增加一个计数
// 返回新的头节点编号
int update(int jobi, int jobv, int l, int r, int i) {
	int rt = ++cnt;
	ls[rt] = ls[i];
	rs[rt] = rs[i];
	firstSize[rt] = firstSize[i] + jobv;
	if (l == r) {
		return rt;
	}
	int mid = (l + r) / 2;
	if (jobi <= mid) {
		ls[rt] = update(jobi, jobv, l, mid, ls[rt]);
	} else {
		rs[rt] = update(jobi, jobv, mid + 1, r, rs[rt]);
	}
	return rt;
}

// 从右往左建立各个版本的线段树
void prepare() {
    cnt = 0;
    memset(pos,0,sizeof(pos));
    root[n + 1] = build(1, n);
    for (int i = n; i >= 1; i--) {
        if (pos[arr[i]] == 0) {
            root[i] = update(i, 1, 1, n, root[i + 1]);
        } else {
            root[i] = update(pos[arr[i]], -1, 1, n, root[i + 1]);
            root[i] = update(i, 1, 1, n, root[i]);
        }
        pos[arr[i]] = i;
    }
}

// 数组范围l~r，信息在i号节点
// jobl ~ jobr范围上，一共有几种不同的数字，也就是这个范围上，有多少个位置有1
int querySize(int jobl, int jobr, int l, int r, int i) {
	if (jobl <= l && r <= jobr) {
		return firstSize[i];
	}
	int mid = (l + r) / 2;
	int ans = 0;
	if (jobl <= mid) {
		ans += querySize(jobl, jobr, l, mid, ls[i]);
	}
	if (jobr > mid) {
		ans += querySize(jobl, jobr, mid + 1, r, rs[i]);
	}
	return ans;
}

// 数组范围l~r，信息在i号节点
// 查询这个范围上，第jobk个1在哪
int queryKth(int jobk, int l, int r, int i) {
	if (l == r) {
		return l;
	}
	int mid = (l + r) / 2;
	int lsize = firstSize[ls[i]];
	if (lsize >= jobk) {
		return queryKth(jobk, l, mid, ls[i]);
	} else {
		return queryKth(jobk - lsize, mid + 1, r, rs[i]);
	}
}

int main()
{
    cases=read();
    for(int t=1;t<=cases;t++){
        n=read(),m=read();
        for(int i=1;i<=n;i++){
            arr[i]=read();
        }
        prepare();
        cout<<"Case #"<<t<<": ";
        for(int i=1,a,b,l,r,lastans=0,k;i<=m;i++){
            l=read(),r=read();
            a=(l+lastans)%n+1;
            b=(r+lastans)%n+1;
            l=min(a,b),r=max(a,b);
            k=(querySize(l,r,1,n,root[l])+1)/2;
            lastans=queryKth(k,1,n,root[l]);
            cout<<lastans<<' ';
        }
        cout<<endl;
    }
    return 0;
}
