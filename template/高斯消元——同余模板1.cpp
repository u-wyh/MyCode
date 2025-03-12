// 格子全变成0的操作方案
// 有一个n*m的二维网格，给定每个网格的初始值，一定是0、1、2中的一个
// 如果某个网格获得了一些数值加成，也会用%3的方式变成0、1、2中的一个
// 比如有个网格一开始值是1，获得4的加成之后，值为(1+4)%3 = 2
// 有一个神奇的刷子，一旦在某个网格处刷一下，该网格会获得2的加成
// 并且该网格上、下、左、右的格子，都会获得1的加成
// 最终目标是所有网格都变成0，题目保证一定有解，但不保证唯一解
// 得到哪一种方案都可以，打印一共需要刷几下，并且把操作方案打印出来
// 1 <= n、m <= 30
// 测试链接 : https://acm.hdu.edu.cn/showproblem.php?pid=5755
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有测试用例
#include<iostream>
using namespace std;
const int MOD = 3;
const int MAXS = 1001;

int mat[MAXS][MAXS];
int dir[5] = { 0, -1, 0, 1, 0 };
int n, m, s;
int inv[MOD];

void compute_inv() {
    inv[1] = 1;
    for (int i = 2; i < MOD; i++) {
        inv[i] = (int) (MOD - (long) inv[MOD % i] * (MOD / i) % MOD);
    }
}

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

void swap(int a, int b) {
    int tmp[MAXS + 1];
    //cout<<"swap"<<endl;
    for (int j = 0; j <= MAXS; j++) {
        tmp[j] = mat[a][j];
        mat[a][j] = mat[b][j];
        mat[b][j] = tmp[j];
    }
}

void prepare() {
    for (int i = 1; i <= s; i++) {
        for (int j = 1; j <= s + 1; j++) {
            mat[i][j] = 0;
        }
    }
    int cur, row, col;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cur = i * m + j + 1;
            mat[cur][cur] = 2;
            for (int d = 0; d <= 3; d++) {
                row = i + dir[d];
                col = j + dir[d + 1];
                if (row >= 0 && row < n && col >= 0 && col < m) {
                    mat[cur][row * m + col + 1] = 1;
                }
            }
        }
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
    // 由于本题的特殊性，不需要去管任何自由元的影响
    // 就当自由元不操作，直接求主元的操作次数即可
    for (int i = 1; i <= n; i++) {
        if (mat[i][i] != 0) {
            mat[i][n + 1] = (mat[i][n + 1] * inv[mat[i][i]]) % MOD;
        }
    }
}

int main()
{
    compute_inv();
    int test;
    cin>>test;
    while(test--){
        cin>>n>>m;
        s = n * m;
        prepare();
        for (int i = 1,k; i <= s; i++) {
            cin>>k;
            mat[i][s + 1] = (3 - k) % MOD;
        }
        gauss(s);
        int ans = 0;
        for (int i = 1; i <= s; i++) {
            ans += mat[i][s + 1];
        }
        cout<<ans<<endl;
        for (int i = 1, id = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++, id++) {
                while (mat[id][s + 1]-- > 0) {
                    cout<<i << " " << j<<endl;
                }
            }
        }
    }
    return 0;
}
