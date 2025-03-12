// 浮动区间的最大上中位数，java版
// 为了方便理解，我改写了题意，但是改写的题意和原始题意等效
// 给定一个长度为n的数组arr，下标1~n，一共有m条查询
// 每条查询 a b c d : 左端点在[a,b]之间、右端点在[c,d]之间，保证a<b<c<d
//                   哪个区间有最大的上中位数，打印最大的上中位数
// 题目有强制在线的要求，上一次打印的答案为lastAns，初始时lastAns = 0
// 每次给定四个参数，按照如下方式得到a、b、c、d，查询完成后更新lastAns
// (给定的每个参数 + lastAns) % n + 1，得到四个值，从小到大对应a、b、c、d
// 1 <= n <= 20000
// 1 <= m <= 25000
// 1 <= arr[i] <= 10^9
// 测试链接 : https://www.luogu.com.cn/problem/P2839
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有测试用例
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 20001;
const int MAXT = MAXN * 20;
const int INF = 10000001;

int n, m;

// 原始位置、数值
struct node{
    int pos,val;
}arr[MAXN];

// 可持久化线段树需要
int root[MAXN];
int ls[MAXT];
int rs[MAXT];

// 区间内最大前缀和，前缀不能为空
int pre[MAXT];

// 区间内最大后缀和，后缀不能为空
int suf[MAXT];

// 区间内累加和
int sum[MAXT];
int cnt;

// 查询的问题，a、b、c、d
int ques[4];
// 收集区间信息，pre、suf、sum
int info[3];

bool cmp(node a,node b){
    return a.val<b.val;
}

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
    pre[rt] = suf[rt] = sum[rt] = r - l + 1;
    if (l < r) {
        int mid = (l + r) / 2;
        ls[rt] = build(l, mid);
        rs[rt] = build(mid + 1, r);
    }
    return rt;
}

void up(int i) {
    pre[i] = max(pre[ls[i]], sum[ls[i]] + pre[rs[i]]);
    suf[i] = max(suf[rs[i]], suf[ls[i]] + sum[rs[i]]);
    sum[i] = sum[ls[i]] + sum[rs[i]];
}

// jobi位置，原来是1，现在改为-1
int update(int jobi, int l, int r, int i) {
    int rt = ++cnt;
    ls[rt] = ls[i];
    rs[rt] = rs[i];
    pre[rt] = pre[i];
    suf[rt] = suf[i];
    sum[rt] = sum[i];
    if (l == r) {
        pre[rt] = suf[rt] = sum[rt] = -1;
    } else {
        int mid = (l + r) / 2;
        if (jobi <= mid) {
            ls[rt] = update(jobi, l, mid, ls[rt]);
        } else {
            rs[rt] = update(jobi, mid + 1, r, rs[rt]);
        }
        up(rt);
    }
    return rt;
}

void prepare() {
    sort(arr+1,arr+n+1,cmp);
    //这里不能去重
    //因为单点修改比较容易
    cnt = 0;
    root[1] = build(1, n);
    for (int i = 2; i <= n; i++) {
        //每次将上一个位置变为-1
        root[i] = update(arr[i - 1].pos, 1, n, root[i - 1]);
    }
}

void initInfo() {
    //修改全局变量
    info[0] = info[1] = -INF;
    info[2] = 0;
}

//将新的资源汇总
void mergeRight(int r) {
    info[0] = max(info[0], info[2] + pre[r]);
    info[1] = max(suf[r], info[1] + sum[r]);
    info[2] += sum[r];
}

void query(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        mergeRight(i);
        //这个区间汇总到答案中
    } else {
        int mid = (l + r) / 2;
        if (jobl <= mid) {
            query(jobl, jobr, l, mid, ls[i]);
        }
        if (jobr > mid) {
            query(jobl, jobr, mid + 1, r, rs[i]);
        }
    }
}

bool check(int a, int b, int c, int d, int v) {
    initInfo();
    query(a, b, 1, n, root[v]);
    int best = info[1];
    initInfo();
    query(c, d, 1, n, root[v]);
    best += info[0];
    if (b + 1 <= c - 1) {
        initInfo();
        query(b + 1, c - 1, 1, n, root[v]);
        best += info[2];
    }
    return best >= 0;
}

int compute(int a, int b, int c, int d) {
    int left = 1, right = n, mid, ans = 0;
    while (left <= right) {
        mid = (left + right) / 2;
        if (check(a, b, c, d, mid)) {
            ans = arr[mid].val;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    n=read();
    for(int i=1;i<=n;i++){
        arr[i].pos=i;
        arr[i].val=read();
    }
    prepare();
    m=read();
    for (int i = 1, lastAns = 0; i <= m; i++) {
        for (int j = 0; j < 4; j++) {
            ques[j]=read();
            ques[j] = (ques[j] + lastAns) % n + 1;
        }
        sort(ques, ques + 4);
        lastAns = compute(ques[0], ques[1], ques[2], ques[3]);
        cout << lastAns << endl;
    }
    return 0;
}
