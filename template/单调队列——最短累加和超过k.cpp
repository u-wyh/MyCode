#include<bits/stdc++.h>
using namespace std;

int n,k,h,t;
int nums[1000],sum[1000],q[1000];

int main()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>nums[i];
        sum[i]=sum[i-1]+nums[i];
    }
    h=t=0;
    int ans=1e9;
    for (int i = 0; i <= n; i++) {
        while (h != t && sum[i] - sum[q[h]] >= k) {
            ans = min(ans, i - q[h++]);
        }
        // 前i个数前缀和，从尾部加入
        // 小 大
        while (h != t && sum[q[t - 1]] >= sum[i]) {
            t--;
        }
        q[t++] = i;
    }
    if(ans==1e9)
        ans=-1;
    cout<<ans;
    return 0;
}
