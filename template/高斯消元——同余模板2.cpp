// 工具工厂
// 一共有n种工具，编号1~n，一共有m条记录，其中一条记录格式如下：
// 4 WED SUN 13 18 1 13
// 表示有个工人一共加工了4件工具，从某个星期三开始工作，到某个星期天结束工作
// 加工的工具依次为13号、18号、1号、13号
// 每个工人在工作期间不休息，每件工具都是串行加工的，完成一件后才开始下一件
// 每种工具制作天数是固定的，并且任何工具的制作天数最少3天、最多9天
// 但该数据丢失了，所以现在需要根据记录，推断出每种工具的制作天数
// 如果记录之间存在矛盾，打印"Inconsistent data."
// 如果记录无法确定每种工具的制作天数，打印"Multiple solutions."
// 如果记录能够确定每种工具的制作天数，打印所有结果
// 1 <= n、m <= 300
// 测试链接 : http://poj.org/problem?id=2947
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有测试用例
#include<bits/stdc++.h>
using namespace std;
const int MOD = 7;
const int MAXN = 302;

int mat[MAXN][MAXN];
int inv[MOD];
string days[7] = { "MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN" };
int n, m, s;


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
    int tmp[MAXN + 1];
    //cout<<"swap"<<endl;
    for (int j = 0; j <= MAXN; j++) {
        tmp[j] = mat[a][j];
        mat[a][j] = mat[b][j];
        mat[b][j] = tmp[j];
    }
}

int day(string str) {
    for (int i = 0; i < 7; i++) {
        if (str==days[i]) {
            return i;
        }
    }
    return -1;
}

void prepare() {
	for (int i = 1; i <= s; i++) {
		for (int j = 1; j <= s + 1; j++) {
			mat[i][j] = 0;
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
                // 在模意义下应该求逆元，(a / b) % MOD = (a * b的逆元) % MOD
                mat[i][n + 1] = (mat[i][n + 1] * inv[mat[i][i]]) % MOD;
                mat[i][i] = 1;
            }
        }
    }
}

int main()
{
    compute_inv();
    cin>>n>>m;
    while (n != 0 && m != 0) {
        s = max(n, m);
        prepare();
        for (int i = 1; i <= m; i++) {
            int k ;
            string st,et;
            cin>>k;
            cin>>st>>et;
            for (int j = 1; j <= k; j++) {
                int tool ;
                cin>>tool;
                mat[i][tool] = (mat[i][tool] + 1) % MOD;
            }
            mat[i][s + 1] = ((day(et) - day(st) + 1) % MOD + MOD) % MOD;
        }
        gauss(s);
        int sign = 1;
        for (int i = 1; i <= s; i++) {
            if (mat[i][i] == 0 && mat[i][s + 1] != 0) {
                sign = -1;
                break;
            }
            if (i <= n && mat[i][i] == 0) {
                sign = 0;
            }
        }
        if (sign == -1) {
            cout<<"Inconsistent data."<<endl<<endl;
        } else if (sign == 0) {
            cout<<"Multiple solutions."<<endl<<endl;
        } else {
            for (int i = 1; i <= n; i++) {
                if (mat[i][s + 1] < 3) {
                    mat[i][s + 1] += 7;
                }
            }
            for (int i = 1; i < n; i++) {
                cout<<mat[i][s + 1] << " ";
            }
            cout<<mat[n][s + 1]<<endl<<endl;
        }
        // 下一组n和m
        cin>>n>>m;
    }
    return 0;
}
