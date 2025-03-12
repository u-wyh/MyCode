// 路径最大异或和(递归版)
// 一共有n个点，编号1~n，由m条无向边连接
// 每条边有权值，输入保证图是连通的，可能有环
// 找到1到n的一条路径，路径可以重复经过某些点或边
// 当一条边在路径中出现了多次时，异或的时候也要算多次
// 希望找到一条从1到n的路径，所有边权异或和尽量大，返回这个最大异或和
// 1 <= n <= 50000
// 1 <= m <= 100000
// 0 <= 边权 <= 10^18
// 测试链接 : https://www.luogu.com.cn/problem/P4151
// 提交以下的code，提交时请把类名改成"Main"
// C++这么写能通过，java会因为递归层数太多而爆栈
// java能通过的写法参考本节课Code04_MaximumXorOfPath2文件
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 50001;
const int MAXM = 200002;
const int BIT = 60;

// 链式前向星
int head[MAXN];
int Next[MAXM];
int to[MAXM];
long weight[MAXM];
int cnt=1;

// 所有环的异或和构建的线性基
long basis[BIT + 1];
// 某个节点在dfs过程中是否被访问过
bool visited[MAXN];
// 从头结点到当前节点的异或和
long path[MAXN];

void addEdge(int u, int v, long w) {
    Next[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}

bool insert(long num) {
    for (int i = BIT; i >= 0; i--)
        if (num >> i == 1) {
            if (basis[i] == 0) {
                basis[i] = num;
                return true;
            }
            num ^= basis[i];
        }
    return false;
}

void dfs(int u, int f, long p) {
	path[u] = p;
	visited[u] = true;
	for (int e = head[u]; e != 0; e = Next[e]) {
		int v = to[e];
		if (v != f) {
			long eor = p ^ weight[e];
			if (visited[v]) {
                //这个点访问过了  说明这就是一个环
				insert(eor ^ path[v]);
			} else {
				dfs(v, u, eor);
			}
		}
	}
}

long query(long init) {
    for (int i = BIT; i >= 0; i--) {
        init = max(init, init ^ basis[i]);
    }
    return init;
}

int main()
{
    int n ;
    int m ;
    cin>>n>>m;
    for (int i = 1; i <= m; i++) {
        int u ;
        int v ;
        long w ;
        cin>>u>>v>>w;
        addEdge(u, v, w);
        addEdge(v, u, w);
    }
    dfs(1, 0, 0);
    cout<<query(path[n])<<endl;
    return 0;
}
