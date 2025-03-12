#include <iostream>
#include <vector>
#include <string>
using namespace std;

class TrieNode {
public:
    int pass;//表示有几个单词经过这个字母
    int en;//表示有几个单词在这里结尾
    vector<TrieNode*> nexts;//表示自己下面的节点

    TrieNode() : pass(0), en(0) {
        nexts.resize(26, nullptr);
    }
    //构造函数
};

class Trie1 {
private:
    TrieNode* root;//这个头结点是整棵树的入口

public:
    Trie1() {
        root = new TrieNode();
    }//构造函数

    ~Trie1() {
        deleteTrie(root);
    }//析构函数

    void deleteTrie(TrieNode* node) {
        if (node == nullptr) return;
        for (TrieNode* child : node->nexts) {
            deleteTrie(child);
        }
        delete node;
    }//删除整棵树

    void insert(const string& word) {
        TrieNode* node = root;
        node->pass++;
        for (char ch : word) {
            int path = ch - 'a';//找到这个字符对应的路径
            if (node->nexts[path] == nullptr) {
                //如果这个路径没有建立，那么直接建立一个路径
                node->nexts[path] = new TrieNode();
            }
            node = node->nexts[path];//节点转移到下一个节点
            node->pass++;
        }
        node->en++;//在最后一个节点上en++
    }//插入字符串

    void erase(const string& word) {
        if (countWordsEqualTo(word) > 0) {//判断树里面有没有这个单词
            TrieNode* node = root;
            node->pass--;
            for (char ch : word) {
                int path = ch - 'a';
                TrieNode* child = node->nexts[path];
                if (--child->pass == 0) {
                    //如果变为0  那么删除整棵子树
                    delete node->nexts[path];
                    node->nexts[path] = nullptr;
                    return;
                }
                node = child;
            }
            node->en--;
        }
    }
    // 如果之前word插入过前缀树，那么此时删掉一次
    // 如果之前word没有插入过前缀树，那么什么也不做

    int countWordsEqualTo(const string& word) {
        TrieNode* node = root;
        for (char ch : word) {
            int path = ch - 'a';
            if (node->nexts[path] == nullptr) {
                //表示没有这个路径 返回0
                return 0;
            }
            node = node->nexts[path];
        }
        return node->en;
    }
    //查询前缀树里word出现了几次

    int countWordsStartingWith(const string& pre) {
        TrieNode* node = root;
        for (char ch : pre) {
            int path = ch - 'a';
            if (node->nexts[path] == nullptr) {
                return 0;
            }
            node = node->nexts[path];
        }
        return node->pass;
    }
    //查询前缀树里以pre做前缀的单词有几个
};

int main() {
    Trie1 trie;
    trie.insert("abc");
    trie.insert("abcd");
    trie.insert("abce");
    trie.insert("ab");
    cout << "Count of 'abc': " << trie.countWordsEqualTo("abc") << endl;
    cout << "Count of 'ab': " << trie.countWordsStartingWith("ab") << endl;
    trie.erase("abcd");
    cout << "Count of 'ab' after earse: " << trie.countWordsStartingWith("ab") << endl;

//    Trie1 trie;
//    trie.insert("hello");
//    trie.insert("world");
//    cout << "Count of 'hello': " << trie.countWordsEqualTo("hello") << endl;
//    cout << "Count of 'wor': " << trie.countWordsStartingWith("wor") << endl;
//    trie.erase("hello");
//    cout << "Count of 'hello' after erase: " << trie.countWordsEqualTo("hello") << endl;
    return 0;
}
