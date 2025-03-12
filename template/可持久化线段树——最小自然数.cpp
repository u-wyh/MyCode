// 区间内没有出现的最小自然数，java版
// 给定一个长度为n的数组arr，下标1~n，一共有m条查询
// 每条查询 l r : 打印arr[l..r]内没有出现过的最小自然数，注意0是自然数
// 请用在线算法解决该问题，因为可以设计强制在线的要求，让离线算法失效
// 1 <= n、m <= 2 * 10^5
// 0 <= arr[i] <= 2 * 10^5
// 测试链接 : https://www.luogu.com.cn/problem/P4137
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有测试用例
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 200001;
const int MAXT = MAXN * 22;

int n, m;
int arr[MAXN];
int root[MAXN];
int ls[MAXT];
int rs[MAXT];

// 数字范围中，每个数字出现的最晚位置中，最左的位置在哪
int lateLeft[MAXT];
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
    lateLeft[rt] = 0;
    if (l < r) {
        int mid = (l + r) / 2;
        ls[rt] = build(l, mid);
        rs[rt] = build(mid + 1, r);
    }
    return rt;
}

// 数字范围l~r，信息在i号节点
// 数字范围上，jobi这个数字，最晚出现的位置更新为jobv
// 返回新的头节点编号
int update(int jobi, int jobv, int l, int r, int i) {
	int rt = ++cnt;
	ls[rt] = ls[i];
	rs[rt] = rs[i];
	lateLeft[rt] = lateLeft[i];
	if (l == r) {
		lateLeft[rt] = jobv;
	} else {
		int mid = (l + r) / 2;
		if (jobi <= mid) {
			ls[rt] = update(jobi, jobv, l, mid, ls[rt]);
		} else {
			rs[rt] = update(jobi, jobv, mid + 1, r, rs[rt]);
		}
		lateLeft[rt] = min(lateLeft[ls[rt]], lateLeft[rs[rt]]);
	}
	return rt;
}

// 数字在l~r范围上，没有出现的最小自然数，课上重点图解
int query(int pos, int l, int r, int i) {
	if (l == r) {
		return l;
	}
	int mid = (l + r) / 2;
	if (lateLeft[ls[i]] < pos) {
		// l...mid范围上，每个数字最晚出现的位置中
		// 最左的位置如果在pos以左，说明l...mid范围上，一定有缺失的数字
		return query(pos, l, mid, ls[i]);
	} else {
		// 缺失的数字一定在mid+1....r范围
		// 因为l...r一定有缺失的数字才会来到这个范围的
		// 如果左侧不缺失，那缺失的数字一定在右侧范围上
		return query(pos, mid + 1, r, rs[i]);
	}
}

void prepare() {
    cnt = 0;
    root[0] = build(0, n);
    for (int i = 1; i <= n; i++) {
        if (arr[i] > n || arr[i] < 0) {
            root[i] = root[i - 1];
        } else {
            root[i] = update(arr[i], i, 0, n, root[i - 1]);
        }
    }
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        arr[i]=read();
    }
    prepare();
    for(int i=1,l,r;i<=m;i++){
        l=read(),r=read();
        cout<<query(l,0,n,root[r])<<endl;
    }
    return 0;
}
