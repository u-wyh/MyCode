//��Ȩ���鼯P1196   ���������
/*
��δ������˼�ǣ�
���b���ڲ��鼯�ӵ�a���ڲ��鼯����
��ôb���ڲ��鼯��ͷ���fb��a�����ڲ��鼯ͷ���������a���ڲ��鼯��С  ������Ϊ�Ǽӱ�Ȩ
��Ȩ��С��a���ڲ��鼯��С
Ȼ��a�Ĳ��鼯��С����b��С
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
