#include <string>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct TSTNode{
    bool isEndOfWord;
    TSTNode *left, *middle, *right;
    char value;

    int numNodes;
    TSTNode(){
        isEndOfWord = false;
        left = nullptr;
        right = nullptr;
        middle = nullptr;
        numNodes = 0;
    }

    TSTNode *insert(TSTNode *root, string key, int idx){
    
        TSTNode *cur = root;

        if(idx==key.length()){
            if(cur == nullptr){
                cur = new TSTNode();
                //numNodes++;
            }
            cur->isEndOfWord = true;
            return cur;
        }
        if(cur==nullptr){
            cur = new TSTNode();
            numNodes++;
            cur->value = key[idx];
        }

        if(key[idx] == cur->value)
            cur->middle = insert(cur->middle, key, idx+1);
        else if(key[idx] > cur->value)
            cur->right = insert(cur->right, key, idx);
        else 
            cur->left = insert(cur->left, key, idx);
        
        return cur;
    }

};

bool TST_Search(TSTNode *root, string key){
  TSTNode *cur = root;
  
  int i = 0;
  while(i < key.length()){
      if(cur == nullptr)
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

vector<string> bfs(TSTNode *root, string str){
    vector<string> res;
    queue<pair<TSTNode*, pair<string, int> > > q;

    TSTNode *cur = root;
    q.push({cur, {str, 1}});

    while(!q.empty()){
        TSTNode *cur = q.front().first;
        string str = q.front().second.first;
        bool add = q.front().second.second;
        q.pop();

        if(cur->isEndOfWord == true && add==true){
            res.push_back(str);
        }
        if(cur->left!=nullptr)
            q.push({cur->left, {str, 0}});
        if(cur->middle!=nullptr)
            q.push({cur->middle, {str + cur->value, 1}});
        if(cur->right!=nullptr)
            q.push({cur->right, {str, 0}});
    }
    return res;
}
vector<string> AutoComplete(TSTNode *root, string str){
    vector<string>res;
    TSTNode *cur = root;

    int i = 0;
    while(i < str.length()){
        if(cur == nullptr)
            return res;
        if(cur->value == str[i]){
            cur = cur->middle;
            i++;
            continue;
        }
        if(cur->value < str[i])
            cur = cur->right;
        else cur = cur->left;
    }
    return bfs(cur, str);
}