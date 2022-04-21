#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void readWords(ifstream fileName){
    
}

int main(){

    ifstream inputFile;
    inputFile.open("test.txt");

    string word;
    vector<string> words;

   if(inputFile.is_open()){
        while(inputFile){
            getline(inputFile, word);
            int lastCharacter = word.size()-1;
            if(!isalpha(word.at(lastCharacter))){
                word.pop_back();
            }
            words.push_back(word);
            if(inputFile.eof()) break;
        }
   }else{ cout << "Unable to open file." << endl;}
    
    for(auto ele: words){
        cout << ele << endl;
    }

    return 0;
}