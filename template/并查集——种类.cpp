//P2024
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;

inline int read() {
	char c = getchar(); int n = 0;
	while (c < '0' || c > '9') { c = getchar(); }
	while (c >= '0' && c <= '9') { n = (n << 1) + (n << 3) + (c & 15); c = getchar(); }
	return n;
}

int n, m, ans, fa[MAXN * 3];

int find(int u) {
    return fa[u] == u ? u : fa[u] = find(fa[u]);
}

int main()
{
	n = read(), m = read();
	for (int i = 1; i <= n * 3; i++) {
        fa[i] = i;
    }
	for (int i=1;i<=m;i++) {
		int opt = read(), u = read(), v = read();
		if (u > n || v > n) {
            ans++;
            continue;
        }
		if (opt == 1) {
			if (find(u + n) == find(v) || find(u) == find(v + n)) {
                ans++;
            }
			else {
				fa[find(u)] = find(v);
				fa[find(u + n)] = find(v + n);
				fa[find(u + n + n)] = find(v + n + n);
			}
		} else {
			if (find(u) == find(v) || find(u) == find(v + n)) {
                ans++;
            }
			else {
				fa[find(u + n)] = find(v);
				fa[find(u + n + n)] = find(v + n);
				fa[find(u)] = find(v + n + n);
			}
		}
	}
	cout<<ans;
	return 0;
}
