// 彩灯
// 一共有n个灯泡，开始都是不亮的状态，有m个开关
// 每个开关能改变若干灯泡的状态，改变是指，亮变不亮、不亮变亮
// 比如n=5，某个开关为XXOOO，表示这个开关只能改变后3个灯泡的状态
// 可以随意使用开关，返回有多少种亮灯的组合，全不亮也算一种组合
// 答案可能很大，对 2008 取模
// 1 <= n <= 50
// 1 <= m <= 50
// 测试链接 : https://www.luogu.com.cn/problem/P3857
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有测试用例
#include<bits/stdc++.h>
using namespace std;
const int MOD = 2008;
const int MAXN = 51;

long long arr[MAXN];
long long basis[MAXN];
int n,m;
string s;

bool insert(long num) {
    for (int i = n; i >= 0; i--) {
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
// 计算线性基的大小
int compute() {
	int size = 0;
	for (int i = 1; i <= m; i++) {
        if (insert(arr[i])) {
			size++;
		}
	}
	return size;
}

int main()
{
    cin>>n>>m;
    n--;
    for (int i = 1; i <= m; i++) {
        cin>>s;
        long num = 0;
        for (int j = 0; j <= n; j++) {
            if (s[j] == 'O') {
                num |= 1LL << j;
            }
        }
        arr[i] = num;
    }
    int size = compute();
    //统计出线性基的个数
    //因为线性基里的元素不会产生异或为0的结果   那么每个都有要或不要的选择方式
    //所以有2的size次方
    cout<<((1LL << size) % MOD);
    return 0;
}
