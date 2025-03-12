#include<bits/stdc++.h>
using namespace std;
const int MAXN = 200005;

int arr[MAXN];
int len[MAXN<<2];
int pre[MAXN<<2];
int suf[MAXN<<2];
int n,m;

void up(int l,int r,int i){
    len[i]=max(len[i<<1],len[i<<1|1]);
    pre[i]=pre[i<<1];
    suf[i]=suf[i<<1|1];
    int mid=(l+r)/2;
    int ln=mid-l+1;
    int rn=r-mid;
    if(arr[mid]!=arr[mid+1]){
        len[i]=max(len[i],suf[i<<1]+pre[i<<1|1]);
        if(pre[i<<1]==ln){
            pre[i]+=pre[i<<1|1];
        }
        if(suf[i<<1|1]==rn){
            suf[i]+=suf[i<<1];
        }
    }
}

void build(int l,int r,int i){
    if(l==r){
        len[i]=1;
        suf[i]=1;
        pre[i]=1;
    }else{
        int mid=(l+r)/2;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(l,r,i);
    }
}

void Reverse(int jobi,int l,int r,int i){
    if(l==r){
        arr[jobi]^=1;
    }else{
        int mid=(l+r)/2;
        if(jobi<=mid){
            Reverse(jobi,l,mid,i<<1);
        }else{
            Reverse(jobi,mid+1,r,i<<1|1);
        }
        up(l,r,i);
    }
}

int main()
{
    cin>>n>>m;
    build(1,n,1);
    for(int i=1;i<=m;i++){
        int jobi;
        cin>>jobi;
        Reverse(jobi,1,n,1);
        cout<<len[1]<<endl;
    }
    return 0;
}
