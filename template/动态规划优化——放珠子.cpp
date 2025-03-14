// 将珠子放进背包中
// 给定一个长度为n的数组weights，背包一共有k个
// 其中weights[i]是第i个珠子的重量
// 请你按照如下规则将所有的珠子放进k个背包
// 1，没有背包是空的
// 2，如果第i个珠子和第j个珠子在同一个背包里，那么i到j所有珠子都要在这个背包里
// 一个背包如果包含i到j的所有珠子，这个背包的价格是weights[i]+weights[j]
// 一个珠子分配方案的分数，是所有k个背包的价格之和
// 请返回所有分配方案中，最大分数与最小分数的差值为多少
// 1 <= n, k <= 10^5
// 测试链接 : https://leetcode.cn/problems/put-marbles-in-bags/
#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n,k;
    cin>>n>>k;
    int weight[n];
    for(int i=0;i<n;i++){
        cin>>weight[i];
    }
    int sum[n-1];
    for(int i=1;i<n;i++){
        sum[i-1]=weight[i]+weight[i-1];
    }
    sort(sum,sum+n-1);
    int small = 0;
	int big = 0;
	for (int i = 0, j = n - 2, p = 1; p < k; i++, j--, p++) {
        small += sum[i];
        big += sum[j];
    }
	cout<<(big - small);
    return 0;
}
