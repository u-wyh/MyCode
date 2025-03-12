#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m,k,ans;

int arr[MAXN];
int help[MAXN];//辅助数组

int l[MAXN];
int r[MAXN];

struct bittree{
    int tree[MAXN];
    int lowbit(int x){
        return x&(-x);
    }
    void add(int i,int v){
        while(i<=m){
            tree[i]=max(tree[i],v);
            i+=lowbit(i);
        }
    }
    int sum(int i){
        int ans=0;
        while(i>0){
            ans=max(ans,tree[i]);
            i-=lowbit(i);
        }
        return ans;
    }
}ltree,rtree,bit;

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

int find(int num){
    int l=1,r=m,ans=1;
    while(l<=r){
        int mid=(l+r)/2;
        if(help[mid]>=num){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

int main()
{
    n=read(),k=read();
    for(int i=1;i<=n;i++){
        arr[i]=read();
        help[i]=arr[i];
    }
    sort(help+1,help+n+1);
    for(int i=1;i<=n;i++){
        if(help[i]!=help[i-1]){
            help[++m]=help[i];
        }
    }
    for(int i=1;i<=n;i++){
        arr[i]=find(arr[i]);
        //cout<<arr[i]<<' ';
    }
    //cout<<endl;
    for(int i=1;i<=n;i++){
        l[i]=ltree.sum(arr[i])+1;
        ltree.add(arr[i],l[i]);
        //树状数组中的节点意思是以arr[i]为尾  最长是多少
    }
    for(int i=n;i>=1;i--){
        r[i]=rtree.sum(m-arr[i]+1)+1;
        //因为要求的是以自己开始的最长不降  那么将自己的值反过来
        //所有的i  变成 m-i
        rtree.add(m-arr[i]+1,r[i]);
    }
//    for(int i=1;i<=n;i++){
//        cout<<l[i]<<' ';
//	}
//	cout<<endl;
//	for(int i=1;i<=n;i++){
//        cout<<r[i]<<' ';
//	}
//	cout<<endl;
	int ans=max(k+r[k+1],k+l[n-k]);
	//其实这里可能有问题 我们最好新加两个数组 表示以左  以右  最大值
	//因为如果枚举从k+1开始 树状数组会进入一个0  死循环
	for(int i=k+2;i<=n;i++){
        //cout<<ans<<endl;
        bit.add(arr[i-k-1],l[i-k-1]);
        ans=max(ans,bit.sum(arr[i])+k+r[i]);
	}
	cout<<ans<<endl;
    return 0;
}
