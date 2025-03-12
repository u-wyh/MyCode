// 最大异或和，java版
// 非负序列arr的初始长度为n，一共有m条操作，每条操作是如下两种类型中的一种
// A x     : arr的末尾增加数字x，arr的长度n也增加1
// Q l r x : l~r这些位置中，选一个位置p，现在希望
//           arr[p] ^ arr[p+1] ^ .. ^ arr[n] ^ x 这个值最大
//           打印这个最大值
// 1 <= n、m <= 3 * 10^5
// 0 <= arr[i]、x <= 10^7
// 因为练的就是可持久化前缀树，所以就用在线算法，不要使用离线算法
// 测试链接 : https://www.luogu.com.cn/problem/P4735
// 提交以下的code，提交时请把类名改成"Main"
// java实现的逻辑一定是正确的，但是有一些测试用例通过不了
// 因为这道题根据C++的运行时间，制定通过标准，根本没考虑java的用户
// 想通过用C++实现，本节课Code01_MaxXor2文件就是C++的实现
// 两个版本的逻辑完全一样，C++版本可以通过所有测试
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 600001;
const int MAXT = MAXN * 22;
const int BIT = 25;
int n, m, eor;
int root[MAXN];
int tree[MAXT][2];//01trie只有两条路可以走 一条是0 一条是1
int pass[MAXT];//记录这个节点走过了几次
int cnt = 0;

//当前走到了i节点  插入了num  更新并返回节点编号
int insert(int num, int i) {
    int rt = ++cnt;
    tree[rt][0] = tree[i][0];
    tree[rt][1] = tree[i][1];
    pass[rt] = pass[i] + 1;
    for (int b = BIT, path, pre = rt, cur; b >= 0; b--, pre = cur) {
        path = (num >> b) & 1;
        i = tree[i][path];
        cur = ++cnt;
        tree[cur][0] = tree[i][0];
        tree[cur][1] = tree[i][1];
        pass[cur] = pass[i] + 1;
        tree[pre][path] = cur;
    }
    return rt;
}

int query(int num, int u, int v) {
    int ans = 0;
    for (int b = BIT, path, best; b >= 0; b--) {
        path = (num >> b) & 1;
        best = path ^ 1;
        if (pass[tree[v][best]] > pass[tree[u][best]]) {
            //表示可以是best
            ans += 1 << b;
            u = tree[u][best];
            v = tree[v][best];
        } else {
            u = tree[u][path];
            v = tree[v][path];
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    eor = 0;//作为所有值的异或和
    root[0] = insert(eor, 0);
    for (int i = 1, num; i <= n; i++) {
        cin >> num;
        eor ^= num;
        root[i] = insert(eor, root[i - 1]);
    }
    string op;
    int x, y, z;
    for (int i = 1; i <= m; i++) {
        cin >> op;
        if (op == "A") {
            cin >> x;
            eor ^= x;
            n++;
            root[n] = insert(eor, root[n - 1]);
        } else {
            cin >> x >> y >> z;
            //首先将要查询的变为eor^z
            if (x == 1) {
                cout << query(eor ^ z, 0, root[y - 1]) << "\n";
            } else {
                cout << query(eor ^ z, root[x - 2], root[y - 1]) << "\n";
            }
        }
    }
    return 0;
}
