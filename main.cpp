#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "trienode.cpp"

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

    for(int i = 0; i < words.size(); i++)
        insert(root, words[i]);
    
    search(root, "fun")? cout << "Yes\n" : cout << "No\n"; 
    search(root, "this")? cout << "Yes\n" : cout << "No\n"; 
    search(root, "birthday")? cout << "Yes\n" : cout << "No\n"; 
    search(root, "happy")? cout << "Yes\n" : cout << "No\n"; 

    cout << "Prefix search:" << endl;

    vector<string> queryResult = AutoComplete(root, "aw");    
    if(queryResult.empty()){
        cout << "No suggestions found." << endl;
    }
    else{
        for(auto ele: queryResult){
            cout << ele << endl;
    }
    }
    
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