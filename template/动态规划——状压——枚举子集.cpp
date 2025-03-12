//P5911
#include <bits/stdc++.h>
using namespace std;
long long W_fir,n,f[1<<16],W[1<<16],T[1<<16],tot;
struct node{
	long long t,w;
}a[19];
int main(){
	cin>>W_fir>>n;
	tot=(1<<n)-1;
	for(int i=1; i<=n; i++){
		scanf("%lld%lld",&a[i].t,&a[i].w);
	}
	for(int s=0; s<=tot; s++){
		for(int i=1; i<=n; i++){
			if(s&(1<<(i-1))){
				T[s]=max(T[s],a[i].t);
				W[s]+=a[i].w;
			}
		}
	}
	memset(f,0x3f3f,sizeof(f));
	f[0]=0;
	int s1;
	for(int s=0; s<=tot; s++){
		for(int s2=s; ; s2=s&(s2-1)){
			s1=s^s2;
			if(W[s1]<=W_fir){
				f[s]=min(f[s],T[s1]+f[s2]);
			}
			if(s2==0){
				break;
			}
		}
	}
	cout<<f[tot];
	return 0;
}
