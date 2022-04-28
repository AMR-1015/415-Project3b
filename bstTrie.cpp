#include <string>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct TSTNode{
    bool isEndOfWord;
    TSTNode *left, *middle, *right;
    char value;

    TSTNode(){
        isEndOfWord = false;
        left = nullptr;
        right = nullptr;
        middle = nullptr;
    }
};

TSTNode *insert(TSTNode *root, string key, int idx){
  if(idx==key.length()){
      if(root == nullptr)
        root = new TSTNode();
      root->isEndOfWord = true;
      return root;
  }
  if(root==NULL){
      root = new TSTNode();
      root->value = key[idx];
  }

  if(key[idx] == root->value)
    root->middle = insert(root->middle, key, idx+1);
  else if(key[idx] > root->value)
    root->right = insert(root->right, key, idx);
  else 
    root->left = insert(root->left, key, idx);
  return root;
}

bool search(TSTNode *root, string key){
  TSTNode *cur = root;
  
  int i = 0;
  while(i < key.length()){
      if(root == nullptr)
        return false;
      if(cur->value == key[i]){
          cur = cur->middle;
          i++;
          continue;
      }
      if(cur->value < key[i])
        cur = cur->right;
      else cur = cur->left;
  }
  return cur->isEndOfWord;
}