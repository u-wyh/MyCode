// 相邻与结果不为0的最长子序列
// 给定一个长度为n的数组arr，你可以随意选择数字组成子序列
// 但是要求任意相邻的两个数&的结果不能是0，这样的子序列才是合法的
// 返回最长合法子序列的长度
// 1 <= n <= 10^5
// 0 <= arr[i] <= 10^9
// 测试链接 : https://www.luogu.com.cn/problem/P4310
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有用例
#include<bits/stdc++.h>
using namespace std;

int n;
int pre[32];
int arr[100005];

int main()
{
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    for (int i = 0, num, cur; i < n; i++) {
        num = arr[i];
        cur = 1;
        for (int j = 0; j < 31; j++) {
            if (((num >> j) & 1) == 1) {
                cur = max(cur, pre[j] + 1);
            }
        }
        for (int j = 0; j < 31; j++) {
            if (((num >> j) & 1) == 1) {
                pre[j] = max(pre[j], cur);
            }
        }
    }
    int ans = 0;
    for (int j = 0; j < 31; j++) {
        ans = max(ans, pre[j]);
    }
    cout<<ans;
    return 0;
}
