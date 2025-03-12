//P2744
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 105;
const int MAXM = 20005;

int n,m;
int arr[MAXN];//表示桶的容量
int f[MAXM];//表示要这些牛奶最少需要几个不一样的桶
//实际上是f[i][j]表示前i个桶中  达到j的容量  最少需要几个桶  将第一维缩减了
int q[MAXN];//表示的是在dfs过程中选择的方案

void check(){
    bool vis[MAXM];//表示在dfs过程中选择出来的方案是否可以满足这个量的牛奶
    for(int i=0;i<=m;i++){
        vis[i]=false;
    }
    vis[0]=true;
    for(int i=1;i<=f[m];i++){
        //这里的f[m]表示的选择出来的桶的种类  这个值一定是f[m]
        for(int j=arr[q[i]];j<=m;j++){
            if(vis[j-arr[q[i]]]){
                vis[j]=1;
            }
        }
    }
    if(vis[m]){
        //如果可以实现 那么目前的方案一定是最优的
        //因为我们一开始就排序了
        for(int i=1;i<=f[m];i++){
            cout<<arr[q[i]]<<' ';
        }
        exit(0);
    }
}

void dfs(int u,int dep){
    //表示目前来到第u个桶 已经选了dep个桶
    if(dep==f[m]){
        //如果选择桶的个数已经到达答案  那么就去看看这种方案是否可以得出答案
        check();
        return ;
    }
    if(f[m]-dep>n-u){
        //剪枝 表示即使后面的全选上 也不行
        return;
    }
    for(int i=u+1;i<=n;i++){
        q[dep+1]=i;
        dfs(i,dep+1);
    }
}

int main()
{
    cin>>m>>n;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    sort(arr+1,arr+n+1);//将桶根据容量排序 这是因为要输出方案
    for(int i=1;i<=m;i++){
        f[i]=1e9;
    }
    f[0]=0;
    bool vis[MAXM];//表示的是称量出当前牛奶的最少桶的数量方案  是否用到了这个桶
    for(int i=1;i<=n;i++){
        for(int j=0;j<=m;j++){
            vis[j]=0;
            if(j>=arr[i]){
                int val=vis[j-arr[i]]^1;//如果以前用过这个桶  那么就是0  不用加1了
                if(f[j-arr[i]]+val<=f[j]){
                    //表示可以更新f[j]
                    f[j]=f[j-arr[i]]+val;
                    vis[j]=1;
                }
            }
        }
    }
    cout<<f[m]<<' ';
    dfs(0,0);
    return 0;
}
