#include <iostream>
#include <vector>

class TrieNode {
public:
    TrieNode() : links(26, nullptr) {
        isEnd = false;
    }
    bool contains(char ch) {
        // ch - 'a' gives an integer value location in ASCII, wrt to 'a'
        return links[ch - 'a'] != nullptr;
    }
    // retrieve node based on char and it's index
    TrieNode* get(char ch) {
        return links[ch - 'a'];
    }
    // create a link to node of next symbol
    void put(char ch, TrieNode* node) {
        links[ch - 'a'] = node;
    }
    void setEnd() {
        isEnd = true;
    }
    bool isEndOfWord() {
        return isEnd;
    }
private:
    std::vector<TrieNode*> links;
    bool isEnd;
};

class Trie {
public:
    Trie() {
        root = new TrieNode();
    }
    ~Trie() {
        delete root;
    }

    void insert(const std::string& word) {
        TrieNode* node = root;
        // iterate over all characters
        for(char ch : word) {
            // if char is in word
            if(!node->contains(ch)) {
                node->put(ch, new TrieNode());
            }
            // iterate to the next node, so we could add next element
            node = node->get(ch);
        }
        // set end boolean
        node->setEnd();
    }
    
    bool search(const std::string& word) {
        TrieNode* node = root;
        for(char ch : word) {
            // if char is in word
            if(!node->contains(ch)) {
                return false;
            }
            // iterate to the next node, so we could add next element
            node = node->get(ch);
        }
        return node->isEndOfWord();
    }
    
    bool startsWith(const std::string prefix) {
        TrieNode* node = root;
        for(char ch : prefix) {
            // if char is in word
            if(!node->contains(ch)) {
                return false;
            }
            // iterate to the next node, so we could add next element
            node = node->get(ch);
        }
        return node != nullptr;
    }

private:
    TrieNode* root {nullptr};
};


int main() {
    Trie* obj = new Trie();
    obj->insert("Apple");
    bool param_2 = obj->search("Apple");
    bool param_3 = obj->startsWith("App");
    
}
