//这个需要自己处理一下得到mat矩阵
// 球形空间的中心点
// 如果在n维空间中，那么表达一个点的位置，需要n个坐标的值
// 现在给定n+1个点，每个点都有n个坐标的值，代表在n维空间中的位置
// 假设这n+1个点都在n维空间的球面上，请返回球心的位置
// 球心的位置当然也是n个坐标的值，打印出来
// 在n维空间中，计算任意两点的距离，请用经典的欧式距离
// 1 <= n <= 10
// 坐标信息精确到小数点后6位，绝对值都不超过20000
// 测试链接 : https://www.luogu.com.cn/problem/P4035
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有测试用例
#include <iostream>
#include <cmath>
#include <iomanip>  // for std::setprecision
using namespace std;

const int MAXN = 12;
// 0.0000001 == 1e-7
// 因为double类型有精度问题，所以认为
// 如果一个数字绝对值  <  sml，则认为该数字是0
// 如果一个数字绝对值  >= sml，则认为该数字不是0
const double sml = 1e-7;

double mat[MAXN][MAXN + 1];

// Function to swap rows in the matrix
void swap(int a, int b) {
    //swap的作用是用于交换两个数组的某一行
    //使用系统的内置函数可以  但是时间稍微差一点
    //在程序中 建议全部手写
    //但是手写的时候一定要注意中间数组tmp的类型是int 还是 double
    //并且手写的时候一定要注意列的范围  不能缺少
    double tmp[MAXN + 1];
    for (int j = 0; j <= MAXN; j++) {
        tmp[j] = mat[a][j];
        mat[a][j] = mat[b][j];
        mat[b][j] = tmp[j];
    }
}

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
        swap(i, max);//交换改行最大值
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

int main() {
    int n;
    cin>>n;
    double data[12][12];
    for (int i = 1; i <= n + 1; i++) {
        for (int j = 1; j <= n; j++) {
            cin>>data[i][j];
        }
    }
    //这道题需要自己提炼方程式
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            mat[i][j] = 2 * (data[i][j] - data[i + 1][j]);
            mat[i][n + 1] += data[i][j] * data[i][j] - data[i + 1][j] * data[i + 1][j];
        }
    }
    gauss(n);
    for (int i = 1; i <= n; i++) {
        printf("%.3f ", mat[i][n + 1]);
    }
    return 0;
}
