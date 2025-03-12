//P10392
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,k;
struct node{
    int mmin,minpos;//表示次大值  以及最小的位置
    int mmax,maxpos;//表示最大值  以及最小的位置
    int l,r;
}tree[MAXN<<2];
int arr[MAXN];
int pos[MAXN];
int last=-2;

inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}

void up(node &i,node &l,node &r){
    if(l.mmax>=r.mmax){
        i.mmax=l.mmax;
        i.maxpos=l.maxpos;
        if(l.mmax!=r.mmax){
            if(l.mmin>=r.mmax){
                i.mmin=l.mmin;
                i.minpos=l.minpos;
            }
            else{
                i.mmin=r.mmax;
                i.minpos=r.maxpos;
            }
        }
        else{
            if(l.mmin>=r.mmin){
                i.mmin=l.mmin;
                i.minpos=l.minpos;
            }
            else{
                i.mmin=r.mmin;
                i.minpos=r.minpos;
            }
        }
    }
    else{
        i.mmax=r.mmax;
        i.maxpos=r.maxpos;
        if(r.mmin>=l.mmax){
            i.mmin=r.mmin;
            i.minpos=r.minpos;
        }
        else{
            i.mmin=l.mmax;
            i.minpos=l.maxpos;
        }
    }
}

void build(int l,int r,int i){
    tree[i].l=l;
    tree[i].r=r;
    if(l==r){
        tree[i].mmax=arr[l];
        tree[i].maxpos=l;
        tree[i].mmin=0;
        tree[i].minpos=0;
        return;
    }
    else{
        int mid=(l+r)>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(tree[i],tree[i<<1],tree[i<<1|1]);
    }
}

node query(int jobl,int jobr,int l,int r,int i){
    //cout<<888<<endl;
    if(jobl<=l&&r<=jobr){
        return tree[i];
    }
    int mid=(l+r)>>1;
    node a={0,0,0,0,0,0},b={0,0,0,0,0,0};
    if(jobl<=mid)
        a=query(jobl,jobr,l,mid,i<<1);
    if(jobr>mid)
        b=query(jobl,jobr,mid+1,r,i<<1|1);
    node ans={0,0,0,0,0,0};
    up(ans,a,b);
    return ans;
}

void add(int jobi,int jobv,int l,int r,int i){
    if(l==r){
        tree[i].mmax+=jobv;
        tree[i].maxpos=0;
        return ;
    }
    int mid=(l+r)>>1;
    if(jobi<=mid){
        add(jobi,jobv,l,mid,i<<1);
    }
    else{
        add(jobi,jobv,mid+1,r,i<<1|1);
    }
    up(tree[i],tree[i<<1],tree[i<<1|1]);
}

int main()
{
    n=read();
    k=read();
    for(int i=1;i<=n;i++){
        arr[i]=read();
    }
    build(1,n,1);
//    for(int i=1;i<=5;i++){
//        cout<<tree[i].l<<' '<<tree[i].r<<' '<<tree[i].mmax<<' '<<tree[i].maxpos<<' '<<tree[i].mmin<<' '<<tree[i].minpos<<endl;
//    }
//    cout<<endl;
    for(int i=1;i<=n;i++){
//        cout<<666<<' '<<i<<endl;
        node temp=query(i,min(i+k,n),1,n,1);
//        for(int i=1;i<=5;i++){
//            cout<<tree[i].l<<' '<<tree[i].r<<' '<<tree[i].mmax<<' '<<tree[i].maxpos<<' '<<tree[i].mmin<<' '<<tree[i].minpos<<endl;
//        }
//        cout<<777<<' '<<min(i+k,n)<<endl;
        if(temp.mmax==0){
            //cout<<888<<endl;
            pos[i]=-1;
        }
        else{
            if(temp.mmax==last){
                if(temp.mmin==0){
                    pos[i]=-1;
                }
                else{
                    pos[i]=temp.mmin;
                    add(temp.minpos,-pos[i],1,n,1);
                    k-=(temp.minpos-i);
                }
            }
            else{
                pos[i]=temp.mmax;
                add(temp.maxpos,-pos[i],1,n,1);
                k-=(temp.maxpos-i);
            }
        }
        last=pos[i];
//        cout<<pos[i]<<' '<<k<<endl;
//        for(int i=1;i<=5;i++){
//            cout<<tree[i].l<<' '<<tree[i].r<<' '<<tree[i].mmax<<' '<<tree[i].maxpos<<' '<<tree[i].mmin<<' '<<tree[i].minpos<<endl;
//        }
//        cout<<endl;
    }
    for(int i=1;i<=n;i++){
        cout<<pos[i]<<' ';
    }
    return 0;
}
