// 推导部分和，带权并查集模版题1
// 有n个数字，下标1 ~ n，但是并不知道每个数字是多少
// 先给出m个数字段的累加和，再查询q个数字段的累加和
// 给出数字段累加和的操作 l r v，代表l~r范围上的数字，累加和为v
// 查询数字段累加和的操作 l r，代表查询l~r范围上的数字累加和
// 请根据m个给定，完成q个查询，如果某个查询无法给出答案，打印"UNKNOWN"
// 1 <= n, m, q <= 10^5
// 累加和不会超过long类型范围
// 测试链接 : https://www.luogu.com.cn/problem/P8779
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有测试用例
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+2;

int n,m,q;
int fa[MAXN];
long long dist[MAXN];

//初始化带权并查集
void prepare() {
    for (int i = 0; i <= n; i++) {
        fa[i] = i;
        dist[i] = 0;
    }
}

//寻找i节点的父亲 扁平化处理  并在该过程中更新距离
int find(int i) {
    if (i != fa[i]) {
        int tmp = fa[i];
        fa[i] = find(tmp);
        dist[i] += dist[tmp];//将距离更新正确
    }
    return fa[i];
}

void un(int l, int r, long long v) {
    int lf = find(l), rf = find(r);
    if (lf != rf) {
        fa[lf] = rf;//强制要求后面的节点作为父亲
        dist[lf] = v + dist[r] - dist[l];
    }
}

long long query(int l, int r) {
    if (find(l) != find(r)) {
        //不在一个集合中
        return LLONG_MAX;
    }
    return dist[l] - dist[r];
}

int main()
{
    cin>>n>>m>>q;
    prepare();
    int l,r;//我们将这些看成区间  每次r++
    long long v;
    for(int i=1;i<=m;i++){
        cin>>l>>r>>v;
        r++;
        un(l,r,v);
    }
    for (int i = 1; i <= q; i++) {
        cin>>l>>r;
        r++;
        v = query(l, r);
        if (v == LLONG_MAX) {
            cout<<"UNKNOWN"<<endl;
        } else {
            cout<<v<<endl;
        }
    }
    return 0;
}
