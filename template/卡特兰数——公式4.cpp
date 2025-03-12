// 任意前缀上红多于黑
// 有n个红和n个黑，要组成2n长度的数列，保证任意前缀上，红的数量 >= 黑的数量
// 返回有多少种排列方法，答案对 100 取模
// 1 <= n <= 100
// 测试链接 : https://www.luogu.com.cn/problem/P1722
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有测试用例
#include<bits/stdc++.h>
using namespace std;
const int MOD = 100;
const int MAXN = 1000001;

// 公式4
long long compute4(int n) {
    long long f[n + 1];
    for(int i=0;i<=n;i++){
        f[i]=0;
    }
    f[0] = f[1] = 1;
    for (int i = 2; i <= n; i++) {
        for (int l = 0, r = i - 1; l < i; l++, r--) {
            f[i] = (f[i] + f[l] * f[r] % MOD) % MOD;
        }
    }
    return f[n];
}

int main()
{
    int n;
    cin>>n;
    cout<<compute4(n)<<endl;

    return 0;
}

