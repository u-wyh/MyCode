//P5268
//这道题运用到了差分  首先要将公式整理简化
//我们想要求的是 1到l  区间上的数字词频  和 1到r  区间上相应数字词频的乘积之和
//那么这道题不是求 l到r  区间上的数字词频  所以不使用一般的模板  需要自己手写
//左边每增加一个数  那么对答案的贡献就是右边相应数字的词频
//没减少一个数字  对答案的影响就是右边相应数字的词频
//我们根据此建立莫队
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5e4+5;

int n,m;
struct node{
    int l,r,id,op;
}nums[MAXN<<2];
int cnt=0;
int arr[MAXN];
int pos[MAXN];
int cntl[MAXN],cntr[MAXN];
int res;
int ans[MAXN];

//奇偶性排序优化
bool cmp(node a,node b) {
	return (pos[a.l] ^ pos[b.l]) ? pos[a.l] < pos[b.l] : ((pos[a.l] & 1) ? a.r < b.r : a.r > b.r);
}
//对于左端点在同一奇数块的区间，右端点按升序排列，反之降序。这个东西也是看着没用，但实际效果显著。

void Add(int op,int n){
    //将一个数字加入  并计算贡献
    if(op==1){
        //判断是左边加入还是右边加入
        cntl[arr[n]]++;
        res+=cntr[arr[n]];
    }
    else{
        cntr[arr[n]]++;
        res+=cntl[arr[n]];
    }
}

void Sub(int op,int n){
    //减去一个数字   并处理影响
    if(op==1){
        cntl[arr[n]]--;
        res-=cntr[arr[n]];
    }
    else{
        cntr[arr[n]]--;
        res-=cntl[arr[n]];
    }
}

signed main()
{
    cin>>n;
    int siz=sqrt(n);
    for(int i=1;i<=n;i++){
        cin>>arr[i];
        pos[i]=i/siz;
        //cout<<pos[i]<<' ';
    }
    //cout<<endl;
    cin>>m;
    for(int i=1;i<=m;i++){
        int l1,r1,l2,r2;
        cin>>l1>>r1>>l2>>r2;
        nums[++cnt]={r1,r2,i,1};
        nums[++cnt]={r1,l2-1,i,-1};
        nums[++cnt]={l1-1,r2,i,-1};
        nums[++cnt]={l1-1,l2-1,i,1};
    }
    //cout<<cnt<<endl;
    for(int i=1;i<=cnt;i++){
        if(nums[i].l>nums[i].r){
            int temp=nums[i].l;
            nums[i].l=nums[i].r;
            nums[i].r=temp;
        }
    }
    sort(nums+1,nums+cnt+1,cmp);
    int l=0,r=0;
    for(int i=1;i<=cnt;i++){
        while(nums[i].l<l) Sub(1,l--);
        while(nums[i].r>r) Add(-1,++r);
        while(nums[i].l>l) Add(1,++l);
        while(nums[i].r<r) Sub(-1,r--);
        //注意这道题的区间不是l到r  而是1到l和1到r  不能用正常做法做
        //匹配区间  得到答案
        if(nums[i].op==1){
            ans[nums[i].id]+=res;
        }
        else{
            ans[nums[i].id]-=res;
        }
    }
    for(int i=1;i<=m;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}
