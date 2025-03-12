// 幸运数字(递归版)
// 一共有n个点，编号1~n，由n-1条边连成一棵树，每个点上有数字
// 一共有q条查询，每次返回a到b的路径上，可以随意选择数字，能得到的最大异或和
// 1 <= n <= 2 * 10^4
// 1 <= q <= 2 * 10^5
// 0 <= 点上的数字 <= 2^60
// 测试链接 : https://www.luogu.com.cn/problem/P3292
// 提交以下的code，提交时请把类名改成"Main"
// C++这么写能通过，java会因为递归层数太多而爆栈
// java能通过的写法参考本节课Code03_LuckyNumber2文件
#include<bits/stdc++.h>
using namespace std;
// 节点个数上限
const int MAXN = 20002;
// 树上倍增的次方上限
const int LIMIT = 16;
// 节点值最大的位数
const int BIT = 60;

// 每个节点值的数组
long arr[MAXN];

// 链式前向星
int head[MAXN];
int Next[MAXN << 1];
int to[MAXN << 1];
int cnt=1;

// 树上倍增需要的深度表
int deep[MAXN];
// 树上倍增需要的倍增表
int stjump[MAXN][LIMIT];
// 树上倍增根据实际节点个数确定的次方
int power;

// bases[i][j]表示：
// 头节点到i节点路径上的数字，建立异或空间线性基，其中j位的线性基是哪个数字
long bases[MAXN][BIT + 1];
// levels[i][j]表示：
// 头节点到i节点路径上的数字，建立异或空间线性基，其中j位的线性基来自哪一层
int levels[MAXN][BIT + 1];
long basis[BIT + 1];

int log2(int n) {
    int ans = 0;
    while ((1 << ans) <= (n >> 1)) {
        ans++;
    }
    return ans;
}

void addEdge(int u, int v) {
    Next[cnt] = head[u];
    to[cnt] = v;
    head[u] = cnt++;
}

// 插入和替换线性基，本题最重要的函数
bool insertReplace(long curv, int curl, long* basis, int* level) {
    //要插入表中的数字curv  目前的等级curl
    //异或表basis  等级表level
    for (int i = BIT; i >= 0; i--) {
        if (curv >> i == 1) {
            if (basis[i] == 0) {
                basis[i] = curv;
                level[i] = curl;
                return true;
            }
            if (curl > level[i]) {
                long tmp1 = curv;
                curv = basis[i];
                basis[i] = tmp1;
                int tmp2 = level[i];
                level[i] = curl;
                curl = tmp2;
            }
            curv ^= basis[i];
        }
    }
    return false;
}

int lca(int x, int y) {
    //找到xy的LCA
	if (deep[x] < deep[y]) {
		int tmp = x;
		x = y;
		y = tmp;
	}
	for (int p = power; p >= 0; p--) {
		if (deep[stjump[x][p]] >= deep[y]) {
			x = stjump[x][p];
		}
	}
	if (x == y) {
		return x;
	}
	for (int p = power; p >= 0; p--) {
		if (stjump[x][p] != stjump[y][p]) {
			x = stjump[x][p];
			y = stjump[y][p];
		}
	}
	return stjump[x][0];
}

void dfs(int u, int f) {
    deep[u] = deep[f] + 1;
    stjump[u][0] = f;
    for (int p = 1; p <= power; p++) {
        stjump[u][p] = stjump[stjump[u][p - 1]][p - 1];
    }
    for (int i = 0; i <= BIT; i++) {
        //首先继承来自父亲节点的异或表
        bases[u][i] = bases[f][i];
        levels[u][i] = levels[f][i];
    }
    insertReplace(arr[u], deep[u], bases[u], levels[u]);
    //将自己位置上的数字加入这张表中
    for (int e = head[u]; e != 0; e = Next[e]) {
        //向子节点遍历
        if (to[e] != f) {
            dfs(to[e], u);
        }
    }
}

long query(int x, int y) {
    int Lca = lca(x, y);
    long basisx[BIT+1];
    long levelx[BIT+1];
    for(int i=0;i<=BIT;i++){
        basisx[i]=bases[x][i];
        levelx[i]=levels[x][i];
    }
    long basisy[BIT+1];
    long levely[BIT+1];
    for(int i=0;i<=BIT;i++){
        basisy[i]=bases[y][i];
        levely[i]=levels[y][i];
    }
    for(int i=0;i<=BIT;i++){
        basis[i]=0;
    }
    for (int i = BIT; i >= 0; i--) {
        long num = basisx[i];
        if (levelx[i] >= deep[Lca] && num != 0) {
            basis[i] = num;
        }
        //首先将表变为x的表  去除等级不足lca的数据
    }
    for (int i = BIT; i >= 0; i--) {
        long num = basisy[i];
        if (levely[i] >= deep[Lca] && num != 0) {
            //将y的表插入到其中生成有效表
            for (int j = i; j >= 0; j--) {
                if (num >> j == 1) {
                    if (basis[j] == 0) {
                        basis[j] = num;
                        break;
                    }
                    num ^= basis[j];
                }
            }
        }
    }
    long ans = 0;
    for (int i = BIT; i >= 0; i--) {
        ans = max(ans, ans ^ basis[i]);
    }
    return ans;
}

int main()
{
    int n ;
    int q ;
    cin>>n>>q;
    power=log2(n);
    for (int i = 1; i <= n; i++) {
        cin>>arr[i];
    }
    for (int i = 1, u, v; i < n; i++) {
        cin>>u>>v;
        addEdge(u, v);
        addEdge(v, u);
    }
    dfs(1, 0);
    for (int i = 1, x, y; i <= q; i++) {
        cin>>x>>y;
        cout<<query(x, y)<<endl;
    }
    return 0;
}
