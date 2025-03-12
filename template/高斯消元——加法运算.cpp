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
    //cout<<"swap"<<endl;
    for (int j = 0; j <= MAXN; j++) {
        tmp[j] = mat[a][j];
        mat[a][j] = mat[b][j];
        mat[b][j] = tmp[j];
    }
}

// Gaussian Elimination to solve linear equations
void gauss(int n) {
    for (int i = 1; i <= n; i++) {
        //最外层循环每次解决一行 求出xi
        int max = i;
        for (int j = 1; j <= n; j++) {
            if (j < i && abs(mat[j][j]) >= sml) {
                //如果已经结束的行存在主元  那么这一行不能用于交换
                //否则即使这一行已经结束  但是没有主元   可能还是会用于交换
                continue;
            }
            if (abs(mat[j][i]) > abs(mat[max][i])) {
                //每次都要比较一下大小
                max = j;
            }
        }
        swap(i, max);//交换改行最大值
        if (abs(mat[i][i]) >= sml) {
            //表示存在主元  否则表明这个xi没有主元
            double tmp = mat[i][i];
            for (int j = i; j <= n + 1; j++) {
                mat[i][j] /= tmp;
                //将当前行的主元编程一
            }
            for (int j = 1; j <= n; j++) {
                if (i != j) {
                    //将该列的非主元清除
                    double rate = mat[j][i] / mat[i][i];
                    for (int k = i; k <= n + 1; k++) {
                        mat[j][k] -= mat[i][k] * rate;
                    }
                }
            }
        }
    }
}

// Function to print the matrix
void print(int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n + 1; j++) {
            std::cout << std::fixed << std::setprecision(2) << mat[i][j] << "  ";
        }
        std::cout << std::endl;
    }
    std::cout << "========================" << std::endl;
}

