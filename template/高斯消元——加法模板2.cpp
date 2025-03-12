//最最基本的模版题
// 高斯消元解决加法方程组模版(区分矛盾、多解、唯一解)
// 一共有n个变量，给定n个加法方程，构成一个加法方程组
// 如果方程组存在矛盾，打印-1
// 如果方程组无法确定唯一解，打印0
// 如果方程组存在唯一解，打印每个变量的值，保留小数点后两位
// 1 <= n <= 50
// 测试链接 : https://www.luogu.com.cn/problem/P2455
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有测试用例
#include <iostream>
#include <cmath>
#include <iomanip>  // for std::setprecision
using namespace std;

const int MAXN = 101;
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
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n+1;j++){
            cin>>mat[i][j];
        }
    }
    gauss(n);
    int sign = 1;
    for (int i = 1; i <= n; i++) {
        if (abs(mat[i][i]) < sml && abs(mat[i][n + 1]) >= sml) {
            //矛盾可以理解为没有主元和自由元  但是有结果
            sign = -1;
            break;
        }
        if (abs(mat[i][i]) < sml) {
            //多解可以理解为没有主元和自由元  结果为0  认为没有结果s
            sign = 0;
        }
    }
    if (sign == 1) {
        for (int i = 1; i <= n; i++) {
            printf("x%d=%.2lf\n",i, mat[i][n + 1]);
        }
    } else {
        cout<<sign<<endl;
    }
    return 0;
}
