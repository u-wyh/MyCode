#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

struct TrieNode {
    TrieNode* children[26];
    int pass;
    string word;
    TrieNode() : pass(0), word("") {
        memset(children, 0, sizeof(children));
    }
};

class Trie {
public:
    TrieNode* root;
    Trie() {
        root = new TrieNode();
    }

    void insert(const string& word) {
        TrieNode* cur = root;
        cur->pass++;
        for (char c : word) {
            int idx = c - 'a';
            if (!cur->children[idx]) {
                cur->children[idx] = new TrieNode();
            }
            cur = cur->children[idx];
            cur->pass++;
        }
        cur->word = word;
    }

    void clear() {
        clearHelper(root);
        delete root;
    }

private:
    void clearHelper(TrieNode* node) {
        if (!node) return;
        for (int i = 0; i < 26; ++i) {
            if (node->children[i]) {
                clearHelper(node->children[i]);
                delete node->children[i];
            }
        }
    }
};

class Solution {
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        Trie trie;
        for (const string& word : words) {
            trie.insert(word);
        }

        vector<string> ans;
        int rows = board.size();
        int cols = board[0].size();
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                dfs(board, visited, trie.root, i, j, ans);
            }
        }

        trie.clear();
        return ans;
    }

private:
    void dfs(vector<vector<char>>& board, vector<vector<bool>>& visited, TrieNode* node, int i, int j, vector<string>& ans) {
        if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size() || visited[i][j] || board[i][j] == 0) {
            return;
        }

        char tmp = board[i][j];
        int idx = tmp - 'a';
        TrieNode* nextNode = node->children[idx];
        if (!nextNode || nextNode->pass == 0) {
            return;
        }

        visited[i][j] = true;
        board[i][j] = 0;

        if (!nextNode->word.empty()) {
            ans.push_back(nextNode->word);
            nextNode->word = "";  // Mark as visited to avoid duplicates
            nextNode->pass--;  // Decrement pass count for the node
        }

        dfs(board, visited, nextNode, i - 1, j, ans);
        dfs(board, visited, nextNode, i + 1, j, ans);
        dfs(board, visited, nextNode, i, j - 1, ans);
        dfs(board, visited, nextNode, i, j + 1, ans);

        board[i][j] = tmp;
        visited[i][j] = false;
    }
};

int main() {
    vector<vector<char>> board = {
        {'o', 'a', 'a', 'n'},
        {'e', 't', 'a', 'e'},
        {'i', 'h', 'k', 'r'},
        {'i', 'f', 'l', 'v'}
    };

    vector<string> words = {"oath", "pea", "eat", "rain"};

    Solution sol;
    vector<string> result = sol.findWords(board, words);

    for (const string& word : result) {
        cout << word << endl;
    }

    return 0;
}