int main() {
    // 唯一解
    // 1*x1 + 2*x2 - 1*x3 = 9
    // 2*x1 - 1*x2 + 2*x3 = 7
    // 1*x1 - 2*x2 + 2*x3 = 0
    cout<<"唯一解"<<endl;
    mat[1][1] = 1; mat[1][2] = 2; mat[1][3] = -1; mat[1][4] = 9;
    mat[2][1] = 2; mat[2][2] = -1; mat[2][3] = 2; mat[2][4] = 7;
    mat[3][1] = 1; mat[3][2] = -2; mat[3][3] = 2; mat[3][4] = 0;
    gauss(3);
    print(3);

    // 矛盾
    // 1*x1 + 1*x2 = 3
    // 2*x1 + 2*x2 = 7
    cout<<"矛盾"<<endl;
    mat[1][1] = 1; mat[1][2] = 1; mat[1][3] = 3;
    mat[2][1] = 2; mat[2][2] = 2; mat[2][3] = 7;
    gauss(2);
    print(2);

    // 多解
    // 1*x1 + 1*x2 = 3
    // 2*x1 + 2*x2 = 6
    cout<<"多解"<<endl;
    mat[1][1] = 1; mat[1][2] = 1; mat[1][3] = 3;
    mat[2][1] = 2; mat[2][2] = 2; mat[2][3] = 6;
    gauss(2);
    print(2);

    // 表达式冗余，唯一解
    // 1*x1 + 2*x2 - 1*x3 + 0*x4 = 9
    // 2*x1 + 4*x2 - 2*x3 + 0*x4 = 18
    // 2*x1 - 1*x2 + 2*x3 + 0*x4 = 7
    // 1*x1 - 2*x2 + 2*x3 + 0*x4 = 0
    cout<<"表达式冗余，唯一解"<<endl;
    mat[1][1] = 1; mat[1][2] = 2; mat[1][3] = -1; mat[1][4] = 0; mat[1][5] = 9;
    mat[2][1] = 2; mat[2][2] = 4; mat[2][3] = -2; mat[2][4] = 0; mat[2][5] = 18;
    mat[3][1] = 2; mat[3][2] = -1; mat[3][3] = 2; mat[3][4] = 0; mat[3][5] = 7;
    mat[4][1] = 1; mat[4][2] = -2; mat[4][3] = 2; mat[4][4] = 0; mat[4][5] = 0;
    gauss(4);
    print(4);

    // 表达式冗余，矛盾
    // 1*x1 + 2*x2 - 1*x3 = 9
    // 2*x1 + 4*x2 - 2*x3 = 18
    // 2*x1 - 1*x2 + 2*x3 = 7
    // 4*x1 - 2*x2 + 4*x3 = 10
    cout<<"表达式冗余，矛盾"<<endl;
    mat[1][1] = 1; mat[1][2] = 2; mat[1][3] = -1; mat[1][4] = 0; mat[1][5] = 9;
    mat[2][1] = 2; mat[2][2] = 4; mat[2][3] = -2; mat[2][4] = 0; mat[2][5] = 18;
    mat[3][1] = 2; mat[3][2] = -1; mat[3][3] = 2; mat[3][4] = 0; mat[3][5] = 7;
    mat[4][1] = 4; mat[4][2] = -2; mat[4][3] = 4; mat[4][4] = 0; mat[4][5] = 10;
    gauss(4);
    print(4);

    // 表达式冗余，多解
    // 1*x1 + 2*x2 - 1*x3 = 9
    // 2*x1 + 4*x2 - 2*x3 = 18
    // 2*x1 - 1*x2 + 2*x3 = 7
    // 4*x1 - 2*x2 + 4*x3 = 14
    cout<<"表达式冗余，多解"<<endl;
    mat[1][1] = 1; mat[1][2] = 2; mat[1][3] = -1; mat[1][4] = 0; mat[1][5] = 9;
    mat[2][1] = 2; mat[2][2] = 4; mat[2][3] = -2; mat[2][4] = 0; mat[2][5] = 18;
    mat[3][1] = 2; mat[3][2] = -1; mat[3][3] = 2; mat[3][4] = 0; mat[3][5] = 7;
    mat[4][1] = 4; mat[4][2] = -2; mat[4][3] = 4; mat[4][4] = 0; mat[4][5] = 14;
    gauss(4);
    print(4);

    // 表达式不足，矛盾
    // 1*x1 + 2*x2 - 1*x3 = 5
    // 2*x1 + 4*x2 - 2*x3 = 7
    cout<<"表达式不足，矛盾"<<endl;
    mat[1][1] = 1; mat[1][2] = 2; mat[1][3] = -1; mat[1][4] = 5;
    mat[2][1] = 2; mat[2][2] = 4; mat[2][3] = -2; mat[2][4] = 7;
    mat[3][1] = 0; mat[3][2] = 0; mat[3][3] = 0;  mat[3][4] = 0;
    gauss(3);
    print(3);

    // 表达式不足，多解
    // 1*x1 + 2*x2 - 1*x3 = 5
    // 2*x1 + 2*x2 - 1*x3 = 8
    cout<<"表达式不足，多解"<<endl;
    mat[1][1] = 1; mat[1][2] = 2; mat[1][3] = -1; mat[1][4] = 5;
    mat[2][1] = 2; mat[2][2] = 2; mat[2][3] = -1; mat[2][4] = 8;
    mat[3][1] = 0; mat[3][2] = 0; mat[3][3] = 0;  mat[3][4] = 0;
    gauss(3);
    print(3);

    // 正确区分矛盾、多解、唯一解
    // 0*x1 + 2*x2 = 3
    // 0*x1 + 0*x2 = 0
    cout<<"正确区分矛盾、多解、唯一解"<<endl;
    mat[1][1] = 0; mat[1][2] = 2; mat[1][3] = 3;
    mat[2][1] = 0; mat[2][2] = 0; mat[2][3] = 0;
    gauss(2);
    print(2);

    // 有些主元可以确定值
    // a  + b + c = 5
    // 2a + b + c = 7
    cout<<"有些主元可以确定值"<<endl;
    mat[1][1] = 1; mat[1][2] = 1; mat[1][3] = 1; mat[1][4] = 5;
    mat[2][1] = 2; mat[2][2] = 1; mat[2][3] = 1; mat[2][4] = 7;
    mat[3][1] = 0; mat[3][2] = 0; mat[3][3] = 0; mat[3][4] = 0;
    gauss(3);
    print(3);

    // 有些主元还受到自由元的影响
    // a + b = 5
    cout<<"有些主元还受到自由元的影响"<<endl;
    mat[1][1] = 1; mat[1][2] = 1; mat[1][3] = 5;
    mat[2][1] = 0; mat[2][2] = 0; mat[2][3] = 0;
    gauss(2);
    print(2);

    return 0;
}
