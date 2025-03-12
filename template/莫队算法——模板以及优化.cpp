//P2709
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e4+5;

int n,m,k;
struct node{
    int l,r,sub;
}nums[MAXN];
int arr[MAXN];
int pos[MAXN],cnt[MAXN];
long long ans[MAXN];
long long res;//计算结余  也就是答案

//奇偶性排序优化
bool cmp2(node a,node b) {
	return (pos[a.l] ^ pos[b.l]) ? pos[a.l] < pos[b.l] : ((pos[a.l] & 1) ? a.r < b.r : a.r > b.r);
}

bool cmp(node a,node b){
    if(pos[a.l]==pos[b.l]){
        return a.r<b.r;
    }
    else{
        return pos[a.l]<pos[b.l];
    }
}

void Add(int n){
    //将一个数字加入  并计算贡献
    cnt[arr[n]]++;
    res+=(cnt[arr[n]]*cnt[arr[n]]-(cnt[arr[n]]-1)*(cnt[arr[n]]-1));
}

void Sub(int n){
    //减去一个数字   并处理影响
    cnt[arr[n]]--;
    res-=((cnt[arr[n]]+1)*(cnt[arr[n]]+1)-cnt[arr[n]]*cnt[arr[n]]);
}

int main()
{
    cin>>n>>m>>k;
    int siz=sqrt(n);//确立块的大小
    for(int i=1;i<=n;i++){
        cin>>arr[i];
        pos[i]=i/siz;//确定分组信息
    }
    for(int i=1;i<=m;i++){
        cin>>nums[i].l>>nums[i].r;
        nums[i].sub=i;
    }
    sort(nums+1,nums+m+1,cmp);
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
    for(int i=1;i<=m;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}
