// 上学需要的最少跳跃能力
// 青蛙住在一条河边，家在0位置, 每天到河对岸的上学，学校在n位置
// 河里的石头排成了一条直线，青蛙每次跳跃必须落在一块石头或者岸上
// 给定一个长度为n-1的数组arr，表示1~n-1位置每块石头的高度数值
// 每次青蛙从一块石头起跳，这块石头的高度就会下降1
// 当石头的高度下降到0时，青蛙不能再跳到这块石头上，跳跃后使石头高度下降到0是允许的
// 青蛙一共需要去学校上x天课, 所以它需要往返x次，青蛙具有跳跃能力y, 它可以跳跃不超过y的距离
// 请问青蛙的跳跃能力至少是多少，才能用这些石头往返x次
// 1 <= n <= 10^5
// 1 <= arr[i] <= 10^4
// 1 <= x <= 10^9
// 测试链接 : https://www.luogu.com.cn/problem/P8775
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有用例
#include<bits/stdc++.h>
using namespace std;

int n;
long nums[100005];

int main()
{
    int x;
    cin>>n>>x;
    for(int i=1;i<n;i++){
        cin>>nums[i];
    }
    nums[n]=2*x;
    int ans = 0;
    // 窗口[l,r)，左闭右开！左闭右开！左闭右开！
    // 窗口内的累加和是sum
    // 当r来到n+1位置，那么窗口一定无法继续右扩了，因为n位置有足够的高度
    long sum = nums[1];
    for (int l = 1, r = 2; l <= n; l++) {
        while (sum < x * 2) {
            sum += nums[r++];
        }
        ans = max(ans, r - l);
        sum -= nums[l];
    }
    cout<<ans;
    return 0;
}
