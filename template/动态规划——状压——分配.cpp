// 分配重复整数
// 给你一个长度为n的整数数组nums，这个数组中至多有50个不同的值
// 同时你有m个顾客的订单quantity，其中整数quantity[i]是第i位顾客订单的数目
// 请你判断是否能将nums中的整数分配给这些顾客，且满足：
// 第i位顾客恰好有quantity[i]个整数、第i位顾客拿到的整数都是相同的
// 每位顾客都要满足上述两个要求，返回是否能都满足
// 测试链接 : https://leetcode.cn/problems/distribute-repeating-integers/

#include<bits/stdc++.h>
using namespace std;

int n,m;
int nums[100005],quanity[15];
int dp[1<<11][55];

// 当前来到的数字，编号index，个数cnt[index]
// status : 订单状态，1还需要去满足，0已经满足过了
bool f(int* cnt, int* sum, int status, int index) {
	if (status == 0) {
		return true;
	}
	// status != 0
	if (index == n) {
		return false;
	}
	if (dp[status][index] != 0) {
		return dp[status][index] == 1;
	}
	bool ans = false;
	int k = cnt[index];
	// 这是整个实现最核心的枚举
	// j枚举了status的所有子集状态
	// 建议记住
	for (int j = status; j > 0; j = (j - 1) & status) {
		if (sum[j] <= k && f(cnt, sum, status ^ j, index + 1)) {
			ans = true;
			break;
		}
	}
	if (!ans) {
		ans = f(cnt, sum, status, index + 1);
	}
	dp[status][index] = ans ? 1 : -1;
	return ans;
}

int main()
{
    cin>>n>>m;
    for(int i=0;i<n;i++){
        cin>>nums[i];
    }
    sort(nums,nums+n);
    for(int i=0;i<m;i++){
        cin>>quanity[i];
    }
    int cunt = 1;
    for (int i = 1; i < n; i++) {
        if (nums[i - 1] != nums[i]) {
            cunt++;
        }
    }
    int* cnt = new int[cunt];
    int c = 1;
    for (int i = 1, j = 0; i < n; i++) {
        if (nums[i - 1] != nums[i]) {
            cnt[j++] = c;
            c = 1;
        } else {
            c++;
        }
    }
    cnt[cunt - 1] = c;
    n=cunt;
//    for(int i=0;i<n;i++){
//        cout<<cnt[i]<<' ';
//    }
//    cout<<endl;
    //cout<<n<<endl;
    int* sum = new int[1 << m];
    for(int i=0;i<(1<<m);i++){
        sum[i]=0;
    }
    // 下面这个枚举是生成quantity中的每个子集，所需要数字的个数
    for (int i = 0, v, h; i < m; i++) {
        v = quanity[i];
        h = 1 << i;
        for (int j = 0; j < h; j++) {
            sum[h | j] = sum[j] + v;
        }
    }
//    for(int i=0;i<(1<<m);i++){
//        cout<<sum[i]<<' ';
//    }
//    cout<<endl;
    cout<<f(cnt, sum, (1 << m) - 1, 0);
    delete[] sum;
    delete[] cnt;
    return 0;
}
