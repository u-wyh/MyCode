// ���ϵ�����ש��(չʾ��̬�滮˼·�����Ż�ö�٣������пռ�ѹ��)
// һ����ɵ�������״��ש���ڵ��һ����n�㣬��1����n��ש��ÿ��ݼ���������������
// 4 2 9 5
//  3 1 7
//   2 4
//    8
// ��Ҫ�ӵ�1�㿪ʼ�ڣ�ÿ�ڿ�һ��ש�����Ի����ֵ��Ϊ���棬��1���ש����������
// �����ڵ������ש���������ģ�����i���j��ש������Ҫȷ��i-1���(j��j+1)��ש�Ѿ����ڿ�
// ��������m��ש��������������
// 1 <= n <= 50
// 1 <= m <= 1300
// ש����ֵ <= 100
// �������� : https://www.luogu.com.cn/problem/P1437
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 51;
const int MAXM = 1301;

int grid[MAXN][MAXN];
int dp[MAXN][MAXM];
int suffix[MAXN][MAXM];
int n, m;

// Ԥ����ṹ�Ż�ö��
void prepare(int rowLimit) {
    for (int col = 0; col <= m; col++) {
        for (int row = rowLimit, suf = 0; row >= 0; row--) {
            suf = max(suf, dp[row][col]);
            suffix[row][col] = suf;
        }
    }
}

int main()
{
    cin>>n>>m;
    for (int j = 1; j <= n; j++) {
        for (int i = n; i >= j; i--) {
            cin>>grid[i][j];
        }
    }
    int ans = 0;
    for (int i = 1, cur, maxans; i <= n; i++) {
        prepare(i-1);
        // cur�ǵ�ǰ�е�����
        cur = 0;
        for (int j = 0; j <= i; j++) {
            cur += grid[i][j];
            // ���ڵ�j��ש���ܹ��ڵ�����һ��������
            // (j + 1) * j / 2��Ҳ���ǵȲ�����
            // ���kС�����ֵ�����壬��Ϊ������0
            for (int k = (j + 1) * j / 2; k <= m; k++) {
                dp[j][k] = suffix[max(0, j - 1)][k - j] + cur;
                ans = max(ans, dp[j][k]);
            }
        }
    }
    cout<<ans;
    return 0;
}
