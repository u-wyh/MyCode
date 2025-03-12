// 最大为N的数字组合
// 给定一个按 非递减顺序 排列的数字数组 digits
// 已知digits一定不包含'0'，可能包含'1' ~ '9'，且无重复字符
// 你可以用任意次数 digits[i] 来写的数字
// 例如，如果 digits = ['1','3','5']
// 我们可以写数字，如 '13', '551', 和 '1351315'
// 返回 可以生成的小于或等于给定整数 n 的正整数的个数
// 测试链接 : https://leetcode.cn/problems/numbers-at-most-n-given-digit-set/
#include<bits/stdc++.h>
using namespace std;

int n,m;//表示最大不能大于n  一共有m个数位供选择
int digits[10];//表示可以使用的数字

// offset是辅助变量，完全由len决定，只是为了方便提取n中某一位数字，不是关键变量
// 还剩下len位没有决定
// 如果之前的位已经确定比n小，那么free == 1，表示接下的数字可以自由选择
// 如果之前的位和n一样，那么free == 0，表示接下的数字不能大于num当前位的数字
// 如果之前的位没有使用过数字，fix == 0
// 如果之前的位已经使用过数字，fix == 1
// 返回最终<=num的可能性有多少种
int f1(int offset, int len, int free, int fix) {
	if (len == 0) {
		return fix == 1 ? 1 : 0;
	}
	int ans = 0;
	// num在当前位的数字
	int cur = (n / offset) % 10;
	if (fix == 0) {
		// 之前从来没有选择过数字
		// 当前依然可以不要任何数字，累加后续的可能性
		ans += f1(offset / 10, len - 1, 1, 0);
	}
	if (free == 0) {
		// 不能自由选择的情况
		for (int i : digits) {
			if (i < cur) {
				ans += f1(offset / 10, len - 1, 1, 1);
			} else if (i == cur) {
				ans += f1(offset / 10, len - 1, 0, 1);
			} else {
				// i > cur
				break;
			}
		}
	} else {
		// 可以自由选择的情况
		ans += m * f1( offset / 10, len - 1, 1, 1);
	}
	return ans;
}

int main()
{
    cin>>n>>m;
    int tmp = n/ 10;
    int len = 1;//用于测定n的长度
    int offset = 1;//这个实际上是10的len-1次方
    while (tmp > 0) {
        tmp /= 10;
        len++;
        offset *= 10;
    }
    for(int i=0;i<m;i++){
        cin>>digits[i];
    }
    cout<<f1(offset, len, 0, 0)<<endl;
    return 0;
}
