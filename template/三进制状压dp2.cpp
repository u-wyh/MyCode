// 用三种不同颜色为网格涂色
// 给你两个整数m和n，表示m*n的网格，其中每个单元格最开始是白色
// 请你用红、绿、蓝三种颜色为每个单元格涂色，所有单元格都需要被涂色
// 要求相邻单元格的颜色一定要不同
// 返回网格涂色的方法数，答案对 1000000007 取模
// 1 <= m <= 5
// 1 <= n <= 1000
// 测试链接 : https://leetcode.cn/problems/painting-a-grid-with-three-different-colors/
// 有兴趣的同学可以自己改一下空间压缩的版本
#include<iostream>
#include<cmath>
using namespace std;
const int MAXN = 1001;
const int MAXM = 5;
const int MAXS = pow(3, MAXM);
const int MOD = 1000000007;

int n,m;//表示有n行m列
int maxs;
int first[MAXS];
int size;
int dp[MAXN][MAXM][MAXS];

// s表示当前状态，按照3进制来理解
// 当前来到第j号格，3的j次方是bit
// 返回s第j号格的值
int get(int s, int bit) {
	return (s / bit) % 3;
}

// s表示当前状态，按照3进制来理解
// 当前来到第j号格，3的j次方是bit
// 把s第j号格的值设置成v，返回新状态
int set(int s, int bit, int v) {
	return s - get(s, bit) * bit + v * bit;
}

// 取得所有第一行的有效状态   因为第一行没有上方  所以特别处理
void dfs(int j, int s, int bit) {
    if (j == m) {
        //表示一个有效的第一行状态
        first[size++] = s;
    } else {
        int left = j == 0 ? -1 : get(s, bit / 3);
        if (left != 0) {
            dfs(j + 1, set(s, bit, 0), bit * 3);
        }
        if (left != 1) {
            dfs(j + 1, set(s, bit, 1), bit * 3);
        }
        if (left != 2) {
            dfs(j + 1, set(s, bit, 2), bit * 3);
        }
    }
}

int f(int i,int j,int s,int bit){
    if(i==n){
        return 1;
    }
    if(j==m){
        return f(i+1,0,s,1);
    }
    if(dp[i][j][s]!=-1){
        return dp[i][j][s];
    }
    int left=j==0?-1:get(s,bit/3);
    int up=get(s,bit);
    int ans = 0;
    if (up != 0 && left != 0) {
        ans = (ans + f(i, j + 1, set(s, bit, 0), bit * 3)) % MOD;
    }
    if (up != 1 && left != 1) {
        ans = (ans + f(i, j + 1, set(s, bit, 1), bit * 3)) % MOD;
    }
    if (up != 2 && left != 2) {
        ans = (ans + f(i, j + 1, set(s, bit, 2), bit * 3)) % MOD;
    }
    dp[i][j][s] = ans;
    return ans;
}

int main()
{
    cin>>n>>m;
    if(m>n){
        n^=m;
        m^=n;
        n^=m;
    }
    maxs=pow(3,m);
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            for(int s=0;s<maxs;s++){
                dp[i][j][s]=-1;
            }
        }
    }
    dfs(0,0,1);//完成第一行所有有效状态的统计
    int ans=0;
    for (int i = 0; i < size; i++) {
        ans = (ans + f(1, 0, first[i], 1)) % MOD;
    }
    cout<<ans<<endl;
    return 0;
}
