// 天际线问题(洛谷测试)
// 测试链接 : https://www.luogu.com.cn/problem/P1904
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法
// 提交以下的code，提交时请把类名改成"Main"，可以直接通过
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5005;

struct node{
    int l,r,h;
}nums[MAXN];
int xsort[3*MAXN];
int height[3*MAXN];
int n;

bool cmp(node a,node b){
    return a.l<b.l;
}

// 查询数值v的排名(离散值)
int getrank(int n, int v) {
    int ans = 0;
    int l = 1, r = n, mid;
    while (l <= r) {
        mid = (l + r) >> 1;
        if (xsort[mid] >= v) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return ans;
}

// 准备工作如下
// 1) 收集大楼左边界、右边界-1、右边界的值
// 2) 收集的所有值排序、去重
// 3) 大楼的左边界和右边界，修改成排名值
// 4) 大楼根据左边界排序
// 5) 清空height数组
// 6) 返回离散值的个数
int prepare(){
    int cnt=0;
    for(int i=1;i<=n;i++){
        xsort[++cnt]=nums[i].l;
        xsort[++cnt]=nums[i].r-1;
        xsort[++cnt]=nums[i].r;
    }
    sort(xsort+1,xsort+cnt+1);
    int m = 1;
    for (int i = 1; i <= cnt; i++) {
        if (xsort[m] != xsort[i]) {
            xsort[++m] = xsort[i];
        }
    }
    //cout<<m<<endl;
    // 修改大楼影响到的左右边界，都变成排名值
    for (int i = 1; i <= n; i++) {
        nums[i].l = getrank(m, nums[i].l);
        // 大楼影响到的右边界，减少1！
        // 课上重点说明的内容
        nums[i].r = getrank(m, nums[i].r - 1);
    }
    // 所有大楼根据左边界排序
    sort(nums+1,nums+n+1,cmp);
    // 返回有多少个不同的离散值
//    for(int i=1;i<=n;i++){
//        cout<<nums[i].l<<' '<<nums[i].r<<' '<<nums[i].h<<endl;
//    }
    return m;
}

// 自定义类型，包含两个int型数据
struct Node {
    int data1;
    int data2;

    // 为了在优先队列中使用，需要定义比较运算符或提供比较函数
    // 这里我们定义一个比较函数对象，用于大根堆（即比较函数返回true时，第一个参数节点应排在第二个参数节点之后）
    struct Compare {
        bool operator()(const Node& lhs, const Node& rhs) const {
            // 假设我们想要根据data1来构建大根堆，如果data1相同，则根据data2来构建大根堆（可选）
            if (lhs.data1 != rhs.data1) {
                return lhs.data1 < rhs.data1; // 小于号用于大根堆，因为priority_queue默认是小顶堆行为通过<来实现大顶堆
            } else {
                return lhs.data2 < rhs.data2; // 如果data1相同，则比较data2
            }
        }
    };
};

int main()
{
    n=1;
    while(cin>>nums[n].l>>nums[n].h>>nums[n].r){
        n++;
    }
    n--;
    int m=prepare();
//    for(int i=1;i<=n;i++){
//        cout<<nums[i].l<<' '<<nums[i].r<<' '<<nums[i].h<<endl;
//    }
    priority_queue<Node, vector<Node>, Node::Compare> heap;
    for (int i = 1, j = 1; i <= m; i++) {
        for (; j <= n && nums[j].l <= i; j++) {
            heap.push({ nums[j].h, nums[j].r });
        }
        while (!heap.empty() && heap.top().data2 < i) {
            heap.pop();
        }
        if (!heap.empty()) {
            height[i] = heap.top().data1;
        }
    }
    for (int i = 1, pre = 0; i <= m; i++) {
        //cout<<height[i]<<' ';
        if (pre != height[i]) {
            cout<<xsort[i]<<' '<<height[i]<<' ';
        }
        pre = height[i];
    }
    return 0;
}
