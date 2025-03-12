// 返回无序数组中累加和为给定值的最长子数组长度
// 给定一个无序数组arr, 其中元素可正、可负、可0
// 给定一个整数aim
// 求arr所有子数组中累加和为aim的最长子数组长度
// 测试链接 : https://www.nowcoder.com/practice/36fb0fd3c656480c92b569258a1223d5
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法
// 提交以下的code，提交时请把类名改成"Main"，可以直接通过

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,aim;
int nums[MAXN];
int sum[MAXN];
map<int ,int >M;
int ans=0;

int main()
{
    cin>>n>>aim;
    M[0]=0;
    for(int i=1;i<=n;i++){
        cin>>nums[i];
        sum[i]=sum[i-1]+nums[i];
        if(M.find(sum[i])==M.end()){
            M[sum[i]]=i;
        }
        if(M.find(aim-sum[i])!=M.end()){
            ans=max(ans,i-M[aim-sum[i]]);
        }
    }
    cout<<ans;
    return 0;
}
