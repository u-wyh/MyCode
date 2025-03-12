//https://acm.hdu.edu.cn/showproblem.php?pid=1506
#include <iostream>
#include <vector>
#include <stack>
#include <cstdio>

using namespace std;

const int MAXN = 10000001;

int arr[MAXN];
int ls[MAXN];
int rs[MAXN];
int sta[MAXN];
int n;
int ans=0;
int size[MAXN];

//如果没有变小的数字  那么建树就是一直往右边节点建立
//也不会有节点从栈中弹出
void build() {
    ans=0;
    for(int i=1;i<=n;i++){
        size[i]=0;
        ls[i]=0;
        rs[i]=0;
    }
    int top = 0;
    for (int i = 1; i <= n; i++) {
        int pos = top;
        while (pos > 0 && arr[sta[pos]] > arr[i]) {
            //单调栈  弹出不符合的元素
            pos--;
        }
        if (pos > 0) {
            //那么就是没有弹干净   那么当前节点就会成为栈顶节点的右孩子
            rs[sta[pos]] = i;
        }
        if (pos < top) {
            //表示有元素弹出 那么一定是当前节点的左孩子节点
            ls[i] = sta[pos + 1];
        }
        sta[++pos] = i;//加入栈中
        top = pos;
    }
}

void dfs(int u){
    size[u]=1;
    if(ls[u]!=0){
        dfs(ls[u]);
    }
    if(rs[u]!=0){
        dfs(rs[u]);
    }
    size[u]+=(size[ls[u]]+size[rs[u]]);
    //cout<<u<<' '<<size[u]<<endl;
    ans=max(ans,size[u]*arr[u]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    while(n!=0){
        for (int i = 1; i <= n; i++) {
            cin >> arr[i];
        }
        build();
        dfs(sta[1]);
        cout<<ans<<endl;
        cin>>n;
    }
    return 0;
}
