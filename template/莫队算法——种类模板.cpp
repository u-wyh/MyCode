//P3901   求种类
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m,k;
struct node{
    int l,r,k,sub;
}nums[MAXN];
int arr[MAXN];
int pos[MAXN],cnt[MAXN];
int ans[MAXN];
int res;//计算结余  也就是答案

//奇偶性排序优化
bool cmp2(node a,node b) {
	return (pos[a.l] ^ pos[b.l]) ? pos[a.l] < pos[b.l] : ((pos[a.l] & 1) ? a.r < b.r : a.r > b.r);
}
//对于左端点在同一奇数块的区间，右端点按升序排列，反之降序。这个东西也是看着没用，但实际效果显著。

bool cmp(node a,node b){
    if(pos[a.l]==pos[b.l]){
        return a.r<b.r;
    }
    else{
        return pos[a.l]<pos[b.l];
    }
}

bool cmp1(node a,node b){
    return a.sub<b.sub;
}

void Add(int n){
    //将一个数字加入  并计算贡献
    cnt[arr[n]]++;
    if(cnt[arr[n]]==1){
        res++;
    }
}

void Sub(int n){
    //减去一个数字   并处理影响
    cnt[arr[n]]--;
    if(cnt[arr[n]]==0){
        res--;
    }
}

int main()
{
    cin>>n>>m;
    int siz=sqrt(n);//确立块的大小
    for(int i=1;i<=n;i++){
        cin>>arr[i];
        pos[i]=i/siz;//确定分组信息
    }
    for(int i=1;i<=m;i++){
        cin>>nums[i].l>>nums[i].r;
        nums[i].k=nums[i].r-nums[i].l+1;
        nums[i].sub=i;
    }
    sort(nums+1,nums+m+1,cmp2);
    //将问题排序
    //如果分组相同  按照右端点排序  否则按照组大小排序
    int l=1,r=0;
    for(int i=1;i<=m;i++){
        while(nums[i].l<l) Add(--l);
        while(nums[i].r>r) Add(++r);
        while(nums[i].l>l) Sub(l++);
        while(nums[i].r<r) Sub(r--);
        //匹配区间  得到答案
        ans[nums[i].sub]=res;
    }
    sort(nums+1,nums+m+1,cmp1);
    for(int i=1;i<=m;i++){
        if(ans[i]==nums[i].k){
            cout<<"Yes"<<endl;
        }
        else{
            cout<<"No"<<endl;
        }
    }
    return 0;
}

