// 在二维字符数组中搜索可能的单词
// 给定一个 m x n 二维字符网格 board 和一个单词（字符串）列表 words
// 返回所有二维网格上的单词。单词必须按照字母顺序，通过 相邻的单元格 内的字母构成
// 其中“相邻”单元格是那些水平相邻或垂直相邻的单元格
// 同一个单元格内的字母在一个单词中不允许被重复使用
// 1 <= m, n <= 12
// 1 <= words.length <= 3 * 10^4
// 1 <= words[i].length <= 10
// 测试链接 : https://leetcode.cn/problems/word-search-ii/

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 10001;

int tree[MAXN][26];
int pass[MAXN];
string en[MAXN];
int cnt=1;
char board[13][13];
string words[30004];
int n,m,k;
vector<string>ans;

// i,j : 此时来到的格子位置，i行、j列
// t : 前缀树的编号
// ans : 收集到了哪些字符串，都放入ans
int dfs(int i, int j, int t) {
    // 越界 或者 走了回头路，直接返回0
    if (i < 0 || i == n || j < 0 || j == m || board[i][j] == 0) {
        return 0;
    }
    // 不越界 且 不是回头路
    // 用tmp记录当前字符
    char tmp = board[i][j];
    // 路的编号
    // a -> 0
    // b -> 1
    // ...
    // z -> 25
    int road = tmp - 'a';
    t = tree[t][road];//表示下一条路怎么走
    if (pass[t] == 0) {
        //表示没有走的必要了
        return 0;
    }
    // i，j位置有必要来
    // fix ：从当前i，j位置出发，一共收集到了几个字符串
    int fix = 0;
    if (en[t] != "") {
        //说明这是一个单词的结尾
        fix++;
        ans.push_back(en[t]);
        en[t] = "";
    }
    // 把i，j位置的字符，改成0，后续的过程，是不可以再来到i，j位置的！
    board[i][j] = 0;
    fix += dfs(i - 1, j, t);
    fix += dfs(i + 1, j, t);
    fix += dfs(i, j - 1, t);
    fix += dfs(i, j + 1, t);
    //向下递归
    pass[t] -= fix;
    //fix的增加要么是在这个位置实现的  要么是走的下面位置上实现的  但不管怎么实现的  当前位置一定是有贡献的
    //那么当前位置要减去fix
    //并且这个一旦减少就不会复原  即不会有重复的输入到ans中去
    board[i][j] = tmp;//复原
    return fix;
}

void build() {
    cnt = 1;
    for (string word : words) {
        int cur = 1;
        pass[cur]++;
        for (int i = 0, path; i < word.length(); i++) {
            path = word[i] - 'a';
            if (tree[cur][path] == 0) {
                tree[cur][path] = ++cnt;
            }
            cur = tree[cur][path];
            pass[cur]++;
        }
        en[cur] = word;//结尾位置储存的是整个单词  为了方便记录答案
        //en  pass数组也是用于剪枝的  每找到一个单词  pass  en会减少
        //从而后面就不用搜索了
    }
}

int main()
{
    cin>>n>>m>>k;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>board[i][j];
        }
    }
    //输入网格字符信息
    for(int i=1;i<=k;i++){
        cin>>words[i];
    }
    //输入要查询的单词信息
    build();
    //将所有单词建树
    //根据建立的前缀树进行剪枝
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            dfs(i, j, 1);
            //从任意起点搜索
        }
    }
    for (const string& word : ans) {
        cout << word << endl;
    }
    return 0;
}
