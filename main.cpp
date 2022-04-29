#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "trienode.cpp"
#include "bstTrie.cpp"

using namespace std;

vector<string> readWords(string fileName);

int main(){
    string fileName;

    cout << "Enter name of the file: ";
    cin >> fileName;

    vector<string> words = readWords(fileName);
    // for(auto ele: words){
    //     cout << ele << endl;
    // }

    struct TrieNode *root = getNode();
    struct TSTNode *TSTRoot = new TSTNode;

    for(int i = 0; i < words.size(); i++)
        insert(root, words[i]);

    for(int i = 0; i < words.size(); i++)
         TSTRoot->insert(TSTRoot, words[i], 0);

    string inputPrefix;

    cout << "\nTime taken to build the standard Trie is ******* and space occupied by it is *******" << endl;
    cout << "Time taken to build the BST based Trie is ******* and space occupied by it is *******" << endl;

    cout << "\nEnter search string: ";
    cin >> inputPrefix;

    vector<string> standardTrieResult = AutoComplete(root, inputPrefix);
    vector<string> TSTResult = AutoComplete(TSTRoot, inputPrefix);

    cout << "Time taken to search in the standard Trie is *******" << endl;
    cout << "Auto-complete results using standard Trie are: ";
    if(standardTrieResult.empty()){
        cout << "No suggestions found." << endl;
    }
    else{
        for(auto ele: standardTrieResult){
            cout << ele << ", ";
        }
        cout << endl;
    }
    cout << "Time taken to find auto-complete results in the standard Trie is *******" << endl;

    cout << "\nTime taken to search in the BST based Trie is *******" << endl;
    cout << "Auto-complete results using BST based Trie are: ";
    if(standardTrieResult.empty()){
        cout << "No suggestions found." << endl;
    }
    else{
        for(auto ele: TSTResult){
            cout << ele << ", ";
        }
        cout << endl;
    }
    cout << "Time taken to find auto-complete results in the BST based Trie is *******" << endl;
    // cout << "Stantard Trie:" << endl;
    // search(root, "fun")? cout << "Yes\n" : cout << "No\n"; 
    // search(root, "this")? cout << "Yes\n" : cout << "No\n"; 

    // cout << "\nTST Trie:" << endl;
    // search(TSTRoot, "hello")? cout << "Yes\n" : cout << "No\n"; 
    // search(TSTRoot, "help")? cout << "Yes\n" : cout << "No\n"; 
    
    
   // cout << "\nPrefix search:" << endl;

    // vector<string> queryResult = AutoComplete(TSTRoot, inputPrefix);    
    // if(queryResult.empty()){
    //     cout << "No suggestions found." << endl;
    // }
    // else{
    //     for(auto ele: queryResult){
    //         cout << ele << endl;
    //     }
    // }
    
    return 0;
    
}

vector<string> readWords(string fileName){
    ifstream inputFile;
    inputFile.open(fileName);
    string word;
    vector<string> words;

   if(inputFile.is_open()){
        while(inputFile >> word){
            int lastCharacter = word.size()-1;
            if(!isalpha(word.at(lastCharacter))){
                word.pop_back();
            }
            words.push_back(word);
        }
   }else{ cout << "Unable to open file." << endl;}

   return words;
    
}