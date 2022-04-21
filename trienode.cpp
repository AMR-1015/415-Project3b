#include <string>

using namespace std;
// #ifdef TRIENODE_H
// #define TRIENODE_H

const int size = 26; 

struct TrieNode
{
    struct TrieNode *children[size];
    bool isEndOfWord;
};

struct TrieNode *getNode(){
    struct TrieNode *root = new TrieNode;

    root->isEndOfWord = false;
    
    for(int i = 0; i < size; i++){
        root->children[i] = nullptr;
    }

    return root;
}

void insert(struct TrieNode *root, string key){
    struct TrieNode *current = root;

    for(int i = 0; i < key.length(); i++){
        int index = key[i] - 'a';

        if(!current->children[index])
            current->children[index] = getNode();

        current = current->children[index];
    }
    current->isEndOfWord = true;
}

bool search(struct TrieNode *root, string key){
    struct TrieNode *current = root;

    for(int i = 0; i < key.length(); i++){
        int index = key[i] - 'a';

        if(!current->children[index])
            return false;
        
        current = current->children[index];
    }
    return (current->isEndOfWord);
}

// #endif