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
string search(TrieNode* root, const string &key) {
    TrieNode* curr = root;

    for (char c : key) {
        int index = c - 'a';
        if (!curr->children[index])
            return "not found";
        curr = curr->children[index];
    }

    return curr->isEndOfWord ? "found" : "not found";
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
    vector<string> generateEditDistance1(const string& word) {
    vector<string> results;
    int n = word.size();

    // Deletions
    for (int i = 0; i < n; i++) {
        results.push_back(word.substr(0, i) + word.substr(i+1));
    }

    // Insertions
    for (int i = 0; i <= n; i++) {
        for (char c = 'a'; c <= 'z'; c++) {
            results.push_back(word.substr(0, i) + c + word.substr(i));
        }
    }

    // Replacements
    for (int i = 0; i < n; i++) {
        for (char c = 'a'; c <= 'z'; c++) {
            if (c != word[i])
                results.push_back(word.substr(0, i) + c + word.substr(i+1));
        }
    }

    // Transpositions
    for (int i = 0; i < n - 1; i++) {
        string transposed = word;
        swap(transposed[i], transposed[i + 1]);
        results.push_back(transposed);
    }

    return results;
}
// Distance Checking

 // spell checker
int main() {
    TrieNode* root = new TrieNode();

    insert(root, "hello");
    insert(root, "help");
    insert(root, "heap");

    cout << search(root, "help") << endl;   // 1
    cout << search(root, "hel") << endl;    // 0

    root = deleteKey(root, "help");

    cout << search(root, "help") << endl;   // 0
    cout << search(root, "hello") << endl;  // 1

    return 0;
}
