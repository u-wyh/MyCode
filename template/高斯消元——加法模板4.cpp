//给出了矩阵中的一部分关系  需要自己整理剩下的关系
// 有一次错误称重求最重物品
// 一共有n个物品，编号1~n，定义合法方案如下：
// 1，每个物品的重量都是确定的
// 2，每个物品的重量一定都是正整数
// 3，最重的物品有且仅有1个
// 每次称重格式类似：3 2 5 6 10，代表本次称重涉3个物品，编号为2、5、6，总重量10
// 一共有n+1条称重数据，称重数据整体有效的条件为：
// 错误的称重数据有且仅有1条，只有排除这条错误称重，才能求出一种合法方案
// 如果称重数据有效，打印最重三角形的编号
// 如果称重数据无效，打印"illegal"
// 1 <= m <= n <= 100
// 测试链接 : https://www.luogu.com.cn/problem/P5027
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有测试用例
#include <iostream>
#include <cmath>
#include <iomanip>  // for std::setprecision
#include <climits>
#include <cfloat>
using namespace std;

const int MAXN = 102;
// 0.0000001 == 1e-7
// 因为double类型有精度问题，所以认为
// 如果一个数字绝对值  <  sml，则认为该数字是0
// 如果一个数字绝对值  >= sml，则认为该数字不是0
const double sml = 1e-7;
int n;
int data[MAXN][MAXN];
double mat[MAXN][MAXN + 1];

//void swap(int a, int b) {
//    double tmp[MAXN + 1];
//    //cout<<"swap"<<endl;
//    for (int j = 0; j <= MAXN; j++) {
//        tmp[j] = mat[a][j];
//        mat[a][j] = mat[b][j];
//        mat[b][j] = tmp[j];
//    }
//}
//
//void swapdata(int a, int b) {
//    double tmp[MAXN + 1];
//    for (int j = 0; j <= MAXN; j++) {
//        tmp[j] = data[a][j];
//        data[a][j] = data[b][j];
//        data[b][j] = tmp[j];
//    }
//}

// Gaussian Elimination to solve linear equations
void gauss(int n) {
    for (int i = 1; i <= n; i++) {
        int max = i;
        for (int j = 1; j <= n; j++) {
            if (j < i && std::abs(mat[j][j]) >= sml) {
                continue;
            }
            if (std::abs(mat[j][i]) > std::abs(mat[max][i])) {
                max = j;
            }
        }
        swap(mat[i], mat[max]);//交换改行最大值
        if (std::abs(mat[i][i]) >= sml) {
            double tmp = mat[i][i];
            for (int j = i; j <= n + 1; j++) {
                mat[i][j] /= tmp;
            }
            for (int j = 1; j <= n; j++) {
                if (i != j) {
                    double rate = mat[j][i] / mat[i][i];
                    for (int k = i; k <= n + 1; k++) {
                        mat[j][k] -= mat[i][k] * rate;
                    }
                }
            }
        }
    }
}

int check() {
    gauss(n);
    double maxv = 0;
    int maxt = 0;
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (mat[i][i] == 0) {
            return 0;
        }
        if (mat[i][n + 1] <= 0 || mat[i][n + 1] != (int) mat[i][n + 1]) {
            return 0;
        }
        if (maxv < mat[i][n + 1]) {
            maxv = mat[i][n + 1];
            maxt = 1;
            ans = i;
        } else if (maxv == mat[i][n + 1]) {
            maxt++;
        }
    }
    if (maxt > 1) {
        return 0;
    }
    return ans;
}

int main() {
    cin>>n;
    for (int i = 1, m; i <= n + 1; i++) {
        cin>>m;
        for (int j = 1, cur; j <= m; j++) {
            cin>>cur;
            data[i][cur] = 1;
        }
        cin>>data[i][n + 1];
    }
    //这道题的方程式信息就不全
    //并且还要自己补充一些信息以达到n*(n+1)
    int ans = 0;
    int times = 0;
    for (int k = 1; k <= n + 1; k++) {
        swap(data[k], data[n + 1]);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n + 1; j++) {
                mat[i][j] = data[i][j];
            }
        }
        swap(data[k], data[n + 1]);
        int cur = check();
        if (cur != 0) {
            times++;
            ans = cur;
        }
    }
    if (times != 1) {
        cout<<"illegal"<<endl;
    } else {
        cout<<ans<<endl;
    }
    return 0;
}

