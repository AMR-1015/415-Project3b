#include <string>
#include <iostream>
#include <vector>

using namespace std;
// #ifdef TRIENODE_H
// #define TRIENODE_H

const int size = 26; 
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

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

bool isLastNode(struct TrieNode* root)
{
    for (int i = 0; i < size; i++)
        if (root->children[i])
            return false;
    return true;
}

void suggestionsRec(struct TrieNode* root,
                    string currPrefix)
{
    // found a string in Trie with the given prefix
    if (root->isEndOfWord)
        cout << currPrefix << endl;
 
    for (int i = 0; i < size; i++)
        if (root->children[i]) {
            // child node character value
            char child = 'a' + i;
            suggestionsRec(root->children[i],
                           currPrefix + child);
        }
}

// print suggestions for given query prefix.
int printAutoSuggestions(TrieNode* root, const string query)
{
    struct TrieNode* current = root;
    for (char c : query) {
        int ind = CHAR_TO_INDEX(c);
 
        // no string in the Trie has this prefix
        if (!current->children[ind])
            return false;
 
        current = current->children[ind];
    }
    // If prefix is present as a word, but
    // there is no subtree below the last
    // matching node.
    if (isLastNode(current)) {
        cout << query << endl;
        return -1;
    }
    suggestionsRec(current, query);
    return 1;
}

// #endif