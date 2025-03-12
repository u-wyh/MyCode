// 除法求值
// 所有变量都用字符串表示，并且给定若干组等式
// 比如等式
// ["ab", "ef"] = 8，代表ab / ef = 8
// ["ct", "ef"] = 2，代表ct / ef = 2
// 所有等式都是正确的并且可以进行推断，给定所有等式之后，会给你若干条查询
// 比如查询，["ab", "ct"]，根据上面的等式推断，ab / ct = 4
// 如果某条查询中的变量，从来没在等式中出现过，认为答案是-1.0
// 如果某条查询的答案根本推断不出来，认为答案是-1.0
// 返回所有查询的答案
// 测试链接 : https://leetcode.cn/problems/evaluate-division/
#include <bits/stdc++.h>

using namespace std;

unordered_map<string, string> father;
unordered_map<string, double> dist;

void prepare(const vector<vector<string>>& equations) {
    father.clear();
    dist.clear();
    for (const auto& list : equations) {
        for (const auto& key : list) {
            father[key] = key;
            dist[key] = 1.0;
        }
    }
}

string find(const string& x) {
    //表示这个单词从来没有出现过
    if (father.find(x) == father.end()) {
        return "";
    }
    string tmp, fa = x;
    if (x != father[x]) {
        tmp = father[x];
        fa = find(tmp);
        dist[x] *= dist[tmp];
        father[x] = fa;
    }
    return fa;
}

void union_sets(const string& l, const string& r, double v) {
    string lf = find(l), rf = find(r);
    if (lf != rf) {
        father[lf] = rf;
        dist[lf] = dist[r] / dist[l] * v;
    }
}

double query(const string& l, const string& r) {
    string lf = find(l), rf = find(r);
    if (lf.empty() || rf.empty() || lf != rf) {
        return -1.0;
    }
    return dist[l] / dist[r];
}

vector<double> calcEquation(const vector<vector<string>>& equations, const vector<double>& values, const vector<vector<string>>& queries) {
    prepare(equations);
    for (size_t i = 0; i < values.size(); ++i) {
        union_sets(equations[i][0], equations[i][1], values[i]);
    }
    vector<double> ans;
    for (const auto& query : queries) {
        ans.push_back(::query(query[0], query[1]));
    }
    return ans;
}

int main() {
    // Example usage:
    vector<vector<string>> equations = {{"a","b"},{"b","c"},{"bc","cd"}};
    vector<double> values = {1.5,2.5,5.0};
    vector<vector<string>> queries = {{"a","c"},{"c","b"},{"bc","cd"},{"cd","bc"}};

    vector<double> results = calcEquation(equations, values, queries);

    for (double result : results) {
        printf("%.5lf ",result);
    }

    return 0;
}
