#include <iostream>
using namespace std;

struct TrieNode {
    TrieNode* children[26];
    bool isEndOfWord;

    TrieNode() {
        isEndOfWord = false;
        for(int i = 0; i < 26; i++)
            children[i] = nullptr;
    }
};

class Trie {
private:
    TrieNode* root;

public:
    Trie() {
        root = new TrieNode();
    }

    // Inserts a word into the trie.
    void insert(const string& word) {
        TrieNode* node = root;
        for(char ch : word) {
            int idx = ch - 'a';
            if(!node->children[idx])
                node->children[idx] = new TrieNode();
            node = node->children[idx];
        }
        node->isEndOfWord = true;
    }

    // Returns true if the word is in the trie.
    bool search(const string& word) {
        TrieNode* node = root;
        for(char ch : word) {
            int idx = ch - 'a';
            if(!node->children[idx])
                return false;
            node = node->children[idx];
        }
        return node->isEndOfWord;
    }

    // Returns true if there is any word in the trie that starts with the given prefix.
    bool startsWith(const string& prefix) {
        TrieNode* node = root;
        for(char ch : prefix) {
            int idx = ch - 'a';
            if(!node->children[idx])
                return false;
            node = node->children[idx];
        }
        return true;
    }

    ~Trie() {
        clear(root);
    }

private:
    void clear(TrieNode* node) {
        if(!node) return;
        for(int i = 0; i < 26; ++i)
            clear(node->children[i]);
        delete node;
    }
};
