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
            return "not found" ;
        curr = curr->children[index];
    }

    return curr->isEndOfWord ? "found" : "not found";
}