// 统计重复个数
// 如果字符串x删除一些字符，可以得到字符串y，那么就说y可以从x中获得
// 给定s1和a，代表s1拼接a次，记为字符串x
// 给定s2和b，代表s2拼接b次，记为字符串y
// 现在把y拼接m次之后，得到的字符串依然可能从x中获得，返回尽可能大的m
// s1、s2只由小写字母组成
// 1 <= s1长度、s2长度 <= 100
// 1 <= a、b <= 10^6
// 测试链接 : https://leetcode.cn/problems/count-the-repetitions/
#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include <cmath>

using namespace std;

bool find(const string& str1, int n, vector<vector<int>>& next, const string& str2) {
    vector<int> right(26, -1);//先全部初始化为-1
    for (int i = n - 1; i >= 0; --i) {
        //这里是为了避免有的字母存在但是还没有出现
        right[str1[i] - 'a'] = i + n;
    }
    for (int i = n - 1; i >= 0; --i) {
        right[str1[i] - 'a'] = i;
        for (int j = 0; j < 26; ++j) {
            next[i][j] = (right[j] != -1) ? (right[j] - i + 1) : -1;
        }
    }
    for (char c : str2) {
        //判断s2的所有字符是不是都出现过
        //如果没有的话  那么一定是false
        if (next[0][c - 'a'] == -1) {
            return false;
        }
    }
    return true;
}

int getMaxRepetitions(const string& str1, int a, const string& str2, int b) {
    const char* s1 = str1.c_str();
    const char* s2 = str2.c_str();
    int n = str1.length();
    vector<vector<int>> next(n, vector<int>(26, 0));

    if (!find(str1, n, next, str2)) {
        return 0;
    }

    vector<vector<long long>> st(n, vector<long long>(30, 0));
    for (int i = 0, cur, len; i < n; ++i) {
        cur = i;
        len = 0;
        for (char c : str2) {
            len += next[cur][c - 'a'];
            cur = (cur + next[cur][c - 'a']) % n;
        }
        st[i][0] = len;
    }

    for (int p = 1; p <= 29; ++p) {
        for (int i = 0; i < n; ++i) {
            st[i][p] = st[i][p - 1] + st[(st[i][p - 1] + i) % n][p - 1];
        }
    }

    long long ans = 0;
    for (int p = 29, start = 0; p >= 0; --p) {
        if (st[start % n][p] + start <= static_cast<long long>(n) * a) {
            ans += 1LL << p;
            start += st[start % n][p];
        }
    }

    return static_cast<int>(ans / b);
}

int main() {
    string str1 ,str2;
    int a ,b;
    cin>>str1>>a>>str2>>b;

    cout << "Max repetitions: " << getMaxRepetitions(str1, a, str2, b) << endl;

    return 0;
}
