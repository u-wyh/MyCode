// k算法模版（洛谷）
// 动态空间实现
// 测试链接 : https://www.luogu.com.cn/problem/P3366
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法
// 提交以下所有代码，把主类名改成Main，可以直接通过
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5001;
const int MAXM = 200001;

int father[MAXN];
int n,m;
struct node{
    int st,en,val;
}edge[MAXM];

void build(){
    for(int i=1;i<=n;i++){
        father[i]=i;
    }
}

int find(int i){
    if (i != father[i]){
        father[i] = find(father[i]);
    }
    return father[i];
}

bool un(int x,int y){
    int fx=find(x);
    int fy=find(y);
    if(fx!=fy){
        father[fx]=fy;
        return true;
    }else{
        return false;
    }
}
//如果这两个节点以前就不是一个组里面的  那么合并他们
//否则返回false

bool cmp(node a,node b){
    return a.val<b.val;
}

int main()
{
    cin>>n>>m;
    build();
    for(int i=1;i<=m;i++){
        cin>>edge[i].st>>edge[i].en>>edge[i].val;
    }
    sort(edge+1,edge+m+1,cmp);
    int ans=0;
    int edgecnt=0;
    //edgecnt统计记录了多少条边
    for(int i=1;i<=m;i++){
        if(un(edge[i].st,edge[i].en)){
            //如果这条边的左右以前不在一个组里面   继续
            ans+=edge[i].val;
            edgecnt++;
        }
    }
    if(edgecnt==n-1){
        cout<<ans;
    }else{
        cout<<"orz";
    }
    return 0;
}
