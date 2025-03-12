// 统计有多少个不同的字符串
// 测试链接 : https://www.luogu.com.cn/problem/P3370
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法
// 提交以下的code，提交时请把类名改成"Main"，可以直接通过
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 10001;
const int BASE = 499;

vector<long long> nums(MAXN);
int n;

int v(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0' + 1;
    } else if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 11;
    } else {
        return c - 'a' + 37;
    }
}

long long value(const string& s) {
    long long ans = 0;
    for (size_t i = 0; i < s.length(); i++) {
        ans = ans * BASE + v(s[i]);
    }
    return ans;
}

//long long value(const string& s) {
//    long long ans = v(s[0]);//这里一开始可以设置为0  下面从0开始
//    for (size_t i = 1; i < s.length(); i++) {
//        ans = ans * BASE + v(s[i]);
//    }
//    return ans;
//}

// 数字 + 大写 + 小写
// '0' -> 1
// '1' -> 2
// ...
// '9' -> 10
// 'A' -> 11
// 'B' -> 12
// ...
// 'Z' -> 36
// 'a' -> 37
// ...
// 'z' -> 62

int cnt() {
    sort(nums.begin(), nums.begin() + n);
    int ans = 1;
    for (int i = 1; i < n; i++) {
        if (nums[i] != nums[i - 1]) {
            ans++;
        }
    }
    return ans;
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        string line;
        cin >> line;
        nums[i] = value(line);
    }
    cout << cnt() << endl;
    return 0;
}
