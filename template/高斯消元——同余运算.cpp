#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 课上讲述高斯消元解决同余方程组的例子

const int MOD = 7;
const int MAXN = 101;
vector<vector<int>> mat(MAXN, vector<int>(MAXN + 1));
vector<int> inv(MOD);
//我们求逆元可以直接做出逆元表  适用于求一些多次要使用的连续的数字的逆元
//在这里也提供了费马小定理求逆元的函数  适用于解决只需要个别数字的逆元

// 快速幂算法
long long power(long long num, long long pow, long long mod) {
    long long ans = 1;
    while (pow > 0) {
        if (pow % 2 == 1) {
            ans = (ans * num) % mod;
        }
        num = (num * num) % mod;
        pow /= 2;
    }
    return ans;
}

// 费马小定理计算逆元
long long fermat(long long num, long long mod) {
    return power(num, mod - 2, mod);
}

// 逆元线性递推公式求逆元表，讲解099 - 除法同余
void compute_inv() {
    inv[1] = 1;
    for (int i = 2; i < MOD; i++) {
        inv[i] = MOD - (long long)inv[MOD % i] * (MOD / i) % MOD;
    }
}

// 求a和b的最大公约数，保证a和b都不等于0
int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

void swap(int a, int b) {
    int tmp[MAXN + 1];
    //cout<<"swap"<<endl;
    for (int j = 0; j <= MAXN; j++) {
        tmp[j] = mat[a][j];
        mat[a][j] = mat[b][j];
        mat[b][j] = tmp[j];
    }
}

// 高斯消元解决同余方程组模版，保证初始系数没有负数
void gauss(int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            // 已经成为主元的行不参与
            if (j < i && mat[j][j] != 0) {
                continue;
            }
            // 找到系数不等于0的行做主元即可
            if (mat[j][i] != 0) {
                swap(i,j);
                break;
            }
        }
        if (mat[i][i] != 0) {
            for (int j = 1; j <= n; j++) {
                if (i != j && mat[j][i] != 0) {
                    int gcd_val = gcd(mat[j][i], mat[i][i]);
                    int a = mat[i][i] / gcd_val;
                    int b = mat[j][i] / gcd_val;
                    if (j < i && mat[j][j] != 0) {
                        // 如果j行有主元，那么从j列到i-1列的所有系数 * a
                        // 正确更新主元和自由元之间的关系
                        for (int k = j; k < i; k++) {
                            mat[j][k] = (mat[j][k] * a) % MOD;
                        }
                    }
                    // 正常消元
                    for (int k = i; k <= n + 1; k++) {
                        mat[j][k] = ((mat[j][k] * a - mat[i][k] * b) % MOD + MOD) % MOD;
                    }
                }
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        if (mat[i][i] != 0) {
            // 检查当前主元是否被若干自由元影响
            // 如果当前主元不受自由元影响，那么可以确定当前主元的值
            // 否则保留这种影响，正确显示主元和自由元的关系
            bool flag = false;
            for (int j = i + 1; j <= n; j++) {
                if (mat[i][j] != 0) {
                    flag = true;
                    break;
                }
            }
            if (!flag) {
                //这里表示主元不受自由元影响  可以直接求出他的同余值
                // 在模意义下应该求逆元，(a / b) % MOD = (a * b的逆元) % MOD
                mat[i][n + 1] = (mat[i][n + 1] * inv[mat[i][i]]) % MOD;
                mat[i][i] = 1;
            }
        }
    }
}

void print(int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n + 1; j++) {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
    cout << "========================" << endl;
}

int main() {
    // 逆元表建立好
    compute_inv();
    cout << "课上图解的例子，唯一解" << endl;
    // 4*x1 + 2*x2 + 4*x3 同余 3
    // 2*x1 + 5*x2 + 2*x3 同余 2
    // 6*x1 + 3*x2 + 4*x3 同余 5
    mat[1][1] = 4; mat[1][2] = 2; mat[1][3] = 4; mat[1][4] = 3;
    mat[2][1] = 2; mat[2][2] = 5; mat[2][3] = 2; mat[2][4] = 2;
    mat[3][1] = 6; mat[3][2] = 3; mat[3][3] = 4; mat[3][4] = 5;
    gauss(3);
    print(3);

    cout << "表达式存在矛盾的例子" << endl;
    // 1*x1 + 2*x2 + 3*x3 同余 2
    // 2*x1 + 4*x2 + 6*x3 同余 5
    // 0*x1 + 3*x2 + 4*x3 同余 2
    mat[1][1] = 1; mat[1][2] = 2; mat[1][3] = 3; mat[1][4] = 2;
    mat[2][1] = 2; mat[2][2] = 4; mat[2][3] = 6; mat[2][4] = 5;
    mat[3][1] = 0; mat[3][2] = 3; mat[3][3] = 4; mat[3][4] = 2;
    gauss(3);
    print(3);

    cout << "课上图解的例子，多解" << endl;
    cout << "只有确定了自由元，才能确定主元的值" << endl;
    cout << "如果是多解的情况，那么在消元结束后" << endl;
    cout << "二维矩阵中主元和自由元的关系是正确的" << endl;
    cout << "课上也进行了验证" << endl;
    // 1*x1 + 2*x2 + 3*x3 同余 2
    // 2*x1 + 4*x2 + 6*x3 同余 4
    // 0*x1 + 3*x2 + 4*x3 同余 2
    mat[1][1] = 1; mat[1][2] = 2; mat[1][3] = 3; mat[1][4] = 2;
    mat[2][1] = 2; mat[2][2] = 4; mat[2][3] = 6; mat[2][4] = 4;
    mat[3][1] = 0; mat[3][2] = 3; mat[3][3] = 4; mat[3][4] = 2;
    gauss(3);
    print(3);

    cout << "注意下面这个多解的例子" << endl;
    // 1*x1 + 1*x2 + 1*x3 同余 3
    // 2*x1 + 1*x2 + 1*x3 同余 5
    // 0*x1 + 3*x2 + 3*x3 同余 3
    mat[1][1] = 1; mat[1][2] = 1; mat[1][3] = 1; mat[1][4] = 3;
    mat[2][1] = 2; mat[2][2] = 1; mat[2][3] = 1; mat[2][4] = 5;
    mat[3][1] = 0; mat[3][2] = 3; mat[3][3] = 3; mat[3][4] = 3;
    gauss(3);
    print(3);
    cout << "最后一个例子里" << endl;
    cout << "主元x1，不受其他自由元影响，值可以直接确定" << endl;
    cout << "只有自由元x3确定了值，主元x2的值才能确定。" << endl;
    cout << "本节课提供的模版，对于能求出的主元可以得到正确结果" << endl;
    cout << "对于不能求出的主元，该模版也能给出，主元和自由元的正确关系" << endl;
    cout << "有些题目需要这种多解情况下，主元和自由元之间的正确关系" << endl;
    cout << "绝大多数模版和讲解都没有考虑这个，但值得引起重视" << endl;
    cout << "如果有些题目不需要这种正确关系" << endl;
    cout << "那么逻辑可以化简，让常数时间更快，比如本节课的题目1" << endl;
    return 0;
}
