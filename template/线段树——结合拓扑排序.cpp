//P8099
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,k;

int arr[MAXN];//原始数组
int val[MAXN];//辅助数组
int in[MAXN];//入度数组

map<int,int>vis;//这个是用于记录出现了多少次  帮助离散化

//线段树部分
pair<int,int>tree[MAXN<<2];
int tag[MAXN<<2];//懒标记数组

//树状数组部分
int bit[MAXN];//用于处理入度

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

//树状数组
int lowbit(int x){
    return x&(-x);
}

void add(int x,int v){
    while(x<=n){
        bit[x]+=v;
        x+=lowbit(x);
    }
}

int query(int x){
    int ans=0;
    while(x){
        ans+=bit[x];
        x-=lowbit(x);
    }
    return ans;
}

//线段树部分
void up(int i){
    if(tree[i<<1].second<tree[i<<1|1].second){
        tree[i]=tree[i<<1];
    }
    else if(tree[i<<1].second>tree[i<<1|1].second){
        tree[i]=tree[i<<1|1];
    }
    else{
        tree[i].second=tree[i<<1].second;//反正都是一样的
        tree[i].first=min(tree[i<<1].first,tree[i<<1|1].first);
        //如果度数一样  那么选择编号较小的  因为编号小的一定比大的优秀
    }
}

void build(int l,int r,int i){
    if(l==r){
        tree[i]={l,in[l]};
    }
    else{
        int mid=(l+r)/2;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
}

void lazy(int i,int v){
    tag[i]+=v;
    tree[i].second+=v;
}

void down(int i){
    if(tag[i]){
        lazy(i<<1,tag[i]);
        lazy(i<<1|1,tag[i]);
        tag[i]=0;
    }
}

void update(int jobl,int jobr,int jobv,int l,int r,int i){
    if(jobr<jobl){
        return ;
    }
    if(jobl<=l&&r<=jobr){
        lazy(i,jobv);
        return ;
    }
    else{
        down(i);
        int mid=(l+r)/2;
        if(jobl<=mid)
            update(jobl,jobr,jobv,l,mid,i<<1);
        if(jobr>mid)
            update(jobl,jobr,jobv,mid+1,r,i<<1|1);
        up(i);
    }
}

int main()
{
    n=read(),k=read();
    for(int i=1;i<=n;i++){
        arr[i]=read();
        val[i]=arr[i];
    }

    //离散化  即使相等的  也要变成不同编号  这里用到了记忆数组
    sort(arr+1,arr+n+1);
    for(int i=1;i<=n;i++){
        vis[val[i]]++;
        val[i]=lower_bound(arr+1,arr+n+1,val[i])-arr+vis[val[i]]-1;
        //此时的val[i]是按照大小排序 并且如果一样的 位置小的编号小
        //cout<<val[i]<<' ';
    }
    //cout<<endl;

    //计算离散化各个编号对应的点的入度
    //这一部分依靠的  树状数组
    for(int i=1;i<=n;i++){
        int x = lower_bound(arr + 1, arr + n + 1, arr[val[i]] - k) - arr - 1;
        int y = lower_bound(arr + 1, arr + n + 1, arr[val[i]] + k + 1) - arr - 1;
        //x y 以及区间内的数字  都是符合当前节点的范围
        in[val[i]]=(i-1)-(query(y)-query(x));
        //他的入度计算公式是  前面有了(i-1)个数字  (query(y)-query(x))表示的是符合要求的有多少
        //那么剩下的就是会指向该节点的数字个数
        add(val[i],1);
        //cout<<x<<' '<<y<<' '<<in[val[i]]<<endl;
    }

    //建树过程
    build(1,n,1);//这个建树节点编号是离散化后的编号

    for(int i=1;i<=n;i++){
        int u=tree[1].first;
        cout<<arr[u]<<endl;

        int x = lower_bound(arr + 1, arr + n + 1, arr[u] - k) - arr - 1;
        int y = lower_bound(arr + 1, arr + n + 1, arr[u] + k + 1) - arr - 1;

        update(1,x,-1,1,n,1);
        update(y+1,n,-1,1,n,1);
        update(u,u,n,1,n,1);//因为每次最多减少一个度数 设置为n  就一定不会在输出了
    }
    return 0;
}
