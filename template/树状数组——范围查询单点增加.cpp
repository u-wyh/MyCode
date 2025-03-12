// 树状数组单点增加、范围查询模版
// 测试链接 : https://www.luogu.com.cn/problem/P3374
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法
// 提交以下的code，提交时请把类名改成"Main"，可以直接通过
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 500001;

int tree[MAXN];
int n,m;

int lowbit(int x){
    return x & -x;
}

void add(int i,int v){
    while(i<=n){
        tree[i]+=v;
        i+=lowbit(i);
        //每一次都加上自己最右侧的1
        //相当于把所有包含该状态的数字都增加
    }
}

int sum(int i){
    int ans=0;
    while(i>0){
        ans+=tree[i];
        i-=lowbit(i);
        //每一次都减去自己最右侧的1
        //相当于将整个区间拆分开为几个小区间加速  和乘法快速幂相似
    }
    return ans;
}
//这个函数求的是从1到i所有数字的和

int query(int l,int r){
    return sum(r)-sum(l-1);
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        int v;
        cin>>v;
        add(i,v);
        //我们初始时认为树状数组里面的数字全都是0   直接调用add操作建立树状数组
    }
    for(int i=1,op;i<=m;i++){
        cin>>op;
        if(op==1){
            int x,v;
            cin>>x>>v;
            add(x,v);
        }else {
            int l,r;
            cin>>l>>r;
            cout<<query(l,r)<<endl;
        }
    }
    return 0;
}
