//P3388
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e4+5;

vector<int>vec[MAXN];
int dfn[MAXN],low[MAXN];
int Time;
bool cut[MAXN];
bool instack[MAXN];
int n,m;

// v:当前点 r：本次搜索树的root
void tarjan(int u,int r) {
	dfn[u] = low[u] = ++Time;
	int child = 0;
	for (int i = 0; i < vec[u].size(); i++) {
		int v = vec[u][i];
		if (!dfn[v]) {
			tarjan(v, r);
			low[u] = min(low[u], low[v]);
			if (low[v] >= dfn[u] && u != r)
                cut[u] = true;//不是根而且他的孩子无法跨越他回到祖先
			if (r == u)
                child++; //如果是搜索树的根，统计孩子数目
		}
		low[u] = min(low[u], dfn[v]);//已经搜索过了
	}
	if (child >= 2 && u == r)
        cut[r] = 1;
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        vec[u].push_back(v);
        vec[v].push_back(u);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i]){
            tarjan(i,i);
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        if(cut[i]){
            ans++;
        }
    }
    cout<<ans<<endl;
    for(int i=1;i<=n;i++){
        if(cut[i]){
            cout<<i<<' ';
        }
    }
    return 0;
}
