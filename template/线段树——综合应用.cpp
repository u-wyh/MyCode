#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1000005;

int arr[MAXN];
long add[MAXN << 2];
long change[MAXN << 2];
long Max[MAXN<<2];
bool update[MAXN << 2];
int n,m;

inline long long Read()
{
    long long  x=0,f=1;char ch=getchar();
    while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
    while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
    return x*f;
}

inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
    while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
    return x*f;
}

// 累加和信息的汇总
void up(int i) {
    // 父范围的累加和 = 左范围累加和 + 右范围累加和
    Max[i] = max(Max[i << 1] ,Max[i << 1 | 1]);
}

// 建树
void build(int l, int r, int i) {
    if (l == r) {
        Max[i] = arr[l];
    } else {
        int mid = (l + r) >> 1;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);
        up(i);
    }
    add[i] = 0;
    change[i] = 0;
    update[i] = false;
}


// 当前来到l~r范围，对应的信息下标是i，范围上数字的个数是n = r-l+1
// 现在收到一个懒更新任务 : l~r范围上每个数字增加v
// 这个懒更新任务有可能是任务范围把当前线段树范围全覆盖导致的
// 也有可能是父范围的懒信息下发下来的
// 总之把线段树当前范围的sum数组和add数组调整好
// 就不再继续往下下发了，懒住了
void updatelazy(int i, long v) {
    change[i] = v;
    add[i] = 0;
    Max[i] = v;
    update[i] = true;
}

void addlazy(int i,long v){
    add[i] += v;
    Max[i] += v;
}

// 懒信息的下发
void down(int i) {
    if (update[i]) {
        updatelazy(i << 1, change[i]);
        updatelazy(i << 1 | 1, change[i]);
        update[i] = false;
    }
    if (add[i] != 0) {
        // 发左
        addlazy(i << 1, add[i]);
        // 发右
        addlazy(i << 1 | 1, add[i]);
        // 父范围懒信息清空
        add[i] = 0;
    }
}

// 范围修改
// jobl ~ jobr范围上每个数字增加jobv
void Add(int jobl, int jobr, long jobv, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        addlazy(i, jobv);
    } else {
        int mid = (l + r) >> 1;
        down(i);
        if (jobl <= mid) {
            Add(jobl, jobr, jobv, l, mid, i << 1);
        }
        if (jobr > mid) {
            Add(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
        }
        up(i);//汇总修改数据
    }
}

void Update(int jobl, int jobr, long jobv, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        updatelazy(i, jobv);
    } else {
        int mid = (l + r) >> 1;
        down(i);
        if (jobl <= mid) {
            Update(jobl, jobr, jobv, l, mid, i << 1);
        }
        if (jobr > mid) {
            Update(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
        }
        up(i);
    }
}

long query(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        return Max[i];
    }
    int mid = (l + r) >> 1;
    down(i);
    long ans = -1e12;
    if (jobl <= mid) {
        ans =max(ans, query(jobl, jobr, l, mid, i << 1));
    }
    if (jobr > mid) {
        ans =max(ans, query(jobl, jobr, mid + 1, r, i << 1 | 1));
    }
    return ans;
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        arr[i]=read();
    build(1,n,1);
    long jobv;
    for (int i = 1, op, jobl, jobr; i <= m; i++) {
        cin>>op;
        if (op == 1) {
            jobl=Read();
            jobr=Read();
            jobv=Read();
            Update(jobl, jobr, jobv, 1, n, 1);
        } else if(op == 2){
            jobl=Read();
            jobr=Read();
            jobv=Read();
            Add(jobl, jobr, jobv, 1, n, 1);
        } else {
            jobl=Read();
            jobr=Read();
            cout<<query(jobl, jobr, 1, n, 1)<<endl;
        }
    }
    return 0;
}

