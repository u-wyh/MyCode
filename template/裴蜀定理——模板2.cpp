// 修理宝塔
// 一共有编号1~n的宝塔，其中a号和b号宝塔已经修好了
// Yuwgna和Iaka两个人轮流修塔，Yuwgna先手，Iaka后手，谁先修完所有的塔谁赢
// 每次可以选择j+k号或者j-k号塔进行修理，其中j和k是任意两个已经修好的塔
// 也就是输入n、a、b，如果先手赢打印"Yuwgna"，后手赢打印"Iaka"
// 2 <= n <= 2 * 10^4
// 测试链接 : https://acm.hdu.edu.cn/showproblem.php?pid=5512
// 测试链接 : https://vjudge.net/problem/HDU-5512
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有测试用例
#include<iostream>
using namespace std;

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main()
{
    int cases;
    cin>>cases;
    for (int t = 1, n, a, b; t <= cases; t++) {
        cin>>n>>a>>b;
        cout<<"Case #" << t << ": ";
        if (((n / gcd(a, b)) & 1) == 1) {
            cout<<"Yuwgna"<<endl;
        } else {
            cout<<"Iaka"<<endl;;
        }
    }
    return 0;
}
