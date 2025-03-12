// 完全没有重复的数字个数
// 给定正整数n，返回在[1, n]范围内每一位都互不相同的正整数个数
// 测试链接 : https://leetcode.cn/problems/count-special-integers/
#include<bits/stdc++.h>
using namespace std;

int n;
int cnt[10];//表示还有k位可以随便填的话，最多可以填多少种

// 之前已经确定了和num一样的前缀，且确定的部分一定不为空
// 还有len位没有确定
// 哪些数字已经选了，哪些数字没有选，用status表示
// 返回<=num且每一位数字都不一样的正整数有多少个
int f(int len, int offset, int status) {
	if (len == 0) {
		// num自己
		return 1;
	}
	int ans = 0;
	// first是num当前位的数字
	int first = (n / offset) % 10;
	for (int cur = 0; cur < first; cur++) {
		if ((status & (1 << cur)) == 0) {
			ans += cnt[len - 1];//表示目前这个位置上的数字比实际小，那么接下来的位置可以随便填数字了
		}
	}
	if ((status & (1 << first)) == 0) {
		ans += f(len - 1, offset / 10, status | (1 << first));
		//表示这个位置上的数字就是该数
	}
	return ans;
}

int main()
{
    cin>>n;
    int tmp = n/ 10;
    int len = 1;//用于测定n的长度
    int offset = 1;//这个实际上是10的len-1次方
    while (tmp > 0) {
        len++;
        offset *= 10;
        tmp /= 10;
    }
    // cnt[i] :
    // 一共长度为len，还剩i位没有确定，确定的前缀为len-i位，且确定的前缀不为空
    // 0~9一共10个数字，没有选择的数字剩下10-(len-i)个
    // 那么在后续的i位上，有多少种排列
    // 比如：len = 4
    // cnt[4]不计算
    // cnt[3] = 9 * 8 * 7
    // cnt[2] = 8 * 7
    // cnt[1] = 7
    // cnt[0] = 1，表示前缀已确定，后续也没有了，那么就是1种排列，就是前缀的状况,可以认为是本身
    // 再比如：len = 6
    // cnt[6]不计算
    // cnt[5] = 9 * 8 * 7 * 6 * 5
    // cnt[4] = 8 * 7 * 6 * 5
    // cnt[3] = 7 * 6 * 5
    // cnt[2] = 6 * 5
    // cnt[1] = 5
    // cnt[0] = 1，表示前缀已确定，后续也没有了，那么就是1种排列，就是前缀的状况
    // 下面for循环就是求解cnt的代码
    cnt[0] = 1;
    for (int i = 1, k = 10 - len + 1; i < len; i++, k++) {
        cnt[i] = cnt[i - 1] * k;
    }
    int ans = 0;
    if (len >= 2) {
        // 如果n的位数是len位，先计算位数少于len的数中，每一位都互不相同的正整数个数，并累加
        // 所有1位数中，每一位都互不相同的正整数个数 = 9
        // 所有2位数中，每一位都互不相同的正整数个数 = 9 * 9
        // 所有3位数中，每一位都互不相同的正整数个数 = 9 * 9 * 8
        // 所有4位数中，每一位都互不相同的正整数个数 = 9 * 9 * 8 * 7
        // ...比len少的位数都累加...
        ans = 9;
        for (int i = 2, a = 9, b = 9; i < len; i++, b--) {
            a *= b;
            ans += a;
        }
        //此时，通过这个过程，所有的数位不足情况都被加上去了
    }
    // 如果n的位数是len位，已经计算了位数少于len个的情况
    // 下面计算一定有len位的数字中，<=n且每一位都互不相同的正整数个数
    int first = n / offset;
    // 小于num最高位数字的情况
    ans += (first - 1) * cnt[len - 1];
    // 后续累加上，等于num最高位数字的情况
    ans += f(len - 1,offset / 10, 1 << first);
    cout<<ans;
    return 0;
}
