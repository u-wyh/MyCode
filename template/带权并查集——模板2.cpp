// 狡猾的商人，带权并查集模版题2
// 有n个月的收入，下标1 ~ n，但是并不知道每个月收入是多少
// 操作 l r v，代表从第l个月到第r个月，总收入为v
// 一共给你m个操作，请判断给定的数据是自洽还是自相矛盾
// 自洽打印true，自相矛盾打印false
// 1 <= n <= 100    1 <= m <= 1000
// 总收入不会超过int类型范围
// 测试链接 : https://www.luogu.com.cn/problem/P2294
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有测试用例
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 102;

int n,m,t;
int fa[MAXN];
int dist[MAXN];
bool ans;

//初始化带权并查集
void prepare() {
    ans=true;
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

void un(int l, int r, int v) {
    int lf = find(l), rf = find(r);
    if (lf != rf) {
        fa[lf] = rf;//强制要求后面的节点作为父亲
        dist[lf] = v + dist[r] - dist[l];
    }
}

//用于检查是否出现逻辑错误  对不上的情况
bool check(int l, int r,int v) {
    if (find(l) == find(r)) {
        if ((dist[l] - dist[r]) != v) {
            return false;
        }
    }
    return true;
}

int main()
{
    cin>>t;
    while(t--){
        cin>>n>>m;
        n++;
        prepare();
        for (int i = 1, l, r, v; i <= m; i++) {
            cin>>l>>r>>v;
            r++;
            if (!check(l, r, v)) {
                ans = false;
                //即使出现了问题也不能停止   还要把所有的数据读完
            } else {
                un(l, r, v);
            }
        }
        if(ans){
            cout<<"true"<<endl;
        }
        else{
            cout<<"false"<<endl;
        }
    }
    return 0;
}
