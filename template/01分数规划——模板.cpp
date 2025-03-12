// 01分数规划模版题
// 给定n个数据，每个数据有(a, b)两个值，都为整数，并且都是非负的
// 请舍弃掉k个数据，希望让剩下数据做到，所有a的和 / 所有b的和，这个比值尽量大
// 如果剩下数据所有b的和为0，认为无意义
// 最后，将该比值 * 100，小数部分四舍五入的整数结果返回
// 1 <= n <= 100
// 0 <= a、b <= 10^9
// 测试链接 : https://www.luogu.com.cn/problem/P10505
// 测试链接 : http://poj.org/problem?id=2976
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有测试用例
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1001;
const double sml = 1e-6;

struct node {
    double x,y,r;
}arr[MAXN];
int n,k;

bool cmp(node a,node b){
    return a.r>b.r;
}

bool check(double x) {
    // x固定的情况下，得到所有数据的结余
    for (int i = 1; i <= n; i++) {
        arr[i].r = arr[i].x - x * arr[i].y;
    }
    // 结余从大到小排序
    sort(arr + 1, arr + n + 1, cmp);
    // 最大k个结余的累加和
    double sum = 0;
    for (int i = 1; i <= k; i++) {
        sum += arr[i].r;
    }
    return sum >= 0;
}

int main()
{
    cin>>n>>k;
    while((n+k)!=0){
        k = n - k;
        for (int i = 1; i <= n; i++) {
            cin>>arr[i].x;
        }
        for (int i = 1; i <= n; i++) {
            cin>>arr[i].y;
        }
        double l = 0, r = 0, x;
        for (int i = 1; i <= n; i++) {
            r += arr[i].x;
        }
        double ans = 0;
        while (l < r && r - l >= sml) {
            x = (l + r) / 2;
            if (check(x)) {
                ans = x;
                l = x + sml;
            } else {
                r = x - sml;
            }
        }
        cout<<((int) (100 * (ans + 0.005)))<<endl;
        cin>>n>>k;
    }
    return 0;
}
