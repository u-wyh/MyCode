//P2279
#include<iostream>
#include<cstdio>
#include<algorithm>
#define N 2020
#define FOR(i,a,b) for(int i=a;i<=b;i++)
using namespace std;

int n,b[N],f[N],d[N],o[N],ans,u,v,w;

bool cmp(int x,int y){
    return d[x]>d[y];
}

int main()
{
	scanf("%d",&n);
	b[1]=1,o[1]=o[0]=N;
	FOR(i,2,n)
        scanf("%d",&f[i]),d[i]=d[f[i]]+1,b[i]=i,o[i]=N;
	sort(b+1,b+n+1,cmp);
	FOR(i,1,n){
		v=b[i],w=f[v],u=f[f[v]];
		o[v]=min(o[v],min(o[w]+1,o[u]+2));
		if(o[v]>2){
			o[u]=0,ans++;
			o[f[u]]=min(o[f[u]],1),o[f[f[u]]]=min(o[f[f[u]]],2);
		}
	}
	printf("%d",ans);
	return 0;
}
