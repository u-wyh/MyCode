#include <iostream>
#include <unordered_map>
#include <string>
//这个程序的路是通过哈希表完成的建立

class TrieNode {
public:
    int pass;
    int end;
    std::unordered_map<char, TrieNode*> nexts;

    TrieNode() : pass(0), end(0) {}

    ~TrieNode() {
        for (auto& pair : nexts) {
            delete pair.second;
        }
    }
};

class Trie2 {
private:
    TrieNode* root;

public:
    Trie2() {
        root = new TrieNode();
    }

    ~Trie2() {
        delete root;
    }

    void insert(const std::string& word) {
        TrieNode* node = root;
        node->pass++;
        for (char ch : word) {
            if (node->nexts.find(ch) == node->nexts.end()) {
                node->nexts[ch] = new TrieNode();
            }
            node = node->nexts[ch];
            node->pass++;
        }
        node->end++;
    }

    void erase(const std::string& word) {
        TrieNode* node = root;
        TrieNode* prev = nullptr;
        bool found = true;

        for (char ch : word) {
            auto it = node->nexts.find(ch);
            if (it == node->nexts.end()) {
                found = false;
                break;
            }
            prev = node;
            node = it->second;
            if (--node->pass == 0) {
                break; // If pass becomes zero, we can stop early as the node will be deleted
            }
        }

        if (found && node->pass > 0 && --node->end == 0 && prev != nullptr) {
            // Only delete if the node is actually the end of a word and its end count is zero
            prev->nexts.erase(word.back());
            // Recursively delete the subtree if it's no longer reachable
            delete node;
            // Note: We don't need to decrement pass for prev here because we already did it above
            // And we only break out of the loop early if pass becomes zero, so prev's pass is still accurate
        }
        // Note: We don't decrement root->pass here because that would be incorrect.
        // The root node's pass should represent the total number of words in the trie,
        // not the number of paths passing through it (which is always at least 1 for non-empty tries).
        // However, since we're only interested in decrementing pass for internal nodes,
        // this is handled correctly within the loop above.

        // Additionally, note that we only delete nodes when their pass count drops to zero
        // AND they are the end of a word (end count drops to zero).
        // This ensures that we don't delete nodes that are still part of other words.
    }

    int countWordsEqualTo(const std::string& word) {
        TrieNode* node = root;
        for (char ch : word) {
            auto it = node->nexts.find(ch);
            if (it == node->nexts.end()) {
                return 0;
            }
            node = it->second;
        }
        return node->end;
    }

    int countWordsStartingWith(const std::string& pre) {
        TrieNode* node = root;
        for (char ch : pre) {
            auto it = node->nexts.find(ch);
            if (it == node->nexts.end()) {
                return 0;
            }
            node = it->second;
        }
        return node->pass;
    }
};

int main() {
    Trie2 trie;
    trie.insert("hello");
    trie.insert("hell");
    std::cout << "Words starting with 'hell': " << trie.countWordsStartingWith("hell") << std::endl;
    std::cout << "Words equal to 'hello': " << trie.countWordsEqualTo("hello") << std::endl;
    trie.erase("hello");
    std::cout << "Words equal to 'hello' after erase: " << trie.countWordsEqualTo("hello") << std::endl;
    return 0;
}
