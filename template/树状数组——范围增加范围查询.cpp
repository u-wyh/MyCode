// 树状数组范围增加、范围查询模版
// 测试链接 : https://www.luogu.com.cn/problem/P3372
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法
// 提交以下的code，提交时请把类名改成"Main"，可以直接通过
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100005;

int n,m;
long tree1[MAXN],tree2[MAXN];

int lowbit(int x){
    return x & -x;
}

void add(long *tree,int i,long  v){
    while(i<=n){
        tree[i]+=v;
        i+=lowbit(i);
        //每一次都加上自己最右侧的1
    }
}

long sum(long *tree,int i){
    int ans=0;
    while(i>0){
        ans+=tree[i];
        i-=lowbit(i);
        //每一次都减去自己最右侧的1
    }
    return ans;
}

void Add(int l, int r, long v) {
    //第一个数组更新
    add(tree1, l, v);
    add(tree1, r + 1, -v);

    //第二个数组更新
    add(tree2, l, (l - 1) * v);
    add(tree2, r + 1, -(r * v));
}

long range(int l, int r) {
    return (sum(tree1, r) * r - sum(tree2, r)) - (sum(tree1, l - 1) * (l - 1) - sum(tree2, l - 1));
    //即 从1到r的累加和  减去从1到l-1的累加和
}
//计算从l到r的累加和

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        long  cur;
        cin>>cur;
        Add(i,i,cur);
    }
    long v;
    for (int i = 1, op, l, r; i <= m; i++) {
        cin>>op;
        if (op == 1) {
            cin>>l>>r>>v;
            Add(l, r, v);
        } else {
            cin>>l>>r;
            cout<<range(l,r)<<endl;
        }
    }
    return 0;
}
