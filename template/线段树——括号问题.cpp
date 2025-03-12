//P10513
//这道题求的是子序列 不一定是连续的
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5e5+5;

struct node{
    int l,r;
    int lcnt,rcnt;//统计左括号和右括号的数量
    int ans,result;//分别统计 () 和 )( 的数量
    //统计result是为了反转时方便操作
    int tag;//如果是1  表示有反转任务
}tree[MAXN<<2];
char str[MAXN];
int n,m;

inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch)) {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (isdigit(ch)) {
        x = (x << 3) + (x << 1) + (ch - '0');
        ch = getchar();
    }
    return x * f;
}

void up(int i){
    tree[i].lcnt=tree[i<<1].lcnt+tree[i<<1|1].lcnt;
    tree[i].rcnt=tree[i<<1].rcnt+tree[i<<1|1].rcnt;
    tree[i].ans=tree[i<<1].ans+tree[i<<1|1].ans+
                min(tree[i<<1].lcnt-tree[i<<1].ans,tree[i<<1|1].rcnt-tree[i<<1|1].ans);
    tree[i].result=tree[i<<1].result+tree[i<<1|1].result+
                min(tree[i<<1].rcnt-tree[i<<1].result,tree[i<<1|1].lcnt-tree[i<<1|1].result);
}
//向上更新信息

void build(int l,int r,int i){
    if(l==r){
        tree[i].lcnt=str[l]=='('?1:0;
        tree[i].rcnt=str[l]==')'?1:0;
        tree[i].ans=0;
        tree[i].result=0;
    }
    else{
        int mid = (l + r) >> 1;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);
        up(i);
    }
    tree[i].l=l;
    tree[i].r=r;
    tree[i].tag=0;
}

inline void updatelazy(int i) {
    tree[i].tag^=1;
    //这个标记的意思是该节点上已经修改过了  接下来就是修改的代码
    //但是自己的两个孩子节点没有修改  因为没有必要
    //只有使用这个孩子的时候才会修改

    int temp=tree[i].lcnt;
    tree[i].lcnt=tree[i].rcnt;
    tree[i].rcnt=temp;

    temp=tree[i].ans;
    tree[i].ans=tree[i].result;
    tree[i].result=temp;
}
//懒住了  不再往下传递
//除非需要的时候才会更新

// 懒信息的下发
inline void down(int i) {
    if (tree[i].tag) {
        updatelazy(i << 1);
        updatelazy(i << 1 | 1);
        tree[i].tag=0;
    }
}

inline void update(int jobl,int jobr,int l,int r,int i){
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
            update(jobl, jobr,l, mid, i << 1);
        }
        if (jobr > mid) {
            update(jobl, jobr,mid + 1, r, i << 1 | 1);
        }
        up(i);
    }
}
//这道题目的要求仅仅是反转  不需要jobv

void add(node &p, node &a, node &b)
{
	p.lcnt = a.lcnt + b.lcnt;
	p.rcnt = a.rcnt + b.rcnt;
	p.ans = a.ans + b.ans + min(a.lcnt - a.ans, b.rcnt - b.ans);
	p.result = a.result + b.result + min(a.rcnt - a.result, b.lcnt - b.result);
}
//仅仅是为了query服务的  所以不需要tag l r等

node query(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        return tree[i];
    }
    int mid = (l + r) >> 1;
    down(i);
    node a={0,0,0,0,0,0,0},b={0,0,0,0,0,0,0},ans={0,0,0,0,0,0,0};
    if (jobl <= mid) {
        a=query(jobl, jobr, l, mid, i << 1);
    }
    if (jobr > mid) {
        b=query(jobl, jobr, mid + 1, r, i << 1 | 1);
    }
    add(ans,a,b);
    return ans;
}
//这道题的查询答案不能仅仅通过左右儿子的相加得到
//还需要中间的操作  所以定义为node

signed main()
{
    cin>>n;
    scanf("%s", str + 1);//读入初始字符
    cin>>m;
    build(1,n,1);
    for(int i=1;i<=m;i++){
        int op,l,r;
        op=read();
        l=read();
        r=read();
        if(op==1){
            update(l,r,1,n,1);
        }
        else{
            cout<<query(l,r,1,n,1).ans<<endl;
        }
    }
    return 0;
}
