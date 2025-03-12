//P3420
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1000005;
int fa[MAXN];
int ans=0,n;

void build(){
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
}

int find(int i){
    if (i != fa[i]){
        fa[i] = find(fa[i]);
    }
    return fa[i];
}
void un(int x,int y){
    int fx=find(x);
    int fy=find(y);
    if(fx!=fy){
        fa[fx]=fy;
    }
    else
        ans++;
}

int main(){
	cin>>n;
	build();
	for(int i=1;i<=n;i++){
        int a;
        cin>>a;
        un(a,i);
	}
	cout<<ans;
	return 0;
}
