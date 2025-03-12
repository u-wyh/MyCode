// 乘法快速幂模版
// 求a的b次方，对p取模的结果
// 测试链接 : https://www.luogu.com.cn/problem/P1226
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法
// 提交以下的code，提交时请把类名改成"Main"，可以直接通过
#include<bits/stdc++.h>
using namespace std;

long long power(long long a,long long b,long long mod){
    long long ans=1;
    while(b>0){
        if(b&1){
            ans=(ans*a)%mod;
        }
        a=(a*a)%mod;//a每次相当于倍增  只有b的这一位上有1的时候 才会将a乘进ans中
        b>>=1;//b向右移动一位
    }
    return ans;
}

int main()
{
    long long a,b,mod;
    cin>>a>>b>>mod;
    cout<<a<<"^"<<b<< " mod "<<mod<<"="<<power(a,b,mod)<<endl;
    return 0;
}
