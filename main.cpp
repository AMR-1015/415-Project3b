#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <algorithm>
#include <ctime>
#include <vector>
#include "trienode.cpp"
#include "bstTrie.cpp"

using namespace std;

vector<string> readWords(string fileName);
vector<string> readFile(string fileName);
vector<string> wordHelper(vector<string> words);

void caseTwo(TrieNode *, TSTNode *, vector<string>, auto t1, auto t2, int s1, int s2);


int main(){
    string fileName;

    cout << "Enter name of the file: ";
    cin >> fileName;

    // if(argc != 2){
    //     std::cout << "Usage" << argv[0] << " nameOfAnInputFile " << std:: endl;
    // }
    
    vector<string> words = readFile(fileName);
   
    // cout << "Words in file:" << endl;
    // for(auto ele: words){
    //     cout << ele << endl;
    // }
    // cout << endl;

    struct TrieNode *root = getNode();
    struct TSTNode *TSTRoot = new TSTNode;

    std::clock_t startTrie; //timerStart
    startTrie = std::clock();

    for(int i = 0; i < words.size(); i++){
        insert(root, words[i]);
    }
    std::clock_t endTrie; //timerEnd
    endTrie = std::clock();

    auto standardTrieTime = (endTrie - startTrie)/(double)(CLOCKS_PER_SEC/10);
    int standardTrieSpace = (root->numNodes + 1) * 26;

    std::clock_t startTST; //timerStart
    startTST = std::clock();
    for(int i = 0; i < words.size(); i++){
         TSTRoot->insert(TSTRoot, words[i], 0);
    }
    std::clock_t endTST; //timerEnd
    endTST = std::clock();

    auto TST_Total_Time = (endTST - startTST)/(double)(CLOCKS_PER_SEC/10);
    int TST_Size = (TSTRoot->numNodes * 3) + 1;


    string inputPrefix;

    cout << "\nTime taken to build the standard Trie is " << standardTrieTime << " nanoseconds and space occupied by it is " << standardTrieSpace << " nodes" << endl;
    cout << "Time taken to build the BST based Trie is " << TST_Total_Time << " nanoseconds and space occupied by it is " << TST_Size << " nodes" << endl;
    
    int i = 0;
    while(i < 3){
        cout << "\nEnter search string: ";
        cin >> inputPrefix;

        std::clock_t startTrieAuto;
        startTrieAuto = clock();

        vector<string> standardTrieResult = AutoComplete(root, inputPrefix);

        std::clock_t endTrieAuto;
        endTrieAuto = clock();

        std::clock_t startTSTAuto;
        startTSTAuto = clock();

        vector<string> TSTResult = AutoComplete(TSTRoot, inputPrefix);

        std::clock_t endTSTAuto;
        endTSTAuto = clock();

        std::clock_t startTrieSearch1;
        startTrieSearch1 = clock();

        search(root, inputPrefix );

        std::clock_t endTrieSearch1;
        endTrieSearch1 = clock();

        std::clock_t startTSTSearch1;
        startTSTSearch1 = clock();

        TST_Search(TSTRoot, inputPrefix);

        std::clock_t endTSTSearch1;
        endTSTSearch1 = clock();

        cout << "Time taken to search in the standard Trie is "<< (endTrieSearch1 - startTrieSearch1)/(double)(CLOCKS_PER_SEC/10) << " milliseconds."  << endl;
        cout << "Auto-complete results using standard Trie are: " ;
        if(standardTrieResult.empty()){
            cout << "No suggestions found." << endl;
        }
        else{
            for(auto ele: standardTrieResult){
                cout << ele << ", ";
            }
            cout << endl;
        }
        cout << "Time taken to find auto-complete results in the standard Trie is " << (endTrieAuto - startTrieAuto)/(double)(CLOCKS_PER_SEC/10) << " milliseconds."  << endl;

        cout << "\nTime taken to search in the BST based Trie is "<< (endTSTSearch1 - startTSTSearch1)/(double)(CLOCKS_PER_SEC/10) << " milliseconds."  << endl;
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
        cout << "Time taken to find auto-complete results in the BST based Trie is " << (endTSTAuto - startTSTAuto)/(double)(CLOCKS_PER_SEC/10) << " milliseconds."  << endl;

        i++;

    }
    

    cout << endl;
    caseTwo(root, TSTRoot, words, standardTrieTime, TST_Total_Time, standardTrieSpace, TST_Size);
   
    return 0;
    
}

vector<string> readFile(string fileName)
{
    ifstream inputFile;
    inputFile.open(fileName);
    string word;
    //string word2;
    char c;
    vector<string> words;

    if(inputFile.is_open()){
        while(inputFile.get(c)){
           if(isalpha(c)){
               word += c;
           }
           else{
                if(word == "s") word.clear();
                if(word.empty()) continue;
                if(isupper(word[0])) word[0] = tolower(word[0]);  
                words.push_back(word);
                word.clear();
           }
           
        }
       
   }else{ cout << "Unable to open file." << endl;}

   return words;

}


void caseTwo(TrieNode *root, TSTNode *TSTRoot, vector<string> words, auto t1, auto t2, int s1, int s2){
    cout << "Case Two:" << endl;
    std::clock_t searchTST; //timerStart
    searchTST = std::clock();
    for(int i = 0; i < words.size(); i++)
         TST_Search(TSTRoot, words[i]); 

    std::clock_t endTST_Search; //timerEnd
    endTST_Search = std::clock();

    std::clock_t searchTrie; //timerStart
    searchTrie = std::clock();
    for(int i = 0; i < words.size(); i++)
         search(root, words[i]); 

    std::clock_t endTrieSearch; //timerEnd
    endTrieSearch = std::clock();


    cout << "\nTime taken to build the standard Trie is " << t1 << " millisconds and space occupied by it is " << s1 << " nodes." << endl;
    cout << "Time taken to build the BST based Trie is " << t2 << " milliseconds and space occupied by it is " << s2 << " nodes." << endl;

    cout << "\nTime taken to search all the strings in the standard Trie is " << (endTrieSearch - searchTrie)/(double)(CLOCKS_PER_SEC/10) << " milliseconds." << endl;
    cout << "Time taken to search all the strings in the BST based Trie is "<< (endTST_Search - searchTST)/(double)(CLOCKS_PER_SEC/10) << " milliseconds." << endl;
}