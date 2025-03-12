// 没有上司的舞会
// 某大学有n个职员，编号为1...n
// 他们之间有从属关系，也就是说他们的关系就像一棵以校长为根的树
// 父结点就是子结点的直接上司
// 现在有个周年庆宴会，宴会每邀请来一个职员都会增加一定的快乐指数
// 但是如果某个职员的直接上司来参加舞会了
// 那么这个职员就无论如何也不肯来参加舞会了
// 所以请你编程计算邀请哪些职员可以使快乐指数最大
// 返回最大的快乐指数。
// 测试链接 : https://www.luogu.com.cn/problem/P1352
// 本题和讲解037的题目7类似
// 链式链接 : https://leetcode.cn/problems/house-robber-iii/
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法
// 提交以下的code，提交时请把类名改成"Main"，可以直接通过

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 6001;

int head[MAXN];
int Next[MAXN];
int to[MAXN];
int cnt=1;
//链式前向星建立树
int nums[MAXN];
bool boss[MAXN];
int yes[MAXN];
// yes[i] : i为头的整棵树，在i来的情况下，整棵树能得到的最大快乐值
int no[MAXN];
// no[i] : i为头的整棵树，在i不来的情况下，整棵树能得到的最大快乐值
int n,h;

void f(int u) {
    no[u] = 0;
    yes[u] = nums[u];
    for (int ei = head[u], v; ei > 0; ei = Next[ei]) {
        v = to[ei];
        f(v);//通过这个步骤  可以实现每一次都可以调用自己子节点的yes和no
        no[u] += max(no[v], yes[v]);
        yes[u] += no[v];
    }
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        boss[i]=true;
    }
    for(int i=1;i<=n;i++){
        cin>>nums[i];
    }
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        Next[cnt]=head[v];
        to[cnt]=u;
        head[v]=cnt++;
        boss[u]=false;//为了寻找最大的老板
    }
    for (int i = 1; i <= n; i++) {
        if (boss[i]) {
            h = i;
            break;
        }
    }
    f(h);
    cout<<max(no[h],yes[h]);
    return 0;
}

