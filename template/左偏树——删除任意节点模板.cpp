// 断罪者，删除任意编号节点，C++版
// 给定t，w，k，表示一共有t个人，死亡方式都为w，地狱阈值都为k，w和k含义稍后解释
// 每个人都给定n和m，表示这人一生有n件错事，有m次领悟
// 这个人的n件错事，给定对应的n个罪恶值，然后给定m次领悟，领悟类型如下
// 2 a   : 第a件错事的罪恶值变成0
// 3 a b : 第a件错事所在的集合中，最大罪恶值的错事，罪恶值减少b
//         如果减少后罪恶值变成负数，认为这件错事的罪恶值变为0
//         如果集合中，两件错事都是最大的罪恶值，取编号较小的错事
// 4 a b : 第a件错事所在的集合与第b件错事所在的集合合并
// 一个错事集合的罪恶值 = 这个集合中的最大罪恶值，只取一个
// 一个人的罪恶值 = 这个人所有错事集合的罪恶值累加起来
// 然后根据死亡方式w，对每个人的罪恶值做最后调整，然后打印这个人的下场
// 如果w==1，不调整
// 如果w==2，人的罪恶值 -= 错事集合的罪恶值中的最大值
// 如果w==3，人的罪恶值 += 错事集合的罪恶值中的最大值
// 如果一个人的罪恶值 == 0，打印"Gensokyo 0"
// 如果一个人的罪恶值  > k，打印"Hell "，然后打印罪恶值
// 如果一个人的罪恶值 <= k，打印"Heaven "，然后打印罪恶值
// 一共有t个人，所以最终会有t次打印
// 1 <= t <= 30
// 1 <= n <= 2 * 10^6
// 错事罪恶值可能很大，输入保证每个人的罪恶值用long类型不溢出
// 测试链接 : https://www.luogu.com.cn/problem/P4971
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2000001;
int t, w, n, m;
long long k;
long long num[MAXN];
// up[i]表示节点i在左偏树结构上的父亲节点
int up[MAXN];
int ls[MAXN];
int rs[MAXN];
int dist[MAXN];
// father[i]表示并查集里节点i的路径信息
int fa[MAXN];

void prepare() {
    dist[0] = -1;
    for (int i = 1; i <= n; i++) {
        up[i] = ls[i] = rs[i] = dist[i] = 0;
        fa[i] = i;
    }
}

int find(int i) {
    return fa[i] == i ? i : (fa[i] = find(fa[i]));
}

int merge(int i, int j) {
    if (i == 0 || j == 0) {
        return i + j;
    }
    int tmp;
    if (num[i] < num[j] || (num[i] == num[j] && i > j)) {
        tmp = i; i = j; j = tmp;
    }
    rs[i] = merge(rs[i], j);
    up[rs[i]] = i;//特殊的地方  就是将右儿子的父亲节点更新
    if (dist[ls[i]] < dist[rs[i]]) {
        tmp = ls[i]; ls[i] = rs[i]; rs[i] = tmp;
    }
    dist[i] = dist[rs[i]] + 1;
    fa[ls[i]] = fa[rs[i]] = i;
    return i;
}

// 节点i是所在左偏树的任意节点，删除节点i，返回整棵树的头节点编号
int remove(int i) {
    int h = find(i);//找到这棵树的头结点
    fa[ls[i]] = ls[i];
    fa[rs[i]] = rs[i];//将左右两个儿子的父亲暂时改为自己
    int s = merge(ls[i], rs[i]);//将两个儿子合并  返回新节点
    int f = up[i];//f是i节点的上一层节点
    fa[i] = s;//相当于删除头结点操作
    up[s] = f;//这里多写一步  将两个儿子的合并后节点s的父亲改为f
    if (h != i) {
        fa[s] = h;//并查集的扁平化处理
        if (ls[f] == i) {
            ls[f] = s;
        } else {
            rs[f] = s;
        }
        //向上修正
        for (int d = dist[s], tmp; dist[f] > d + 1; f = up[f], d++) {
            dist[f] = d + 1;
            if (dist[ls[f]] < dist[rs[f]]) {
                tmp = ls[f]; ls[f] = rs[f]; rs[f] = tmp;
            }
        }
    }
    up[i] = ls[i] = rs[i] = dist[i] = 0;//将这个节点的信息修正
    return fa[s];
}

void reduce(int i, long long v) {
    int h = remove(i);//将这个点完全移除
    num[i] = max(num[i] - v, 0LL);//修正这个点的权值
    fa[h] = fa[i] = merge(h, i);//将这个点重新加入其中
}

long long compute() {
    long long ans = 0;
    long long mx = 0;
    for (int i = 1; i <= n; i++) {
        if (fa[i] == i) {
            ans += num[i];
            if (num[i] > mx) mx = num[i];
        }
    }
    if (w == 2) {
        ans -= mx;
    } else if (w == 3) {
        ans += mx;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> t >> w >> k;
    for(int i = 1; i <= t; i++) {
        cin >> n >> m;
        prepare();
        for (int j = 1; j <= n; j++) {
            cin >> num[j];
        }
        for (int j = 1, op, a, b; j <= m; j++) {
            cin >> op >> a;
            if (op == 2) {
                reduce(a, num[a]);
            } else if (op == 3) {
                cin >> b;
                reduce(find(a), b);
            } else {
                cin >> b;
                int l = find(a);
                int r = find(b);
                if (l != r) {
                    merge(l, r);
                }
            }
        }
        long long ans = compute();
        if (ans == 0) {
            cout << "Gensokyo " << ans << endl;
        } else if (ans > k) {
            cout << "Hell " << ans << endl;
        } else {
            cout << "Heaven " << ans << endl;
        }
    }
    return 0;
}
