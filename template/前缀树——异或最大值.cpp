// 数组中两个数的最大异或值
// 给你一个整数数组 nums ，返回 nums[i] XOR nums[j] 的最大运算结果，其中 0<=i<=j<=n
// 1 <= nums.length <= 2 * 10^5
// 0 <= nums[i] <= 2^31 - 1
// 测试链接 : https://leetcode.cn/problems/maximum-xor-of-two-numbers-in-an-array/

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int MAXM = 3e6+5;

int nums[MAXN];
int n;
int ans=0;
int tree[MAXM][2];
int cnt=1;
int high;

void insert(int num) {
    int cur = 1;
    for (int i = high, path; i >= 0; i--) {
        path = (num >> i) & 1;
        if (tree[cur][path] == 0) {
            tree[cur][path] = ++cnt;
        }
        cur = tree[cur][path];
    }
}

void build(){
    int maxans=INT_MIN;
    for(int i=1;i<=n;i++){
        maxans=max(maxans,nums[i]);
    }
    high=31-__builtin_clz(maxans);//选择出有效的位数  即不要前缀0
    for(int num:nums){
        insert(num);//将数字插入前缀树中
    }
}

int maxXor(int num) {
    // 最终异或的结果(尽量大)
    int ans = 0;
    // 前缀树目前来到的节点编号
    int cur = 1;
    for (int i = high, status, want; i >= 0; i--) {
        // status : num第i位的状态
        status = (num >> i) & 1;
        // want : num第i位希望遇到的状态
        want = status ^ 1;
        if (tree[cur][want] == 0) { // 询问前缀树，能不能达成
            // 不能达成
            want ^= 1;
        }
        // want变成真的往下走的路
        ans |= (status ^ want) << i;
        cur = tree[cur][want];
    }
    return ans;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>nums[i];
    }
    build();//将所有的值加入树中
    for (int num : nums) {
        //将每一个数选择一个数字使答案最大
        ans = max(ans, maxXor(num));
    }
    cout<<ans;
    return 0;
}
