// 格点连线上有几个格点
// 二维网格中只有x和y的值都为整数的坐标，才叫格点
// 给定两个格点，A在(x1, y1)，B在(x2, y2)
// 返回A和B的连线上，包括A和B在内，一共有几个格点
// -10^9 <= x1、y1、x2、y2 <= 10^9
// 测试链接 : https://lightoj.com/problem/how-many-points
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有测试用例
#include<bits/stdc++.h>
using namespace std;

long gcd(long a, long b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main()
{
    int cases ;
    cin>>cases;
    for (int t = 1; t <= cases; t++) {
        long x1,y1,x2,y2;
        cin>>x1>>y1>>x2>>y2;
        long ans = gcd(abs(x1 - x2), abs(y1 - y2)) + 1;
        cout<<"Case " << t + ": " << ans<<endl;
    }
    return 0;
}
