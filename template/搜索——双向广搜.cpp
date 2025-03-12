// 单词接龙
// 字典 wordList 中从单词 beginWord 和 endWord 的 转换序列
// 是一个按下述规格形成的序列 beginWord -> s1 -> s2 -> ... -> sk ：
// 每一对相邻的单词只差一个字母。
// 对于 1 <= i <= k 时，每个 si 都在 wordList 中
// 注意， beginWord 不需要在 wordList 中。sk == endWord
// 给你两个单词 beginWord 和 endWord 和一个字典 wordList
// 返回 从 beginWord 到 endWord 的 最短转换序列 中的 单词数目
// 如果不存在这样的转换序列，返回 0 。
// 测试链接 : https://leetcode.cn/problems/word-ladder/

#include <iostream>
#include <unordered_set>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int ladderLength(string begin, string end, vector<string>& wordList) {
    // 总词表
    unordered_set<string> dict(wordList.begin(), wordList.end());
    if (dict.find(end) == dict.end()) {
        return 0;
    }

    // 数量小的一侧
    unordered_set<string> smallLevel;
    // 数量大的一侧
    unordered_set<string> bigLevel;
    // 由数量小的一侧，所扩展出的下一层列表
    unordered_set<string> nextLevel;

    smallLevel.insert(begin);
    bigLevel.insert(end);

    for (int len = 2; !smallLevel.empty(); ++len) {
        for (const auto& w : smallLevel) {
            // 从小侧扩展
            string word = w;
            for (int j = 0; j < word.size(); ++j) {
                // 每一位字符都试
                char old = word[j];
                for (char change = 'a'; change <= 'z'; ++change) {
                    // 每一位字符都从a到z换一遍
                    if (change != old) {
                        word[j] = change;
                        string next = word;
                        if (bigLevel.find(next) != bigLevel.end()) {
                            return len;
                        }
                        if (dict.find(next) != dict.end()) {
                            dict.erase(next);
                            nextLevel.insert(next);
                        }
                    }
                }
                word[j] = old;
            }
        }

        if (nextLevel.size() <= bigLevel.size()) {
            swap(smallLevel, nextLevel);
            nextLevel.clear();
        } else {
            swap(smallLevel, bigLevel);
            swap(bigLevel, nextLevel);
            nextLevel.clear();
        }
    }

    return 0;
}

int main() {
    string begin = "hit";
    string end = "cog";
    vector<string> wordList = {"hot", "dot", "dog", "lot", "log"};

    int result = ladderLength(begin, end, wordList);
    cout << "Minimum number of steps: " << result << endl;

    return 0;
}
