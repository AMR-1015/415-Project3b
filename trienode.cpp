#include <string>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;
// #ifdef TRIENODE_H
// #define TRIENODE_H

const int children_size = 26; 

struct TrieNode
{
    struct TrieNode *children[children_size];
    bool isEndOfWord;
    int numNodes;
};

struct TrieNode *getNode(){
    struct TrieNode *root = new TrieNode;

    root->isEndOfWord = false;
    root->numNodes=0;
    
    for(int i = 0; i < children_size; i++){
        root->children[i] = nullptr;
    }

    return root;
}

void insert(struct TrieNode *root, string key){
    struct TrieNode *current = root;

    for(int i = 0; i < key.length(); i++){
        int index = key[i] - 'a';

        if(!current->children[index]){
            current->children[index] = getNode();
            root->numNodes++;
        }

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

vector<string> bfs(TrieNode *root, string str){
  vector<string> res;
  queue<pair<TrieNode*, string>> q;

  TrieNode *cur = root;
  q.push({cur, str}); 

  while(!q.empty()){
      TrieNode *cur = q.front().first;
      string str = q.front().second;
      q.pop();
      if(cur->isEndOfWord == true){
          res.push_back(str);
      }
      for(int i=0; i < children_size; i++){
          if(cur->children[i] != nullptr){
              q.push({cur->children[i], str + char(i + 'a')});
          }
      }
  }
  return res;
}

vector<string> AutoComplete(TrieNode *root, string str){
  TrieNode *cur = root;
  vector<string> res;

  int prefixSize = str.length();

  for(int i=0; i < prefixSize; i++){
      int newIndex = str[i]-'a';
      if(cur->children[newIndex] == nullptr)
        return res;
      cur = cur->children[newIndex];
  }
  return bfs(cur,str);
}


// #endif