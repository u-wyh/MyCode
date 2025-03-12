#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int n,m;
ll arr[10000005];
ll l,s,r,e,maxans,eor;

ll read(){//¿ì¶Á
	short f=1;ll x;char ch;
	while(ch=getchar(),ch<'0'||ch>'9')
		if(ch=='-') f=-1;
	x=ch-'0';
	while(ch=getchar(),ch>='0'&&ch<='9')
		x=x*10+ch-'0';
	return x*f;
}

void Set(ll l,ll r,ll s,ll e,ll d){
    arr[l]+=s;
    arr[l+1]+=(d-s);
    arr[r+1]-=(d+e);
    arr[r+2]+=e;
}

void build(){
    for(int i=1;i<=n;i++){
        arr[i]+=arr[i-1];
    }
    for(int i=1;i<=n;i++){
        arr[i]+=arr[i-1];
    }
}

int main()
{
    cin>>n>>m;
    while(m--){
        l=read(),r=read(),s=read(),e=read();
        Set(l,r,s,e,(e-s)/(r-l));
    }
    build();
    eor=0;
    for(int i=1;i<=n;i++){
        maxans=max(maxans,arr[i]);
        eor^=arr[i];
        //printf("%3d",arr[i]);
    }
    //printf("\n");
    cout<<eor<<' '<<maxans<<endl;
    return 0;
}
