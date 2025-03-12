// 银河英雄传说
// 一共有30000搜战舰，编号1~30000，一开始每艘战舰各自成一队
// 如果若干战舰变成一队，那么队伍里的所有战舰竖直地排成一列
// 实现如下两种操作，操作一共调用t次
// M l r : 合并l号战舰所在队伍和r号战舰所在队伍
//         l号战舰的队伍，整体移动到，r号战舰所在队伍的最末尾战舰的后面
//         如果l号战舰和r号战舰已经是一队，不进行任何操作
// C l r : 如果l号战舰和r号战舰不在一个队伍，打印-1
//         如果l号战舰和r号战舰在一个队伍，打印它俩中间隔着几艘战舰
// 1 <= t <= 5 * 10^5
// 测试链接 : https://www.luogu.com.cn/problem/P1196
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有测试用例
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 30001;

int n=30000;
int fa[MAXN];
int dist[MAXN];
int sz[MAXN];

//初始化带权并查集
void prepare() {
    for (int i = 0; i <= n; i++) {
        fa[i] = i;
        dist[i] = 0;
        sz[i]=1;
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

void un(int l, int r) {
    int lf = find(l), rf = find(r);
    if (lf != rf) {
        fa[lf] = rf;//强制要求后面的节点作为父亲
        dist[lf] += sz[rf];
        sz[rf] += sz[lf];
    }
}

int query(int l, int r) {
    if (find(l) != find(r)) {
        //不在一个集合中
        return -1;
    }
    return abs(dist[l] - dist[r])-1;
}

int main()
{
    prepare();
    int t;
    cin>>t;
    for(int i=1,l,r;i<=t;i++){
        char op;
        cin>>op>>l>>r;
        if(op=='M'){
            un(l,r);
        }
        else{
            cout<<query(l,r)<<endl;
        }
    }
    return 0;
}
