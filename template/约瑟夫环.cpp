// 约瑟夫环问题
// 一共有1~n这些点，组成首尾相接的环
// 从1号点从数字1开始报数，哪个节点报到数字k，就删除该节点
// 然后下一个节点从数字1开始重新报数，最终环上会剩下一个节点
// 返回该节点的编号
// 1 <= n, k <= 10^6
// 测试链接 : https://www.luogu.com.cn/problem/P8671
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有测试用例
#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n,k;
    cin>>n>>k;
    int ans = 1;
    for (int c = 2; c <= n; c++) {
        ans = (ans + k - 1) % c + 1;
    }
    cout<<ans;
    return 0;
}
