#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 101;

vector<vector<int>> mat(MAXN, vector<int>(MAXN + 1, 0));
//事实上  我们一般用静态表   此段代码由ai生成

// 注意：这里为了简化，我们直接交换行向量，而不是真正的行向量内容
// 需要在函数外定义一个辅助函数来真正交换两个vector<int>
void swap(int a, int b) {
    cout<<"swap"<<endl;
    vector<int> tmp = mat[a];
    mat[a] = mat[b];
    mat[b] = tmp;
}

// 高斯消元解决异或方程组模版
// 需要保证变量有n个，表达式也有n个
void gauss(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j < i && mat[j][j] == 1) {
                continue;
            }
            if (mat[j][i] == 1) {
                //异或运算  要么是0要么是1  所以找到1就可以结束了
                swap(i, j);
                break;
            }
        }
        if (mat[i][i] == 1) {
            for (int j = 0; j < n; j++) {
                if (i != j && mat[j][i] == 1) {
                    for (int k = i; k <= n; k++) {
                        mat[j][k] ^= mat[i][k];
                    }
                }
            }
        }
    }
}

void print(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= n; j++) {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
    cout << "========================" << endl;
}

int main() {
    cout << "课上图解的例子，有唯一解" << endl;
    // x1 ^ x2 ^ x3 = 0
    // x1 ^ x3 ^ x4 = 1
    // x2 ^ x3 ^ x4 = 1
    // x3 ^ x4 = 0
    mat[0][0] = 1; mat[0][1] = 1; mat[0][2] = 1; mat[0][3] = 0; mat[0][4] = 0;
    mat[1][0] = 1; mat[1][1] = 0; mat[1][2] = 1; mat[1][3] = 1; mat[1][4] = 1;
    mat[2][0] = 0; mat[2][1] = 1; mat[2][2] = 1; mat[2][3] = 1; mat[2][4] = 1;
    mat[3][0] = 0; mat[3][1] = 0; mat[3][2] = 1; mat[3][3] = 1; mat[3][4] = 0;
    gauss(4);
    print(4);

    cout << "表达式存在矛盾的例子" << endl;
    // x1 ^ x2 = 1
    // x1 ^ x3 = 1
    // x2 ^ x3 = 1
    mat[0][0] = 1; mat[0][1] = 1; mat[0][2] = 0; mat[0][3] = 1;
    mat[1][0] = 1; mat[1][1] = 0; mat[1][2] = 1; mat[1][3] = 1;
    mat[2][0] = 0; mat[2][1] = 1; mat[2][2] = 1; mat[2][3] = 1;
    gauss(3);
    print(3);

    cout << "表达式存在多解的例子" << endl;
    // x1 ^ x3 = 1
    // x2 ^ x3 = 1
    // x1 ^ x2 = 0
    mat[0][0] = 1; mat[0][1] = 0; mat[0][2] = 1; mat[0][3] = 1;
    mat[1][0] = 0; mat[1][1] = 1; mat[1][2] = 1; mat[1][3] = 1;
    mat[2][0] = 1; mat[2][1] = 1; mat[2][2] = 0; mat[2][3] = 0;
    // 注意：这个例子在C++中应该仍然使用3个变量，所以去掉下面的行
    // mat[3][0] = 1; mat[3][1] = 1; mat[3][2] = 0; mat[3][3] = 0; // 这行不应该存在
    gauss(3);
    print(3);

    cout << "注意下面这个多解的例子" << endl;
    // x1 ^ x3 ^ x4 = 0
    // x2 ^ x3 ^ x4 = 0
    // x1 ^ x2 = 0
    // x3 ^ x4 = 1
    mat[0][0] = 1; mat[0][1] = 0; mat[0][2] = 1; mat[0][3] = 1; mat[0][4] = 0;
    mat[1][0] = 0; mat[1][1] = 1; mat[1][2] = 1; mat[1][3] = 1; mat[1][4] = 0;
    mat[2][0] = 1; mat[2][1] = 1; mat[2][2] = 0; mat[2][3] = 0; mat[2][4] = 0;
    mat[3][0] = 0; mat[3][1] = 0; mat[3][2] = 1; mat[3][3] = 1; mat[3][4] = 1;
    gauss(4);
    print(4);
    cout << "最后一个例子里" << endl;
    cout << "主元x1和x2，不受其他自由元影响，值可以直接确定" << endl;
    cout << "但是主元x3，受到自由元x4的影响，x3 ^ x4 = 1" << endl;
    cout << "只有自由元x4确定了值，主元x3的值才能确定" << endl;
    cout << "这里是想说，消元完成后，如果结论是多解，那么" << endl;
    cout << "有些主元的值可以直接确定" << endl;
    cout << "有些主元的值需要若干自由元确定之后才能确定" << endl;
    cout << "这就是上节课讲解的内容：" << endl;
    cout << "主元和自由元之间的依赖关系" << endl;
    cout << "请确保已经掌握" << endl;

    return 0;
}
