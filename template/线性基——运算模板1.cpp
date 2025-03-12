// 最大异或和
// 给定一个长度为n的数组arr，arr中都是long类型的非负数，可能有重复值
// 在这些数中选取任意个，使得异或和最大，返回最大的异或和
// 1 <= n <= 50
// 0 <= arr[i] <= 2^50
// 测试链接 : https://www.luogu.com.cn/problem/P3812
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有测试用例
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 51;
const int BIT = 50;

long arr[MAXN];
long basis[BIT + 1];
int n;

// 线性基里插入num，如果线性基增加了返回true，否则返回false
bool insert(long num) {
	for (int i = BIT; i >= 0; i--) {
		if (num >> i == 1) {
			if (basis[i] == 0) {
				basis[i] = num;
				return true;
			}
			num ^= basis[i];
		}
	}
	return false;
}

// 普通消元
// 计算最大异或和
long compute() {
	for (int i = 1; i <= n; i++) {
		insert(arr[i]);
	}
	long ans = 0;
	for (int i = BIT; i >= 0; i--) {
		ans = max(ans, ans ^ basis[i]);
	}
	//如果可以使答案增加  那么就异或上这个数字
	return ans;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    cout<<compute()<<endl;
    return 0;
}
