//P4087
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

int n,g;
struct node{
    int pos;
    int mmax;
    int maxnum;
    int mmin;
    int minnum;//表示最大的数字和次大的数字 以及数目
}tree[MAXN<<2];
struct node1{
    int t,pos,v;
}nums[MAXN];
int m=1;
int tmp[MAXN];

bool cmp(node1 a,node1 b){
    return a.t<b.t;
}

int getrank(int v){
    int l=1,r=m,ans=1;
    while(l<=r){
        int mid=(l+r)/2;
        if(tmp[mid]>=v){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

void up(int i){
    if(tree[i<<1].mmax>tree[i<<1|1].mmax){
        tree[i].pos=tree[i<<1].pos;
        tree[i].mmax=tree[i<<1].mmax;
        tree[i].maxnum=tree[i<<1].maxnum;
        if(tree[i<<1].mmin>tree[i<<1|1].mmax){
            tree[i].mmin=tree[i<<1].mmin;
            tree[i].minnum=tree[i<<1].minnum;
        }
        else if(tree[i<<1].mmin==tree[i<<1|1].mmax){
            tree[i].mmin=tree[i<<1].mmin;
            tree[i].minnum=tree[i<<1].minnum+tree[i<<1|1].maxnum;
        }
        else{
            tree[i].mmin=tree[i<<1|1].mmax;
            tree[i].minnum=tree[i<<1|1].maxnum;
        }
    }
    else if(tree[i<<1].mmax<tree[i<<1|1].mmax){
        tree[i].pos=tree[i<<1|1].pos;
        tree[i].mmax=tree[i<<1|1].mmax;
        tree[i].maxnum=tree[i<<1|1].maxnum;
        if(tree[i<<1|1].mmin>tree[i<<1].mmax){
            tree[i].mmin=tree[i<<1|1].mmin;
            tree[i].minnum=tree[i<<1|1].minnum;
        }
        else if(tree[i<<1|1].mmin==tree[i<<1].mmax){
            tree[i].mmin=tree[i<<1|1].mmin;
            tree[i].minnum=tree[i<<1|1].minnum+tree[i<<1].maxnum;
        }
        else{
            tree[i].mmin=tree[i<<1].mmax;
            tree[i].minnum=tree[i<<1].maxnum;
        }
    }
    else {
        tree[i].pos=tree[i<<1].pos;
        tree[i].mmax=tree[i<<1].mmax;
        tree[i].maxnum=tree[i<<1].maxnum+tree[i<<1|1].maxnum;
        if(tree[i<<1].mmin>tree[i<<1|1].mmin){
            tree[i].mmin=tree[i<<1].mmin;
            tree[i].minnum=tree[i<<1].minnum;
        }
        else if(tree[i<<1].mmin==tree[i<<1|1].mmin){
            tree[i].mmin=tree[i<<1].mmin;
            tree[i].minnum=tree[i<<1].minnum+tree[i<<1|1].minnum;
        }
        else{
            tree[i].mmin=tree[i<<1|1].mmin;
            tree[i].minnum=tree[i<<1|1].minnum;
        }
    }
}

void build(int l,int r,int i){
    if(l==r&&l==m+1){
        tree[i].pos=l;
        tree[i].mmax=g;
        tree[i].maxnum=1;
        tree[i].mmin=-1;
        tree[i].minnum=0;
        return ;
    }
    if(l==r){
        tree[i].pos=l;
        tree[i].mmax=g;
        tree[i].maxnum=1;
        tree[i].mmin=0;
        tree[i].minnum=0;
        //cout<<i<<' '<<tree[i].mmax<<' '<<tree[i].maxnum<<endl;
        return;
    }
    else{
        int mid=(l+r)/2;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
        //cout<<i<<' '<<tree[i].mmax<<' '<<tree[i].maxnum<<endl;
    }
}

void add(int pos,int v,int l,int r,int i){
    //cout<<i<<' ';
    if(l==r){
        //cout<<i<<' '<<tree[i].mmax<<' ';
        tree[i].mmax+=v;
        //cout<<tree[i].mmax<<endl;
    }
    else{
        int mid=(l+r)/2;
        if(pos<=mid){
            add(pos,v,l,mid,i<<1);
        }
        else{
            add(pos,v,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

int main()
{
    cin>>n>>g;
    for(int i=1;i<=n;i++){
        cin>>nums[i].t>>nums[i].pos>>nums[i].v;
        tmp[i]=nums[i].pos;
    }
    sort(tmp+1,tmp+n+1);
    sort(nums+1,nums+n+1,cmp);
    for(int i=2;i<=n;i++){
        if(tmp[i]!=tmp[i-1]){
            tmp[++m]=tmp[i];
        }
    }
//    for(int i=1;i<=m;i++){
//        cout<<tmp[i]<<' ';
//    }
//    cout<<endl;
    for(int i=1;i<=n;i++){
        nums[i].pos=getrank(nums[i].pos);
    }
    //cout<<g<<endl;
    m++;
    build(1,m,1);
//    cout<<endl;
//    for(int i=1;i<=n;i++){
//        cout<<nums[i].t<<' '<<nums[i].pos<<' '<<nums[i].v<<endl;
//    }
    int ans=0,prenum=0,premax=0,prepos;
    for(int i=1;i<=n;i++){
        prepos=tree[1].pos;
        premax=tree[1].mmax;
        prenum=tree[1].maxnum;
        //cout<<premax<<' '<<prenum<<endl;
        add(nums[i].pos,nums[i].v,1,m,1);
        if(prenum!=tree[1].maxnum){
            ans++;
        }
        else if(prenum==1&&prepos!=tree[1].pos){
            ans++;
        }
    }
    cout<<ans<<endl;
    return 0;
}
//最大的那个牛的产量发生了变化  如果还是最大的  实际上是不增加答案的
