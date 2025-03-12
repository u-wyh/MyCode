// 统计整数数目
// 给你两个数字字符串 num1 和 num2 ，以及两个整数max_sum和min_sum
// 如果一个整数 x 满足以下条件，我们称它是一个好整数
// num1 <= x <= num2
// min_sum <= digit_sum(x) <= max_sum
// 请你返回好整数的数目
// 答案可能很大，答案对 1000000007 取模
// 注意，digit_sum(x)表示x各位数字之和
// 测试链接 : https://leetcode.cn/problems/count-of-integers/
#include<bits/stdc++.h>
using namespace std;
const int MOD = 1e9+7;

string s1,s2;//以字符串的形式输入的最大最小值
int minsum,maxsum;//要求的数位和值
int dp[25][400][2];//dp[i][j][k]表示在第i位，目前和是j，自由状态为k

int len;
char str[30];//这两个全局变量用于函数之中，在主函数中会被更新

void build() {
	for (int i = 0; i < len; i++) {
		for (int j = 0; j <= maxsum; j++) {
			dp[i][j][0] = -1;
			dp[i][j][1] = -1;
		}
	}
}

// 注意：
// 数字，char[] num
// 数字长度，int len
// 累加和最小要求，int min
// 累加和最大要求，int max
// 这四个变量都是全局静态变量，所以不用带参数，直接访问即可
// 递归含义：
// 从num的高位出发，当前来到i位上
// 之前决定的数字累加和是sum
// 之前的决定已经比num小，后续可以自由选择数字，那么free == 1
// 之前的决定和num一样，后续不可以自由选择数字，那么free == 0
// 返回有多少种可能性
int f(int i, int sum, int free) {
	if (sum > maxsum) {
		return 0;
	}
	if (sum + (len - i) * 9 < minsum) {
		return 0;
	}
	if (i == len) {
		return 1;
	}
	if (dp[i][sum][free] != -1) {
		return dp[i][sum][free];
	}
	// cur : num当前位的数字
	int cur = str[i] - '0';
	int ans = 0;
	if (free == 0) {
		// 还不能自由选择
		for (int pick = 0; pick < cur; pick++) {
			ans = (ans + f(i + 1, sum + pick, 1)) % MOD;
		}
		ans = (ans + f(i + 1, sum + cur, 0)) % MOD;
	} else {
		// 可以自由选择
		for (int pick = 0; pick <= 9; pick++) {
			ans = (ans + f(i + 1, sum + pick, 1)) % MOD;
		}
	}
	dp[i][sum][free] = ans;
	return ans;
}

bool check() {
	int sum = 0;
	for (char cha : str) {
		sum += cha - '0';
	}
	return sum >= minsum && sum <= maxsum;
}

//首先，大体思路是求出0~max上的符合要求的数字减去0~min-1上的符合要求的数字
//但是，给出的数字很长，即使是long也会溢出，并且直接减1也比较麻烦
//比如最小值是100000000000000000000000000000000000  需要手动改为9
//所以我们的思路是求出0~max上的符合要求的数字减去0~min  对min特判
int main()
{
    cin>>s1>>s2>>minsum>>maxsum;

    copy(s1.begin(), s1.end(), str);
    str[s1.length()] = '\0';
    len=s1.length();
    build();
    int ans=f(0,0,0);//求出0~max上的符合要求的数字
    copy(s2.begin(), s2.end(), str);
    str[s2.length()] = '\0';
    len=s2.length();
    build();//求出0~min上的符合要求的数字
    if(check()){
        ans=(ans+1)%MOD;
    }
    cout<<ans<<endl;
    return 0;
}
