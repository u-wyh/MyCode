// 树状数组范围增加、单点查询模版
// 测试链接 : https://www.luogu.com.cn/problem/P3368
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法
// 提交以下的code，提交时请把类名改成"Main"，可以直接通过
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 500001;

int tree[MAXN];
//这个数组实际上是一个差分数组
int n,m;

int lowbit(int x){
    return x & -x;
}

void add(int i,int v){
    while(i<=n){
        tree[i]+=v;
        i+=lowbit(i);
        //每一次都加上自己最右侧的1
    }
}
//这个函数的作用是数组的i位置加上v

int sum(int i){
    int ans=0;
    while(i>0){
        ans+=tree[i];
        i-=lowbit(i);
        //每一次都减去自己最右侧的1
    }
    return ans;
}
//这个函数求的是这个差分数组从1到i数字的累加和  那么就相当于这个数字实际值

int main()
{
    cin>>n>>m;
    int pre=0;
    for(int i=1;i<=n;i++){
        int cur;
        cin>>cur;
        add(i,cur-pre);
        //我们初始时认为树状数组里面的数字全都是0   直接调用add操作建立树状数组
        //cur-pre  相当于差分值  我们把这个数值加到这个位置上
        //当然  我们直接可以这么写  add(i,cur)  add(i+1,-cur)   这个操作也是一样的
        pre=cur;
    }
    for(int i=1,op,x,y,k;i<=m;i++){
        cin>>op;
        if(op==1){
            cin>>x>>y>>k;
            add(x,k);
            add(y+1,-k);
        }else {
            cin>>x;
            cout<<sum(x)<<endl;
        }
    }
    return 0;
}
