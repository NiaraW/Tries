#include <iostream>
using namespace std;

const int ALPHABET_SIZE = 26;

// Trie node
struct TrieNode {
    TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord;

    TrieNode() {
        isEndOfWord = false;
        for (int i = 0; i < ALPHABET_SIZE; i++)
            children[i] = nullptr;
    }
};
void insert(TrieNode* root, const string &key) {
    TrieNode* curr = root;

    for (char c : key) {
        int index = c - 'a';
        if (curr->children[index] == nullptr)
            curr->children[index] = new TrieNode();
        curr = curr->children[index];
    }

    curr->isEndOfWord = true;
}
bool search(TrieNode* root, const string &key) {
    TrieNode* curr = root;

    for (char c : key) {
        int index = c - 'a';
        if (!curr->children[index])
            return false;
        curr = curr->children[index];
    }

    return curr->isEndOfWord;
}
bool isEmpty(TrieNode* node) {
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (node->children[i] != nullptr)
            return false;
    return true;
}

TrieNode* deleteKey(TrieNode* root, const string &key, int depth = 0) {
    if (!root)
        return nullptr;

    // If we've reached the end of the word
    if (depth == key.size()) {
        if (root->isEndOfWord)
            root->isEndOfWord = false;

        // If no children → delete node
        if (isEmpty(root)) {
            delete root;
            return nullptr;
        }

        return root;
    }

    int index = key[depth] - 'a';
    root->children[index] = deleteKey(root->children[index], key, depth + 1);

    // If current node is useless
    if (isEmpty(root) && !root->isEndOfWord) {
        delete root;
        return nullptr;
    }

    return root;
}