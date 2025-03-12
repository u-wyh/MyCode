// 串联所有单词的子串
// 给定一个字符串s和一个字符串数组words
// words中所有字符串长度相同
// s中的串联子串是指一个包含 words中所有字符串以任意顺序排列连接起来的子串
// 例如words = { "ab","cd","ef" }
// 那么"abcdef"、"abefcd"、"cdabef"、"cdefab"、"efabcd"、"efcdab"都是串联子串。
// "acdbef"不是串联子串，因为他不是任何words排列的连接
// 返回所有串联子串在s中的开始索引
// 你可以以任意顺序返回答案
// 测试链接 : https://leetcode.cn/problems/substring-with-concatenation-of-all-words/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <cmath>

using namespace std;

const int MAXN = 10001;
const int BASE = 499;
long long power[MAXN];
long long hash_val[MAXN];

void build(const string& str) {
    power[0] = 1;
    for (int j = 1; j < MAXN; ++j) {
        power[j] = power[j - 1] * BASE;
    }
    hash_val[0] = str[0] - 'a' + 1;
    for (int j = 1; j < str.length(); ++j) {
        hash_val[j] = hash_val[j - 1] * BASE + str[j] - 'a' + 1;
    }
}

// 范围是s[l,r)，左闭右开
long long getHash(int l, int r) {
    long long ans = hash_val[r - 1];
    if (l > 0) {
        ans -= hash_val[l - 1] * power[r - l];
    }
    return ans;
}

// 计算一个字符串的哈希值
long long hashString(const string& str) {
    if (str.empty()) {
        return 0;
    }
    int n = str.length();
    long long ans = str[0] - 'a' + 1;
    for (int j = 1; j < n; ++j) {
        ans = ans * BASE + str[j] - 'a' + 1;
    }
    return ans;
}

vector<int> findSubstring(const string& s, const vector<string>& words) {
    vector<int> ans;
    if (s.empty() || words.empty()) {
        return ans;
    }
    // words的词频表
    unordered_map<long long, int> map;
    for (const string& key : words) {
        long long v = hashString(key);
        map[v]++;
    }
    build(s);
    int n = s.length();
    int wordLen = words[0].length();
    int wordNum = words.size();
    int allLen = wordLen * wordNum;
    // 窗口的词频表
    unordered_map<long long, int> window;
    for (int init = 0; init < wordLen && init + allLen <= n; ++init) { // 同余分组
        // init是当前组的首个开头
        int debt = wordNum;
        // 建立起窗口
        for (int l = init, r = init + wordLen, part = 0; part < wordNum; l += wordLen, r += wordLen, ++part) {
            long long cur = getHash(l, r);
            window[cur]++;
            if (window[cur] <= map[cur]) {
                debt--;
            }
        }
        if (debt == 0) {
            ans.push_back(init);
        }
        // 接下来窗口进一个、出一个
        for (int l1 = init, r1 = init + wordLen, l2 = init + allLen,
             r2 = init + allLen + wordLen; r2 <= n; l1 += wordLen, r1 += wordLen, l2 += wordLen, r2 += wordLen) {
            long long out = getHash(l1, r1);
            long long in = getHash(l2, r2);
            window[out]--;
            if (window[out] < map[out]) {
                debt++;
            }
            window[in]++;
            if (window[in] <= map[in]) {
                debt--;
            }
            if (debt == 0) {
                ans.push_back(r1);
            }
        }
        window.clear();
    }
    return ans;
}

int main() {
    string s ;
    int n;
    cin>>s>>n;
    vector<string> words;
    for(int i=0;i<n;i++){
        string str;
        cin >>str;
        words.push_back(str);
    }
    vector<int> result = findSubstring(s, words);
    for (int index : result) {
        cout << index << " ";
    }
    cout << endl;
    return 0;
}
// 如果s的长度为n，words里所有单词的总长度为m
// 时间复杂度O(n + m)，最优解的时间复杂度与单词个数、单词长度是无关的
// 所有题解都没有做到这个复杂度的
// 虽然这个做法打败比例没有到100%，但那是因为测试数据量不够大
// 所以最优解的时间复杂度优势没有体现出来
// 这个方法绝对是最优解，只有同余分组 + 字符串哈希，时间复杂度才能到最优
/*
barfoothefoobarman
2
foo
bar

barfoofoobarthefoobarman
3
bar
foo
the

wordgoodgoodgoodbestword
4
word
best
good
word
*/
