//带权并查集P1196   这个好像不是
/*
这段代码的意思是：
如果b所在并查集接到a所在并查集后面
那么b所在并查集的头结点fb到a的所在并查集头结点距离就是a所在并查集大小  我们认为是加边权
边权大小是a所在并查集大小
然后a的并查集大小加上b大小
*/
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

int f[30010],sz[30010],cnt[30010];

inline int find(int x)noexcept{
	if(f[x]==x)return x;
	else {
		int p=find(f[x]);
		sz[x]+=sz[f[x]];
		return f[x]=p;
	}
}

int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	for(int i=1;i<=30000;i++)f[i]=i,sz[i]=0,cnt[i]=1;
	int t;cin>>t;
	while(t--){
		char c;cin>>c;
		if(c=='M'){
			int x,y;
			cin>>x>>y;
			int fx=find(x),fy=find(y);
			sz[fx]+=cnt[fy];
			f[fx]=fy;
			cnt[fy]+=cnt[fx];
			cnt[fx]=0;
		}
		if(c=='C'){
			int x,y;cin>>x>>y;
			if(find(x)!=find(y)){
				cout<<-1<<'\n';
			}
			else {
				cout<<abs(sz[x]-sz[y])-1<<'\n';
			}
		}
	}
	return 0;
}
